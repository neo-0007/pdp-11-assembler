#include "a_to_m.h"
/*
[
    ["MOV","#5","R1"],
    ["MOV","#3","R2"],
    ["ADD","R1","R2"]
];
*/

/*
    0001 010111 000001
    0000 000000 001001
    0001 010111 000010
    0000 000000 000011
    0110 000001 000010
*/


bin_value_with_type* get_opcode_data(char* opcode,ht* so_table,ht* do_table,ht* bo_table){
    char* bin_value;
    bin_value_with_type* result = malloc(sizeof(bin_value_with_type));
    if (result==NULL){
        return NULL;
    }
    
    if(ht_get_value(so_table,opcode)!=NULL){
        bin_value=ht_get_value(so_table,opcode);
        result->bin_val=bin_value;
        result->operand_type=SINGLE_OPERAND;

        return result;
    }else if(ht_get_value(do_table,opcode)!=NULL){
        bin_value=ht_get_value(do_table,opcode);
        result->bin_val=bin_value;
        result->operand_type=DOUBLE_OPERAND;

        return result;
    }else if(ht_get_value(bo_table,opcode)!=NULL){
        bin_value=ht_get_value(bo_table,opcode);
        result->bin_val=bin_value;
        result->operand_type=BRANCH_OPERAND;

        return result;        
    }

    result->bin_val=NULL;
    result->operand_type=INVALID_OPERAND;

    return result;
}


operand_data get_operand_data(char* operand){
    int reg_num;
    int x_value = 0;
    int mode = -1;
    operand_data result;
    
    strcpy(result.binary_str, "");  // Initialize as empty
    strcpy(result.x_binary, "");

    // Register Mode (Rn)
    if (sscanf(operand, "R%d", &reg_num) == 1) {
        mode = 0b000;
    }
    // Register Deferred (Rn)
    else if (sscanf(operand, "(R%d)", &reg_num) == 1) {
        mode = 0b001;
    }
    // Autoincrement (Rn)+
    else if (sscanf(operand, "(R%d)+", &reg_num) == 1) {
        mode = 0b010;
    }
    // Autoincrement Deferred @(Rn)+
    else if (sscanf(operand, "@(R%d)+", &reg_num) == 1) {
        mode = 0b011;
    }
    // Autodecrement -(Rn)
    else if (sscanf(operand, "-(R%d)", &reg_num) == 1) {
        mode = 0b100;
    }
    // Autodecrement Deferred @-(Rn)
    else if (sscanf(operand, "@-(R%d)", &reg_num) == 1) {
        mode = 0b101;
    }
    // Indexed X(Rn) (ignore X, only extract Rn)
    else if (sscanf(operand, "%d(R%d)",&x_value,&reg_num) == 2) {
        mode = 0b110;
    }
    // Indexed Deferred @X(Rn) (ignore X, only extract Rn)
    else if (sscanf(operand, "@%d(R%d)",&x_value,&reg_num) == 2) {
        mode = 0b111;
    }
    
    if (mode == -1 || reg_num < 0 || reg_num > 7) {
        strcpy(result.binary_str, "ERROR");
        return result; 
    }

    int value = (mode << 3) | reg_num;

    for (int i = 5; i >= 0; i--) {
        result.binary_str[5 - i] = ((value >> i) & 1) ? '1' : '0';
    }
    result.binary_str[6] = '\0';

    if(mode == 0b110 || mode == 0b111){
	    for(int i = 15; i>=0;i--){
	    	result.x_binary[15 - i] = ((x_value >> i) & 1) ? '1' : '0';
	    }
	    result.x_binary[16] = '\0';
    }

    return result;
}





