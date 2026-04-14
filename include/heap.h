#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

//forward declaration
typedef struct Node Node;//Avoids cyclic dependency


typedef struct MinHeap{
    size_t size;
    size_t capacity;
    Node ** heap;
} MinHeap;


//To create a new minHeap with given capacity
MinHeap * createMinHeap(int capacity);

//To insert node in minheap
//Return 1 on success 0 on failure
int insertNode(MinHeap* minHeap, Node* node);

//Return node at top of heap
//Return NULL if heap is empty
Node* peakMinHeap(MinHeap* minHeap);

//To pop top node in heap
//Returns 1 on success 0 on failure
int popMinHeap(MinHeap* minHeap);

//To free memory allocated to heap
void destroyMinHeap(MinHeap* minHeap);









#endif