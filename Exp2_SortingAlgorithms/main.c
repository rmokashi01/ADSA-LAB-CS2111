#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

void displayMenu()
{
    printf("\n+--------------------------------------------------------------+\n");
    printf("|                    SORTING ALGORITHMS VISUALIZER             |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("| 1. Merge Sort                                                |\n");
    printf("| 2. Quick Sort                                                |\n");
    printf("| 3. Heap Sort                                                 |\n");
    printf("| 4. All Algorithms                                            |\n");
    printf("| 5. Exit                                                      |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("Enter your choice (1-5): ");
}

void runMergeSort(int arr[], int n)
{
    int arrCopy[n];
    for (int i = 0; i < n; i++) arrCopy[i] = arr[i];
    
    printHeader("MERGE SORT - DIVIDE & CONQUER", arrCopy, n);
    mergeSort(arrCopy, 0, n - 1);
    printFooter();
    printArray(arrCopy, n);
}

void runQuickSort(int arr[], int n)
{
    int arrCopy[n];
    for (int i = 0; i < n; i++) arrCopy[i] = arr[i];
    
    printHeader("QUICK SORT - PARTITION BASED", arrCopy, n);
    quickSort(arrCopy, 0, n - 1);
    printFooter();
    printArray(arrCopy, n);
}

void runHeapSort(int arr[], int n)
{
    int arrCopy[n];
    for (int i = 0; i < n; i++) arrCopy[i] = arr[i];
    
    printHeader("HEAP SORT - BINARY HEAP", arrCopy, n);
    heapSort(arrCopy, n);
    printFooter();
    printArray(arrCopy, n);
}

int main()
{
    int n, choice;
    int *arr = NULL;
    
    printf("\n+--------------------------------------------------------------+\n");
    printf("|                   WELCOME TO SORTING VISUALIZER              |\n");
    printf("+--------------------------------------------------------------+\n");
    
    // Input array
    printf("\nEnter number of elements: ");
    scanf("%d", &n);
    
    arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    
    printf("\nOriginal Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                runMergeSort(arr, n);
                break;
            case 2:
                runQuickSort(arr, n);
                break;
            case 3:
                runHeapSort(arr, n);
                break;
            case 4:
                runMergeSort(arr, n);
                runQuickSort(arr, n);
                runHeapSort(arr, n);
                break;
            case 5:
                printf("\nExiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);
    
    free(arr);
    return 0;
}