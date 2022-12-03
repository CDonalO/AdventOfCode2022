#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int highest_sum = 0;
    int sum = 0;
    char buff[255];
    while (fgets(buff,255,stdin)!=NULL){
        if(strcmp(buff,"\n") == 0){
            if(sum > highest_sum) {
                highest_sum = sum;

                sum = 0;
            }
        }
        sum += atoi(buff);
    }
    printf("%d\n",highest_sum);
    return 0;
}
