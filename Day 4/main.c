#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void rangeIntoInt(char range[],int* low,int* high){
    char* right;
    *low = strtol(range,&right,10);
    *high = strtol(right,&right,10);
    *high *=-1;
}

int checkFullOverlap(char section1[],char section2[]){
    int s1Low = 0;
    int s1High = 0;
    int s2Low = 0;
    int s2High = 0;
    rangeIntoInt(section1,&s1Low,&s1High);
    rangeIntoInt(section2,&s2Low,&s2High);
    if(s1Low >= s2Low && s1High <= s2High){
        return 1;
    } else if(s2Low >= s1Low && s2High <= s1High){
        return 1;
    }
    return 0;
}

int checkOverlap(char section1[],char section2[]){
    int s1Low = 0;
    int s1High = 0;
    int s2Low = 0;
    int s2High = 0;
    rangeIntoInt(section1,&s1Low,&s1High);
    rangeIntoInt(section2,&s2Low,&s2High);

    if(s1Low <= s2High && s2Low <= s1High){
        return 1;
    }
    return 0;
}

int main() {
    int fullOverlaps = 0;
    int overlaps = 0;
    char buff[255];
    char left[100];
    char right[100];

    while(fgets(buff,255,stdin)!= NULL){
        char *c = strtok(buff, ",");
        strcpy(left,c);
        c = strtok(NULL,",");
        strcpy(right,c);
        if(right[strlen(c)-1] == '\n'){
            right[strlen(c)-1] = '\000';
        }
        fullOverlaps += checkFullOverlap(left,right);
        overlaps += checkOverlap(left,right);
    }
    printf("%d\n",fullOverlaps);
    printf("%d\n",overlaps);
    return 0;
}
