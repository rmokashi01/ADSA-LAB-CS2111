#ifndef PRIMS_H
#define PRIMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// ===================== CONSTANTS =====================
#define MAX_BUILDINGS 100
#define MAX_NAME_LEN 50
#define INF 1e9
#define EARTH_RADIUS 6371.0  // Earth's radius in km for real GPS calculations

// ===================== ENUMERATIONS =====================
typedef enum {
    HOSPITAL = 0,
    SCHOOL = 1,
    GOVERNMENT = 2,
    RESIDENTIAL = 3,
    COMMERCIAL = 4,
    DATA_CENTER = 5
} BuildingType;

typedef enum {
    PLAIN = 0,      // Normal terrain
    URBAN = 1,      // City area
    HILLY = 2,      // Mountainous
    RIVER = 3,      // River crossing
    FOREST = 4      // Forest area
} TerrainType;

// ===================== DATA STRUCTURES =====================
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    double latitude;   // GPS coordinates
    double longitude;
    BuildingType type;
    int population;    // For priority calculation
} Building;

typedef struct {
    int src_id;
    int dest_id;
    double distance_km;
    TerrainType terrain;
    bool is_feasible;
    double base_cost;      // In million rupees
    double adjusted_cost;  // After terrain and priority adjustments
} Connection;

typedef struct {
    Building* buildings;
    double** adj_matrix;      // Adjusted cost matrix
    double** dist_matrix;     // Distance matrix
    int** terrain_matrix;     // Terrain type matrix
    int vertex_count;
    int edge_count;
    int start_vertex;        // Starting building (usually data center)
    char city_name[MAX_NAME_LEN];
} CityGraph;

typedef struct {
    int parent[MAX_BUILDINGS];
    double key[MAX_BUILDINGS];
    bool in_mst[MAX_BUILDINGS];
    double total_cost;
    int connections_used;
    Connection mst_edges[MAX_BUILDINGS - 1];
} MSTResult;

// ===================== GRAPH OPERATIONS =====================
CityGraph* createCityGraph(const char* city_name, int max_vertices);
void destroyCityGraph(CityGraph* graph);
void addBuilding(CityGraph* graph, int id, const char* name, double lat, double lon, 
                 BuildingType type, int population);
void addConnection(CityGraph* graph, int src, int dest, TerrainType terrain, bool feasible);
void calculateAllDistances(CityGraph* graph);
void calculateAllCosts(CityGraph* graph);

// ===================== PRIM'S ALGORITHM CORE =====================
MSTResult* primMST(CityGraph* graph, int start_vertex);
void primMSTStepByStep(CityGraph* graph, int start_vertex);
int findMinKeyVertex(double key[], bool in_mst[], int n);

// ===================== VISUALIZATION FUNCTIONS =====================
void printBuildingInfo(Building b);
void printConnectionInfo(CityGraph* graph, int src, int dest);
void printCityGraph(CityGraph* graph);
void printMSTResult(CityGraph* graph, MSTResult* result);
void printProgressBar(int current, int total, int bar_width);
void printCityMapASCII(CityGraph* graph, MSTResult* result);

// ===================== COST CALCULATION HELPERS =====================
double calculateDistance(double lat1, double lon1, double lat2, double lon2);
double calculateAdjustedCost(double distance, TerrainType terrain, BuildingType src_type, 
                            BuildingType dest_type, int src_pop, int dest_pop);
const char* getBuildingTypeName(BuildingType type);
const char* getTerrainTypeName(TerrainType terrain);
double getTerrainMultiplier(TerrainType terrain);
double getPriorityMultiplier(BuildingType type);

// ===================== FILE I/O OPERATIONS =====================
CityGraph* loadCityFromCSV(const char* filename);
void saveMSTToCSV(CityGraph* graph, MSTResult* result, const char* filename);
void saveNetworkPlan(CityGraph* graph, MSTResult* result, const char* filename);
void generateReport(CityGraph* graph, MSTResult* result, const char* filename);

// ===================== DEMO & UTILITY FUNCTIONS =====================
CityGraph* generateDemoCity(int building_count);
void compareAlgorithms(CityGraph* graph);
void calculateStatistics(CityGraph* graph, MSTResult* result);
void animateMSTConstruction(CityGraph* graph, MSTResult* result, int delay_ms);

// ===================== ALGORITHM COMPARISON =====================
MSTResult* kruskalMST(CityGraph* graph);  // For comparison
double calculateNaiveNetworkCost(CityGraph* graph);  // Random connections cost
double calculateStarNetworkCost(CityGraph* graph);   // All connect to center

#endif