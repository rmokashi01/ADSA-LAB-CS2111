#include "prims.h"

// ========== FORWARD DECLARATIONS OF STATIC HELPER FUNCTIONS ==========
static char* formatConnection(CityGraph* graph, int src, int dest);
static double calculateTotalFiberLength(MSTResult* result);
static double findLongestConnection(MSTResult* result);
static double findShortestConnection(MSTResult* result);

// ===================== GRAPH OPERATIONS =====================

CityGraph* createCityGraph(const char* city_name, int max_vertices) {
    CityGraph* graph = (CityGraph*)malloc(sizeof(CityGraph));
    if (!graph) {
        fprintf(stderr, "Memory allocation failed for graph\n");
        return NULL;
    }
    
    // Initialize basic info
    strncpy(graph->city_name, city_name, MAX_NAME_LEN - 1);
    graph->city_name[MAX_NAME_LEN - 1] = '\0';
    graph->vertex_count = 0;
    graph->edge_count = 0;
    graph->start_vertex = -1;
    
    // Allocate memory for buildings array
    graph->buildings = (Building*)malloc(max_vertices * sizeof(Building));
    if (!graph->buildings) {
        fprintf(stderr, "Memory allocation failed for buildings\n");
        free(graph);
        return NULL;
    }
    
    // Allocate memory for adjacency matrix (costs)
    graph->adj_matrix = (double**)malloc(max_vertices * sizeof(double*));
    graph->dist_matrix = (double**)malloc(max_vertices * sizeof(double*));
    graph->terrain_matrix = (int**)malloc(max_vertices * sizeof(int*));
    
    if (!graph->adj_matrix || !graph->dist_matrix || !graph->terrain_matrix) {
        fprintf(stderr, "Memory allocation failed for matrices\n");
        free(graph->buildings);
        free(graph);
        return NULL;
    }
    
    for (int i = 0; i < max_vertices; i++) {
        graph->adj_matrix[i] = (double*)malloc(max_vertices * sizeof(double));
        graph->dist_matrix[i] = (double*)malloc(max_vertices * sizeof(double));
        graph->terrain_matrix[i] = (int*)malloc(max_vertices * sizeof(int));
        
        if (!graph->adj_matrix[i] || !graph->dist_matrix[i] || !graph->terrain_matrix[i]) {
            fprintf(stderr, "Memory allocation failed for matrix row %d\n", i);
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(graph->adj_matrix[j]);
                free(graph->dist_matrix[j]);
                free(graph->terrain_matrix[j]);
            }
            free(graph->adj_matrix);
            free(graph->dist_matrix);
            free(graph->terrain_matrix);
            free(graph->buildings);
            free(graph);
            return NULL;
        }
        
        // Initialize matrices
        for (int j = 0; j < max_vertices; j++) {
            graph->adj_matrix[i][j] = INF;
            graph->dist_matrix[i][j] = 0.0;
            graph->terrain_matrix[i][j] = PLAIN;
        }
        graph->adj_matrix[i][i] = 0.0; // Diagonal to 0
    }
    
    printf("[INFO] Created city graph '%s' with capacity for %d buildings\n", 
           city_name, max_vertices);
    return graph;
}

void destroyCityGraph(CityGraph* graph) {
    if (!graph) return;
    
    // Free building array
    free(graph->buildings);
    
    // Free matrices
    if (graph->adj_matrix) {
        for (int i = 0; i < MAX_BUILDINGS; i++) {
            free(graph->adj_matrix[i]);
        }
        free(graph->adj_matrix);
    }
    
    if (graph->dist_matrix) {
        for (int i = 0; i < MAX_BUILDINGS; i++) {
            free(graph->dist_matrix[i]);
        }
        free(graph->dist_matrix);
    }
    
    if (graph->terrain_matrix) {
        for (int i = 0; i < MAX_BUILDINGS; i++) {
            free(graph->terrain_matrix[i]);
        }
        free(graph->terrain_matrix);
    }
    
    free(graph);
    printf("[INFO] City graph destroyed\n");
}

void addBuilding(CityGraph* graph, int id, const char* name, double lat, double lon, 
                 BuildingType type, int population) {
    if (!graph || id < 0 || id >= MAX_BUILDINGS) {
        fprintf(stderr, "Invalid building ID or graph\n");
        return;
    }
    
    if (graph->vertex_count >= MAX_BUILDINGS) {
        fprintf(stderr, "Maximum building capacity reached\n");
        return;
    }
    
    Building* b = &graph->buildings[id];
    b->id = id;
    strncpy(b->name, name, MAX_NAME_LEN - 1);
    b->name[MAX_NAME_LEN - 1] = '\0';
    b->latitude = lat;
    b->longitude = lon;
    b->type = type;
    b->population = population;
    
    // Update vertex count if this is a new building
    if (id >= graph->vertex_count) {
        graph->vertex_count = id + 1;
    }
    
    // Mark as start vertex if it's the first data center
    if (type == DATA_CENTER && graph->start_vertex == -1) {
        graph->start_vertex = id;
    }
    
    printf("[INFO] Added building: %s (ID: %d, Type: %s, Pop: %d)\n",
           name, id, getBuildingTypeName(type), population);
}

void addConnection(CityGraph* graph, int src, int dest, TerrainType terrain, bool feasible) {
    if (!graph || src < 0 || src >= graph->vertex_count || 
        dest < 0 || dest >= graph->vertex_count || src == dest) {
        fprintf(stderr, "Invalid building indices for connection\n");
        return;
    }
    
    // Calculate distance between buildings
    double dist = calculateDistance(graph->buildings[src].latitude,
                                   graph->buildings[src].longitude,
                                   graph->buildings[dest].latitude,
                                   graph->buildings[dest].longitude);
    
    // Calculate adjusted cost
    double cost = calculateAdjustedCost(dist, terrain,
                                       graph->buildings[src].type,
                                       graph->buildings[dest].type,
                                       graph->buildings[src].population,
                                       graph->buildings[dest].population);
    
    // If not feasible, set cost to INF
    if (!feasible) {
        cost = INF;
    }
    
    // Update matrices (undirected graph)
    graph->adj_matrix[src][dest] = cost;
    graph->adj_matrix[dest][src] = cost;
    graph->dist_matrix[src][dest] = dist;
    graph->dist_matrix[dest][src] = dist;
    graph->terrain_matrix[src][dest] = terrain;
    graph->terrain_matrix[dest][src] = terrain;
    
    graph->edge_count++;
    
    printf("[INFO] Added connection: %s ↔ %s (%.2f km, %s, Cost: ₹%.2fM)\n",
           graph->buildings[src].name, graph->buildings[dest].name,
           dist, getTerrainTypeName(terrain), cost);
}

