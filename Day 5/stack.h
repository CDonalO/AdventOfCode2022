#ifndef DAY_5_STACK_H
#define DAY_5_STACK_H

#include <stdbool.h>

typedef struct Stack{
    int top;
    char *items;
    int capacity;
}stack;

void push(char item, stack * s);
char pop(stack * s);
stack* createStack(int capacity);
char peek(stack * s);
bool isFull(stack * s);
bool isEmpty(stack * s);
void clearStack(stack * s);
stack * reverseStack(stack *s);
void printStack(stack*s);



#endif //DAY_5_STACK_H
