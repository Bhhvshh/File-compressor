#ifndef FILE_FORMAT_H
#define FILE_FORMAT_H

#include "config.h"

typedef struct FileHeader{
    int specialNumber; //Will be used to identify if it is really a compressed file or not and what is format of file
    int bitCounter;    //Number of bits compressed(written in compressed file)
    int freqCount[MAX_UNIQUE_BYTES];//Frequency of every character to decode/decompress compressed file 
    //Will use serialized huffman tree in place of this for smaller size and better performance
} FileHeader;

//To create a new file header with given data
//can be freed by caller
FileHeader* createFileHeader(int specialNumber, int bitCounter,int *freqArray);

//Reads header(as fileheader format) from file
//Uses fseek to go to the top of file and read header
//Return 1 on success and 0 on failure
int readFileHeader(FileHeader* fh, FILE* file);

//Reads header(as fileheader format) from file
//Uses fseek to go to the top of file and read header
//Return 1 on success and 0 on failure
int writeFileHeader(FileHeader* fh, FILE* file);

#endif