void calculateAllDistances(CityGraph* graph) {
    if (!graph) return;
    
    printf("[INFO] Calculating distances between all buildings...\n");
    for (int i = 0; i < graph->vertex_count; i++) {
        for (int j = i + 1; j < graph->vertex_count; j++) {
            double dist = calculateDistance(graph->buildings[i].latitude,
                                           graph->buildings[i].longitude,
                                           graph->buildings[j].latitude,
                                           graph->buildings[j].longitude);
            graph->dist_matrix[i][j] = dist;
            graph->dist_matrix[j][i] = dist;
        }
    }
    printf("[INFO] Distance calculation complete\n");
}

void calculateAllCosts(CityGraph* graph) {
    if (!graph) return;
    
    printf("[INFO] Calculating costs for all possible connections...\n");
    for (int i = 0; i < graph->vertex_count; i++) {
        for (int j = i + 1; j < graph->vertex_count; j++) {
            if (graph->adj_matrix[i][j] == INF) {
                // Calculate cost for non-explicit connections
                double cost = calculateAdjustedCost(graph->dist_matrix[i][j],
                                                   graph->terrain_matrix[i][j],
                                                   graph->buildings[i].type,
                                                   graph->buildings[j].type,
                                                   graph->buildings[i].population,
                                                   graph->buildings[j].population);
                graph->adj_matrix[i][j] = cost;
                graph->adj_matrix[j][i] = cost;
            }
        }
    }
    printf("[INFO] Cost calculation complete\n");
}

// ===================== PRIM'S ALGORITHM CORE =====================

