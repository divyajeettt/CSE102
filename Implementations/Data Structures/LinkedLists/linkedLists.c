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

///////////////////////////////////////////////////////////////////////////////

void print(Node *head) {
    for (Node *curr=head; curr; curr=curr->next)
        printf("%d ", curr->data);
    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////

void append(Node **tail, int data) {
    Node *node = makeNode(data);
    (*tail)->next = node;
    *tail = node;
}

///////////////////////////////////////////////////////////////////////////////

Node *insert(Node *head, int data, int position) {
    // returns the head

    Node *curr = head;
    Node *node = makeNode(data);

    if (position == 1) {
        node->next = head;
        return node;
    }

    for (int i=1; i != position-1; i++)
        curr = curr->next;
    
    node->next = curr->next;
    curr->next = node;
    return head;
}

///////////////////////////////////////////////////////////////////////////////

Node *search(Node *head, int value) {
    for (Node *curr=head; curr; curr=curr->next) {
        if (curr->data == value)
            return curr;
    }
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////

Node *searchRecursive(Node *head, int value) {
    if (!head)
        return NULL;
    else if (head->data == value)
        return head;
    else
        return searchRecursive(head->next, value);
}

///////////////////////////////////////////////////////////////////////////////

Node *deleteByPosition(Node **head, int position) {
    Node *curr = *head;
    Node *prev = NULL;

    if (position == 1) {
        *head = curr->next;
        return curr;
    }

    for (int i=0; i != position-1; i++) {
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next;
    return curr;
}

///////////////////////////////////////////////////////////////////////////////

Node *reverse(Node *head) {
    if (!head) 
        return NULL;

    Node *prev = NULL, *curr = head;
    Node *next;

    while (curr) {
        next = curr->next;    // Find the next Node
        curr->next = prev;    // Reverse the link on current Node
        prev = curr;          // Update previous Node to be the current Node
        curr = next;          // Make the current Node the next Node
    }

    return prev;
}

///////////////////////////////////////////////////////////////////////////////

Node *reverseRecursive(Node *head) {
    if (!head)
        return NULL;
    
    Node *next = head->next;

    if (!next)
        return head;
    
    Node *reversedSubList = reverseRecursive(next);
    next->next = head;
    head->next = NULL;
    return reversedSubList;
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    Node *head = makeNode(1);
    Node *tail = head;

    for (int i=2; i < 11; i++) {
        append(&tail, i);
    }
    print(head);

    // head = insert(head, 3, 1);
    // print(head);

    // Node* searched = search(head, 2);
    // if (!searched)
    //     printf("Not found \n");
    // else
    //     printf("Found at address: %x \n", searched);

    // Node* searched = searchRecursive(head, 10);
    // if (!searched)
    //     printf("Not found \n");
    // else
    //     printf("Found at address: %x \n", searched);

    // Node* deleted = deleteByPosition(&head, 3);
    // if (!deleted)
    //     printf("Not found \n");
    // else {
    //     printf("Deleted element = %d, Updated list = ", deleted -> data);
    //     print(head);
    // }

    // Node* reversed = reverse(head);
    // print(reversed);

    // Node* reversed = reverseRecursive(head);
    // print(reversed);

    return 0;
}