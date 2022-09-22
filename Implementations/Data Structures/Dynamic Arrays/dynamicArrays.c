# include <stdio.h>
# include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////

typedef struct Array {
    int size, length, *list;
} Array;

///////////////////////////////////////////////////////////////////////////////

Array *makeArray(int size) {
    Array *array = (Array *)malloc(sizeof(Array));
    array->list = (int *)malloc(size*sizeof(int));
    array->size = size;
    array->length = 0;
    return array;
}

///////////////////////////////////////////////////////////////////////////////

void print(Array *array) {
    for (int i=0; i < array->length; i++)
        printf("%d ", array->list[i]);
    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////

void append(Array *array, int data) {
    if (array->length == array->size) {
        array->size *= 2;
        array->list = (int *)realloc(array->list, array->size*sizeof(int));
    }
    array->list[array->length++] = data;
}

///////////////////////////////////////////////////////////////////////////////

void insert(Array *array, int position, int data) {
    append(array, data);
    int n = array->length - 1;

    for (int i=position; i <= n; i++) {
        int temp = array->list[n];
        array->list[n] = array->list[i];
        array->list[i] = temp;
    }
}

///////////////////////////////////////////////////////////////////////////////

int delete(Array *array, int position) {
    // -1 represents IndexError
    if (position >= array->length)
        return -1;
    else {
        for (int i=position; i < array->length-1; i++)
            array->list[i] = array->list[i+1];

        array->length--;
        return 1;
    }
}

///////////////////////////////////////////////////////////////////////////////

int main() {
    Array *array = makeArray(2);

    for (int i=1; i < 11; i++) {
        append(array, i);
        print(array);
    }

    delete(array, 5);
    print(array);

    delete(array, 8);
    print(array);

    for (int i=0; i < 7; i++) {
        delete(array, 0);
        print(array);
    }

    for (int i=0; i <= 8; i++) {
        insert(array, 0, i);
        print(array);
    }

    delete(array, 9);
    insert(array, 0, 9);
    print(array);

    insert(array, 4, 100);
    print(array);

    return 0;
}