int findMinKeyVertex(double key[], bool in_mst[], int n) {
    double min = INF;
    int min_index = -1;
    
    for (int v = 0; v < n; v++) {
        if (!in_mst[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    
    return min_index;
}

MSTResult* primMST(CityGraph* graph, int start_vertex) {
    if (!graph || start_vertex < 0 || start_vertex >= graph->vertex_count) {
        fprintf(stderr, "Invalid graph or start vertex\n");
        return NULL;
    }
    
    MSTResult* result = (MSTResult*)malloc(sizeof(MSTResult));
    if (!result) {
        fprintf(stderr, "Memory allocation failed for MST result\n");
        return NULL;
    }
    
    // Initialize
    for (int i = 0; i < graph->vertex_count; i++) {
        result->key[i] = INF;
        result->in_mst[i] = false;
        result->parent[i] = -1;
    }
    
    // Start with the given vertex
    result->key[start_vertex] = 0;
    result->parent[start_vertex] = -1; // Root of MST
    
    // Store connections
    result->connections_used = 0;
    result->total_cost = 0.0;
    
    printf("\n╔═══════════════════════════════════════════════╗\n");
    printf("║     PRIM'S ALGORITHM - MST CONSTRUCTION      ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");
    
    // Prim's algorithm
    for (int count = 0; count < graph->vertex_count; count++) {
        // Pick minimum key vertex not yet in MST
        int u = findMinKeyVertex(result->key, result->in_mst, graph->vertex_count);
        if (u == -1) break; // Graph might be disconnected
        
        result->in_mst[u] = true;
        
        // If u is not the start vertex, add edge to MST
        if (result->parent[u] != -1) {
            int v = result->parent[u];
            double cost = graph->adj_matrix[u][v];
            
            // Store this edge in result
            Connection edge;
            edge.src_id = v;
            edge.dest_id = u;
            edge.distance_km = graph->dist_matrix[u][v];
            edge.terrain = graph->terrain_matrix[u][v];
            edge.adjusted_cost = cost;
            
            result->mst_edges[result->connections_used] = edge;
            result->connections_used++;
            result->total_cost += cost;
            
            // Print progress
            printf("Step %2d: Connect %-25s → %-25s\n", 
                   count, graph->buildings[v].name, graph->buildings[u].name);
            printf("        Distance: %6.2f km | Terrain: %-10s | Cost: ₹%6.2fM\n",
                   edge.distance_km, getTerrainTypeName(edge.terrain), cost);
            printf("        Total cost so far: ₹%.2fM\n", result->total_cost);
            printf("        ──────────────────────────────────────────────\n");
        }
        
        // Update key values of adjacent vertices
        for (int v = 0; v < graph->vertex_count; v++) {
            if (graph->adj_matrix[u][v] != INF && !result->in_mst[v] && 
                graph->adj_matrix[u][v] < result->key[v]) {
                result->parent[v] = u;
                result->key[v] = graph->adj_matrix[u][v];
            }
        }
        
        // Show progress bar
        int progress = (count + 1) * 100 / graph->vertex_count;
        printProgressBar(count + 1, graph->vertex_count, 40);
    }
    
    printf("\n✅ MST Construction Complete!\n");
    printf("   Total Buildings: %d\n", graph->vertex_count);
    printf("   Total Connections: %d\n", result->connections_used);
    printf("   Total Cost: ₹%.2f Million\n", result->total_cost);
    
    return result;
}

void primMSTStepByStep(CityGraph* graph, int start_vertex) {
    if (!graph) return;
    
    printf("\n🎬 STEP-BY-STEP PRIM'S ALGORITHM DEMO\n");
    printf("=========================================\n");
    
    // Initialize arrays for visualization
    double key[MAX_BUILDINGS];
    int parent[MAX_BUILDINGS];
    bool in_mst[MAX_BUILDINGS];
    
    for (int i = 0; i < graph->vertex_count; i++) {
        key[i] = INF;
        parent[i] = -1;
        in_mst[i] = false;
    }
    
    key[start_vertex] = 0;
    
    printf("\nInitial State:\n");
    printf("Start Building: %s\n", graph->buildings[start_vertex].name);
    printf("Key values: ");
    for (int i = 0; i < graph->vertex_count; i++) {
        printf("%.1f ", key[i] == INF ? -1.0 : key[i]);
    }
    printf("\n\n");
    
    for (int step = 1; step <= graph->vertex_count; step++) {
        printf("─── Step %d ───\n", step);
        
        // Find minimum key vertex not in MST
        int u = findMinKeyVertex(key, in_mst, graph->vertex_count);
        if (u == -1) break;
        
        printf("Selected vertex: %s (Key: %.2f)\n", 
               graph->buildings[u].name, key[u]);
        
        in_mst[u] = true;
        
        if (parent[u] != -1) {
            printf("  → Added edge: %s ←→ %s (Cost: %.2f)\n",
                   graph->buildings[parent[u]].name,
                   graph->buildings[u].name,
                   graph->adj_matrix[u][parent[u]]);
        }
        
        // Update adjacent vertices
        printf("  Updating neighbors:\n");
        for (int v = 0; v < graph->vertex_count; v++) {
            if (graph->adj_matrix[u][v] != INF && !in_mst[v]) {
                double new_key = graph->adj_matrix[u][v];
                if (new_key < key[v]) {
                    printf("    • %s: Key %.2f → %.2f (Parent: %s)\n",
                           graph->buildings[v].name, key[v], new_key,
                           graph->buildings[u].name);
                    key[v] = new_key;
                    parent[v] = u;
                }
            }
        }
        
        printf("\nCurrent MST Status:\n");
        printf("In MST: ");
        for (int i = 0; i < graph->vertex_count; i++) {
            if (in_mst[i]) printf("%s ", graph->buildings[i].name);
        }
        printf("\n\n");
    }
    
    // Calculate total cost
    double total_cost = 0;
    for (int i = 0; i < graph->vertex_count; i++) {
        if (parent[i] != -1) {
            total_cost += graph->adj_matrix[i][parent[i]];
        }
    }
    
    printf("✨ Final MST:\n");
    printf("Total Cost: ₹%.2f Million\n", total_cost);
    for (int i = 0; i < graph->vertex_count; i++) {
        if (parent[i] != -1) {
            printf("%s — %s (₹%.2fM)\n",
                   graph->buildings[parent[i]].name,
                   graph->buildings[i].name,
                   graph->adj_matrix[i][parent[i]]);
        }
    }
}

// ===================== VISUALIZATION FUNCTIONS =====================

void printBuildingInfo(Building b) {
    const char* type_str = getBuildingTypeName(b.type);
    printf("🏢 Building %d: %s\n", b.id, b.name);
    printf("   Type: %s\n", type_str);
    printf("   Location: (%.6f, %.6f)\n", b.latitude, b.longitude);
    printf("   Population: %d\n", b.population);
}

void printConnectionInfo(CityGraph* graph, int src, int dest) {
    if (!graph || src < 0 || src >= graph->vertex_count || 
        dest < 0 || dest >= graph->vertex_count) {
        return;
    }
    
    printf("🔗 Connection: %s ↔ %s\n", 
           graph->buildings[src].name, graph->buildings[dest].name);
    printf("   Distance: %.2f km\n", graph->dist_matrix[src][dest]);
    printf("   Terrain: %s\n", getTerrainTypeName(graph->terrain_matrix[src][dest]));
    printf("   Cost: ₹%.2f Million\n", graph->adj_matrix[src][dest]);
}

void printCityGraph(CityGraph* graph) {
    if (!graph) {
        printf("Graph is NULL\n");
        return;
    }
    
    printf("\n");
    printf("┌──────────────────────────────────────────────────────────────┐\n");
    printf("│                   CITY GRAPH INFORMATION                     │\n");
    printf("├──────────────────────────────────────────────────────────────┤\n");
    printf("│ City: %-54s │\n", graph->city_name);
    printf("│ Buildings: %-52d │\n", graph->vertex_count);
    printf("│ Start Vertex: %-49d │\n", graph->start_vertex);
    if (graph->start_vertex != -1) {
        printf("│ Start Building: %-48s │\n", graph->buildings[graph->start_vertex].name);
    }
    printf("└──────────────────────────────────────────────────────────────┘\n");
    
    printf("\n🏢 BUILDINGS:\n");
    printf("───┬────────────────────────────────────┬─────────────┬──────────────┬──────────┐\n");
    printf("ID │ Name                               │ Type        │ Location     │ Population │\n");
    printf("───┼────────────────────────────────────┼─────────────┼──────────────┼──────────┤\n");
    
    for (int i = 0; i < graph->vertex_count; i++) {
        printf("%2d │ %-34s │ %-11s │ (%6.2f,%6.2f) │ %8d │\n",
               graph->buildings[i].id,
               graph->buildings[i].name,
               getBuildingTypeName(graph->buildings[i].type),
               graph->buildings[i].latitude,
               graph->buildings[i].longitude,
               graph->buildings[i].population);
    }
    printf("───┴────────────────────────────────────┴─────────────┴──────────────┴──────────┘\n");
    
    // Print adjacency matrix (only non-INF values)
    printf("\n🔗 CONNECTIONS (Cost Matrix):\n");
    int connection_count = 0;
    for (int i = 0; i < graph->vertex_count; i++) {
        for (int j = i + 1; j < graph->vertex_count; j++) {
            if (graph->adj_matrix[i][j] != INF) {
                connection_count++;
                printf("%2d. %s ↔ %s: ₹%6.2fM (%.2f km, %s)\n",
                       connection_count,
                       graph->buildings[i].name,
                       graph->buildings[j].name,
                       graph->adj_matrix[i][j],
                       graph->dist_matrix[i][j],
                       getTerrainTypeName(graph->terrain_matrix[i][j]));
            }
        }
    }
    printf("\nTotal possible connections: %d\n", connection_count);
}

// Static helper function for formatting connection strings
static char* formatConnection(CityGraph* graph, int src, int dest) {
    static char buffer[100];
    snprintf(buffer, sizeof(buffer), "%s → %s",
             graph->buildings[src].name,
             graph->buildings[dest].name);
    return buffer;
}

void printMSTResult(CityGraph* graph, MSTResult* result) {
    if (!graph || !result) return;
    
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                 MINIMUM SPANNING TREE RESULT                ║\n");
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║ City: %-53s ║\n", graph->city_name);
    printf("║ Total Buildings: %-43d ║\n", graph->vertex_count);
    printf("║ Total Cost: ₹%-46.2fM ║\n", result->total_cost);
    printf("╠══════════════════════════════════════════════════════════════╣\n");
    printf("║                      OPTIMAL CONNECTIONS                    ║\n");
    printf("╠─────┬────────────────────────────────────┬───────────────────╣\n");
    printf("║ No. │ Connection                        │ Cost (₹M)         ║\n");
    printf("╟─────┼────────────────────────────────────┼───────────────────╢\n");
    
    double cumulative_cost = 0;
    for (int i = 0; i < result->connections_used; i++) {
        Connection edge = result->mst_edges[i];
        cumulative_cost += edge.adjusted_cost;
        
        printf("║ %3d │ %-34s │ %9.2f (Σ%.2f)  ║\n",
               i + 1,
               edge.src_id < edge.dest_id ? 
               formatConnection(graph, edge.src_id, edge.dest_id) :
               formatConnection(graph, edge.dest_id, edge.src_id),
               edge.adjusted_cost,
               cumulative_cost);
    }
    
    printf("╚═════╧════════════════════════════════════╧═══════════════════╝\n");
    
    // Calculate statistics
    double avg_cost = result->total_cost / result->connections_used;
    double total_distance = 0;
    for (int i = 0; i < result->connections_used; i++) {
        total_distance += result->mst_edges[i].distance_km;
    }
    
    printf("\n📊 STATISTICS:\n");
    printf("   Average connection cost: ₹%.2f Million\n", avg_cost);
    printf("   Total fiber length: %.2f km\n", total_distance);
    printf("   Cost per km: ₹%.2f Million\n", result->total_cost / total_distance);
}

void printProgressBar(int current, int total, int bar_width) {
    float progress = (float)current / total;
    int pos = bar_width * progress;
    
    printf("[");
    for (int i = 0; i < bar_width; i++) {
        if (i < pos) printf("█");
        else if (i == pos) printf("▌");
        else printf(" ");
    }
    printf("] %d/%d (%.1f%%)\r", current, total, progress * 100);
    fflush(stdout);
}

void printCityMapASCII(CityGraph* graph, MSTResult* result) {
    if (!graph) return;
    
    printf("\n");
    printf("     🗺️  CITY MAP (ASCII Visualization)\n");
    printf("     ──────────────────────────────\n");
    
    // Create a simple 2D representation
    int map_size = 20;
    char map[20][20];
    
    // Initialize map with spaces
    for (int i = 0; i < map_size; i++) {
        for (int j = 0; j < map_size; j++) {
            map[i][j] = ' ';
        }
    }
    
    // Scale coordinates to fit in map
    double min_lat = INF, max_lat = -INF;
    double min_lon = INF, max_lon = -INF;
    
    for (int i = 0; i < graph->vertex_count; i++) {
        if (graph->buildings[i].latitude < min_lat) min_lat = graph->buildings[i].latitude;
        if (graph->buildings[i].latitude > max_lat) max_lat = graph->buildings[i].latitude;
        if (graph->buildings[i].longitude < min_lon) min_lon = graph->buildings[i].longitude;
        if (graph->buildings[i].longitude > max_lon) max_lon = graph->buildings[i].longitude;
    }
    
    // Place buildings on map
    for (int i = 0; i < graph->vertex_count; i++) {
        int x = (int)((graph->buildings[i].longitude - min_lon) / 
                     (max_lon - min_lon) * (map_size - 3)) + 1;
        int y = (int)((graph->buildings[i].latitude - min_lat) / 
                     (max_lat - min_lat) * (map_size - 3)) + 1;
        
        if (x >= 0 && x < map_size && y >= 0 && y < map_size) {
            switch(graph->buildings[i].type) {
                case HOSPITAL:    map[y][x] = 'H'; break;
                case SCHOOL:      map[y][x] = 'S'; break;
                case GOVERNMENT:  map[y][x] = 'G'; break;
                case RESIDENTIAL: map[y][x] = 'R'; break;
                case COMMERCIAL:  map[y][x] = 'C'; break;
                case DATA_CENTER: map[y][x] = 'D'; break;
                default:          map[y][x] = 'B'; break;
            }
        }
    }
    
    // Draw MST connections
    if (result) {
        for (int i = 0; i < result->connections_used; i++) {
            Connection edge = result->mst_edges[i];
            Building src = graph->buildings[edge.src_id];
            Building dest = graph->buildings[edge.dest_id];
            
            int x1 = (int)((src.longitude - min_lon) / (max_lon - min_lon) * (map_size - 3)) + 1;
            int y1 = (int)((src.latitude - min_lat) / (max_lat - min_lat) * (map_size - 3)) + 1;
            int x2 = (int)((dest.longitude - min_lon) / (max_lon - min_lon) * (map_size - 3)) + 1;
            int y2 = (int)((dest.latitude - min_lat) / (max_lat - min_lat) * (map_size - 3)) + 1;
            
            // Simple line drawing (Bresenham's would be better)
            int dx = x2 - x1;
            int dy = y2 - y1;
            int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
            
            if (steps > 0) {
                float x_inc = dx / (float)steps;
                float y_inc = dy / (float)steps;
                float x = x1, y = y1;
                
                for (int s = 0; s <= steps; s++) {
                    int ix = (int)x;
                    int iy = (int)y;
                    if (ix >= 0 && ix < map_size && iy >= 0 && iy < map_size) {
                        if (map[iy][ix] == ' ') map[iy][ix] = '.';
                    }
                    x += x_inc;
                    y += y_inc;
                }
            }
        }
    }
    
    // Print the map
    printf("    ");
    for (int i = 0; i < map_size; i++) printf("─");
    printf("\n");
    
    for (int i = map_size - 1; i >= 0; i--) {
        printf("    │");
        for (int j = 0; j < map_size; j++) {
            printf("%c", map[i][j]);
        }
        printf("│\n");
    }
    
    printf("    ");
    for (int i = 0; i < map_size; i++) printf("─");
    printf("\n");
    
    // Legend
    printf("\nLegend: H=Hospital, S=School, G=Government, R=Residential,\n");
    printf("        C=Commercial, D=Data Center, .=MST Connection\n");
}

// ===================== COST CALCULATION HELPERS =====================

double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    // Using Haversine formula for accurate distance calculation
    double lat1_rad = lat1 * M_PI / 180.0;
    double lon1_rad = lon1 * M_PI / 180.0;
    double lat2_rad = lat2 * M_PI / 180.0;
    double lon2_rad = lon2 * M_PI / 180.0;
    
    double dlat = lat2_rad - lat1_rad;
    double dlon = lon2_rad - lon1_rad;
    
    double a = sin(dlat/2) * sin(dlat/2) +
               cos(lat1_rad) * cos(lat2_rad) *
               sin(dlon/2) * sin(dlon/2);
    
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double distance = EARTH_RADIUS * c;
    
    return distance;
}

double calculateAdjustedCost(double distance, TerrainType terrain, BuildingType src_type, 
                            BuildingType dest_type, int src_pop, int dest_pop) {
    // Base cost per km (in million rupees)
    double base_rate_per_km = 2.5;
    
    // Calculate base cost
    double cost = distance * base_rate_per_km;
    
    // Apply terrain multiplier
    cost *= getTerrainMultiplier(terrain);
    
    // Apply priority multipliers for building types
    double src_mult = getPriorityMultiplier(src_type);
    double dest_mult = getPriorityMultiplier(dest_type);
    double avg_mult = (src_mult + dest_mult) / 2.0;
    cost *= avg_mult;
    
    // Apply population factor (serving more people = better efficiency)
    int total_pop = src_pop + dest_pop;
    double pop_efficiency = 1.0 - (log10(total_pop + 1) / 10.0);
    if (pop_efficiency < 0.7) pop_efficiency = 0.7;
    if (pop_efficiency > 1.2) pop_efficiency = 1.2;
    
    cost *= pop_efficiency;
    
    // Minimum cost (even for very short distances)
    if (cost < 0.5) cost = 0.5;
    
    return cost;
}

const char* getBuildingTypeName(BuildingType type) {
    switch(type) {
        case HOSPITAL:    return "Hospital";
        case SCHOOL:      return "School";
        case GOVERNMENT:  return "Government";
        case RESIDENTIAL: return "Residential";
        case COMMERCIAL:  return "Commercial";
        case DATA_CENTER: return "Data Center";
        default:          return "Unknown";
    }
}

const char* getTerrainTypeName(TerrainType terrain) {
    switch(terrain) {
        case PLAIN:   return "Plain";
        case URBAN:   return "Urban";
        case HILLY:   return "Hilly";
        case RIVER:   return "River";
        case FOREST:  return "Forest";
        default:      return "Unknown";
    }
}

double getTerrainMultiplier(TerrainType terrain) {
    switch(terrain) {
        case PLAIN:   return 1.0;
        case URBAN:   return 1.3;  // 30% more expensive in cities
        case HILLY:   return 1.8;  // 80% more in hills
        case RIVER:   return 2.5;  // 150% more for river crossing
        case FOREST:  return 1.5;  // 50% more in forests
        default:      return 1.0;
    }
}

double getPriorityMultiplier(BuildingType type) {
    switch(type) {
        case HOSPITAL:    return 0.7;  // 30% discount for hospitals
        case SCHOOL:      return 0.8;  // 20% discount for schools
        case GOVERNMENT:  return 0.9;  // 10% discount for government
        case DATA_CENTER: return 1.0;  // No discount for data centers
        case RESIDENTIAL: return 1.1;  // 10% premium for residential
        case COMMERCIAL:  return 1.2;  // 20% premium for commercial
        default:          return 1.0;
    }
}

// ===================== FILE I/O OPERATIONS =====================

CityGraph* loadCityFromCSV(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        return NULL;
    }
    
    printf("[INFO] Loading city data from: %s\n", filename);
    
    // Read city name from first line
    char city_name[MAX_NAME_LEN];
    fgets(city_name, MAX_NAME_LEN, file);
    // Remove newline
    city_name[strcspn(city_name, "\n")] = 0;
    
    CityGraph* graph = createCityGraph(city_name, MAX_BUILDINGS);
    if (!graph) {
        fclose(file);
        return NULL;
    }
    
    char line[256];
    int section = 0; // 0=buildings, 1=connections
    
    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines and comments
        if (line[0] == '\n' || line[0] == '#') continue;
        
        // Check for section headers
        if (strstr(line, "[BUILDINGS]")) {
            section = 0;
            continue;
        }
        if (strstr(line, "[CONNECTIONS]")) {
            section = 1;
            continue;
        }
        
        // Parse based on section
        if (section == 0) {
            // Format: id,name,type,lat,lon,population
            int id;
            char name[MAX_NAME_LEN];
            char type_str[20];
            double lat, lon;
            int population;
            BuildingType type;
            
            if (sscanf(line, "%d,%49[^,],%19[^,],%lf,%lf,%d", 
                      &id, name, type_str, &lat, &lon, &population) == 6) {
                
                // Convert type string to enum
                if (strcmp(type_str, "HOSPITAL") == 0) type = HOSPITAL;
                else if (strcmp(type_str, "SCHOOL") == 0) type = SCHOOL;
                else if (strcmp(type_str, "GOVERNMENT") == 0) type = GOVERNMENT;
                else if (strcmp(type_str, "RESIDENTIAL") == 0) type = RESIDENTIAL;
                else if (strcmp(type_str, "COMMERCIAL") == 0) type = COMMERCIAL;
                else if (strcmp(type_str, "DATA_CENTER") == 0) type = DATA_CENTER;
                else type = RESIDENTIAL;
                
                addBuilding(graph, id, name, lat, lon, type, population);
            }
        } else if (section == 1) {
            // Format: src,dest,terrain,feasible
            int src, dest;
            char terrain_str[20];
            char feasible_str[10];
            TerrainType terrain;
            bool feasible;
            
            if (sscanf(line, "%d,%d,%19[^,],%9s", 
                      &src, &dest, terrain_str, feasible_str) == 4) {
                
                // Convert terrain string
                if (strcmp(terrain_str, "PLAIN") == 0) terrain = PLAIN;
                else if (strcmp(terrain_str, "URBAN") == 0) terrain = URBAN;
                else if (strcmp(terrain_str, "HILLY") == 0) terrain = HILLY;
                else if (strcmp(terrain_str, "RIVER") == 0) terrain = RIVER;
                else if (strcmp(terrain_str, "FOREST") == 0) terrain = FOREST;
                else terrain = PLAIN;
                
                feasible = (strcmp(feasible_str, "TRUE") == 0 || 
                           strcmp(feasible_str, "1") == 0);
                
                addConnection(graph, src, dest, terrain, feasible);
            }
        }
    }
    
    fclose(file);
    
    // Calculate distances and costs for all connections
    calculateAllDistances(graph);
    calculateAllCosts(graph);
    
    printf("[INFO] Successfully loaded city with %d buildings and %d connections\n",
           graph->vertex_count, graph->edge_count);
    
    return graph;
}

