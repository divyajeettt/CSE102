# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Edge {
    int start, end, weight;
} Edge;

Edge *makeEdge(int start, int end, int weight) {
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->weight = weight;
    edge->start = start;
    edge->end = end;
    return edge;
}

///////////////////////////////////////////////////////////////////////////////

int *bellmanFordAlgo(Edge **edges, int N, int E, int source) {
    // O(EV) or o(V³0)

    int *finalWeights = (int *)malloc(N*sizeof(int));
    for (int i=0; i < N; i++)
        finalWeights[i] = INT_MAX;

    finalWeights[source] = 0;

    for (int i=0; i < N-1; i++) {
        int updated = 0;
        for (int j=0; j < E; j++) {
            int start = edges[j]->start;
            int end = edges[j]->end;
            int weight = edges[j]->weight;
            if (finalWeights[start] + weight < finalWeights[end]) {
                finalWeights[end] = finalWeights[start] + weight;
                updated++;
            }
        }
        if (!updated)
            break;
    }

    return finalWeights;
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    int N = 7;
    int E = 10;

    Edge *edges[10] = {
        makeEdge(0, 1, 6),
        makeEdge(0, 2, 5),
        makeEdge(0, 3, 5),
        makeEdge(1, 4, -1),
        makeEdge(2, 1, -2),
        makeEdge(2, 4, 1),
        makeEdge(3, 2, -2),
        makeEdge(3, 5, -1),
        makeEdge(4, 6, 3),
        makeEdge(5, 6, 3),
    };

    int *shortestDistances = bellmanFordAlgo(edges, N, E, 0);

    for (int i=0; i < N; i++)
        printf("%d ", shortestDistances[i]);

    return 0;
}