#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

// Hash Table structure
struct HashTable {
    int* array;
    int size;
};

// Initialize a new hash table
struct HashTable* initHashTable(int size);

// Hash function (simple modulo)
int hash(int key, int size);

// Insert key into the hash table using linear probing
void insertLinearProbing(struct HashTable* table, int key);

// Search for a key in the hash table
bool search(struct HashTable* table, int key);

// Delete a key from the hash table
void deleteKey(struct HashTable* table, int key);

// Display the contents of the hash table
void displayHashTable(struct HashTable* table);

int main() {
    struct HashTable* table = initHashTable(SIZE);
    int choice, key;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert key\n");
        printf("2. Search key\n");
        printf("3. Delete key\n");
        printf("4. Display hash table\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insertLinearProbing(table, key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(table, key)) {
                    printf("Key %d found in the hash table.\n", key);
                } else {
                    printf("Key %d not found in the hash table.\n", key);
                }
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteKey(table, key);
                break;
            case 4:
                displayHashTable(table);
                break;
            case 5:
                printf("Exiting...\n");
                free(table->array);
                free(table);
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}

struct HashTable* initHashTable(int size) {
    struct HashTable* table = (struct HashTable*)malloc(sizeof(struct HashTable));
    table->array = (int*)malloc(size * sizeof(int));
    table->size = size;

    // Initialize all elements to -1 (indicating empty slot)
    for (int i = 0; i < size; i++) {
        table->array[i] = -1;
    }

    return table;
}

int hash(int key, int size) {
    return key % size;
}

void insertLinearProbing(struct HashTable* table, int key) {
    int index = hash(key, table->size);

    while (table->array[index] != -1) {
        // Linear probing: move to the next slot if collision occurs
        index = (index + 1) % table->size;
    }

    table->array[index] = key;
    printf("Key %d inserted at index %d.\n", key, index);
}

bool search(struct HashTable* table, int key) {
    int index = hash(key, table->size);
    int originalIndex = index;

    while (table->array[index] != -1) {
        if (table->array[index] == key) {
            return true;
        }

        // Linear probing: move to the next slot if collision occurs
        index = (index + 1) % table->size;

        // If we've checked all slots and haven't found the key, break the loop
        if (index == originalIndex) {
            break;
        }
    }

    return false;
}

void deleteKey(struct HashTable* table, int key) {
    int index = hash(key, table->size);
    int originalIndex = index;

    while (table->array[index] != -1) {
        if (table->array[index] == key) {
            table->array[index] = -1;
            printf("Key %d deleted from index %d.\n", key, index);
            return;
        }

        // Linear probing: move to the next slot if collision occurs
        index = (index + 1) % table->size;

        // If we've checked all slots and haven't found the key, break the loop
        if (index == originalIndex) {
            break;
        }
    }

    printf("Key %d not found for deletion.\n", key);
}

void displayHashTable(struct HashTable* table) {
    printf("Hash Table:\n");
    for (int i = 0; i < table->size; i++) {
        printf("Index %d: ", i);
        if (table->array[i] != -1) {
            printf("%d", table->array[i]);
        } else {
            printf("Empty");
        }
        printf("\n");
    }
}
