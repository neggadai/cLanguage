#include <stdio.h>
#include "stack.h"

int main() {
    Stack s;
    init_stack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("top of stack: %d\n", peek(&s));

    while (!is_empty(&s)) {
        printf("extracted: %d\n", pop(&s));
    }

    return 0;
}