void saveMSTToCSV(CityGraph* graph, MSTResult* result, const char* filename) {
    if (!graph || !result) return;
    
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Cannot create file: %s\n", filename);
        return;
    }
    
    fprintf(file, "# MINIMUM SPANNING TREE - OPTIMAL FIBER NETWORK\n");
    fprintf(file, "# City: %s\n", graph->city_name);
    fprintf(file, "# Total Cost: ₹%.2f Million\n", result->total_cost);
    fprintf(file, "# Generated on: %s", ctime(&(time_t){time(NULL)}));
    fprintf(file, "\n");
    
    fprintf(file, "SRC_ID,SRC_NAME,DEST_ID,DEST_NAME,DISTANCE_KM,TERRAIN,COST_MILLIONS\n");
    
    for (int i = 0; i < result->connections_used; i++) {
        Connection edge = result->mst_edges[i];
        fprintf(file, "%d,%s,%d,%s,%.2f,%s,%.2f\n",
                edge.src_id,
                graph->buildings[edge.src_id].name,
                edge.dest_id,
                graph->buildings[edge.dest_id].name,
                edge.distance_km,
                getTerrainTypeName(edge.terrain),
                edge.adjusted_cost);
    }
    
    fclose(file);
    printf("[INFO] MST saved to: %s\n", filename);
}

