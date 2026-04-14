#ifndef BITIO_H
#define BITIO_H

#include <stdint.h>
#include<stdio.h>

//Will act as buffer to write bit by bit as machine writes byte by byte
typedef struct BitWriter{
    FILE* file; //File where we write/read
    uint8_t buffer; //8 bit buffer
    int bitCount;
   

} BitWriter;

//To create a new bitwriter
//It is dynamically allocated so can be freed by caller
//can be  used as buffer to read as well
BitWriter* createBitWriter(FILE * file);

//To read bit by bit from file
int bitbybitInput(BitWriter * bw);
//To write bit by bit in file
void bitbybitOutput(BitWriter* bw,int bit);


#endif