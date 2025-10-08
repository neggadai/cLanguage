#pragma once
#include <stdbool.h>

#define STACK_MAX 100

typedef struct {
    int data[STACK_MAX];
    int top;
} Stack;

void init_stack(Stack* s);
bool is_empty(Stack* s);
bool is_full(Stack* s);
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);

