# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Node {
    int data;
    struct Node *next;
} Node;

///////////////////////////////////////////////////////////////////////////////

Node *makeNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

Node *makeCircularLinkedList(int *array, int n) {
    if (n == 0)
        return NULL;
    
    Node *head = makeNode(array[0]);
    
    if (n == 1) {
        head->next = head;
        return head;
    }

    Node *prev = head;
    Node *node;
    for (int i=1; i < n; i++) {
        node = makeNode(array[i]);
        prev->next = node;
        prev = node;
    }
    
    node->next = head;
    return node;
}

///////////////////////////////////////////////////////////////////////////////

void print(Node *rear) {
    if (!rear)
        return;
    
    Node *curr = rear->next;
    do {
        printf("%d ", curr->data);
        curr = curr->next;
    } while (curr != rear->next);
    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////

void sortedInsert(Node **rear, int data, int ascending) {
    // insert Node in circularly sorted Linked List
    Node *node = makeNode(data);

    if (!(*rear)) {
        *rear = node;
        node->next = node;
    }

    Node *prev = *rear;
    Node *curr = prev->next;

    if (ascending) {
        while (curr->next != (*rear)->next && curr->data <= data) {
            prev = curr;
            curr = curr->next;
        }
        if (curr == *rear && data > curr->data) {
            node->next = (*rear)->next;
            (*rear)->next = node;
            *rear = node;
            return;
        }
    } else {
        while (curr->next != (*rear)->next && curr->data >= data) {
            prev = curr;
            curr = curr->next;
        }
        if (curr == *rear && data < curr->data) {
            node->next = (*rear)->next;
            (*rear)->next = node;
            *rear = node;
            return;
        }
    }
    prev->next = node;
    node->next = curr;
}

///////////////////////////////////////////////////////////////////////////////

Node *search(Node *rear, int value) {
    Node *curr = rear->next;
    do {
        if (curr->data == value)
            return curr;
        curr = curr->next;
    } while (curr != rear->next);
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////

Node *deleteByValue(Node **rear, int value) {
    Node *prev = *rear;
    Node *curr = prev->next;
    
    int found = 0;
    do {
        if (curr->data == value) {
            found = 1;
            break;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != (*rear)->next);

    if (!found)
        return NULL;

    prev->next = curr->next;
    
    if (curr == *rear)
        *rear = prev;

    return curr;
}

///////////////////////////////////////////////////////////////////////////////

void reverse(Node **rear, int *ascending) {
    Node *prev = *rear;
    Node *curr = prev->next;
    Node *copy = curr;
    Node *next;

    do {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        if (curr == *rear)
            (*rear)->next = prev;
    } while (curr != (*rear)->next);
    
    *rear = copy;
    *ascending = 1 - (*ascending);
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    int array[5] = {3, 4, 8, 10, 12};
    Node* rear = makeCircularLinkedList(array, 5);
    int ascending = 1;
    print(rear);

    sortedInsert(&rear, 6, ascending);
    sortedInsert(&rear, 7, ascending);
    sortedInsert(&rear, 15, ascending);
    print(rear);

    Node* searched = search(rear, 8);
    if (!searched)
        printf("Not found \n");
    else
        printf("Found at address: %x \n", searched);

    Node* deleted = deleteByValue(&rear, 15);
    if (!deleted)
        printf("Not found \n");
    else {
        printf("Deleted element = %d, Updated list = ", deleted -> data);
        print(rear);
    }
    
    reverse(&rear, &ascending);
    print(rear);
    sortedInsert(&rear, 13, ascending);
    print(rear);

    return 0;
}