void saveNetworkPlan(CityGraph* graph, MSTResult* result, const char* filename) {
    if (!graph || !result) return;
    
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Cannot create file: %s\n", filename);
        return;
    }
    
    fprintf(file, "╔══════════════════════════════════════════════════════════════╗\n");
    fprintf(file, "║           SMART CITY FIBER NETWORK IMPLEMENTATION PLAN      ║\n");
    fprintf(file, "╠══════════════════════════════════════════════════════════════╣\n");
    fprintf(file, "║ City: %-53s ║\n", graph->city_name);
    fprintf(file, "║ Total Buildings: %-43d ║\n", graph->vertex_count);
    fprintf(file, "║ Total Cost: ₹%-46.2fM ║\n", result->total_cost);
    fprintf(file, "║ Estimated Timeline: 6-8 months                              ║\n");
    fprintf(file, "║ Contractor: GCEK Infrastructure Division                    ║\n");
    fprintf(file, "╚══════════════════════════════════════════════════════════════╝\n\n");
    
    fprintf(file, "PHASE 1: SITE SURVEY & PERMISSIONS (Month 1-2)\n");
    fprintf(file, "──────────────────────────────────────────────\n");
    fprintf(file, "• Survey all %d building locations\n", graph->vertex_count);
    fprintf(file, "• Obtain municipal permits\n");
    fprintf(file, "• Finalize contractor agreements\n\n");
    
    fprintf(file, "PHASE 2: TRENCHING & CABLE LAYING (Month 3-6)\n");
    fprintf(file, "──────────────────────────────────────────────\n");
    fprintf(file, "SEQUENCE OF CONSTRUCTION:\n\n");
    
    for (int i = 0; i < result->connections_used; i++) {
        Connection edge = result->mst_edges[i];
        fprintf(file, "%2d. Connect %s to %s\n", i + 1,
                graph->buildings[edge.src_id].name,
                graph->buildings[edge.dest_id].name);
        fprintf(file, "    • Distance: %.2f km\n", edge.distance_km);
        fprintf(file, "    • Terrain: %s\n", getTerrainTypeName(edge.terrain));
        fprintf(file, "    • Estimated cost: ₹%.2f Million\n", edge.adjusted_cost);
        fprintf(file, "    • Timeline: %d weeks\n", (int)(edge.distance_km * 0.5) + 1);
        fprintf(file, "\n");
    }
    
    fprintf(file, "PHASE 3: TESTING & COMMISSIONING (Month 7-8)\n");
    fprintf(file, "──────────────────────────────────────────────\n");
    fprintf(file, "• Fiber optic cable testing\n");
    fprintf(file, "• Network equipment installation\n");
    fprintf(file, "• Speed and reliability testing\n");
    fprintf(file, "• Official launch and handover\n");
    
    fclose(file);
    printf("[INFO] Network plan saved to: %s\n", filename);
}

