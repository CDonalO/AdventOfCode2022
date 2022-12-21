#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hashmap.h"

void executeMove(int n,char dir,int index);

typedef struct coords{
    int x;
    int y;
}knot;

enum {knotCount=10};


knot knots[knotCount];
map * m[knotCount];


void moveTail(int index){
    if (index == knotCount-1){
        return;
    }
    addKey(knots[index+1].x,knots[index+1].y,1,m[index+1]);
    int xDif = knots[index].x-knots[index+1].x;
    int yDif = knots[index].y-knots[index+1].y;
    if (xDif >= 2){
        knots[index+1].x = knots[index].x-1;
        if (yDif == 1 || yDif == -1){
            knots[index+1].y += yDif;
        }
    }else if (xDif <= -2){
        knots[index+1].x = knots[index].x+1;
        if (yDif == 1 || yDif == -1){
            knots[index+1].y += yDif;
        }
    }

    if (yDif >= 2){
        knots[index+1].y = knots[index].y-1;
        if (xDif == 1 || xDif == -1){
            knots[index+1].x += xDif;
        }
    } else if (yDif <= -2){
        knots[index+1].y = knots[index].y+1;
        if (xDif == 1 || xDif == -1){
            knots[index+1].x += xDif;
        }
    }
    moveTail(index+1);
}

void executeMove(int n,char dir,int index){
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
        knots[index].x += xOffset;
        knots[index].y += yOffset;
        moveTail(index);
    }
}

void countVisited(int * sum,int knot){
    addKey(knots[knot].x,knots[knot].y,1,m[knot]);
    kv * current = NULL;
    for (int i = 0; i < m[knot]->capacity; i++) {
        current = &m[knot]->map[i];
        while (current != NULL){
            *sum += current->value;
            current = current->next;
        }
    }
}

void init(){
    for (int i = 0; i < knotCount; i++) {
        m[i] = createMap(300);
        knots[i].x = 0;
        knots[i].y = 0;
    }
}

int main() {
    init();
    char buff[25];
    char move;
    int amount;
    char * startOfBuff;
    while (fgets(buff,25,stdin)){
        startOfBuff = buff;
        move = buff[0];
        startOfBuff++;
        amount = strtol(startOfBuff,NULL,10);
        executeMove(amount,move,0);
    }
    amount = 0;
    // Alter KnotCount and knot for different parts
    countVisited(&amount,9);
    printf("\n%d",amount);
    return 0;
}
