# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Queue {
    int size, head, tail, *list;
} Queue;

///////////////////////////////////////////////////////////////////////////////

Queue *makeQueue(int size) {
    Queue* queue = (Queue *)malloc(sizeof(Queue));
    queue->size = size + 1;
    queue->head = queue->tail = 0;
    queue->list = (int *)malloc(size*sizeof(int));
    return queue;
}

///////////////////////////////////////////////////////////////////////////////

void print(Queue *queue) {
    for (int i=queue->head; i < queue->size; i=(i+1)%queue->size) {
        printf("%d ", queue->list[i]);
        if (i+1 == queue->tail)
            break;
    }
    printf("\n");
    // printf("\nhead=%d tail=%d \n", queue->head, queue->tail);
}

///////////////////////////////////////////////////////////////////////////////

int isEmpty(Queue *queue) {
    return (queue->head == queue->tail);
}

int isFull(Queue *queue) {
    return (queue->head == ((queue->tail + 1) % queue->size));
}

///////////////////////////////////////////////////////////////////////////////

int front(Queue *queue) {
    // returns the element at head of the queue
    if (isEmpty(queue))
        return -1;
    else
        return queue->list[queue->head];
}

///////////////////////////////////////////////////////////////////////////////

int enqueue(Queue *queue, int data) {
    // -1 represents OVERFLOW, 1 represents successful insertion 
    if (isFull(queue))
        return -1;
    else {
        queue->list[queue->tail++] = data;
        queue->tail %= queue->size;
        return 1;
    }
}

///////////////////////////////////////////////////////////////////////////////

int dequeue(Queue* queue) {
    // -1 represents UNDERFLOW
    if (isEmpty(queue))
        return -1;
    else {
        int dequeued = queue->list[queue->head++];
        queue->head %= queue->size;
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