#ifndef A_TO_M_H
#define A_TO_M_H

#include "hash_table.h"

typedef enum{
    SINGLE_OPERAND,
    DOUBLE_OPERAND,
    BRANCH_OPERAND,
    INVALID_OPERAND
} op_type;

typedef struct{
    char *bin_val;
    op_type operand_type;
} bin_value_with_type;

typedef struct {
    char binary_str[7];   // 6-bit binary representation of mode + reg
    char x_binary[17];    // 16-bit binary representation of X (if applicable)
} operand_data;

bin_value_with_type* get_opcode_data(char* opcode,ht* so_table,ht* do_table,ht* bo_table);

operand_data get_operand_data(char* operand);

#endif
