#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void init_stack(Stack* s) {
    s->top = -1;
}

bool is_empty(Stack* s) {
    return s->top == -1;
}

bool is_full(Stack* s) {
    return s->top == STACK_MAX - 1;
}

void push(Stack* s, int value) {
    if (is_full(s)) {
        printf("stack is overloaded");
        exit(1);
    }
    s->data[++s->top] = value;
}

int pop(Stack* s) {
    if (is_empty(s)) {
        printf("stack is empty");
        exit(1);
    }
    return s->data[s->top--];
}

int peek(Stack* s) {
    if (is_empty(s)) {
        printf("stack is empty");
        exit(1);
    }
    return s->data[s->top];
}

