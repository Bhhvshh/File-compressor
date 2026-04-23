#include<stdio.h>
#include<stdlib.h>
#include "../include/fileformat.h"
#include "../include/huffman.h"


FileHeader* createFileHeader(int specialNumber, int bitCounter,int *freqArray){
    FileHeader* fh = malloc(sizeof(*fh));
    if(!fh){
        perror("Failed to allocate memory:");
        return NULL;
    }

    fh->specialNumber =  specialNumber;
    fh->bitCounter = bitCounter;
    for(int i = 0;i<MAX_UNIQUE_BYTES;i++ ){
        fh->freqCount[i] = freqArray[i];
    }

    return fh;
}

int readFileHeader(FileHeader* fh, FILE* file){
    fseek(file,0,SEEK_SET);  // go to start of file before reading header
    if(fread(fh,sizeof(*fh),1,file)<1) return 0;
    return 1;
}


int writeFileHeader(FileHeader* fh, FILE* file){
    fseek(file,0,SEEK_SET); // GO to start of the file before writing header
    if(fwrite(fh,sizeof(*fh),1,file)<1) return 0;

    return 1;
}