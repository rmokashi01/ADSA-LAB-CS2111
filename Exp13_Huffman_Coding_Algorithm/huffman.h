#ifndef HUFFMAN_H
#define HUFFMAN_H

#define MAX_TREE_HEIGHT 100
#define MAX_CHAR 256

// Huffman tree node
typedef struct MinHeapNode {
    char data;                      // character
    int freq;                       // frequency
    struct MinHeapNode *left, *right;
} MinHeapNode;

// Min Heap structure
typedef struct MinHeap {
    int size;
    int capacity;
    MinHeapNode** array;
} MinHeap;

MinHeapNode* newNode(char data, int freq);
MinHeap* createMinHeap(int capacity);
void insertMinHeap(MinHeap* minHeap, MinHeapNode* node);
MinHeapNode* extractMin(MinHeap* minHeap);
void buildMinHeap(MinHeap* minHeap);
MinHeapNode* buildHuffmanTree(const char text[]);
void printCodes(MinHeapNode* root, int arr[], int top);

#endif
