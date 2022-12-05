#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct Map{
    char key;
    int value;
}map;

enum { size = 100};
int used = 0;
map itemMap[size];

void clearMap(){
    for(int i =0;i<used;i++){
        itemMap[i].key = ' ';
        itemMap[i].value = 0;
    }
    used = 0;
}

void addOrIncr(char key){
    for(int i=0;i<used;i++){
        if(itemMap[i].key == key){
            itemMap[i].value +=1;
            return;
        }
    }
    itemMap[used].key = key;
    itemMap[used].value = 1;
    used++;
}

bool contains(char key){
    for(int i=0;i<used;i++){
        if(itemMap[i].key == key){
            return true;
        }
    }
    return false;
}

int typeToPoints(char c){
    if(c >= 'A' && c <= 'Z'){
        return c-'A'+1+26;
    } else {
        return c-'a'+1;
    }
}


int main() {
    int prioritySum = 0;
    char buff[255];
    char *startOfString;
    char left[255];
    char right[255];
    size_t len = 0;
//    for(int i = 65;i<123;i++){
//        printf("%c",i);
//    }
    while (fgets(buff,255,stdin)!=NULL){
        len = strlen(buff)-1;
        startOfString = buff;
        memcpy(left,startOfString,len/2);
        left[len/2] = '\000';
        startOfString += len/2;
        memcpy(right,startOfString,len/2);
        right[len/2] = '\000';
        for(int i =0;i<len/2;i++){
            addOrIncr(left[i]);
        }
        for(int i =0;i<len/2;i++){
            bool has = contains(right[i]);
            if(has){
                char z = right[i];
                prioritySum += typeToPoints(right[i]);
                printf("%c",right[i]);
                break;
            }
        }
        printf("\n");
        clearMap();
    }
    printf("%d",prioritySum);
    return 0;
}
