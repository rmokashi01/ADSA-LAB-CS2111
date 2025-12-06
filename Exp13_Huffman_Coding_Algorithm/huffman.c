#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

// Create new tree node
MinHeapNode* newNode(char data, int freq) {
    MinHeapNode* node = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

// Create min heap
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (MinHeapNode**)malloc(heap->capacity * sizeof(MinHeapNode*));
    return heap;
}

// Swap helper
void swap(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

// Min heapify
void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;

    if (left < heap->size && heap->array[left]->freq < heap->array[smallest]->freq)
        smallest = left;

    if (right < heap->size && heap->array[right]->freq < heap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

// Insert node into heap
void insertMinHeap(MinHeap* heap, MinHeapNode* node) {
    heap->size++;
    int i = heap->size - 1;

    while (i && node->freq < heap->array[(i - 1)/2]->freq) {
        heap->array[i] = heap->array[(i - 1)/2];
        i = (i - 1) / 2;
    }

    heap->array[i] = node;
}

// Extract min node
MinHeapNode* extractMin(MinHeap* heap) {
    MinHeapNode* temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return temp;
}

// Build min heap
void buildMinHeap(MinHeap* heap) {
    int n = heap->size - 1;
    for (int i = (n - 1)/2; i >= 0; i--)
        minHeapify(heap, i);
}

// Build Huffman tree
MinHeapNode* buildHuffmanTree(const char text[]) {
    int freq[MAX_CHAR] = {0};
    
    // Count frequencies
    for (int i = 0; text[i] != '\0'; i++)
        freq[(unsigned char)text[i]]++;

    // Count unique characters
    int unique = 0;
    for (int i = 0; i < MAX_CHAR; i++)
        if (freq[i] > 0) unique++;

    MinHeap* heap = createMinHeap(unique);

    for (int i = 0; i < MAX_CHAR; i++)
        if (freq[i] > 0)
            heap->array[heap->size++] = newNode((char)i, freq[i]);

    buildMinHeap(heap);

    // Build tree
    while (heap->size > 1) {
        MinHeapNode* left = extractMin(heap);
        MinHeapNode* right = extractMin(heap);

        MinHeapNode* merged = newNode('$', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        insertMinHeap(heap, merged);
    }

    return extractMin(heap);
}

// Print Huffman codes
void printCodes(MinHeapNode* root, int arr[], int top) {
    if (!root) return;

    if (root->data != '$') {
        printf("Character '%c' → Code: ", root->data);
        for (int i = 0; i < top; i++)
            printf("%d", arr[i]);
        printf("\n");
    }

    arr[top] = 0;
    printCodes(root->left, arr, top + 1);

    arr[top] = 1;
    printCodes(root->right, arr, top + 1);
}
