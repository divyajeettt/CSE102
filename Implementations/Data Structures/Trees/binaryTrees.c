# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Node {
    int data;
    struct Node *left, *right, *parent;
} Node;

///////////////////////////////////////////////////////////////////////////////

Node *makeNode(int data, Node *parent) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    node->parent = parent;
    return node;
}

///////////////////////////////////////////////////////////////////////////////

// All traversals are O(n)

void preOrder(Node *root) {
    if (root) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *root) {
    if (root) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void postOrder(Node *root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

void levelOrder(Node *root, int n) {
    if (!root)
        return;

    Node **queue = (Node **)malloc(n*sizeof(Node *));
    int head = 0, tail = 0;

    queue[tail++] = root;
    while (head != tail) {
        Node *curr = queue[head++];
        printf("%d ", curr->data);
        if (curr->left)
            queue[tail++] = curr->left;
        if (curr->right)
            queue[tail++] = curr->right;
    }
}

void treePrint(Node *root, int n) {
    Node **currNodes = (Node **)malloc(n*sizeof(Node *));
    currNodes[0] = root;
    int sizeCurrNodes = 1;

    while (sizeCurrNodes != 0) {
        Node *next[n];
        int j = 0;
        for (int i=0; i < sizeCurrNodes; i++) {
            if (currNodes[i]) {
                next[j++] = currNodes[i]->left;
                next[j++] = currNodes[i]->right;
                printf("%d ", currNodes[i]->data);
            }
        }
        sizeCurrNodes = j;
        printf("\n");
        for (int i=0; i < j; i++)
            currNodes[i] = next[i];
    }
}

///////////////////////////////////////////////////////////////////////////////

int countNodes(Node *root) {
    // returns the # of Nodes in the Binary Tree (O(n))
    if (!root)
        return 0;
    else
        return 1 + countNodes(root->left) + countNodes(root->right);
}

///////////////////////////////////////////////////////////////////////////////

int max(int x, int y) {
    return (x < y ? y : x);
}

int height(Node *root) {
    // returns height of the Binary Tree (O(n))
    if (!root)
        return 0;
    else
        return 1 + max(height(root->left), height(root->right));
}

///////////////////////////////////////////////////////////////////////////////

Node *copyBT(Node *root, Node *parent) {
    if (!root)
        return NULL;

    Node *copy = makeNode(root->data, parent);
    copy->left = copyBT(root->left, copy);
    copy->right = copyBT(root->right, copy);
    return copy;
}

///////////////////////////////////////////////////////////////////////////////

Node *maxNode(Node *node1, Node *node2) {
    return ((node1->data < node2->data) ? node2 : node1);
}

Node *maxBT(Node *root) {
    // returns the maximum of a Binary Tree (O(n))

    Node *currMax = root;
    if (root->right)
        currMax = maxNode(currMax, maxBT(root->right));
    if (root->left)
        currMax = maxNode(currMax, maxBT(root->left));
    return currMax;
}

Node *maximum(Node *root) {
    // returns the maximum of a Binary Search Tree (O(logn) - O(n))

    Node *currMax = root;
    while (currMax->right)
        currMax = currMax->right;
    return currMax;
}

Node *maximumRecursive(Node *root) {
    // returns the maximum of a Binary Search Tree recursively (O(logn) - O(n))
    if (!root->right)
        return root;
    else
        return maximumRecursive(root->right);
}

///////////////////////////////////////////////////////////////////////////////

Node *minNode(Node *node1, Node *node2) {
    return ((node1->data < node2->data) ? node1 : node2);
}

Node *minBT(Node *root) {
    // returns the minimum of a Binary Tree (O(n))

    Node *currMin = root;

    if (root->left)
        currMin = minNode(currMin, minBT(root->left));
    if (root->right)
        currMin = minNode(currMin, minBT(root->right));

    return currMin;
}

Node *minimum(Node *root) {
    // returns the minimum of a Binary Search Tree (O(logn) - O(n))

    Node *currMin = root;
    while (currMin->left)
        currMin = currMin->left;
    return currMin;
}

Node *minimumRecursive(Node *root) {
    // returns the minimum of a Binary Search Tree recursively (O(logn) - O(n))
    if (!root->left)
        return root;
    else
        return minimumRecursive(root->left);
}

///////////////////////////////////////////////////////////////////////////////

int checkBST(Node *root, int min, int max) {
    // checks if a Binary Tree is a Binary Search Tree or not
    if (!root || (root->data == min && root->data == max))
        return 1;
    else
        return (
           root->data >= min && root->data <= max &&
           checkBST(root->left, min, root->data) &&
           checkBST(root->right, root->data, max)
        );
}

///////////////////////////////////////////////////////////////////////////////

void insert(Node **root, int value, Node *parent) {
    // insert a Node in the correct position in the Binary Search Tree

    if (!(*root))
        *root = makeNode(value, parent);

    else {
        if (value <= (*root)->data)
            insert(&((*root)->left), value, *root);
        else
            insert(&((*root)->right), value, *root);
    }
}

///////////////////////////////////////////////////////////////////////////////

Node *search(Node *root, int value) {
    Node *curr = root;
    while (curr) {
        if (curr->data == value)
            return curr;
        else if (value <= curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return NULL;
}

Node *searchRecursive(Node *root, int value) {
    if (!root)
        return NULL;

    if (root->data == value)
        return root;

    if (value <= root->data)
        return searchRecursive(root->left, value);
    else
        return searchRecursive(root->right, value);
}

///////////////////////////////////////////////////////////////////////////////

Node *successor(Node *node) {
    // returns the successor of the given Node of the Binary Search Tree
    if (node->right)
        return minimum(node->right);

    Node *ancestor = node->parent;
    if (!ancestor)
        return NULL;

    // go up the Tree until you encunter a Node that is a left child
    // lowest ancestor of node whose left child is also an ancestor of node
    while (ancestor && node == ancestor->right) {
        node = ancestor;
        ancestor = ancestor->parent;
    }
    return ancestor;
}

Node *predecessor(Node *node) {
    // returns the predecessor of the given Node of the Binary Search Tree
    if (node->left)
        return maximum(node->left);

    Node *ancestor = node->parent;
    if (!ancestor)
        return NULL;

    // go up the Tree until you encounter a Nodee that is a right child
    // lowest ancestor of node whose right child is also an ancestor of node
    while (ancestor && node == ancestor->left) {
        node = ancestor;
        ancestor = ancestor->parent;
    }
    return ancestor;
}

///////////////////////////////////////////////////////////////////////////////

Node *deleteByValue(Node **root, int value) {
    Node *searched = search(*root, value);

    if (!searched)
        return NULL;

    Node *parent = searched->parent;
    int isLeftChild;

    if (!(searched->left || searched->right)) {
        isLeftChild = (parent->left == searched);
        if (isLeftChild)
            parent->left = NULL;
        else
            parent->right = NULL;
        return searched;
    }
    else if (!(searched->left && searched->right)) {
        Node *child = (searched->left) ? searched->left : searched->right;
        isLeftChild = (parent->left == searched);
        if (isLeftChild)
            parent->left = child;
        else
            parent->right = child;
        return searched;
    }
    else {
        Node *removed = deleteByValue(root, successor(searched)->data);
        Node *copy = searched;
        searched->data = removed->data;
        return copy;
    }
}

///////////////////////////////////////////////////////////////////////////////

void invert(Node *root) {
    // inverts a binary Tree, i.e. returns its mirror image
    if (root) {
        Node *temp = root->left;
        root->left = root->right;
        root->right = temp;
        invert(root->left);
        invert(root->right);
    }
}

///////////////////////////////////////////////////////////////////////////////

void saveInOrder(Node *root, int *array) {
    static int index = 0;
    if (root) {
        saveInOrder(root->left, array);
        array[index++] = root->data;
        saveInOrder(root->right, array);
    }
}

void saveReverseOrder(Node *root, int *array) {
    static int index = 0;
    if (root) {
        saveReverseOrder(root->right, array);
        array[index++] = root->data;
        saveReverseOrder(root->left, array);
    }
}

int isMirror(Node *root, int n) {
    // returns true if the binary tree is root->left is a mirror image of
    // root->recursively

    int *inOrderTraversal = (int *)malloc(n*sizeof(int));
    saveInOrder(root, inOrderTraversal);

    int *reverseOrderTraversal = (int *)malloc(n*sizeof(int));
    saveReverseOrder(root, reverseOrderTraversal);

    for (int i=0; i < n; i++) {
        if (inOrderTraversal[i] != reverseOrderTraversal[i])
            return 0;
    }
    return 1;
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    // Node *root = makeNode(10, NULL);
    // root->left = makeNode(5, root);
    // root->left->left = makeNode(3, root->left);
    // root->left->right = makeNode(27, root->left);
    // printf("%d", checkBST(root, 3, 27));

    // Node *root = makeNode(10, NULL);
    // root->left = makeNode(50, root);
    // root->right = makeNode(50, root);
    // root->left->left = makeNode(20, root->left);
    // root->left->right = makeNode(30, root->left);
    // root->right->right = makeNode(20, root->right);
    // root->right->left = makeNode(30, root->right);

    // treePrint(root, countNodes(root));
    // printf("Is Mirror Tree?: %s \n", (isMirror(root, countNodes(root)) ? "Yes" : "No"));

    // printf("preOrder = "); preOrder(root); printf("\n");
    // printf("inOrder = "); inOrder(root); printf("\n");
    // printf("postOrder = "); postOrder(root); printf("\n");

    // printf("Is Binary Search Tree?: %s \n", (checkBST(root, minBT(root), maxBT(root)) ? "Yes" : "No"));

    // Node *root = makeNode(15, NULL);
    // printf("Is Binary Search Tree?: %s \n", (checkBST(root, minBT(root)->data, maxBT(root)->data) ? "Yes" : "No"));
    // printf("%x \n", successor(root));
    // printf("%x \n", predecessor(root));

    // insert(&root, 5, NULL);
    // insert(&root, 16, NULL);
    // insert(&root, 3, NULL);
    // insert(&root, 12, NULL);
    // insert(&root, 20, NULL);
    // insert(&root, 10, NULL);
    // insert(&root, 13, NULL);
    // insert(&root, 18, NULL);
    // insert(&root, 23, NULL);
    // insert(&root, 6, NULL);
    // insert(&root, 7, NULL);

    // treePrint(root, countNodes(root));

    // preOrder(root); printf("\n");
    // inOrder(root); printf("\n");
    // postOrder(root); printf("\n");
    // printf("Is Binary Search Tree?: %s \n", (checkBST(root, minBT(root)->data, maxBT(root)->data) ? "Yes" : "No"));
    // levelOrder(root, countNodes(root));

    // deleteByValue(&root, 15);
    // treePrint(root, countNodes(root));

    // invert(root);
    // treePrint(root, countNodes(root));

    // preOrder(root); printf("\n");
    // inOrder(root); printf("\n");
    // postOrder(root); printf("\n");

    return 0;
}