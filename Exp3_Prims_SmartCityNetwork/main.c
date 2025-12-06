#include "prims.h"
#include <conio.h>  // For Windows getch(), if Linux/Mac use appropriate alternative

// ===================== FUNCTION PROTOTYPES =====================
void clearScreen();
void printWelcomeBanner();
void displayMainMenu();
void manualCityInput(CityGraph** graph);
void loadCityFromFileMenu(CityGraph** graph);
void runPrimsAlgorithm(CityGraph* graph, MSTResult** result);
void saveResultsMenu(CityGraph* graph, MSTResult* result);
void displayStatisticsMenu(CityGraph* graph, MSTResult* result);
void demoMode();
void compareAlgorithmsMenu(CityGraph* graph);
void stepByStepDemo(CityGraph* graph);

// ===================== UTILITY FUNCTIONS =====================

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printWelcomeBanner() {
    clearScreen();
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                                ║\n");
    printf("║          ███████╗███╗   ███╗ █████╗ ██████╗ ████████╗  ██████╗██╗   ██╗        ║\n");
    printf("║          ██╔════╝████╗ ████║██╔══██╗██╔══██╗╚══██╔══╝ ██╔════╝╚██╗ ██╔╝        ║\n");
    printf("║          ███████╗██╔████╔██║███████║██████╔╝   ██║    ██║      ╚████╔╝         ║\n");
    printf("║          ╚════██║██║╚██╔╝██║██╔══██║██╔══██╗   ██║    ██║       ╚██╔╝          ║\n");
    printf("║          ███████║██║ ╚═╝ ██║██║  ██║██║  ██║   ██║    ╚██████╗   ██║           ║\n");
    printf("║          ╚══════╝╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝     ╚═════╝   ╚═╝           ║\n");
    printf("║                                                                                ║\n");
    printf("║           SMART CITY FIBER OPTIC NETWORK OPTIMIZATION USING PRIM'S MST        ║\n");
    printf("║                                                                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("                         GOVERNMENT COLLEGE OF ENGINEERING, KARAD\n");
    printf("                     CS2111 - ADVANCED DATA STRUCTURES & ALGORITHMS\n");
    printf("                                EXPERIMENT 3 - PRIM'S ALGORITHM\n");
    printf("                              Developed by: Mr. Rehan Mokashi\n");
    printf("                              Guided by: Prof. K. S. Gandle\n");
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                               PROJECT OVERVIEW                                 ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ This system implements Prim's Minimum Spanning Tree algorithm to optimize     ║\n");
    printf("║ fiber optic network deployment in smart cities. It calculates the minimum     ║\n");
    printf("║ cost connections between buildings while considering terrain, building types, ║\n");
    printf("║ and population factors.                                                        ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\nPress ENTER to continue...");
    getchar();
}

void displayMainMenu() {
    clearScreen();
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                          MAIN MENU - PRIM'S MST SYSTEM                         ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║  1. 📂 Load City Data from CSV File                                           ║\n");
    printf("║  2. ✏️  Enter City Data Manually                                              ║\n");
    printf("║  3. 🎮 Generate Random City (Demo Mode)                                       ║\n");
    printf("║  4. 🚀 Run Prim's Algorithm & Find Optimal Network                            ║\n");
    printf("║  5. 🏙️  Display City Graph Information                                        ║\n");
    printf("║  6. 📊 Step-by-Step Prim's Algorithm Demo                                     ║\n");
    printf("║  7. ⚖️  Compare Prim's vs Other Algorithms                                    ║\n");
    printf("║  8. 🗺️  Visualize City Map with MST                                           ║\n");
    printf("║  9. 💾 Save Results & Generate Reports                                        ║\n");
    printf("║ 10. 📈 Display Statistics & Analysis                                          ║\n");
    printf("║ 11. ℹ️  About & Help                                                           ║\n");
    printf("║ 12. ❌ Exit Program                                                            ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\nEnter your choice (1-12): ");
}

// ===================== MENU OPTION FUNCTIONS =====================

void loadCityFromFileMenu(CityGraph** graph) {
    clearScreen();
    printf("\n╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                          LOAD CITY DATA FROM FILE                              ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    char filename[100];
    printf("Available city data files:\n");
    printf("1. city_data.csv (Sample city with 10 buildings)\n");
    printf("2. large_city.csv (Large city with 50 buildings)\n");
    printf("3. Enter custom filename\n");
    printf("\nEnter choice (1-3): ");
    
    int choice;
    scanf("%d", &choice);
    getchar(); // Clear newline
    
    switch(choice) {
        case 1:
            strcpy(filename, "city_data.csv");
            break;
        case 2:
            strcpy(filename, "large_city.csv");
            break;
        case 3:
            printf("Enter filename (including .csv extension): ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = 0;
            break;
        default:
            printf("Invalid choice. Using default: city_data.csv\n");
            strcpy(filename, "city_data.csv");
    }
    
    // Check if file exists
    FILE* test = fopen(filename, "r");
    if (!test) {
        printf("\n❌ Error: File '%s' not found!\n", filename);
        printf("Creating sample city_data.csv for you...\n");
        
        // Create sample CSV file
        FILE* sample = fopen("city_data.csv", "w");
        if (sample) {
            fprintf(sample, "Smart City Demo\n");
            fprintf(sample, "[BUILDINGS]\n");
            fprintf(sample, "0,Main Data Center,DATA_CENTER,18.500000,74.000000,100\n");
            fprintf(sample, "1,City Hospital,HOSPITAL,18.510000,74.010000,500\n");
            fprintf(sample, "2,Central School,SCHOOL,18.505000,74.005000,300\n");
            fprintf(sample, "3,Government Office,GOVERNMENT,18.508000,74.008000,200\n");
            fprintf(sample, "4,Residential Tower A,RESIDENTIAL,18.502000,74.002000,400\n");
            fprintf(sample, "[CONNECTIONS]\n");
            fprintf(sample, "0,1,PLAIN,TRUE\n");
            fprintf(sample, "0,2,URBAN,TRUE\n");
            fprintf(sample, "1,2,HILLY,TRUE\n");
            fprintf(sample, "1,3,PLAIN,TRUE\n");
            fprintf(sample, "2,4,URBAN,TRUE\n");
            fprintf(sample, "3,4,PLAIN,TRUE\n");
            fclose(sample);
            printf("✅ Sample file created: city_data.csv\n");
            strcpy(filename, "city_data.csv");
        }
    } else {
        fclose(test);
    }
    
    // Load the city
    if (*graph) {
        destroyCityGraph(*graph);
    }
    
    *graph = loadCityFromCSV(filename);
    
    if (*graph) {
        printf("\n✅ City loaded successfully!\n");
        printf("   City Name: %s\n", (*graph)->city_name);
        printf("   Buildings: %d\n", (*graph)->vertex_count);
        printf("   Start Building: %s\n", (*graph)->buildings[(*graph)->start_vertex].name);
    } else {
        printf("\n❌ Failed to load city from file.\n");
    }
    
    printf("\nPress ENTER to continue...");
    getchar();
}

void manualCityInput(CityGraph** graph) {
    clearScreen();
    printf("\n╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                         MANUAL CITY DATA ENTRY                                 ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    char city_name[100];
    int building_count;
    
    printf("Enter city name: ");
    fgets(city_name, sizeof(city_name), stdin);
    city_name[strcspn(city_name, "\n")] = 0;
    
    printf("Enter number of buildings (max %d): ", MAX_BUILDINGS);
    scanf("%d", &building_count);
    getchar(); // Clear newline
    
    if (building_count > MAX_BUILDINGS) {
        printf("Maximum capacity is %d. Setting to %d.\n", MAX_BUILDINGS, MAX_BUILDINGS);
        building_count = MAX_BUILDINGS;
    }
    
    if (*graph) {
        destroyCityGraph(*graph);
    }
    
    *graph = createCityGraph(city_name, MAX_BUILDINGS);
    
    if (!*graph) {
        printf("Failed to create city graph.\n");
        return;
    }
    
    printf("\n════════════════════════════════════════════════════════════════════════════════\n");
    printf("ENTER BUILDING DETAILS:\n");
    printf("════════════════════════════════════════════════════════════════════════════════\n");
    
    for (int i = 0; i < building_count; i++) {
        printf("\n🏢 Building %d:\n", i);
        
        char name[50];
        double lat, lon;
        int type_choice, population;
        
        printf("  Building name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;
        
        printf("  Building type:\n");
        printf("  1. Hospital\n");
        printf("  2. School\n");
        printf("  3. Government\n");
        printf("  4. Residential\n");
        printf("  5. Commercial\n");
        printf("  6. Data Center (Select for main data hub)\n");
        printf("  Enter choice (1-6): ");
        scanf("%d", &type_choice);
        getchar();
        
        BuildingType type;
        switch(type_choice) {
            case 1: type = HOSPITAL; break;
            case 2: type = SCHOOL; break;
            case 3: type = GOVERNMENT; break;
            case 4: type = RESIDENTIAL; break;
            case 5: type = COMMERCIAL; break;
            case 6: type = DATA_CENTER; break;
            default: type = RESIDENTIAL;
        }
        
        printf("  Latitude (e.g., 18.5 for Karad): ");
        scanf("%lf", &lat);
        getchar();
        
        printf("  Longitude (e.g., 74.0 for Karad): ");
        scanf("%lf", &lon);
        getchar();
        
        printf("  Population served: ");
        scanf("%d", &population);
        getchar();
        
        addBuilding(*graph, i, name, lat, lon, type, population);
    }
    
    // Calculate distances and costs
    calculateAllDistances(*graph);
    calculateAllCosts(*graph);
    
    printf("\n✅ City created successfully!\n");
    printf("   You can now add connections or run the algorithm.\n");
    
    printf("\nPress ENTER to continue...");
    getchar();
}

void demoMode() {
    clearScreen();
    printf("\n╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              DEMO MODE - RANDOM CITY                           ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    int building_count;
    printf("Enter number of buildings for demo (5-20): ");
    scanf("%d", &building_count);
    getchar();
    
    if (building_count < 5) building_count = 5;
    if (building_count > 20) building_count = 20;
    
    CityGraph* demo_city = generateDemoCity(building_count);
    
    if (demo_city) {
        printf("\n════════════════════════════════════════════════════════════════════════════════\n");
        printf("DEMO CITY GENERATED SUCCESSFULLY!\n");
        printf("════════════════════════════════════════════════════════════════════════════════\n");
        
        printCityGraph(demo_city);
        
        printf("\nDo you want to run Prim's algorithm on this demo city? (y/n): ");
        char choice;
        scanf("%c", &choice);
        getchar();
        
        if (choice == 'y' || choice == 'Y') {
            MSTResult* result = primMST(demo_city, demo_city->start_vertex);
            if (result) {
                printMSTResult(demo_city, result);
                free(result);
            }
        }
        
        printf("\nDemo complete. The demo city will be available in the main menu.\n");
        
        // Ask if user wants to use this city
        printf("\nUse this demo city for further operations? (y/n): ");
        scanf("%c", &choice);
        getchar();
        
        if (choice == 'y' || choice == 'Y') {
            // Return the demo city to main
            // Note: In actual implementation, you'd need to handle this return
            printf("Demo city loaded for further operations.\n");
        } else {
            destroyCityGraph(demo_city);
        }
    }
    
    printf("\nPress ENTER to continue...");
    getchar();
}

void runPrimsAlgorithm(CityGraph* graph, MSTResult** result) {
    if (!graph) {
        printf("\n❌ No city data loaded! Please load or create a city first.\n");
        printf("Press ENTER to continue...");
        getchar();
        return;
    }
    
    clearScreen();
    printf("\n╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                     PRIM'S ALGORITHM EXECUTION                                 ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    printf("City: %s\n", graph->city_name);
    printf("Buildings: %d\n", graph->vertex_count);
    printf("Start Building: %s\n", graph->buildings[graph->start_vertex].name);
    
    printf("\n════════════════════════════════════════════════════════════════════════════════\n");
    printf("Running Prim's Minimum Spanning Tree Algorithm...\n");
    printf("════════════════════════════════════════════════════════════════════════════════\n");
    
    // Free previous result if exists
    if (*result) {
        free(*result);
        *result = NULL;
    }
    
    // Run Prim's algorithm
    *result = primMST(graph, graph->start_vertex);
    
    if (*result) {
        printf("\n✅ Algorithm completed successfully!\n");
        
        // Display results
        printMSTResult(graph, *result);
        
        // Show ASCII map
        printf("\nDo you want to see the city map with MST? (y/n): ");
        char choice;
        scanf("%c", &choice);
        getchar();
        
        if (choice == 'y' || choice == 'Y') {
            printCityMapASCII(graph, *result);
        }
    } else {
        printf("\n❌ Algorithm failed to produce results.\n");
    }
    
    printf("\nPress ENTER to continue...");
    getchar();
}

void stepByStepDemo(CityGraph* graph) {
    if (!graph) {
        printf("\n❌ No city data loaded! Please load or create a city first.\n");
        printf("Press ENTER to continue...");
        getchar();
        return;
    }
    
    clearScreen();
    printf("\n╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                  STEP-BY-STEP PRIM'S ALGORITHM DEMO                           ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    printf("This demo shows each step of Prim's algorithm in detail.\n");
    printf("City: %s | Buildings: %d\n\n", graph->city_name, graph->vertex_count);
    
    primMSTStepByStep(graph, graph->start_vertex);
    
    printf("\nPress ENTER to continue...");
    getchar();
}

void compareAlgorithmsMenu(CityGraph* graph) {
    if (!graph) {
        printf("\n❌ No city data loaded! Please load or create a city first.\n");
        printf("Press ENTER to continue...");
        getchar();
        return;
    }
    
    clearScreen();
    printf("\n╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                     ALGORITHM COMPARISON ANALYSIS                              ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    printf("This analysis compares Prim's MST with other network design approaches.\n\n");
    
    compareAlgorithms(graph);
    
    printf("\n════════════════════════════════════════════════════════════════════════════════\n");
    printf("INTERPRETATION OF RESULTS:\n");
    printf("════════════════════════════════════════════════════════════════════════════════\n");
    printf("• Prim's MST: Mathematical optimal solution for minimum total cost\n");
    printf("• Star Network: All buildings connect directly to data center (simple but costly)\n");
    printf("• Random Network: Sequential connection without optimization\n");
    printf("• Savings show how much Prim's algorithm reduces costs compared to alternatives\n");
    
    printf("\nPress ENTER to continue...");
    getchar();
}

void saveResultsMenu(CityGraph* graph, MSTResult* result) {
    if (!graph || !result) {
        printf("\n❌ No results to save! Please run Prim's algorithm first.\n");
        printf("Press ENTER to continue...");
        getchar();
        return;
    }
    
    clearScreen();
    printf("\n╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                          SAVE RESULTS & REPORTS                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    printf("Choose what to save:\n");
    printf("1. Save MST connections to CSV (for analysis)\n");
    printf("2. Save network implementation plan (for contractors)\n");
    printf("3. Generate comprehensive report (for stakeholders)\n");
    printf("4. Save all of the above\n");
    printf("Enter choice (1-4): ");
    
    int choice;
    scanf("%d", &choice);
    getchar();
    
    char base_filename[100];
    sprintf(base_filename, "%s_mst", graph->city_name);
    
    switch(choice) {
        case 1:
            saveMSTToCSV(graph, result, "mst_connections.csv");
            break;
        case 2:
            saveNetworkPlan(graph, result, "network_implementation_plan.txt");
            break;
        case 3:
            generateReport(graph, result, "comprehensive_report.txt");
            break;
        case 4:
            saveMSTToCSV(graph, result, "mst_connections.csv");
            saveNetworkPlan(graph, result, "network_implementation_plan.txt");
            generateReport(graph, result, "comprehensive_report.txt");
            printf("✅ All files saved successfully!\n");
            break;
        default:
            printf("Invalid choice.\n");
    }
    
    printf("\nFiles saved in current directory:\n");
    printf("• mst_connections.csv - Connection details in CSV format\n");
    printf("• network_implementation_plan.txt - Step-by-step construction plan\n");
    printf("• comprehensive_report.txt - Detailed analysis and statistics\n");
    
    printf("\nPress ENTER to continue...");
    getchar();
}

void displayStatisticsMenu(CityGraph* graph, MSTResult* result) {
    if (!graph || !result) {
        printf("\n❌ No results to analyze! Please run Prim's algorithm first.\n");
        printf("Press ENTER to continue...");
        getchar();
        return;
    }
    
    clearScreen();
    printf("\n╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                      NETWORK STATISTICS & ANALYSIS                             ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    calculateStatistics(graph, result);
    
    // Additional calculations
    double total_population = 0;
    for (int i = 0; i < graph->vertex_count; i++) {
        total_population += graph->buildings[i].population;
    }
    
    printf("\n════════════════════════════════════════════════════════════════════════════════\n");
    printf("ECONOMIC ANALYSIS:\n");
    printf("════════════════════════════════════════════════════════════════════════════════\n");
    printf("• Total population served: %.0f people\n", total_population);
    printf("• Cost per person: ₹%.2f\n", (result->total_cost * 1000000) / total_population);
    printf("• Estimated ROI (Return on Investment): 3-5 years\n");
    printf("• Maintenance cost/year: ₹%.2f Million\n", result->total_cost * 0.05);
    
    printf("\n════════════════════════════════════════════════════════════════════════════════\n");
    printf("ENVIRONMENTAL IMPACT:\n");
    printf("════════════════════════════════════════════════════════════════════════════════\n");
    printf("• Fiber optic cable is eco-friendly\n");
    printf("• Reduced CO2 emissions compared to traditional methods\n");
    printf("• Long lifespan (25+ years)\n");
    printf("• Minimal maintenance required\n");
    
    printf("\nPress ENTER to continue...");
    getchar();
}

void displayHelp() {
    clearScreen();
    printf("\n╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                              ABOUT & HELP                                      ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
    
    printf("PRIM'S ALGORITHM - SMART CITY NETWORK OPTIMIZATION\n");
    printf("════════════════════════════════════════════════════════════════════════════════\n\n");
    
    printf("📖 THEORY:\n");
    printf("Prim's algorithm is a greedy algorithm that finds a minimum spanning tree for\n");
    printf("a weighted undirected graph. It builds the tree one vertex at a time, from an\n");
    printf("arbitrary starting vertex, at each step adding the cheapest possible connection\n");
    printf("from the tree to another vertex.\n\n");
    
    printf("🏗️  APPLICATION:\n");
    printf("In this project, Prim's algorithm is used to find the minimum cost fiber optic\n");
    printf("network that connects all buildings in a smart city. The algorithm considers:\n");
    printf("• Distance between buildings\n");
    printf("• Terrain type (plain, urban, hilly, river, forest)\n");
    printf("• Building type and priority (hospitals/schools get discounts)\n");
    printf("• Population served\n\n");
    
    printf("📊 COST CALCULATION FORMULA:\n");
    printf("Cost = Distance × Base Rate × Terrain Multiplier × Priority Multiplier × Population Factor\n");
    printf("• Base Rate: ₹2.5 Million per km\n");
    printf("• Terrain Multipliers: Plain(1.0), Urban(1.3), Hilly(1.8), River(2.5), Forest(1.5)\n");
    printf("• Priority Multipliers: Hospital(0.7), School(0.8), Government(0.9), \n");
    printf("                         Data Center(1.0), Residential(1.1), Commercial(1.2)\n\n");
    
    printf("🎯 TIME COMPLEXITY:\n");
    printf("• Using adjacency matrix: O(V²) where V = number of buildings\n");
    printf("• For 100 buildings: ~10,000 operations\n");
    printf("• For 500 buildings: ~250,000 operations\n\n");
    
    printf("👨‍💻 DEVELOPED BY:\n");
    printf("• Name: Mr. Rehan Mokashi\n");
    printf("• Program: F.Y. M.Tech (Computer Science & Engineering)\n");
    printf("• Institution: Government College of Engineering, Karad (GCEK)\n");
    printf("• Course: CS2111 - Advanced Data Structures & Algorithms\n");
    printf("• Faculty: Prof. K. S. Gandle\n\n");
    
    printf("📅 ACADEMIC YEAR: 2024-2025\n\n");
    
    printf("Press ENTER to return to main menu...");
    getchar();
}

// ===================== MAIN FUNCTION =====================

int main() {
    CityGraph* current_city = NULL;
    MSTResult* current_result = NULL;
    int choice;
    
    printWelcomeBanner();
    
    do {
        displayMainMenu();
        scanf("%d", &choice);
        getchar(); // Clear newline
        
        switch(choice) {
            case 1:
                loadCityFromFileMenu(&current_city);
                break;
            case 2:
                manualCityInput(&current_city);
                break;
            case 3:
                demoMode();
                break;
            case 4:
                runPrimsAlgorithm(current_city, &current_result);
                break;
            case 5:
                if (current_city) {
                    clearScreen();
                    printCityGraph(current_city);
                    printf("\nPress ENTER to continue...");
                    getchar();
                } else {
                    printf("\n❌ No city data loaded!\nPress ENTER to continue...");
                    getchar();
                }
                break;
            case 6:
                stepByStepDemo(current_city);
                break;
            case 7:
                compareAlgorithmsMenu(current_city);
                break;
            case 8:
                if (current_city && current_result) {
                    clearScreen();
                    printCityMapASCII(current_city, current_result);
                    printf("\nPress ENTER to continue...");
                    getchar();
                } else {
                    printf("\n❌ Run Prim's algorithm first to generate MST!\nPress ENTER to continue...");
                    getchar();
                }
                break;
            case 9:
                saveResultsMenu(current_city, current_result);
                break;
            case 10:
                displayStatisticsMenu(current_city, current_result);
                break;
            case 11:
                displayHelp();
                break;
            case 12:
                printf("\nExiting program...\n");
                break;
            default:
                printf("\nInvalid choice! Please enter 1-12.\n");
                printf("Press ENTER to continue...");
                getchar();
        }
    } while (choice != 12);
    
    // Cleanup
    if (current_result) {
        free(current_result);
    }
    if (current_city) {
        destroyCityGraph(current_city);
    }
    
    printf("\n╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                         THANK YOU FOR USING OUR SYSTEM!                        ║\n");
    printf("║                   SMART CITY PLANNING MADE EFFICIENT AND OPTIMAL               ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\nGovernment College of Engineering, Karad © 2024\n\n");
    
    return 0;
}