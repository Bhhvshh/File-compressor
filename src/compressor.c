#include<stdio.h>
#include<stdlib.h>
#include "../include/huffman.h"
#include "../include/fileformat.h"


int compress(FILE* in, FILE* out){
    
    int freqArray[MAX_UNIQUE_BYTES] = {0};
    PrefixCodes codes[MAX_UNIQUE_BYTES];
    int c;

    //frequency counting of input file
    while((c = fgetc(in))!=EOF){
        c = (unsigned char) c;
        freqArray[c]++;

    }
    // fseek(in,0,SEEK_SET);
    
    //Build huffman tree
    Node* root = huffmanTreeBuiler(freqArray);

    //Generate huffman prefix codes
    for(int i = 0 ;i<MAX_UNIQUE_BYTES;i++) 
       codes[i].code = NULL; //initialize every code to NULL, Avoids problems which can happen when you try to free the memory
    
    huffmanCodeGenerator(codes,root);

    if(huffmanEncode(in,out,codes,freqArray)==0) return 0;
    
    huffmanFreeTree(root);
    freePrefixCodes(codes);

    return 1;


}

int decompress(FILE* in, FILE* out){
  
    
    FileHeader* fh = malloc(sizeof(*fh));
    PrefixCodes codes[MAX_UNIQUE_BYTES];
    
    //read file header
    if(readFileHeader(fh,in)==0) return 0;

    //To check if file is really compressed by our program
    if(fh->specialNumber != SPECIAL_NUMBER){
        printf("Invalid file: this file is not compressed by this program\n");
        printf("you can only decompres files compressed by this program\n");
        return 0;
    }
    
    int bitCounter = fh->bitCounter;
    // printf("Bitcounter %d\n",bitCounter);
    
    //Build huffman tree
    Node* root = huffmanTreeBuiler(fh->freqCount);
    
    //Generate prefix codes
    
    for(int i = 0 ;i<MAX_UNIQUE_BYTES;i++) 
        codes[i].code = NULL;  //initialize every code to NULL, Avoids problems which can happen when you try to free the memory

    huffmanCodeGenerator(codes,root);


    // for(int i = 0;i<MAX_UNIQUE_BYTES;i++){
    //     if(codes[i].code) printf("%c %s\n",(unsigned char)i, codes[i].code);
    // }


    if(huffmanDecode(in,out,root,codes,bitCounter) == 0) return 0;
    
    huffmanFreeTree(root);
    freePrefixCodes(codes);

    free(fh);







    return 1;
}