void generateReport(CityGraph* graph, MSTResult* result, const char* filename) {
    if (!graph || !result) return;
    
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Cannot create file: %s\n", filename);
        return;
    }
    
    fprintf(file, "SMART CITY FIBER NETWORK OPTIMIZATION REPORT\n");
    fprintf(file, "=============================================\n\n");
    
    fprintf(file, "1. EXECUTIVE SUMMARY\n");
    fprintf(file, "────────────────────\n");
    fprintf(file, "• Algorithm Used: Prim's Minimum Spanning Tree\n");
    fprintf(file, "• Optimization Goal: Minimize total fiber optic cable cost\n");
    fprintf(file, "• City: %s\n", graph->city_name);
    fprintf(file, "• Total Buildings Connected: %d\n", graph->vertex_count);
    fprintf(file, "• Optimal Connections Required: %d\n", result->connections_used);
    fprintf(file, "• Minimum Total Cost: ₹%.2f Million\n\n", result->total_cost);
    
    fprintf(file, "2. COST-BENEFIT ANALYSIS\n");
    fprintf(file, "────────────────────────\n");
    
    // Calculate comparison metrics
    double star_cost = calculateStarNetworkCost(graph);
    double random_cost = calculateNaiveNetworkCost(graph);
    double savings_vs_star = ((star_cost - result->total_cost) / star_cost) * 100;
    double savings_vs_random = ((random_cost - result->total_cost) / random_cost) * 100;
    
    fprintf(file, "Comparison with Alternative Approaches:\n");
    fprintf(file, "• Star Network (all to center): ₹%.2fM\n", star_cost);
    fprintf(file, "• Random Connections: ₹%.2fM\n", random_cost);
    fprintf(file, "• Prim's MST (Optimized): ₹%.2fM\n", result->total_cost);
    fprintf(file, "• Savings vs Star Network: %.1f%%\n", savings_vs_star);
    fprintf(file, "• Savings vs Random: %.1f%%\n\n", savings_vs_random);
    
    fprintf(file, "3. IMPLEMENTATION DETAILS\n");
    fprintf(file, "─────────────────────────\n");
    fprintf(file, "Building Types Distribution:\n");
    
    int type_counts[6] = {0};
    for (int i = 0; i < graph->vertex_count; i++) {
        type_counts[graph->buildings[i].type]++;
    }
    
    for (int i = 0; i < 6; i++) {
        if (type_counts[i] > 0) {
            fprintf(file, "• %s: %d buildings\n", getBuildingTypeName(i), type_counts[i]);
        }
    }
    
    fprintf(file, "\nTerrain Distribution in MST:\n");
    int terrain_counts[5] = {0};
    for (int i = 0; i < result->connections_used; i++) {
        terrain_counts[result->mst_edges[i].terrain]++;
    }
    
    for (int i = 0; i < 5; i++) {
        if (terrain_counts[i] > 0) {
            fprintf(file, "• %s: %d connections\n", getTerrainTypeName(i), terrain_counts[i]);
        }
    }
    
    fprintf(file, "\n4. TECHNICAL SPECIFICATIONS\n");
    fprintf(file, "───────────────────────────\n");
    fprintf(file, "• Total Fiber Length: %.2f km\n", 
            calculateTotalFiberLength(result));
    fprintf(file, "• Average Connection Length: %.2f km\n",
            calculateTotalFiberLength(result) / result->connections_used);
    fprintf(file, "• Longest Connection: %.2f km\n",
            findLongestConnection(result));
    fprintf(file, "• Shortest Connection: %.2f km\n",
            findShortestConnection(result));
    
    fclose(file);
    printf("[INFO] Report generated: %s\n", filename);
}

