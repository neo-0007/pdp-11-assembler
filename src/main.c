#include <stdio.h>
#include <stdlib.h>
#include "symboltable.h"
#include "opcodes_entry.h"
#include "a_to_m.h"

int main(int argc, char *argv[]){

    int line_count;
    int temp;
    bin_value_with_type* opcode_temp;
    char* operand_temp;

    char ***final_token_list = NULL;
    int *tokens_per_line = NULL;
    ht* symbol_table = ht_create();
    ht* so_table = ht_create();
    ht* do_table = ht_create();
    ht* bo_table = ht_create();

    FILE *file = fopen("output.txt", "w");
	if (file == NULL) {
		perror("Error opening file");
		return 1;
	}

    temp= insert_opcodes_to_ht(&so_table,&do_table,&bo_table);
    if(temp==-1){
        printf("Opcode tables not created!!");
        return -1;
    }

    line_count = tokenlist(&final_token_list, &tokens_per_line,argv[argc-1]);
    symbol_table = symboltable(&final_token_list,&tokens_per_line,&line_count);

    for (size_t i = 0; i<line_count;i++){
        opcode_temp =  get_opcode_data(final_token_list[i][0],so_table,do_table,bo_table);


        if(opcode_temp->operand_type==SINGLE_OPERAND){

            operand_temp = get_operand_data(final_token_list[i][1]);
            fprintf(file,"\n%ld : %s%s\n",i,opcode_temp->bin_val,operand_temp);

        }else if(opcode_temp->operand_type==DOUBLE_OPERAND){

            operand_temp = get_operand_data(final_token_list[i][1]);
            fprintf(file,"\n%ld : %s%s",i,opcode_temp->bin_val,operand_temp);
            operand_temp = get_operand_data(final_token_list[i][2]);
            fprintf(file,"%s\n",operand_temp);

        }else if(opcode_temp->operand_type==BRANCH_OPERAND){

            temp = ht_get_int_value(symbol_table,final_token_list[i][1]);
            temp = temp-(i+1);
            operand_temp = itobconverter(temp);
            fprintf(file,"\n%ld : %s%s\n",i,opcode_temp->bin_val,operand_temp);

        }else if(opcode_temp->operand_type==INVALID_OPERAND){
            fprintf(file,"\nLine[%ld] has error\n",i);
        }
    }

    freeall(&final_token_list,&tokens_per_line,line_count);
    ht_delete(symbol_table);
    ht_delete(so_table);
    ht_delete(do_table);
    ht_delete(bo_table);
    fclose(file);
    return 0;

}