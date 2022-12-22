#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int cycle = 1;
int x = 1;
int signalStrength = 0;
int overflow=0;

void drawPixel(){
    int pixelPos = (cycle % 40)-1;
    if(pixelPos+1 == x || pixelPos-1 == x || pixelPos == x){
        printf("#");
    } else{
        printf(".");
    }
}

void executeOperation(char * op,int arg){
    drawPixel();
    if(cycle%40 == 0){
        printf("\n");
    }
    if((cycle + 20)%40 == 0){
        signalStrength += cycle * x;
    }
    if(strcmp(op,"noop")==0){
        cycle++;
    } else if (strcmp(op,"addx")==0){
        cycle++;
        executeOperation("noop",0);
        x += arg;
    }

}

int main() {
    char buff[25];
    char opcode[5];
    int value;
    char *startOfBuff;
    while (fgets(buff,25,stdin) != NULL){
        startOfBuff = buff+4;
        memcpy(opcode,buff,4);
        value = strtol(startOfBuff,NULL,10);
        executeOperation(opcode,value);
    }
    printf("\n%d",signalStrength);
    return 0;
}
