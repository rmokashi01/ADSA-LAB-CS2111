#include <stdio.h>
#include <string.h>
#include "huffman.h"

int main() {
    char text[500];

    printf("\n===== Experiment 13 - Huffman Coding Algorithm =====\n");
    printf("Enter text to compress (e.g., a medical report line):\n");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    MinHeapNode* root = buildHuffmanTree(text);

    printf("\nHuffman Codes for Each Character:\n");
    int arr[MAX_TREE_HEIGHT];
    printCodes(root, arr, 0);

    return 0;
}
