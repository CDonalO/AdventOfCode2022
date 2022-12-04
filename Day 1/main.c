#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)b - *(int*)a );
}
int getSumOfN(int* arr,int count){
    int sum = 0;
    for(int i =0;i<count;i++){
        int num = *(arr+i);
        sum += num;
    }
    return sum;
}

int main() {
    int highest_sum = 0;
    int sum = 0;
    char buff[255];
    int count = 0;
    int* elves = malloc(sizeof(int));
    while (fgets(buff,255,stdin)!=NULL){
        if(strcmp(buff,"\n") == 0){
            if(sum > highest_sum) {
                highest_sum = sum;
            }
            *(elves+count) = sum;
            count++;
            elves = realloc(elves,(sizeof(int)*(count+1)));
            sum = 0;
        }
        sum += atoi(buff);
    }

    qsort(elves,count,sizeof(int),cmpfunc);
    int sumN = getSumOfN(elves,3);
    printf("%d\n",sumN);
    printf("%d",highest_sum);
	free(elves);
    return 0;
}
