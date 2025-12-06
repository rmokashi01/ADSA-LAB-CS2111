#include "prims.h"

int main() {
    // Create a simple test city
    CityGraph* city = createCityGraph("Test City", 10);
    
    // Add some buildings
    addBuilding(city, 0, "Data Center", 0.0, 0.0, DATA_CENTER, 100);
    addBuilding(city, 1, "Hospital A", 1.0, 1.0, HOSPITAL, 500);
    addBuilding(city, 2, "School B", 2.0, 0.0, SCHOOL, 300);
    
    // Add connections
    addConnection(city, 0, 1, PLAIN, true);
    addConnection(city, 0, 2, URBAN, true);
    addConnection(city, 1, 2, HILLY, true);
    
    // Print city info
    printCityGraph(city);
    
    // Run Prim's algorithm
    MSTResult* result = primMST(city, 0);
    
    // Print results
    printMSTResult(city, result);
    
    // Cleanup
    free(result);
    destroyCityGraph(city);
    
    return 0;
}