# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *makeNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void append(Node **head, int data) {
    Node *node = makeNode(data);
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

int hash(int node) {
    // hash function for adjacency lsit
    return (node - 1);
}

///////////////////////////////////////////////////////////////////////////////

void addDirectedEdge(Node **adjList, int x, int y) {
    // add a Directed edge from the node x to y
    append(&adjList[hash(x)], y);
}

void addUndirectedEdge(Node **adjList, int x, int y) {
    // add an Undirected edge between the nodes x and y
    addDirectedEdge(adjList, x, y);
    addDirectedEdge(adjList, y, x);
}

///////////////////////////////////////////////////////////////////////////////

void reset(int *visited, int n) {
    for (int i=0; i < n; i++)
        visited[i] = 0;
}

void printAdjList(Node **adjList, int n) {
    for (int i=0; i < n; i++) {
        Node *head = adjList[i];
        printf("%d: ", i+1);
        for (Node *curr=head; curr; curr=curr->next)
            printf("%d ", curr->data);
        printf("\n");
    }
}

///////////////////////////////////////////////////////////////////////////////

void BFS(Node **adjList, int n, int start, int *visited) {
    int *queue = (int *)malloc(n*sizeof(int));
    int head = 0, tail = 0;

    queue[tail++] = start;
    visited[hash(start)]++;

    while (head != tail) {
        int curr = queue[head++];
        Node *head = adjList[hash(curr)];
        printf("%d ", curr);

        for (Node *curr=head; curr; curr=curr->next) {
            int child = curr->data;

            if (!visited[hash(child)]) {
                queue[tail++] = child;
                visited[hash(child)]++;
            }
        }
    }
    reset(visited, n);
    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////

void DFS(Node **adjList, int n, int start, int *visited) {
    int *stack = (int *)malloc(n*sizeof(int));
    int top = 0;

    stack[top++] = start;
    visited[hash(start)]++;

    while (top) {
        int curr = stack[--top];
        Node *head = adjList[hash(curr)];
        printf("%d ", curr);

        for (Node *curr=head; curr; curr=curr->next) {
            int child = curr->data;

            if (!visited[hash(child)]) {
                stack[top++] = child;
                visited[hash(child)]++;
            }
        }
    }
    reset(visited, n);
    printf("\n");
}

void DFSRecursive(Node **adjList, int start, int *visited) {
    Node *head = adjList[hash(start)];
    visited[hash(start)]++;
    printf("%d ", start);

    for (Node *curr=head; curr; curr=curr->next) {
        int child = curr->data;
        if (!visited[hash(child)])
            DFSRecursive(adjList, child, visited);
    }
}

///////////////////////////////////////////////////////////////////////////////

int isCyclic(Node **adjList, int start, int *visited) {
    Node *head = adjList[hash(start)];

    for (Node *curr=head; curr; curr=curr->next) {
        int child = curr->data;
        if (visited[hash(child)])
            return 1;
        else {
            visited[hash(child)] = -1;
            if (isCyclic(adjList, child, visited) == 1)
                return 1;
        }
    }
    visited[hash(start)] = 1;
    return 0;
}
///////////////////////////////////////////////////////////////////////////////

int main() {
    int count = 15;
    Node **adjList = makeAdjList(count);

    int *visited = (int *)malloc(count*sizeof(int));
    reset(visited, count);

    int edges[18][2] = {
        {1, 2}, {1, 3}, {1, 6}, {2, 4}, {2, 12}, {3, 4}, {3, 5}, {3, 8},
        {4, 7}, {4, 10}, {5, 7}, {5, 9}, {5, 14}, {6, 8}, {6, 15}, {8, 13},
        {9, 13}, {11, 13}
    };

    for (int i=0; i < 18; i++)
        addUndirectedEdge(adjList, edges[i][0], edges[i][1]);

    // // Acyclic Graph
    // addDirectedEdge(adjList, 1, 2);
    // addDirectedEdge(adjList, 1, 3);
    // addDirectedEdge(adjList, 2, 4);
    // addDirectedEdge(adjList, 2, 5);

    printf("Adjacency List: \n");
    printAdjList(adjList, count);

    printf("BFS: "); BFS(adjList, count, 1, visited);
    printf("DFS: "); DFS(adjList, count, 1, visited);
    printf("DFS Recursive: "); DFSRecursive(adjList, 1, visited); reset(visited, count); printf("\n");

    printf("Is Cyclic: %s", (isCyclic(adjList, 1, visited) ? "Yes" : "No")); reset(visited, count);

    return 0;
}