#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../include/compressor.h"



int main(int arg, char * argv[]){

    if(arg<4){
        printf("There should be exactly four commadline arguments\n Usage: <executable> compress/decompress <file1> <file2> \n\n");
        return 0;
    }

    char *inputFile = argv[2];
    char *outputFile = argv[3];

    FILE* in = fopen(inputFile,"r+b");
    if(!in){
        perror("opening file failed:arg[2]\n");
        return 0;
    }


    FILE* out = fopen(outputFile,"wb");
    if(!out){
        perror("opening file failed2");
        return 0;
    }
    fclose(out);


    out = fopen(outputFile,"r+b");
    if(!out){
        perror("opening file failed3");
        return 0;
    }

    if(strcmp(argv[1],"compress")==0){
        printf("This will take few seconds...\n\n");


        if(compress(in,out)) printf("+Compressed\n");
        else printf("-Failed to compress\n");
       
    }
    else if(strcmp(argv[1],"decompress")==0){
        printf("This will take few seconds...\n\n");

        if(decompress(in,out)) printf("+Decompressed\n");
        else printf("-Failed to decompress\n");
    }
    else{
        printf("-Error: Invalid command\n");
        return 0;
    }
    
    fclose(in);
    fclose(out);


    return 0;
}