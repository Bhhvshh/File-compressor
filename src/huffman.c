#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "../include/huffman.h"
#include "../include/heap.h"
#include "../include/fileformat.h"
#include "../include/bitio.h"


char *strndup(const char *src, size_t n) {
    char *dest = malloc(n + 1);
    if (!dest) return NULL;

    memcpy(dest, src, n);
    dest[n] = '\0';
    return dest;
}

Node* createHuffmanNode(int data ,int freqValue){
    Node* newNode = malloc(sizeof(*newNode));
    if(!newNode){
        perror("Failed to create a node");
        return NULL;
    }

    newNode->data = data;
    newNode->freq = freqValue;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* huffmanTreeBuiler(int freqArray[MAX_UNIQUE_BYTES]){

    MinHeap* minHeap = createMinHeap(MAX_UNIQUE_BYTES);

    for(int i = 0;i<MAX_UNIQUE_BYTES;i++){
        if(freqArray[i]) insertNode(minHeap,createHuffmanNode(i,freqArray[i]));
    }

    //huffman  coding algorithm

    while(minHeap->size > 1){
        Node* node1 = peakMinHeap(minHeap);
        popMinHeap(minHeap);
        Node* node2 = peakMinHeap(minHeap);
        popMinHeap(minHeap);

        int sumFreq = node1->freq + node2->freq;
        Node* parentNode = createHuffmanNode(-1,sumFreq);
        parentNode->left = node1;
        parentNode->right = node2;

        insertNode(minHeap,parentNode);
    }


    Node* root = peakMinHeap(minHeap);

    destroyMinHeap(minHeap);

    return root;


}

int isLeaf(Node * node){
    return (!node->left) && (!node->right);
}

//Helps to generate prefix codes
void helperCodeGenerator(PrefixCodes codes[MAX_UNIQUE_BYTES], Node* root,char *currCode, int index){
    if(!root) return;
    if(isLeaf(root)){
        currCode[index] = '\0';
        codes[root->data].len = index;
        codes[root->data].code = strndup(currCode,index);
        return;
    }
    currCode[index] = '0';
    helperCodeGenerator(codes,root->left,currCode,index + 1);
    currCode[index] = '1';
    helperCodeGenerator(codes,root->right,currCode,index + 1);

}


void huffmanCodeGenerator(PrefixCodes codes[MAX_UNIQUE_BYTES], Node* root){
    if(root==NULL) return;

     if(isLeaf(root)){
        codes[root->data].len = 1;
        codes[root->data].code = strndup("0",1);
        return;
     }

     char currCode[MAX_UNIQUE_BYTES + 1];


     helperCodeGenerator(codes,root,currCode,0);

    





}

void huffmanFreeTree(Node* root){
    if(!root || isLeaf(root)){
        free(root);
        return;
    }

    huffmanFreeTree(root->left);
    huffmanFreeTree(root->right);
    free(root);
}

void freePrefixCodes(PrefixCodes codes[MAX_UNIQUE_BYTES]){
    for(int i = 0;i<MAX_UNIQUE_BYTES;i++)
     free(codes[i].code);


}

//we are using freqArray in header which is not optimal we will change it later
int huffmanEncode(FILE* in, FILE* out,PrefixCodes codes[MAX_UNIQUE_BYTES],int *freqArray){

    FileHeader* fp = createFileHeader(0,0,freqArray); //To ensure there is space to write header after encoding the data in file
    writeFileHeader(fp,out);
    free(fp);
    fp = NULL;//Best practic or something

    // BitWriter* br = createBitWriter(in);
    BitWriter* bw = createBitWriter(out);
    
    int byte;
    int bitCounter = 0;
    
    
    fseek(in,0,SEEK_SET);  //To start reading from start
    while((byte = fgetc(in)) != EOF){

        byte = (unsigned char) byte;

        for(int i = 0;i< codes[byte].len;i++){
        int bit = (codes[byte].code[i] == '1') ? 1 : 0;
        bitbybitOutput(bw, bit);
        bitCounter++;
        }
    }
    //write remaining bits in buffer
    if(bw->bitCount> 0 && bw->bitCount<8){
        bw->buffer<<=(8 - bw->bitCount);
        
        fputc(bw->buffer,out);
        bw->buffer = 0;
        bw->bitCount = 0;
    }

    // printf("Bitcounter in encode: %d",bitCounter);

    //write new header with bitCounter data
    fp = createFileHeader(SPECIAL_NUMBER,bitCounter,freqArray);
    if(writeFileHeader(fp,out)==0) return 0;


    // free(br);
    free(bw);
    free(fp);

    return 1;



    
}


//not a optimal way to do it
// this is suppose to be updated we will store serialized tree in header and use it to decode
int huffmanDecode(FILE *in, FILE *out,Node *root,PrefixCodes codes[MAX_UNIQUE_BYTES],int  bitCounter){
  
     BitWriter* br = createBitWriter(in);
     char buffer[MAX_UNIQUE_BYTES];
     buffer[0] = '\0';
     int index = 0;

    //  printf("%d\n",bitCounter);
    for(int i = 0;i<bitCounter;i++){
        int bit = bitbybitInput(br);
        buffer[index] = bit ? '1' : '0';
        buffer[index+1] = '\0';
        index++;

        // printf("bit %d\n",bit);

        for(int j = 0;j<MAX_UNIQUE_BYTES;j++){
            if(codes[j].code && strcmp(codes[j].code,buffer)==0){
                fputc((unsigned char)j,out);
                // printf("%c\n",(unsigned char)j);
                index = 0;
                break;
            }
        }
    }

    // fputc('a',out);
    free(br);



    return 1;
}