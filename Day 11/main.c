#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Monkey{
    int id;
    long long items[200];
    int itemCount;
    char opSign;
    char opValue[4];
    int modBy;
    int idTrue;
    int idFalse;
}Mon;
enum {monkeyCount=8};

Mon monkeys[monkeyCount];
int itemsInspected[monkeyCount];
long modd = 1;

int cmpfunc(const void * a, const void * b) {
    return ( *(int*)b - *(int*)a );
}

long long operation(long long oldVal,char sign,const char * opVal){
    long long newVal = oldVal;
    long long signVal = strtol(opVal,NULL,10);
    if(strcmp(opVal,"old")==0){
        signVal = oldVal;
    }
    if(sign == '+'){
        newVal += signVal;
    } else if(sign == '*'){
        newVal *= signVal;
    }
    return newVal;
}

void moveItem(long long item,Mon * monkey){
    monkey->items[monkey->itemCount] = item;
    monkey->itemCount++;
}

int main() {
    char buff[125];
    char * start;
    for (int i = 0; i < monkeyCount; i++) {
        fgets(buff,125,stdin);
        start = buff;
        start += 7;
        monkeys[i].id = strtol(start,NULL,10);
        fgets(buff,125,stdin);
        start = buff;
        buff[strlen(buff)-1]='\000';
        start += 18;
        int value = strtol(start,&start,10);
        int count = 0;
        while (value != 0){
            monkeys[i].items[count] = value;
            count++;
            if(strlen(start) != 0){
                start+=2;
            }
            value = strtol(start,&start,10);
        }
        monkeys[i].itemCount = count;
        fgets(buff,125,stdin);
        start = buff;
        start += 23;
        monkeys[i].opSign = start[0];
        start += 2;
        start[strlen(start)-1] = '\000';
        strcpy(monkeys[i].opValue,start);
        fgets(buff,125,stdin);
        start = buff;
        start +=21;
        value = strtol(start,NULL,10);
        monkeys[i].modBy =value;
        modd *= value;
        fgets(buff,125,stdin);
        start = buff;
        start +=29;
        value = strtol(start,NULL,10);
        monkeys[i].idTrue = value;
        fgets(buff,125,stdin);
        start = buff;
        start +=30;
        value = strtol(start,NULL,10);
        monkeys[i].idFalse = value;
        fgets(buff,125,stdin);
    }
    //Change rounds for different parts
    int rounds = 10000;
    for (int i = 0; i < rounds; i++) {
        for (int j = 0; j < monkeyCount; j++) {
            for (int k = 0; k < monkeys[j].itemCount; k++) {
                long long value = operation(monkeys[j].items[k],monkeys[j].opSign,monkeys[j].opValue);
//                Uncomment for part 1
//                value /= 3;
//                Uncomment for part 2
                value %= modd;
                monkeys[j].items[k] = 0;
                if(value % monkeys[j].modBy == 0){
                    moveItem(value,&monkeys[monkeys[j].idTrue]);
                } else{
                    moveItem(value,&monkeys[monkeys[j].idFalse]);
                }
            }
            itemsInspected[j] += monkeys[j].itemCount;
            monkeys[j].itemCount=0;
        }
    }
    qsort(itemsInspected,monkeyCount, sizeof(int),cmpfunc);
    long long monkeyB = ((long long)itemsInspected[0])*((long long)itemsInspected[1]);
    printf("%lld",monkeyB);
    return 0;
}
