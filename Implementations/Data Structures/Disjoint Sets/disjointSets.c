# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct DisjointSet {
    int *rank, *parent;
} Set;

///////////////////////////////////////////////////////////////////////////////

Set *makeSet(int size) {
    Set *set = (Set *)malloc(sizeof(Set));
    set->rank = (int *)malloc(size*sizeof(int));
    set->parent = (int *)malloc(size*sizeof(int));

    for (int i=0; i < size; i++) {
        set->rank[i] = 1;
        set->parent[i] = i; // represents that i-th element is unique
    }

    return set;
}

///////////////////////////////////////////////////////////////////////////////

int findSet(Set *set, int x) {
    if (set->parent[x] == x)
        return x;
    else {
        int parent = findSet(set, set->parent[x]);
        set->parent[x] = parent;
        return parent;
    }
}

///////////////////////////////////////////////////////////////////////////////

void unionSet(Set *set, int u, int v) {
    int uSet = findSet(set, u);
    int vSet = findSet(set, v);

    if (set->rank[uSet] < set->rank[vSet])
        set->parent[uSet] = vSet;

    else if (set->rank[uSet] > set->rank[vSet])
        set->parent[vSet] = uSet;

    else {
        set->parent[vSet] = uSet;
        set->rank[uSet]++;
    }
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    Set *set = makeSet(5);
    unionSet(set, 0, 2);
    unionSet(set, 4, 2);
    unionSet(set, 3, 1);

    printf("%d", findSet(set, 1) == findSet(set, 0));

    for (int i=0; i < 5; i++)
        printf("%d ", set->rank[i]);

    return 0;
}