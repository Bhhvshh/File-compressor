#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include <stdio.h>

//Function to compress input file and give a new compressed file
//Return 1 for success and 0 for failure
int compress(FILE *in, FILE * out);

//Function to decompress input file and give a new compressed file
//Return 1 for success and 0 for failure
int decompress(FILE * in, FILE* out);

#endif