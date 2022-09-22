# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Item {
    int key;    // Items may be given value according to requirements
    struct Item *next;
} Item;

Item *makeItem(int key) {
    Item *item = (Item *)malloc(sizeof(Item));
    item->next = NULL;
    item->key = key;
    return item;
}

///////////////////////////////////////////////////////////////////////////////

typedef struct Table {
    Item **table;
    int length;    // current number of Items in table
    int size;      // size of table
} Table;

Table *makeTable(int size) {
    Table *table = (Table *)malloc(sizeof(Table));
    table->table = (Item **)malloc(size*sizeof(Item *));
    for (int i=0; i < size; i++) {
        table->table[i] = NULL;
    }
    table->size = size;
    table->length = 0;
    return table;
}

///////////////////////////////////////////////////////////////////////////////

void print(Table *table) {
    for (int i=0; i < table->size; i++) {
        printf("%d: ", i);
        for (Item *curr = table->table[i]; curr; curr=curr->next)
            printf("%d ", curr->key);
        printf("\n");
    }
}

///////////////////////////////////////////////////////////////////////////////

int hashKey(int key, Table *table) {
    return (key % table->size);
}

int hashItem(Item *item, Table *table) {
    return hashKey(item->key, table);
}

///////////////////////////////////////////////////////////////////////////////

void insert(Table *table, Item *item) {
    int index = hashItem(item, table);

    // linkedList append
    Item *currItem = table->table[index];
    item->next = currItem;
    table->table[index] = item;

    table->length++;
}

///////////////////////////////////////////////////////////////////////////////

Item *search(Table *table, int key) {
    int index = hashKey(key, table);
    for (Item *curr=table->table[index]; curr; curr=curr->next) {
        if (curr->key == key)
            return curr;
    }
    return NULL;    // return NULL for unsuccsessful search
}

///////////////////////////////////////////////////////////////////////////////

Item *delete(Table *table, int key) {
    int index = hashKey(key, table);

    Item *curr = table->table[index];
    Item *next = curr->next;

    table->length--;

    if (curr->key == key) {
        table->table[index] = next;
        return curr;
    }

    for (; curr; curr=curr->next) {
        if (next->key == key) {
            curr->next = next->next;
            return next;
        }
        curr = next;
        next = next->next;
    }
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    Table *hashTable = makeTable(10);
    int nums[25] = {19, 30, 6, 4, 84, 8, 12, 23, 68, 45, 78, 9, 85, 20, 60, 15, 52, 1, 2, 65, 11, 67, 80, 73, 63};

    for (int i=0; i < 15; i++) {
        insert(hashTable, makeItem(nums[i]));
    }

    print(hashTable);

    Item *searched = search(hashTable, 30);
    // Item *searched = search(hashTable, 29);
    if (!searched)
        printf("Not found! \n");
    else
        printf("%d found \n", searched->key);

    printf("\n");
    delete(hashTable, 20); delete(hashTable, 78);  delete(hashTable, 6);
    print(hashTable);

    return 0;
}