//
// Created by Cordell on 20/12/2022.
//

#ifndef DAY_9_HASHMAP_H
#define DAY_9_HASHMAP_H

#include <stdbool.h>

typedef struct keyValue{
    int* x;
    int* y;
    int value;
    struct keyValue * next;
}kv;

typedef struct hashmap{
    int capacity;
    kv * map;
}map;

map * createMap(int capacity);
bool containsKey(int x,int y, map* m);
int getValue(int x,int y, map* m);
void addKey(int x,int y,int value, map* m);

#endif //DAY_9_HASHMAP_H
