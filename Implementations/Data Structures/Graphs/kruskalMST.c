# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Node {
    int data, numChildren;
    struct Node *parent;
} Node;

typedef struct Edge {
    int start, end, weight;
} Edge;

///////////////////////////////////////////////////////////////////////////////

Node *makeNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->numChildren = 1;
    node->parent = node;
    node->data = data;
    return node;
}

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

void printEdge(Edge *edge) {
    printf("(%c, %c, %d)  ", edge->start, edge->end, edge->weight);
}

void printEdges(Edge **edges, int n) {
    for (int i=0; i < n; i++)
        printEdge(edges[i]);
    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////

void heapify(Edge **array, int index, int size) {
    int n = size - 1;
    while (index <= (n-1)/2) {
        int min = index;
        int left = 2*index + 1;
        int right = 2*index + 2;

        if (array[left]->weight < array[min]->weight)
            min = left;

        if (array[right]->weight < array[min]->weight && right <= n)
            min = right;

        if (min == index)
            break;
        else {
            Edge *temp = array[index];
            array[index] = array[min];
            array[min] = temp;
            index = min;
        }
    }
}

Edge *extractMin(Edge **edges, int *numEdges) {
    Edge *edge = edges[0];
    edges[0] = edges[--(*numEdges)];
    heapify(edges, 0, *numEdges);
    return edge;
}

///////////////////////////////////////////////////////////////////////////////

Node *findSet(Node *node) {
    if (node->parent == node)
        return node;
    else {
        Node *parent = findSet(node->parent);
        node->parent = parent;
        return parent;
    }
}

void unionSet(Node *u, Node *v) {
    if (u->numChildren < v->numChildren) {
        u->parent = v;
        v->numChildren += u->numChildren;
    }
    else {
        v->parent = u;
        u->numChildren += v->numChildren;
    }
}

Edge **kruskalMST(Edge **edges, int E, Node **nodes, int N) {
    // O(ElogV)
    // returns an array of Edges included in the MST

    for (int i=E-1; i >= 0; i--)
        heapify(edges, i, E);

    Edge **treeEdges = (Edge **)malloc(N*sizeof(Edge *));
    int counter = 0;

    while (counter != N-1) {
        Edge *edge = extractMin(edges, &E);
        Node *u = findSet(nodes[hash(edge->start)]);
        Node *v = findSet(nodes[hash(edge->end)]);

        if (u != v) {
            treeEdges[counter++] = edge;
            unionSet(u, v);
        }
    }

    return treeEdges;
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    int countNodes = 9;
    int countEdges = 14;

    Node **nodes = (Node **)malloc(countNodes*sizeof(Node *));
    for (int i=0; i < 9; i++)
        nodes[i] = makeNode(i+97);

    Edge *edges[14] = {
        makeEdge('a', 'b', 4),
        makeEdge('a', 'h', 8),
        makeEdge('b', 'c', 8),
        makeEdge('b', 'h', 11),
        makeEdge('c', 'd', 7),
        makeEdge('c', 'f', 4),
        makeEdge('c', 'i', 2),
        makeEdge('d', 'e', 9),
        makeEdge('d', 'f', 14),
        makeEdge('e', 'f', 10),
        makeEdge('f', 'g', 2),
        makeEdge('g', 'i', 6),
        makeEdge('g', 'h', 1),
        makeEdge('h', 'i', 7)
    };

    Edge **MST = kruskalMST(edges, countEdges, nodes, countNodes);
    printEdges(MST, countNodes-1);

    return 0;
}