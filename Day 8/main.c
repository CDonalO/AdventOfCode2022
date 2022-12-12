#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum {rows=99,columns=99};
int grid[rows][columns];

int checkSurroundings(int y,int x){
    int height = grid[y][x];
    bool left = false;
    for (int i = x-1; i >=0 ; i--) {
        if(grid[y][i] >= height){
            left = true;
            break;
        }
    }
    if(!left){
        return 1;
    }

    bool right = false;
    for (int i = x+1; i<columns ; i++) {
        if(grid[y][i] >= height){
            right = true;
            break;
        }
    }
    if(!right){
        return 1;
    }

    bool up = false;
    for (int i = y+1; i<rows ; i++) {
        if(grid[i][x] >= height){
            up = true;
            break;
        }
    }
    if(!up){
        return 1;
    }

    bool down = false;
    for (int i = y-1; i >=0 ; i--) {
        if(grid[i][x] >= height){
            down = true;
            break;
        }
    }
    if(!down){
        return 1;
    }

    return 0;
}

void findVisibleTrees(int* sum){
    for (int i = 1; i < rows-1; i++) {
        for (int j = 1; j < columns-1; j++) {
            *sum += checkSurroundings(i,j);
        }
    }
}

int calculateScenicScore(int y,int x){
    int up = y;
    int down =rows-1-y;
    int left =x;
    int right =columns-1-x;
    int height = grid[y][x];

    for (int i = x-1; i >=0 ; i--) {
        int num = grid[y][i];
        if(grid[y][i] >= height){
            left = x-i;
            break;
        }
    }


    for (int i = x+1; i<columns ; i++) {
        int num = grid[y][i];
        if(grid[y][i] >= height){
            right=i-x;
            break;
        }
    }

    for (int i = y+1; i<rows ; i++) {
        int num = grid[i][x];
        if(grid[i][x] >= height){
            down = i-y;
            break;
        }
    }



    for (int i = y-1; i >=0 ; i--) {
        int num = grid[i][x];
        if(grid[i][x] >= height){
            up = y-i;
            break;
        }
    }


    return up*down*left*right;
}

void getHighestScenicScore(int* highestScore){
    for (int i = 1; i < rows-1; i++) {
        for (int j = 1; j < columns-1; j++) {
            int num = grid[i][j];
            int score = calculateScenicScore(i,j);
            if(score > *highestScore){
                *highestScore = score;
            }
        }
    }
}

int main() {
    char buff[110];
    int row = 0;
    int highestScenicScore = 0;
    int visibleTrees = columns*2 + rows*2-4;
    while (fgets(buff,110,stdin)!=NULL){
        char * pos = buff;
        for (int i = 0; i < strlen(buff); i++) {
            char num[2];
            memcpy(num,pos,1);
            grid[row][i] = strtol(num,NULL,10);
            pos +=1;
        }
        row++;
    }
    findVisibleTrees(&visibleTrees);
    getHighestScenicScore(&highestScenicScore);
    printf("%d\n",visibleTrees);
    printf("%d",highestScenicScore);
    return 0;
}
