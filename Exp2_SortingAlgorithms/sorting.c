#include <stdio.h>
#include "sorting.h"

// ================= PRINT UTILITY =================
void printArrayStep(const char *msg, int arr[], int n)
{
    printf("| %-25s| ", msg);
    for (int i = 0; i < n; i++)
        printf("%3d ", arr[i]);
    printf("|\n");
}

void printDivider(void)
{
    printf("+---------------------------");
    for (int i = 0; i < 50; i++) printf("-");
    printf("+\n");
}

void printHeader(const char *title, int arr[], int n)
{
    printf("\n");
    printf("+--------------------------------------------------------------+\n");
    printf("| %-60s |\n", title);
    printf("+---------------------------");
    for (int i = 0; i < 50; i++) printf("-");
    printf("+\n");
    printf("| STEP                      | ARRAY ELEMENTS                  |\n");
    printf("+---------------------------");
    for (int i = 0; i < 50; i++) printf("-");
    printf("+\n");
    printArrayStep("Original Array", arr, n);
}

void printFooter(void)
{
    printf("+---------------------------");
    for (int i = 0; i < 50; i++) printf("-");
    printf("+\n\n");
}

// ================= MERGE SORT =================
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    
    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    
    char msg[50];
    sprintf(msg, "Merge [%d-%d] & [%d-%d]", l, m, m+1, r);
    printArrayStep(msg, arr + l, r - l + 1);
    
    int i = 0, j = 0, k = l;
    
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    
    while (i < n1)
        arr[k++] = L[i++];
    
    while (j < n2)
        arr[k++] = R[j++];
    
    printArrayStep("After Merge", arr + l, r - l + 1);
    printDivider();
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        
        char msg[50];
        sprintf(msg, "Split [%d-%d] at %d", l, r, m);
        printArrayStep(msg, arr + l, r - l + 1);
        
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        
        merge(arr, l, m, r);
    }
}

// ================= QUICK SORT =================
int partitionQS(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    
    char msg[50];
    sprintf(msg, "Partition [%d-%d], pivot=%d", low, high, pivot);
    printArrayStep(msg, arr + low, high - low + 1);
    
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            
            if (i != j) {
                sprintf(msg, "Swap %d <-> %d", arr[i], arr[j]);
                printArrayStep(msg, arr + low, high - low + 1);
            }
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    sprintf(msg, "Place pivot at %d", i + 1);
    printArrayStep(msg, arr + low, high - low + 1);
    
    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partitionQS(arr, low, high);
        
        char msg[50];
        sprintf(msg, "Pivot position: %d", pi);
        printArrayStep(msg, arr + low, high - low + 1);
        printDivider();
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ================= HEAP SORT =================
void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        
        char msg[50];
        sprintf(msg, "Heapify: swap %d <-> %d", arr[i], arr[largest]);
        printArrayStep(msg, arr, n);
        
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    printArrayStep("Start Heap Sort", arr, n);
    
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
    printArrayStep("Max Heap Built", arr, n);
    printDivider();
    
    // Extract elements from heap
    for (int i = n - 1; i >= 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        char msg[50];
        sprintf(msg, "Extract max: %d", temp);
        printArrayStep(msg, arr, n);
        
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n)
{
    printf("+--------------------------------------------------------------+\n");
    printf("| FINAL SORTED ARRAY:                                          |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("| ");
    for (int i = 0; i < n; i++)
        printf("%3d ", arr[i]);
    printf(" |\n");
    printf("+--------------------------------------------------------------+\n");
}