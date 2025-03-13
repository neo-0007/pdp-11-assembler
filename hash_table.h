#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITIAL_CAPACITY 10

//ITEM WITH KEY VALUE PAIR
typedef struct {
    char *key;
    char *value;
} ht_item;

//HASH TABLE 
typedef struct {
    ht_item *items;
    size_t capacity;
    size_t length;    
} ht;


//TO CREATE A HASH TABLE
ht* ht_create();

//TO DELETE A HASH TABLE
void ht_delete(ht* table);

//TO INSERT A KEY VALUE PAIR
//RETURNS 0 (SUCCESS)
//RETURNS -1 (FAILURE)
int ht_insert(ht** table, char* key, char* value);

//TO GET THE VALUE USING A KEY
//RETURNS NULL IF KEY IS NOT THERE
char* ht_get_value(ht* table, char* key);

#endif 
