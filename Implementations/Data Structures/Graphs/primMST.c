# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Edge {
    int start, end, weight;
} Edge;

typedef struct Array {
    int size, length;
    Edge **list;
} Array;

///////////////////////////////////////////////////////////////////////////////

Edge *makeEdge(int start, int end, int weight) {
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->weight = weight;
    edge->start = start;
    edge->end = end;
    return edge;
}

int hash(int node) {
    return (node - 'a');
}

///////////////////////////////////////////////////////////////////////////////

Array *makeArray(int size) {
    Array *array = (Array *)malloc(sizeof(Array));

    array->list = (Edge **)malloc(size*sizeof(Edge *));
    for (int i=0; i < size; i++)
        array->list[i] = (Edge *)malloc(sizeof(Edge));

    array->size = size;
    array->length = 0;
    return array;
}

void append(Array *array, Edge *edge) {
    if (array->length == array->size) {
        int size = array->size;
        array->size *= 2;
        array->list = (Edge **)realloc(array->list, array->size*sizeof(Edge *));

        for (int i=size; i < array->size; i++)
            array->list[i] = (Edge *)malloc(sizeof(Edge));
    }
    array->list[array->length++] = edge;
}

///////////////////////////////////////////////////////////////////////////////

Array **makeAdjList(int size) {
    Array **adjList = (Array **)malloc(size*sizeof(Array *));
    for (int i=0; i < size; i++) {
        adjList[i] = makeArray(5);
    }
    return adjList;
}

void addEdge(Array **adjList, int start, int end, int weight) {
    append(adjList[hash(start)], makeEdge(start, end, weight));
    append(adjList[hash(end)], makeEdge(end, start, weight));
}

///////////////////////////////////////////////////////////////////////////////

void printEdge(Edge *edge) {
    printf("(%c, %c, %d)  ", edge->start, edge->end, edge->weight);
}

void printAdjList(Array **adjList, int n) {
    for (int i=0; i < n; i++) {
        Array *list = adjList[i];
        printf("%c: ", i+'a');
        for (int j=0; j < list->length; j++)
            printEdge(list->list[j]);
        printf("\n");
    }
}

///////////////////////////////////////////////////////////////////////////////

void heapify(Edge **heap, int index, int size) {
    int n = size - 1;
    while (index <= (n-1)/2) {
        int min = index;
        int left = 2*index + 1;
        int right = 2*index + 2;

        if (heap[left]->weight < heap[min]->weight)
            min = left;

        if (right <= n && heap[right]->weight < heap[min]->weight)
            min = right;

        if (min == index)
            break;
        else {
            Edge *temp = heap[index];
            heap[index] = heap[min];
            heap[min] = temp;
            index = min;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

Edge *extractMin(Edge **heap, int *n) {
    Edge *extracted = heap[0];

    heap[0] = heap[--(*n)];
    heapify(heap, 0, *n);

    return extracted;
}

///////////////////////////////////////////////////////////////////////////////

void insert(Edge **heap, Edge *edge, int *n) {
    heap[(*n)++] = edge;

    int index = (*n) - 1;
    int parent = (index - 1) / 2;

    while (heap[index]->weight < heap[parent]->weight) {
        Edge *temp = heap[index];
        heap[index] = heap[parent];
        heap[parent] = temp;

        index = parent;
        parent = (index - 1) / 2;
    }
}

///////////////////////////////////////////////////////////////////////////////

Array **primMST(Array **adjList, int start, int N) {
    // O(ElogV)
    // returns a new graph (adjacency list) which is the MST

    Array **MST = makeAdjList(N);
    Array *children = adjList[hash(start)];
    Edge **heap = children->list;
    int count = children->length;

    for (int i=count-1; i >= 0; i--) {
        heapify(heap, i, count);
    }

    heap = (Edge **)realloc(heap, N*N*sizeof(Edge *));

    int *added = (int *)calloc(N, sizeof(int));
    added[hash(start)]++;

    int counter = 0;

    while (counter != N-1) {
        Edge *edge = extractMin(heap, &count);

        if (!added[hash(edge->end)]) {
            addEdge(MST, edge->start, edge->end, edge->weight);
            added[hash(edge->end)]++;

            Array *children = adjList[hash(edge->end)];

            for (int i=0; i < children->length; i++)
                insert(heap, children->list[i], &count);

            counter++;
        }
    }

    return MST;
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    int countNodes = 6;
    Array **adjList = makeAdjList(countNodes);

    addEdge(adjList, 'a', 'b', 2);
    addEdge(adjList, 'a', 'c', 8);
    addEdge(adjList, 'a', 'e', 7);
    addEdge(adjList, 'b', 'c', 5);
    addEdge(adjList, 'b', 'd', 7);
    addEdge(adjList, 'c', 'd', 9);
    addEdge(adjList, 'c', 'e', 8);
    addEdge(adjList, 'd', 'f', 4);
    addEdge(adjList, 'e', 'f', 3);

    Array **MST = primMST(adjList, 'a', countNodes);
    printAdjList(MST, countNodes);

    return 0;
}