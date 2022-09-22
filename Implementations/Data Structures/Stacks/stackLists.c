# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Stack {
    int size, length;
    Node *top;
} Stack;

int isEmpty(Stack *stack);
int push(Stack *stack, int data);
int pop(Stack *stack);

//////////////////////////////////////////////////////////////////////////////

Node *makeNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

Stack *makeStack(int size) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->size = size;
    stack->length = 0;
    stack->top = NULL;
    return stack;
}

//////////////////////////////////////////////////////////////////////////////

void print(Stack *stack) {
    Stack *inverted = makeStack(stack->size);
    
    while (!isEmpty(stack))
        push(inverted, pop(stack));
    
    while (!isEmpty(inverted)) {
        int data = pop(inverted);
        printf("%d ", data);
        push(stack, data);
    }

    printf("\n");
}

//////////////////////////////////////////////////////////////////////////////

int isEmpty(Stack *stack) {
    return (stack->length == 0);
}

int isFull(Stack *stack) {
    return (stack->length == stack->size);
}

//////////////////////////////////////////////////////////////////////////////

int peek(Stack *stack) {
    // returns the element at top of the stack
    if (isEmpty(stack))
        return -1;
    else
        return stack->top->data;
}

//////////////////////////////////////////////////////////////////////////////

int push(Stack *stack, int data) {
    // -1 represents OVERFLOW, 1 represents successful insertion 
    if (isFull(stack))
        return -1;
    else {
        Node *node = makeNode(data);
        node->next = stack->top;
        stack->top = node;
        (stack->length)++;
        return 1;
    } 
}

//////////////////////////////////////////////////////////////////////////////

int pop(Stack *stack) {
    // -1 represents UNDERFLOW
    if (isEmpty(stack))
        return -1;
    else {
        Node *popped = stack->top;
        stack->top = stack->top->next;
        (stack->length)--;
        return popped->data;
    }
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