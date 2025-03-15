#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "tokenizer.h"
#include "hash_table.h"

//REMOVES ALL LABELS FROM THE TOKEN LIST
//STORES THE LABEL LOCATION IN A HASHTABLE
//RETURNS SYMBOL HASH TABLE
ht* symboltable(char ****token_list, int **tokens_per_line, int *lines );


char* itobconverter(int num);

#endif
