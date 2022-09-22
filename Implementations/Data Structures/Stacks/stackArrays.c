# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Stack {
    int size, top, *list;
} Stack;

//////////////////////////////////////////////////////////////////////////////

Stack *makeStack(int size) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->size = size;
    stack->top = 0;
    stack->list = (int *)malloc(size*sizeof(int));
    return stack;
}

//////////////////////////////////////////////////////////////////////////////

void print(Stack *stack) {
    for (int i=0; i < stack->top; i++)
        printf("%d ", stack->list[i]);
    printf("\n");
}

//////////////////////////////////////////////////////////////////////////////

int isEmpty(Stack *stack) {
    return (stack->top == 0);
}

int isFull(Stack *stack) {
    return (stack->top == stack->size);
}

//////////////////////////////////////////////////////////////////////////////

int peek(Stack *stack) {
    // returns the element at top of the stack
    if (isEmpty(stack))
        return -1;
    else
        return stack->list[stack->top - 1];
}

//////////////////////////////////////////////////////////////////////////////

int push(Stack *stack, int data) {
    // -1 represents OVERFLOW, 1 represents successful insertion 
    if (isFull(stack))
        return -1;
    else {
        stack->list[stack->top++] = data;
        return 1;
    } 
}

//////////////////////////////////////////////////////////////////////////////

int pop(Stack *stack) {
    // -1 represents UNDERFLOW
    if (isEmpty(stack))
        return -1;
    else 
        return stack->list[--stack->top];
}

//////////////////////////////////////////////////////////////////////////////

int main() {
    Stack *stack = makeStack(10);

    for (int i=1; i < 11; i++)
        push(stack, i);
    
    print(stack);

    for (int i=0; i < 3; i++) {
        int popped = pop(stack);
        print(stack);
        printf("Popped %d \n", popped);
    }

    printf("Peeking: %d", peek(stack));

    return 0;
}