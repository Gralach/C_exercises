//use standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// linkedlist for chaining 
// if there is a collision with the other 
// value in a hashtable
typedef struct Node {
    int key;
    int value;
    struct Node* next;
 } Node;

// basically a dict in Python
// Lookup time O(1) best case
// Lookup time O(n) worst case
typedef struct HashTable{
    Node** buckets; //pointer to node
    int bucket_size; //bigger bucket_size is better for less collision but takes more memory
} HashTable;

// hash function put index in the HashTable
int hash(int key, int bucket_size)
{
    return key % bucket_size;
}

// Initializes the hash table by allocating memory for it
HashTable* createHashTable(int bucket_size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));  // Allocate memory for the hash table structure
    ht->bucket_size = bucket_size;                          // Set the size of the bucket
    ht->buckets = (Node**)calloc(bucket_size, sizeof(Node*)); // Allocate memory for the bucket array and initialize each entry to NULL
    return ht;  // Return the pointer to the newly created hash table
}

Node* createNode(int key, int value){
    Node* newNode = (Node*)malloc(sizeof(Node*)); //allocate memory for new node
    newNode-> key = key; // set new node key as the input key
    newNode-> value = value; // set new node value as the input value 
    newNode-> next = NULL; 
    return newNode;
}

// insert operation
void insert(HashTable* ht, int key, int value) {
    // create index with hash function
    int index = hash(key, ht->bucket_size);
    // create new Node using given key and value
    Node* newNode = createNode(key, value);
    // insert the new node at beginning of list
    newNode->next = ht->buckets[index];
    // update pointer of hashtable to point to newNode
    ht->buckets[index] = newNode;
}

void delete(HashTable* ht, int key) {
    int index = hash(key, ht->bucket_size);
    Node* current = ht->buckets[index]; 
    Node* prev = NULL; 

    while (current != NULL) { 
        if (current->key == key) {  
            if (prev == NULL) { // if it's the first node
                //update the pointer of the hashtable to the next node
                ht->buckets[index] = current->next; 
            } else {
                // if it's not the first node then unlink
                prev->next = current->next;
            }
            free(current);  // Free the memory for the node being deleted
            return; // Exit the function after deleting the node
        }
        prev = current; // Move the previous pointer to the current node
        current = current->next; // Move the current pointer to the next node
    }
}

Node* search(HashTable* ht, int key){
    int index = hash(key, ht->bucket_size);
    Node* current = ht->buckets[index];
    // if it's not the last node
    while(current!= NULL){
        // check if key is the same or not
        if(current->key == key) return current;
        // go to the next node
        current = current -> next;
    }
    return NULL;
}

// Function to display the result of a search operation
void printSearchResult(HashTable* ht, int key) {
    Node* result = search(ht, key); // Call the search function to find the node with the key
    if (result != NULL) { // If the node was found
        printf("The value is %d\n", result->value); // Print the key and value
    }
}

// Struct to store the operations
typedef struct Operation {
    char type[10];  // Operation type ("insert", "search", or "delete")
    int key;
    int value;
} Operation;

int main() {
    int bucket_size, n;
    scanf("%d %d", &bucket_size, &n);

    HashTable* ht = createHashTable(bucket_size);;
    
    // Create an array to store the operations
    Operation* operations = (Operation*)malloc(n * sizeof(Operation));

    for (int i = 0; i < n; i++){
        scanf("%s", operations[i].type);
        if (strcmp(operations[i].type, "insert")== 0) {
            scanf("%d %d", &operations[i].key, &operations[i].value);
        }
        else{
            scanf("%d", &operations[i].key);
            operations[i].value = 0;
        }
    }

    for (int i = 0; i < n; i++){
        printf("%d\n",i);
        if (strcmp(operations[i].type, "insert") == 0) {
            insert(ht, operations[i].key, operations[i].value);
        } else if (strcmp(operations[i].type, "search") == 0) {
            printSearchResult(ht, operations[i].key);
        } else if (strcmp(operations[i].type, "delete") == 0) {
            delete(ht, operations[i].key);
        }
        printf("**End***\n");
    }

}