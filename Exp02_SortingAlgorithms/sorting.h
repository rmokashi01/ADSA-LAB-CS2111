#ifndef SORTING_H
#define SORTING_H

// Sorting algorithms
void mergeSort(int arr[], int l, int r);
void quickSort(int arr[], int low, int high);
void heapSort(int arr[], int n);

// Visualization functions
void printArray(int arr[], int n);
void printArrayStep(const char *msg, int arr[], int n);
void printDivider(void);
void printHeader(const char *title, int arr[], int n);
void printFooter(void);

// Helper functions for sorting algorithms
int partitionQS(int arr[], int low, int high);
void merge(int arr[], int l, int m, int r);
void heapify(int arr[], int n, int i);

#endif