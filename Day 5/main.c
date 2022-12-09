#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"


enum {initSize=50};
stack **stacks;
int capacity = 0;

void initialiseStack(char str[]){
    int size = strlen(str)/4;
    stacks = malloc(sizeof(stack)*size);
    capacity = size;
    for(int i = 0;i<capacity;i++){
        *(stacks+i) = createStack(initSize);
    }
}

void processLine(char line[]){
    int pos = 0;
    for (int i =1;i< strlen(line);i+=4){
        char aaa = line[i];
        if(isalpha(line[i])){
            push(line[i],*(stacks+pos));
        }
        pos++;
    }
}

void processSingleMove(char move[]){
    int moves = 0;
    int src = 0;
    int dst = 0;
    char * remaining;
    char * c = strchr(move,' ');
    moves = strtol(c,&remaining,10);
    remaining +=1;
    remaining = strchr(remaining,' ');
    src = strtol(remaining,&remaining,10);
    remaining +=1;
    remaining = strchr(remaining, ' ');
    dst = strtol(remaining,&remaining,10);
    for(int i =0;i<moves;i++){
        push(pop(*(stacks+src-1)),*(stacks+dst-1));
    }
}

void processMultiMove(char move[]){
    int moves = 0;
    int src = 0;
    int dst = 0;
    char * remaining;
    char * c = strchr(move,' ');
    moves = strtol(c,&remaining,10);
    remaining +=1;
    remaining = strchr(remaining,' ');
    src = strtol(remaining,&remaining,10);
    remaining +=1;
    remaining = strchr(remaining, ' ');
    dst = strtol(remaining,&remaining,10);

    stack *temp = createStack(initSize);
    for(int i =0;i<moves;i++){
        push(pop(*(stacks+src-1)),temp);
    }
    for(int i=0;i<moves;i++){
        push(pop(temp),*(stacks+dst-1));
    }
    free(temp);
}

int main() {
    char buff[255];
    bool init = false;
    while (fgets(buff,255,stdin) != NULL && buff[0] != '\n'){
        if(!init){
            initialiseStack(buff);
            init = true;
        }
        processLine(buff);
        printf("%s",buff);
    }
    for(int i =0;i<capacity;i++){
        *(stacks+i) = reverseStack(*(stacks+i));
    }
    while (fgets(buff,255,stdin) != NULL){
//        Part 1
//        processSingleMove(buff);
//        Part 2
        processMultiMove(buff);
    }

    for(int i =0;i<capacity;i++){
        printf("[%c] ", peek(*(stacks+i)));
    }
    for(int i =0;i<capacity;i++){
        free(*(stacks+i));
    }
    free(stacks);

    return 0;
}
