#include <time.h>
#include "hash_table.h"


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