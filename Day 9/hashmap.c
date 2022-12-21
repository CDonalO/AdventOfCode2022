//
// Created by Cordell on 20/12/2022.
//
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hashmap.h"




map * createMap(int capacity){
    map * hmap = (map*)malloc(sizeof(map));
    hmap->capacity = capacity;
    hmap->map = malloc(sizeof(kv)*capacity);
    for (int i = 0; i < capacity; i++) {
        hmap->map[i].next = NULL;
        hmap->map[i].x = NULL;
        hmap->map[i].y = NULL;
        hmap->map[i].value = 0;
    }
  return hmap;
}

bool containsKey(int x,int y,map * m){
    int index = abs(y%(m->capacity-1));
    kv * current = &m->map[index];
    if (current->x == NULL){
        return false;
    }
    while (current != NULL){
        if(*current->x == x && *current->y == y){
            return true;
        }
        current = current->next;
    }
    return false;
}

int getValue(int x,int y,map* m){
    bool exists = containsKey(x,y,m);
    if (!exists){
        return 0;
    }
    int index = abs(y%(m->capacity-1));
    kv * current = &m->map[index];
    while (current->x != NULL &&*current->x != x && *current->y != y){
        current = current->next;
    }
    return current->value;
}

void addKey(int x,int y,int value,map * m){
    bool exists = containsKey(x,y,m);
    if(exists){
        return;
    }
    int index = abs(y%(m->capacity-1));
    kv * current = &m->map[index];
    if(current->x == NULL){
        current->x = malloc(sizeof(int));
        current->y = malloc(sizeof(int));
        *current->x = x;
        *current->y = y;
        current->next = NULL;
        current->value = value;

    } else {
        while (current->next != NULL){
            current = current->next;
        }
        current->next = malloc(sizeof(kv));
        current = current->next;
        current->x = malloc(sizeof(int));
        current->y = malloc(sizeof(int));
        *current->x = x;
        *current->y = y;
        current->next = NULL;
        current->value = value;
    }
}