#include<stdlib.h>
#include<stdio.h>
#include "../include/heap.h"
#include "../include/huffman.h"



void swapNodes(Node** a, Node** b){
    Node* tmp = *a;
    *a = *b;
    *b = tmp;
}

MinHeap * createMinHeap(int capacity){
    MinHeap* minHeap = malloc(sizeof(*minHeap));
    if(!minHeap){
        perror("Failed to allocate memory to heap");
        return NULL;
    }

    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->heap = malloc(sizeof(Node*) * capacity);

    if(!(minHeap->heap)){
        perror("Failed to allocate memory to heap array");
        free(minHeap);
        return NULL;
    }

    return minHeap;
}
     
int insertNode(MinHeap* minHeap, Node* node){
    
    if(minHeap->size>=minHeap->capacity) return 0;//heap is full

    minHeap->heap[minHeap->size] = node;
    minHeap->size++;

    int index = minHeap->size - 1;

    //heapify bottom to up
    while(index > 0 && (minHeap->heap[(index-1)/2])->freq > (minHeap->heap[index])->freq){
        swapNodes(&(minHeap->heap[index]), &(minHeap->heap[(index -1)/2]));
        index = (index - 1)/2;
    }




    return 1;
}

Node* peakMinHeap(MinHeap* minHeap){
    if(minHeap->size == 0) return NULL;
    return minHeap->heap[0];
}


int popMinHeap(MinHeap* minHeap){
    int index = 0;
    int size = minHeap->size;
    if(size==0) return 0;//heap is empty

    minHeap->heap[0] = minHeap->heap[minHeap->size - 1];
    minHeap->size--;

    
    while(2*index+1 <size){
        int smallest = index;

        if((minHeap->heap[2*index +1])->freq < (minHeap->heap[smallest])->freq){
            smallest = 2*index + 1;
        }

        if(2*index + 2 < size && (minHeap->heap[2*index + 2])->freq < (minHeap->heap[smallest])->freq){
            smallest = 2*index + 2;
        }

        if(smallest==index) break;

        swapNodes(&(minHeap->heap[index]),&(minHeap->heap[smallest]));
        index = smallest;
    }

    return 1;

    
}


void destroyMinHeap(MinHeap* minHeap){

    if(minHeap) free(minHeap->heap);
    free(minHeap);

}