// ===================== DEMO & UTILITY FUNCTIONS =====================

CityGraph* generateDemoCity(int building_count) {
    if (building_count > MAX_BUILDINGS) {
        building_count = MAX_BUILDINGS;
    }
    
    CityGraph* graph = createCityGraph("Smart City Demo", MAX_BUILDINGS);
    if (!graph) return NULL;
    
    // Seed random generator
    srand(time(NULL));
    
    // Building names pool
    const char* hospitals[] = {"City Hospital", "General Hospital", "Children's Hospital"};
    const char* schools[] = {"Central School", "High School", "Primary School", "College"};
    const char* govt[] = {"Municipal Office", "Police Station", "Fire Station", "Court"};
    const char* residential[] = {"Apartment A", "Apartment B", "Housing Society", "Villa Complex"};
    const char* commercial[] = {"Mall", "Office Tower", "Market", "Hotel"};
    
    // Create buildings
    for (int i = 0; i < building_count; i++) {
        char name[50];
        BuildingType type;
        const char* base_name;
        
        // Assign building type with distribution
        int type_rand = rand() % 100;
        if (type_rand < 15) {  // 15% hospitals
            type = HOSPITAL;
            base_name = hospitals[rand() % 3];
        } else if (type_rand < 35) {  // 20% schools
            type = SCHOOL;
            base_name = schools[rand() % 4];
        } else if (type_rand < 50) {  // 15% government
            type = GOVERNMENT;
            base_name = govt[rand() % 4];
        } else if (type_rand < 80) {  // 30% residential
            type = RESIDENTIAL;
            base_name = residential[rand() % 4];
        } else {  // 20% commercial
            type = COMMERCIAL;
            base_name = commercial[rand() % 4];
        }
        
        // Make first building a data center
        if (i == 0) {
            type = DATA_CENTER;
            strcpy(name, "Main Data Center");
        } else {
            sprintf(name, "%s %d", base_name, i);
        }
        
        // Generate random coordinates within a 10x10 km area
        double lat = 18.5 + (rand() % 1000) / 10000.0;  // Near Karad
        double lon = 74.0 + (rand() % 1000) / 10000.0;
        int population = 100 + rand() % 1000;
        
        addBuilding(graph, i, name, lat, lon, type, population);
    }
    
    // Create random connections (about 30% density)
    int connection_count = (building_count * (building_count - 1)) / 2 * 0.3;
    
    for (int i = 0; i < connection_count; i++) {
        int src = rand() % building_count;
        int dest = rand() % building_count;
        if (src == dest) continue;
        
        TerrainType terrain = rand() % 5;
        bool feasible = (rand() % 10) > 1;  // 80% feasible
        
        addConnection(graph, src, dest, terrain, feasible);
    }
    
    // Calculate all distances and costs
    calculateAllDistances(graph);
    calculateAllCosts(graph);
    
    printf("[INFO] Generated demo city with %d buildings and %d connections\n",
           graph->vertex_count, graph->edge_count);
    
    return graph;
}

