# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Node {
    int data, weight;
    struct Node *next;
} Node;

Node *makeNode(int data, int weight) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->weight = weight;
    node->data = data;
    node->next = NULL;
    return node;
}

void append(Node **head, int data, int weight) {
    Node *node = makeNode(data, weight);
    node->next = *head;
    *head = node;
}

///////////////////////////////////////////////////////////////////////////////

Node **makeAdjList(int size) {
    Node **adjList = (Node **)malloc(size*sizeof(Node *));
    for (int i=0; i < size; i++) {
        adjList[i] = NULL;
    }
    return adjList;
}

///////////////////////////////////////////////////////////////////////////////

void addEdge(Node **adjList, int x, int y, int weight) {
    // add a Directed edge from the node x to y
    append(&adjList[x], y, weight);
}

///////////////////////////////////////////////////////////////////////////////

void printAdjList(Node **adjList, int n) {
    for (int i=0; i < n; i++) {
        Node *head = adjList[i];
        printf("%d: ", i);
        for (Node *curr=head; curr; curr=curr->next)
            printf("(%d, %d) ", curr->data, curr->weight);
        printf("\n");
    }
}

///////////////////////////////////////////////////////////////////////////////

void heapify(Node **array, int index, int size) {
    int n = size - 1;
    while (index <= (n-1)/2) {
        int min = index;
        int left = 2*index + 1;
        int right = 2*index + 2;

        if (array[left]->weight < array[min]->weight)
            min = left;

        if (right <= n && array[right]->weight < array[min]->weight)
            min = right;

        if (min == index)
            break;
        else {
            Node *temp = array[index];
            array[index] = array[min];
            array[min] = temp;
            index = min;
        }
    }
}

Node *extractMin(Node **heap, int *n) {
    Node *node = heap[0];
    heap[0] = heap[--(*n)];
    heapify(heap, 0, *n);
    return node;
}

void insert(Node **heap, int *n, Node *node) {
    heap[(*n)++] = node;

    int i = (*n) - 1;
    int j = (i - 1) / 2;
    while (heap[j]->weight > heap[i]->weight && i >= 0) {
        Node *temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
        i = j;
        j = (i - 1) / 2;
    }
}

int isEmpty(Node **heap, int count) {
    return (count == 0);
}

///////////////////////////////////////////////////////////////////////////////

int *dijkstrasAlgo(Node **adjList, int N, int start) {
    // O(V²) or O(VlogV)

    int *finalWeights = (int *)malloc(N*sizeof(int));
    for (int i=0; i < N; i++)
        finalWeights[i] = INT_MAX;
    finalWeights[start] = 0;

    Node **heap = (Node **)malloc(N*N*sizeof(Node *));
    int count = 0;

    for (Node *curr=adjList[start]; curr; curr=curr->next)
        heap[count++] = curr;

    for (int i=count-1; i >= 0; i--)
        heapify(heap, i, count);

    while (!isEmpty(heap, count)) {
        Node *nearestChild = extractMin(heap, &count);
        int node = nearestChild->data;

        if (nearestChild->weight < finalWeights[node])
            finalWeights[node] = nearestChild->weight;

        for (Node *curr=adjList[node]; curr; curr=curr->next) {
            if (finalWeights[curr->data] == INT_MAX) {
                curr->weight += nearestChild->weight;
                insert(heap, &count, curr);
            }
        }
    }

    return finalWeights;
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    int N = 4;
    Node **adjList = makeAdjList(N);

    addEdge(adjList, 0, 1, 3);
    addEdge(adjList, 1, 2, 4);
    addEdge(adjList, 2, 3, 2);
    addEdge(adjList, 0, 3, 8);

    printAdjList(adjList, N);

    int *shortestDistances = dijkstrasAlgo(adjList, N, 0);

    for (int i=0; i < N; i++)
        printf("%d ", shortestDistances[i]);

    return 0;
}