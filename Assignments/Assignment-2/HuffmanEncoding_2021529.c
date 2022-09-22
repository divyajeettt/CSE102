# include <stdio.h>
# include <stdlib.h>
# include <string.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct Node {
    int data;
    int character;
    struct Node *left, *right;
} Node;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Memory Allocation Functions

Node *makeNode(int data, int character) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->left = node->right = NULL;
    node->character = character;
    node->data = data;
    return node;
}

char *makeCharArray(int size) {
    char *array = (char *)malloc(size*sizeof(char));
    for (int i=0; i < size; i++)
        array[i] = '\0';
    return array;
}

char **makeStrArray(int arraySize, int strLength) {
    char **array = (char **)malloc(arraySize*sizeof(char *));
    for (int i=0; i < arraySize; i++) {
        array[i] = makeCharArray(strLength + 5);
    }
    return array;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Utility Functions

void swap(Node **array, int i, int j) {
    Node *temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

int binaryToDecimal(char *binary) {
    // converts 8 bit binary number to integer

    int decimal = 0;
    while (*binary != '\0') {
        decimal <<= 1;
        if (*binary == '1')
            decimal++;
        binary++;
    }
    return decimal;
}

char *decimalToBinary(int decimal) {
    // converts integer to 8 bit binary number

    char *binary = makeCharArray(9);
    int bit = 128;
    while (bit > 0) {
        *binary++ = ((bit & decimal) ? '1' : '0');
        bit >>= 1;
    }
    return (binary - 8);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Heap Implementation Functions

void heapify(Node **array, int index, int n) {
    int end = n - 1;

    while (index <= (end-1)/2) {
        int min = index;
        int left = 2*index + 1, right = 2*index + 2;

        if (array[left]->data < array[min]->data)
            min = left;

        if (right <= end && array[right]->data < array[min]->data)
            min = right;

        if (min == index)
            break;
        else {
            swap(array, index, min);
            index = min;
        }
    }
}

void heapFromArray(Node **array, int n) {
    for (int i=n-1; i >= 0; i--)
        heapify(array, i, n);
}

void insert(Node **heap, int *n, Node *node) {
    heap[(*n)++] = node;

    int i = (*n) - 1;
    int j = (i - 1) / 2;

    while (heap[i]->data < heap[j]->data && i >= 0) {
        swap(heap, i, j);
        i = j;
        j = (i - 1) / 2;
    }
}

Node *currMin(Node **heap, int n) {
    // NULL denotes empty heap (not needed as per this implementation)
    return ((n != 0) ? heap[0] : NULL);
}

Node *extractMin(Node **heap, int *n) {
    Node *extracted = currMin(heap, *n);

    heap[0] = heap[--(*n)];
    heapify(heap, 0, *n); // Heapify the modified heap

    return extracted;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Huffman Tree Implementation Functions

Node *buildHuffmanTree(Node **heap, int *n) {
    while ((*n) != 1) {
        Node *min1 = extractMin(heap, n);
        Node *min2 = extractMin(heap, n);

        Node *parent = makeNode(min1->data + min2->data, 269); // 269 is a placeholder
        parent->left = min1;
        parent->right = min2;

        insert(heap, n, parent);
    }
    // the Node left in the heap is the huffmanRoot
    return extractMin(heap, n);
}

void getCodes(Node *root, char *characters, char **codes, char *bits) {
    // store the characters and codes in arrays
    static int index = 0;

    if (root->character != 269) {
        characters[index] = root->character;
        codes[index++] = bits;
    }
    else {
        char *leftCopy = makeCharArray(strlen(bits) + 5);
        char *rightCopy = makeCharArray(strlen(bits) + 5);

        getCodes(root->left, characters, codes, strcat(strcpy(leftCopy, bits), "0"));
        getCodes(root->right, characters, codes, strcat(strcpy(rightCopy, bits), "1"));
    }
}

Node *reconstructHuffmanTree(char *characters, char **codes, int n) {
    Node *root = makeNode(0, 269);

    for (int i=0; i < n; i++) {
        Node *curr = root;

        for (int j=0; codes[i][j] != '\0'; j++) {
            if (codes[i][j] == '0') {
                curr->left = ((!curr->left) ? makeNode(0, 269) : curr->left);
                curr = curr->left;
            } else {
                curr->right = ((!curr->right) ? makeNode(0, 269) : curr->right);
                curr = curr->right;
            }
        }
        curr->character = characters[i];
    }

    return root;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void compress(char *inputFile, char *outputFile) {
    freopen(inputFile, "r", stdin);

    int frequencyArray[256] = {0};
    char character;

    while ((character = getchar()) != EOF)
        frequencyArray[character]++;

    frequencyArray[0] = 1; // Treat as EOF
    fclose(stdin);

    int n = 0;
    for (int i=0; i < 256; i++)
        n += (frequencyArray[i] != 0);

    Node **heap = (Node **)malloc(n*sizeof(Node *));
    int count = 0;
    for (int i=0; i < 256; i++) {
        if (frequencyArray[i] != 0)
            heap[count++] = makeNode(frequencyArray[i], i);
    }
    heapFromArray(heap, n);

    Node *huffmanRoot = buildHuffmanTree(heap, &n);

    char **huffmanCodes = makeStrArray(count, 260);
    char *characters = makeCharArray(count + 5);
    char *bits = makeCharArray(260); // max depth of Huffman Tree can be 256

    getCodes(huffmanRoot, characters, huffmanCodes, bits);

    // Print the Codes
    printf("The Huffman Codes are as follows: \n");
    for (int i=0; i < count; i++) {
        if (characters[i] != 0)
            printf("%c: %s\n", characters[i], huffmanCodes[i]);
    }

    // Write the output file
    freopen(outputFile, "wb", stdout);

    printf("%d \n", count);
    char **codeArray = makeStrArray(256, 260);
    for (int i=0; i < count; i++) {
        codeArray[characters[i]] = huffmanCodes[i];
        printf("%d %s\n", characters[i], huffmanCodes[i]);
    }
    fclose(stdout);

    freopen(inputFile, "r", stdin);
    freopen("compress.txt", "w", stdout);

    int counter = 0;
    while ((character = getchar()) != EOF) {
        printf("%s", codeArray[character]);
        counter += strlen(codeArray[character]);
    }
    printf("%s", codeArray[0]); // Add EOF character
    counter += strlen(codeArray[0]);

    // suffix '1' until the file is divisible into bytes
    while ((counter++ % 8) != 0) {
        printf("1");
    }

    fclose(stdin);
    fclose(stdout);

    freopen("compress.txt", "r", stdin);
    freopen(outputFile, "ab", stdout);

    char *code = makeCharArray(9);
    counter = 0;
    char bit;
    while ((bit = getchar()) != EOF) {
        code[counter++] = bit;
        if (counter == 8)
            printf("%c", binaryToDecimal(code));
        counter = counter % 8;
    }

    fclose(stdin);
    fclose(stdout);
    remove("compress.txt");
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void decompress(char *inputFile, char *outputFile) {
    printf("Decompression in Progress...\n");
    freopen(inputFile, "rb", stdin);

    int count;
    scanf("%d", &count);

    char **huffmanCodes = makeStrArray(count, 260);
    char *characters = makeCharArray(count + 5);

    for (int i=0; i < count; i++)
        scanf("%d %s", &characters[i], huffmanCodes[i]);

    freopen("decompress.txt", "w", stdout);

    int character;
    getchar(); // waste a newline character, as present in the file
    while ((character = getchar()) != EOF) {
        char *code = decimalToBinary(character);
        printf("%s", code);
    }

    fclose(stdin);
    fclose(stdout);

    freopen("decompress.txt", "r", stdin);
    freopen(outputFile, "w", stdout);

    Node *huffmanRoot = reconstructHuffmanTree(characters, huffmanCodes, count);

    while (1) {
        Node *curr = huffmanRoot;
        while (curr->character == 269) {
            char bit = getchar();
            curr = ((bit == '0') ? curr->left : curr->right);
        }
        if (curr->character != 0)
            printf("%c", curr->character);
        else
            break; // Break out of the loop when EOF character [chr(0)] is decoded
    }

    fclose(stdin);
    fclose(stdout);
    remove("decompress.txt");
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    char inputFile[128], outputFile[128];
    int mode;

    printf("Enter the name of Input File: "); scanf("%s", inputFile);
    printf("Enter the name of Output File: "); scanf("%s", outputFile);
    printf("Enter mode (0/1): "); scanf("%d", &mode);

    if (mode == 0)
        compress(inputFile, outputFile);
    else
        decompress(inputFile, outputFile);

    return 0;
}