void compareAlgorithms(CityGraph* graph) {
    if (!graph) return;
    
    printf("\n");
    printf("╔═══════════════════════════════════════════════╗\n");
    printf("║         ALGORITHM COMPARISON ANALYSIS        ║\n");
    printf("╚═══════════════════════════════════════════════╝\n\n");
    
    // Run Prim's algorithm
    clock_t start = clock();
    MSTResult* prim_result = primMST(graph, graph->start_vertex);
    clock_t prim_time = clock() - start;
    
    if (!prim_result) return;
    
    // Calculate comparison metrics
    double star_cost = calculateStarNetworkCost(graph);
    double random_cost = calculateNaiveNetworkCost(graph);
    double savings_vs_star = ((star_cost - prim_result->total_cost) / star_cost) * 100;
    double savings_vs_random = ((random_cost - prim_result->total_cost) / random_cost) * 100;
    
    printf("COMPARISON TABLE:\n");
    printf("┌─────────────────┬─────────────────┬─────────────────┬─────────────────┐\n");
    printf("│ Algorithm       │ Total Cost (₹M) │ Time (ms)       │ Efficiency      │\n");
    printf("├─────────────────┼─────────────────┼─────────────────┼─────────────────┤\n");
    printf("│ Prim's MST      │ %15.2f │ %15.3f │     Optimal     │\n", 
           prim_result->total_cost, ((double)prim_time/CLOCKS_PER_SEC)*1000);
    printf("│ Star Network    │ %15.2f │             - │ %6.1f%% Savings │\n", 
           star_cost, savings_vs_star);
    printf("│ Random Network  │ %15.2f │             - │ %6.1f%% Savings │\n", 
           random_cost, savings_vs_random);
    printf("└─────────────────┴─────────────────┴─────────────────┴─────────────────┘\n");
    
    printf("\nKEY INSIGHTS:\n");
    printf("1. Prim's MST provides the mathematically optimal solution\n");
    printf("2. Star network is simple but %d%% more expensive\n", (int)savings_vs_star);
    printf("3. Prim's algorithm complexity: O(V²) for dense graphs\n");
    printf("4. For %d buildings, optimal solution found in %.3f ms\n",
           graph->vertex_count, ((double)prim_time/CLOCKS_PER_SEC)*1000);
    
    free(prim_result);
}

void calculateStatistics(CityGraph* graph, MSTResult* result) {
    if (!graph || !result) return;
    
    printf("\n📈 NETWORK STATISTICS\n");
    printf("═══════════════════════════════\n");
    
    // Calculate various statistics
    double total_length = 0;
    double max_length = 0;
    double min_length = INF;
    double avg_length = 0;
    
    for (int i = 0; i < result->connections_used; i++) {
        double len = result->mst_edges[i].distance_km;
        total_length += len;
        if (len > max_length) max_length = len;
        if (len < min_length) min_length = len;
    }
    
    avg_length = total_length / result->connections_used;
    
    printf("Length Statistics:\n");
    printf("• Total Fiber Length: %.2f km\n", total_length);
    printf("• Average Connection: %.2f km\n", avg_length);
    printf("• Longest Connection: %.2f km\n", max_length);
    printf("• Shortest Connection: %.2f km\n", min_length);
    
    // Cost per km
    double cost_per_km = result->total_cost / total_length;
    printf("\nCost Efficiency:\n");
    printf("• Overall Cost per km: ₹%.2f Million/km\n", cost_per_km);
    printf("• Government Savings: ₹%.2f Million\n", result->total_cost * 0.15);
    
    // Building type distribution in MST
    printf("\nBuilding Types in Network:\n");
    int type_conn_count[6] = {0};
    for (int i = 0; i < result->connections_used; i++) {
        Connection edge = result->mst_edges[i];
        type_conn_count[graph->buildings[edge.src_id].type]++;
        type_conn_count[graph->buildings[edge.dest_id].type]++;
    }
    
    for (int i = 0; i < 6; i++) {
        if (type_conn_count[i] > 0) {
            printf("• %s: %d endpoints\n", getBuildingTypeName(i), type_conn_count[i]);
        }
    }
}

// ===================== HELPER CALCULATION FUNCTIONS =====================

static double calculateTotalFiberLength(MSTResult* result) {
    if (!result) return 0;
    
    double total = 0;
    for (int i = 0; i < result->connections_used; i++) {
        total += result->mst_edges[i].distance_km;
    }
    return total;
}

static double findLongestConnection(MSTResult* result) {
    if (!result || result->connections_used == 0) return 0;
    
    double max_len = 0;
    for (int i = 0; i < result->connections_used; i++) {
        if (result->mst_edges[i].distance_km > max_len) {
            max_len = result->mst_edges[i].distance_km;
        }
    }
    return max_len;
}

static double findShortestConnection(MSTResult* result) {
    if (!result || result->connections_used == 0) return 0;
    
    double min_len = INF;
    for (int i = 0; i < result->connections_used; i++) {
        if (result->mst_edges[i].distance_km < min_len) {
            min_len = result->mst_edges[i].distance_km;
        }
    }
    return min_len == INF ? 0 : min_len;
}

double calculateStarNetworkCost(CityGraph* graph) {
    if (!graph || graph->start_vertex == -1) return INF;
    
    double total_cost = 0;
    for (int i = 0; i < graph->vertex_count; i++) {
        if (i != graph->start_vertex && graph->adj_matrix[graph->start_vertex][i] != INF) {
            total_cost += graph->adj_matrix[graph->start_vertex][i];
        }
    }
    return total_cost;
}

double calculateNaiveNetworkCost(CityGraph* graph) {
    if (!graph) return INF;
    
    // Create a naive spanning tree by connecting in order
    double total_cost = 0;
    for (int i = 1; i < graph->vertex_count; i++) {
        // Connect to previous building
        if (graph->adj_matrix[i-1][i] != INF) {
            total_cost += graph->adj_matrix[i-1][i];
        } else {
            // If no direct connection, find cheapest connection to any previous building
            double min_cost = INF;
            for (int j = 0; j < i; j++) {
                if (graph->adj_matrix[j][i] < min_cost) {
                    min_cost = graph->adj_matrix[j][i];
                }
            }
            if (min_cost != INF) {
                total_cost += min_cost;
            }
        }
    }
    return total_cost;
}

void animateMSTConstruction(CityGraph* graph, MSTResult* result, int delay_ms) {
    // This would typically use a graphical library
    // For CLI, we simulate with text animation
    printf("\n🎬 MST Construction Animation\n");
    printf("==============================\n");
    
    for (int i = 0; i < result->connections_used; i++) {
        printf("Adding connection %d/%d: ", i + 1, result->connections_used);
        printf("%s ↔ %s\n", 
               graph->buildings[result->mst_edges[i].src_id].name,
               graph->buildings[result->mst_edges[i].dest_id].name);
        
        // Simulate delay
        // usleep(delay_ms * 1000);
    }
    
    printf("✨ MST Complete! Total Cost: ₹%.2fM\n", result->total_cost);
}