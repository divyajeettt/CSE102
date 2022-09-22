# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node;

///////////////////////////////////////////////////////////////////////////////

Node *makeNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->prev = node->next = NULL;
    return node;
}

///////////////////////////////////////////////////////////////////////////////

void printForward(Node *head) {
    for (Node *curr=head; curr; curr=curr->next)
        printf("%d ", curr->data);
    printf("\n");
}

void printBackward(Node* tail) {
    for (Node *curr=tail; curr; curr=curr->prev)
        printf("%d ", curr->data);
    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////

void append(Node **tail, int data, int *length) {
    Node *node = makeNode(data);
    (*tail)->next = node;
    node->prev = *tail;
    *tail = node;
    (*length)++;
}

void prepend(Node **head, int data, int *length) {
    Node *node = makeNode(data);
    (*head)->prev = node;
    node->next = *head;
    *head = node;
    (*length)++;

}

///////////////////////////////////////////////////////////////////////////////

void insert(Node **head, Node **tail, int data, int position, int *length) {
    if (position == 0)
        return prepend(head, data, length);

    else if (position == *length)
        return append(tail, data, length);

    else {
        Node *curr = *head;
        for (int i=1; i != position-1; i++)
            curr = curr -> next;

        Node *node = makeNode(data);
        node->next = curr->next;
        curr->next->prev = node;
        node->prev = curr;
        curr->next = node;
        (*length)++;
    }
}

///////////////////////////////////////////////////////////////////////////////

// Searching is the same as searching in Singly Linked Lists
// You may use a two-pointer approach:
//     forward = forward -> next; backward = backward -> prev
// But this approach is still O(n)
// The same cann be implemented recursively

///////////////////////////////////////////////////////////////////////////////

Node *deleteByValue(Node **head, Node **tail, int value) {
    Node *curr = *head;

    if ((*head)->data == value) {
        *head = (*head)->next;
        (*head)->prev = NULL;
    }
    else if ((*tail)->data == value) {
        curr = *tail;
        *tail = (*tail)->prev;
        (*tail)->next = NULL;
    }
    else {
        int found = 0;
        for (; curr; curr=curr->next) {
            if (curr->data == value) {
                found = 1;
                break;
            }
        }

        if (!found)
            return NULL;

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    return curr;
}

///////////////////////////////////////////////////////////////////////////////

Node *reverse(Node *head, Node **tail) {
    // Athough reversing in a doubly linked list does not make much sense
    Node *prev = NULL;
    Node *curr = head;
    Node *next;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        curr->prev = next;
        prev = curr;
        curr = next;
    }

    *tail = head;
    return prev;
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    Node *head = makeNode(1);
    Node *tail = head;
    int length = 1;

    for (int i=2; i < 11; i++) {
        append(&tail, i, &length);
    }

    printForward(head); // printBackward(tail);

    head = reverse(head, &tail);
    printForward(head);
    printBackward(tail);

    // for (int i=0; i > -11; i--) {
    //     prepend(&head, i, &length);
    // }

    // printForward(head); printBackward(tail);

    // insert(&head, &tail, 4, 6, &length);
    // printForward(head); printBackward(tail);

    // deleteByValue(&head, &tail, 4);
    // printForward(head); printBackward(tail);

    return 0;
}