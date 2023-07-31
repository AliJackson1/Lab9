#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
};

// Node for the separate chaining
struct Node
{
    struct RecordType record;
    struct Node* next;
};

// HashType (Hash table with separate chaining)
struct HashType
{
    struct Node* head;
};

// Hash table size
#define HASH_SIZE 10

// Compute the hash function
int hash(int x)
{
    return x % HASH_SIZE;
}

// Function to insert a record into the hash table
void insertRecord(struct HashType* hashTable, struct RecordType record)
{
    int index = hash(record.id);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode)
    {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newNode->record = record;
    newNode->next = hashTable[index].head;
    hashTable[index].head = newNode;
}

// Function to print records from a linked list
void printLinkedList(struct Node* head)
{
    struct Node* current = head;
    while (current != NULL)
    {
        printf("\t%d %c %d\n", current->record.id, current->record.name, current->record.order);
        current = current->next;
    }
}

// Function to display records in the hash structure
void displayRecordsInHash(struct HashType* hashTable, int hashSz)
{
    int i;
    for (i = 0; i < hashSz; ++i)
    {
        printf("Index %d -> ", i);
        printLinkedList(hashTable[i].head);
        printf("\n");
    }
}

// Bubble Sort implementation for sorting records based on ID
void bubbleSort(struct RecordType pData[], int dataSz)
{
    int i, j;
    struct RecordType temp;
    for (i = 0; i < dataSz - 1; ++i)
    {
        for (j = 0; j < dataSz - i - 1; ++j)
        {
            if (pData[j].id > pData[j + 1].id)
            {
                // Swap the records
                temp = pData[j];
                pData[j] = pData[j + 1];
                pData[j + 1] = temp;
            }
        }
    }
}

// Selection Sort implementation for sorting records based on Name
void selectionSort(struct RecordType pData[], int dataSz)
{
    int i, j, minIndex;
    struct RecordType temp;
    for (i = 0; i < dataSz - 1; ++i)
    {
        minIndex = i;
        for (j = i + 1; j < dataSz; ++j)
        {
            if (pData[j].name < pData[minIndex].name)
            {
                minIndex = j;
            }
        }

        // Swap the records
        temp = pData[i];
        pData[i] = pData[minIndex];
        pData[minIndex] = temp;
    }
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType* pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

int main(void)
{
    struct RecordType* pRecords;
    int recordSz = 0;
    struct HashType hashTable[HASH_SIZE] = { NULL }; // Initialize hash table with NULL

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Insert records into the hash table
    for (int i = 0; i < recordSz; ++i)
    {
        insertRecord(hashTable, pRecords[i]);
    }

    // Display records in the hash table
    displayRecordsInHash(hashTable, HASH_SIZE);

    // Sort records based on ID using Bubble Sort
    bubbleSort(pRecords, recordSz);

    // Print sorted records based on ID
    printf("\nSorted Records based on ID:\n");
    printRecords(pRecords, recordSz);

    // Sort records based on Name using Selection Sort
    selectionSort(pRecords, recordSz);

    // Print sorted records based on Name
    printf("\nSorted Records based on Name:\n");
    printRecords(pRecords, recordSz);

    // Clean up (free allocated memory)
    free(pRecords);

    return 0;
}

