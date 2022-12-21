#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashmap.h"

int headX = 0;
int headY = 0;
int tailX = 0;
int tailY = 0;
map * m;

bool checkIfTailNearby(){
    int xDif = abs(headX-tailX);
    int yDif = abs(headY-tailY);
    if(xDif<=1 && xDif >= 0 && yDif<=1 && yDif >=0){
        return true;
    }
    return false;
}

void executeMove(int n,char dir){
    int xOffset = 0;
    int yOffset = 0;
    if(dir == 'U'){
        yOffset = 1;
    }else if(dir == 'D'){
        yOffset = -1;
    } else if(dir == 'L'){
        xOffset = -1;
    } else if(dir == 'R'){
        xOffset = 1;
    }

    for (int i = 0; i < n; i++) {
        headX += xOffset;
        headY += yOffset;
        if (!checkIfTailNearby()){
            addKey(tailX,tailY,1,m);
            tailX = headX-xOffset;
            tailY = headY-yOffset;
        }
    }
}

void countVisited(int * sum){
    kv * current = NULL;
    for (int i = 0; i < m->capacity; i++) {
        current = &m->map[i];
        while (current != NULL){
            *sum += current->value;
            current = current->next;
        }
    }
}

int main() {
    m = createMap(300);
    char buff[25];
    char move;
    int amount;
    int c = 0;
    char * startOfBuff;
    while (fgets(buff,25,stdin)){
        c++;
        if (c == 922){
            c = 922;
        }
        startOfBuff = buff;
        move = buff[0];
        startOfBuff++;
        amount = strtol(startOfBuff,NULL,10);
        executeMove(amount,move);
        printf("%d %s ",c,buff);
    }
    amount = 0;
    countVisited(&amount);
    printf("%d",amount+1);
    return 0;
}
