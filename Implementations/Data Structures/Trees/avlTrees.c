# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Node {
    int data;
    struct Node *left, *right;
    int bf;     // Mainting height of each node => calculate bf in O(1) time
} Node;

///////////////////////////////////////////////////////////////////////////////

Node *makeNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    node->bf = 0;
    return node;
}

///////////////////////////////////////////////////////////////////////////////

int max(int x, int y) {
    return ((x < y) ? y : x);
}

int height(Node *node) {
    return ((!node) ? 0 : max(height(node->left), height(node->right)) + 1);
}

int balanceFactor(Node *node) {
    return (height(node->right) - height(node->left));
}

int minNode(Node *root) {
    return ((!root->left) ? root->data : minNode(root->left));
}

///////////////////////////////////////////////////////////////////////////////

void treePrint(Node* root, int n) {
    Node* currNodes[n];
    currNodes[0] = root;
    int sizeCurrNodes = 1;

    while (sizeCurrNodes != 0) {
        Node* nextNodes[n];
        int indexNextNodes = 0;
        for (int i=0; i < sizeCurrNodes; i++) {
            if (currNodes[i]) {
                nextNodes[indexNextNodes++] = currNodes[i] -> left;
                nextNodes[indexNextNodes++] = currNodes[i] -> right;
                printf("%d ", currNodes[i]->data);
            }
        }
        sizeCurrNodes = indexNextNodes;
        printf("\n");
        for (int i=0; i < indexNextNodes; i++)
            currNodes[i] = nextNodes[i];
    }
}

///////////////////////////////////////////////////////////////////////////////

Node *rotateLeft(Node *node) {
    Node *z = node;
    Node *y = z->right;
    Node *x = y->right;

    z->right = y->left;
    y->left = z;

    z->bf = balanceFactor(z);
    y->bf = balanceFactor(y);

    return y;
}

Node *rotateRight(Node *node) {
    Node *z = node;
    Node *y = z->left;
    Node *x = y->left;

    z->left = y->right;
    y->right = z;

    z->bf = balanceFactor(z);
    y->bf = balanceFactor(y);

    return y;
}


///////////////////////////////////////////////////////////////////////////////

Node *insert(Node *root, int data) {
    if (!root)
        return makeNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);

    root->bf = balanceFactor(root);

    if (root->bf < -1 && data < root->left->data)
        return rotateRight(root);

    else if (root->bf < -1 && data > root->left->data) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    else if (root->bf > 1 && data > root->right->data)
        return rotateLeft(root);

    else if (root->bf > 1 && data < root->right->data) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

///////////////////////////////////////////////////////////////////////////////

Node *deleteByValue(Node *root, int value) {
    if (!root)
        return root;

    if (value < root->data)
        root->left = deleteByValue(root->left, value);
    else if (value > root->data)
        root->right = deleteByValue(root->right, value);
    else {
        if (!(root->left || root->left)) {
            Node *child = ((root->left) ? root->left : root->right);
            if (!child)
                root = NULL;
            else
                *root = *child;
        }
        else {
            int successor = minNode(root->right);
            root->data = successor;
            root->right = deleteByValue(root->right, successor);
        }
    }

    if (!root)
        return root;

    root->bf = balanceFactor(root);

    if (root->bf < -1) {
        if (root->left->bf <= 0)
            root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    else if (root->bf > 1) {
        if (root->right->bf >= 0)
            root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

///////////////////////////////////////////////////////////////////////////////
// All other operations remain the same as BST with worst case Time Complexity of O(logn)

int main() {
    Node *root = NULL;

    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 13);
    root = insert(root, 70);
    root = insert(root, 22);
    root = insert(root, 21);
    root = insert(root, 20);

    treePrint(root, 14);

    root = deleteByValue(root, 10);

    treePrint(root, 13);

    return 0;
}