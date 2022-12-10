#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearArray(char * arr,int size){
    for (int i = 0; i < size; i++) {
        arr[i] = ' ';
    }
}

void shiftElementsLeft(char * arr,int size,char remove,int * pos){
    char * indexOf;
    while ((indexOf = strchr(arr,remove)) != NULL){
        for(int i = 0;i<size-1;i++){
            arr[i] = arr[i+1];
        }
        *pos -=1;
    }

}

int findNUniqueSequence(char str[],int n){
    char * buff = malloc(sizeof(char)*n);
    int pos = 0;
    clearArray(buff,n);
    for(int i = 0;i< strlen(str);i++){
        char * indexOf = strchr(buff,str[i]);
        if(indexOf == NULL){
            buff[pos++] = str[i];
        } else {
            shiftElementsLeft(buff,n,str[i],&pos);
            buff[pos++] = str[i];
        }

        if(pos > n-1){
            return i+1;
        }
    }
    return 0;
}

int main() {
    char buff[5000];
    fgets(buff,5000,stdin);
    // Part 1
    printf("%d\n",findNUniqueSequence(buff,4));
    // Part 2
    printf("%d",findNUniqueSequence(buff,14));
    return 0;
}
