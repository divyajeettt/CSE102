# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Queue {
    int size, length;
    Node *head, *tail;
} Queue;

int isEmpty(Queue *queue);
int enqueue(Queue *queue, int data);
int dequeue(Queue *queue);

///////////////////////////////////////////////////////////////////////////////

Node *makeNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

Queue *makeQueue(int size) {
    Queue* queue = (Queue *)malloc(sizeof(Queue));
    queue->size = size;
    queue->length = 0;
    queue->head = queue->tail = NULL;
    return queue;
}

///////////////////////////////////////////////////////////////////////////////

void print(Queue *queue) {
    Queue *copy = makeQueue(queue->size);
    
    while (!isEmpty(queue)) {
        int data = dequeue(queue);
        printf("%d ", data);
        enqueue(copy, data);
    }
    
    while (!isEmpty(copy))
        enqueue(queue, dequeue(copy));

    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////

int isEmpty(Queue *queue) {
    return (queue->length == 0);
}

int isFull(Queue *queue) {
    return (queue->length == queue->size);
}

///////////////////////////////////////////////////////////////////////////////

int front(Queue *queue) {
    // returns the element at head of the queue
    if (isEmpty(queue))
        return -1;
    else
        return queue->head->data;
}

///////////////////////////////////////////////////////////////////////////////

int enqueue(Queue *queue, int data) {
    // -1 represents OVERFLOW, 1 represents successful insertion 
    if (isFull(queue))
        return -1;
    else {
        Node *node = makeNode(data);
        
        if (isEmpty(queue))
            queue->head = node;
        else
            queue->tail->next = node;

        queue->tail = node;
        (queue->length)++;

        return 1;
    }
}

///////////////////////////////////////////////////////////////////////////////

int dequeue(Queue* queue) {
    // -1 represents UNDERFLOW
    if (isEmpty(queue))
        return -1;
    else {
        int dequeued = queue->head->data;
        queue->head = queue->head->next;
        (queue->length)--;
        return dequeued;
    } 
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    Queue* queue = makeQueue(10);
    
    for (int i=1; i < 11; i++)
        enqueue(queue, i);
    
    print(queue);
    printf("Front: %d \n", front(queue));
    
    for (int i=0; i < 4; i++) {
        int d = dequeue(queue);
        printf("Dequeued: %d \n", d);
    }
    
    print(queue);
    printf("Front: %d \n", front(queue));
    
    enqueue(queue, 11);
    enqueue(queue, 12);

    print(queue);
    printf("Front: %d \n", front(queue));

    return 0;
}