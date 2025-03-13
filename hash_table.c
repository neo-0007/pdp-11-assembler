#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define INITIAL_CAPACITY 10

typedef struct{
    char *key;
    char *value;
} ht_item;

typedef struct{
    ht_item *items;
    size_t capacity;
    size_t length;    
} ht;

ht* ht_create(){
    ht* table = malloc(sizeof(ht));
    if(table == NULL){
        return NULL;
    }

    table->capacity = INITIAL_CAPACITY;
    table->length = 0;
    table->items = calloc(table->capacity, sizeof(ht_item));

    if(table->items == NULL){
        free(table);
        return NULL;
    }

    return table;
}

void ht_delete(ht* table){
    for (size_t i = 0; i < table->capacity; i++) {
        free(table->items[i].key);
        free(table->items[i].value);
    }

    free(table->items);
    free(table);
}

unsigned int get_hash(char* input){
    unsigned int hash = 0;
    unsigned int weight = 31;
    for(size_t i = 0; input[i] != '\0'; i++){
        hash += (input[i] * (weight ^ i));
    }

    return hash;
}

void ht_expand(ht** table) {
    ht* old_table = *table;
    size_t old_capacity = old_table->capacity;


    ht* new_table = ht_create();
    new_table->capacity = old_capacity * 2;
    new_table->items = calloc(new_table->capacity, sizeof(ht_item));

    if (new_table->items == NULL) {
        perror("Failed to expand hash table");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < old_capacity; i++) {
        if (old_table->items[i].key != NULL) {
            unsigned int new_index = get_hash(old_table->items[i].key) % new_table->capacity;
            new_table->items[new_index] = old_table->items[i]; 
        }
    }

    free(old_table->items);
    free(old_table);

    *table = new_table;
}

int ht_insert(ht** table, char* key, char* value){
    if((*table)->length == (*table)->capacity){
        ht_expand(table);
    }

    unsigned int hash_of_key = get_hash(key);
    size_t index = hash_of_key % (*table)->capacity;

    while ((*table)->items[index].key != NULL) { 
        index = (index + 1) % (*table)->capacity;
    }

    (*table)->items[index].key = strdup(key);
    (*table)->items[index].value = strdup(value);

    (*table)->length++;
    return 0;
}

char* ht_get_value(ht* table, char* key){
    unsigned int hash_of_key = get_hash(key);
    size_t index = hash_of_key % table->capacity;

    while (table->items[index].key != NULL) {
        if (strcmp(table->items[index].key, key) == 0) {
            return table->items[index].value;
        }
        index = (index + 1) % table->capacity; 
    }

    return NULL;
}

int main(){
    clock_t start, end;
    
    start = clock();
    ht* test_table = ht_create();
    end = clock();
    printf("\nTime taken for creating ht: %f µs\n", (double)(end - start) / CLOCKS_PER_SEC * 1e6);

    start = clock();
    ht_insert(&test_table, "a", "1");
    ht_insert(&test_table,"b","2");
    ht_insert(&test_table,"c","3");
    end = clock();
    printf("\nTime taken for insertion: %f µs\n", (double)(end - start) / CLOCKS_PER_SEC * 1e6);

    start = clock();
    char* valueA = ht_get_value(test_table, "a");
    char* valueB = ht_get_value(test_table, "b");
    char* valueC = ht_get_value(test_table, "c");
    end = clock();
    printf("\nTime taken for searching: %f µs\n", (double)(end - start) / CLOCKS_PER_SEC * 1e6);

    printf("\nValue at key 'a': %s\n", valueA);
    printf("\nValue at key 'b': %s\n", valueB);
    printf("\nValue at key 'c': %s\n", valueC);

    ht_delete(test_table);
    return 0;
}