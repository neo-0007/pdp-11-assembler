#ifndef TOKENIZER_H
#define TOKENIZER_H


#include<stdio.h>
#include<string.h> 
#include<stdlib.h>

#define MAX_TOKENS 6

//TOKENIZES ONE LINE OF THE PROGRAM
//input[] contains the line as a string
//*tokens[] contain the total tokens in the line
//RETURNS NUMBER OF TOKENS IN A LINE

int tokeniser(char input[],char *tokens[]);


//COLLECTS THE TOKENS FROM EACH LINE AND PUTS THEM INTO AN ARRAY
//RETURNS NUMBER OF LINES

int tokenlist(char ****final_token_list, int **tokens_per_line);


void freeall(char ****final_token_list,int **tokens_per_line,int lines);
#endif 
