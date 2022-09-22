# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Item {
    int key;    // Items may be given value according to requirements
} Item;


Item *makeItem(int key) {
    Item *item = (Item *)malloc(sizeof(Item));
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
        table->table[i] = makeItem(-1);
    }
    table->size = size;
    table->length = 0;
    return table;
}

///////////////////////////////////////////////////////////////////////////////

void print(Table *table) {
    for (int i=0; i < table->size; i++) {
        printf("%d ", table->table[i]->key);
    }
    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////

int hashKey(int key, Table *table) {
    return (key % table->size);
}

int hashItem(Item *item, Table *table) {
    return hashKey(item->key, table);
}

int f(int x) {
    // probing function (may also be implemented as another hash function)
    return x * x;
}

///////////////////////////////////////////////////////////////////////////////

void insert(Table *table, Item *item) {
    int h = hashItem(item, table);

    int index;
    for (int i=0; i < table->size; i++) {
        index = (h + f(i)) % table->size;
        if (table->table[index]->key == -1)
            break;
    }

    table->table[index] = item;
    table->length++;
}

///////////////////////////////////////////////////////////////////////////////

Item *search(Table *table, int key) {
    int h = hashKey(key, table);

    int index;
    for (int i=0; i < table->size; i++) {
        index = (h + f(i)) % table->size;
        if (table->table[index]->key == key)
            return table->table[index];
    }
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////

Item *delete(Table *table, int key) {
    int h = hashKey(key, table);

    int index;
    for (int i=0; i < table->size; i++) {
        index = (h + f(i)) % table->size;
        if (table->table[index]->key == key) {
            Item *copy = table->table[index];
            table->table[index]->key = -1;
            table->length--;
            return copy;
        }
    }
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    int n = 19;
    Table *hashTable = makeTable(n);
    int nums[25] = {19, 30, 6, 4, 84, 8, 12, 23, 68, 45, 78, 9, 85, 20, 60, 15, 52, 1, 2, 65, 11, 67, 80, 73, 63};

    for (int i=0; i < n; i++) {
        insert(hashTable, makeItem(nums[i]));
        print(hashTable);
    }

    Item *searched = search(hashTable, 30);
    // Item *searched = search(hashTable, 29);
    if (!searched)
        printf("Not found! \n");
    else
        printf("%d found \n", searched->key);

    printf("\n");
    delete(hashTable, 19); delete(hashTable, 45);
    delete(hashTable, 68); delete(hashTable, 2);

    print(hashTable);

    insert(hashTable, makeItem(19));
    insert(hashTable, makeItem(1000));
    print(hashTable);

    return 0;
}