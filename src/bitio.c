#include<stdlib.h>
#include<stdio.h>
#include "../include/bitio.h"


BitWriter* createBitWriter(FILE * file){
    BitWriter* bw = malloc(sizeof(*bw));
    if(!bw){
        perror("Failed to allocate memory to bitwriter");
        return NULL;
    }

    bw->file = file;
    bw->buffer = 0;
    bw->bitCount = 0;

    return bw;

}

void bitbybitOutput(BitWriter* bw, int bit){
    bw->buffer = (bw->buffer << 1) | bit;
    bw->bitCount++;
    
    //Write when there are exactly 8 bits in buffer
    if(bw->bitCount == 8){
        fputc(bw->buffer,bw->file);
        bw->buffer = 0;
        bw->bitCount = 0;

    }

}

int bitbybitInput(BitWriter *bw){
    //Read one byte when buffer is empty
    if(bw->bitCount==0){
        int c;//buffer is 8 bit unsigned int so we need extra int to check if it is end of the file
        if((c = fgetc(bw->file)) == EOF) return -1;
        bw->buffer = c;
        bw->bitCount= 8;
    }
    
    //extract first bit from buffer and shift it to right
    int bit = (bw->buffer>>7);
    bw->buffer<<=1;
    bw->bitCount--;

    return bit;
}


