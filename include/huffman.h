#ifndef HUFFMAN_H
#define HUFFMAN_H


#include<stdio.h>
#include "config.h"

//Huffman node
typedef struct Node{
    int data;
    int freq;
    struct Node *left;
    struct Node *right;
} Node;

//To store prefix codes of huffman algorithm
typedef struct PrefixCodes{
    int len;
    char* code;
} PrefixCodes;


//To create huffman node with given data
//Returns NULL on failure
Node* createHuffmanNode(int data, int freq);

//Builds huffman tree
//Returns Root of the huffman tree
Node* huffmanTreeBuiler(int freqArray[MAX_UNIQUE_BYTES]);

//Generate huffman code using huffman tree, store in prefixCodes array
void huffmanCodeGenerator(PrefixCodes codes[MAX_UNIQUE_BYTES], Node *root);

//To free memory allocated to huffman tree
void huffmanFreeTree(Node * root);

//To free memory allocated to code inside every prefixCodes
//It should be initialized to null at start to avoid trying to free random locations
void freePrefixCodes(PrefixCodes codes[MAX_UNIQUE_BYTES]);

//To encode and decode using huffman prefix codes
int huffmanEncode(FILE *in,FILE *out, PrefixCodes codes[MAX_UNIQUE_BYTES],int *freqArray);
int huffmanDecode(FILE *in, FILE *out,Node *root, PrefixCodes codes[MAX_UNIQUE_BYTES], int bitCounter);








#endif