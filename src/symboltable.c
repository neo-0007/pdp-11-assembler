#include "symboltable.h"


char* itobconverter(int num){

	char* bin_string = malloc(sizeof(char)*9);
	
	if(bin_string==NULL) 
		return NULL;

	for(int i = 0; i<8;i++){
		if((num&(1<<i)) ==0)
			bin_string[7-i] = '0';
		else
			bin_string[7-i] = '1';
	}
	bin_string[8] = '\0';
	return bin_string;
}


ht* symboltable(char ****token_list, int **tokens_per_line, int *lines ){
	ht* symbol_table = ht_create();
	int check;
	int s_length;
	char* first_element,*label=NULL;
	for(int i = 0;i<*lines;i++){
		first_element = (*token_list)[i][0];
		s_length = strlen(first_element);
		label = malloc(sizeof(char)*s_length);
		if(first_element[s_length-1]==':'){
			strncpy(label,first_element,s_length-1);
			label[s_length-1] = '\0';
			if((*tokens_per_line)[i]>1){
				check = ht_insert(&symbol_table,label,itobconverter(i));

				for(int j = 0; j <(*tokens_per_line)[i]-1;j++){
					strcpy((*token_list)[i][j],(*token_list)[i][j+1]);
				}
				(*tokens_per_line)[i]--;

			}
			else{	
				check = ht_insert(&symbol_table,label,itobconverter(i));
				free((*token_list)[i][0]); // Free token
				free((*token_list)[i]);    // Free token list for that line
				(*token_list)[i] = NULL;
				// Shift lines up
				memmove((*token_list) + i, (*token_list) + i + 1, (*lines - i - 1) * sizeof(char **));
				memmove((*tokens_per_line) + i, (*tokens_per_line) + i + 1, (*lines - i - 1) * sizeof(int));

				// Shrink the lists
				*token_list = realloc(*token_list, (*lines - 1) * sizeof(char **));
				*tokens_per_line = realloc(*tokens_per_line, (*lines - 1) * sizeof(int));

				(*lines)--; // Decrement total line count
				i--;

			}
		}
		free(label);
	}
	return symbol_table;
}
