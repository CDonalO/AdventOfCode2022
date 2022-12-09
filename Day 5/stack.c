//
// Created by Cordell on 9/12/2022.
//

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

stack * createStack(int capacity){
    stack *s = (stack*)malloc(sizeof(stack));
    s->capacity = capacity;
    s->items = malloc(sizeof(char)*capacity);
    s->top=-1;
    return s;
}
bool isEmpty(stack * s){
    if (s->top == -1){
        return true;
    }
    return false;
}
bool isFull(stack * s){
    if(s->top == s->capacity-1){
        return true;
    }
    return false;
}
char peek(stack * s){
    if (!isEmpty(s)){
        return s->items[s->top];
    }
    return ' ';
}

void push(char item,stack * s){
    if (isFull(s)){
        return;
    }
    s->top +=1;
    s->items[s->top] = item;
}

char pop(stack *s){
    if (isEmpty(s)){
        return ' ';
    }
    char item = s->items[s->top];
    s->items[s->top] = ' ';
    s->top-=1;
    return item;
}

void clearStack(stack*s){
    for (int i = 0; i < s->capacity; ++i) {
        s->items[i] = ' ';
    }
    s->top = -1;
}
stack * reverseStack(stack*s){
    stack * temp = createStack(s->capacity);
    while (!isEmpty(s)){
        push(pop(s),temp);
    }
    free(s);
    return temp;
}

void printStack(stack*s){
    for (int i = s->top; i >= 0; i--) {
        printf(" [%c]",s->items[i]);
    }
    printf("\n");
}

