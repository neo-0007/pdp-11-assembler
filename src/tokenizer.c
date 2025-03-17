#include "tokenizer.h"

int tokeniser(char input[],char *tokens[]){
	char *token;
	int count =0;

	//Removing the comments before tokenizing 
	for(int i =0; input[i] != '\0';i++){
		if(input[i]==';'){
			input[i] = '\0';
			break;		
		}
		if(input[i]>='a' && input[i]<='z')
			input[i] = input[i] - 32;

	}

	token = strtok(input," ,	");	//Tokenizing the string

	while (token != NULL && count < MAX_TOKENS) {

		token[strcspn(token, "\n")] = '\0';
		token[strcspn(token, "\r")] = '\0';

		if(strlen(token)>0){	
			tokens[count] = malloc(strlen(token) + 1);  // Allocate memory
			strcpy(tokens[count], token);  // Copy token
			count++;
		}
		token = strtok(NULL, " ,	");  // Get next token
	}
	return count;

}

int tokenlist(char ****final_token_list, int **tokens_per_line,char* filename){		//Contains all the tokens of the file
	int lines = 0;
	char line[50];
	char *tokens[MAX_TOKENS];
	int count = 0;

	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		perror("Error opening file");
		return 1;
	}

	while (fgets(line, sizeof(line), file) != NULL) {

		count = tokeniser(line,tokens);	

		if(count==0)					//If no tokens present continue
			continue;

		//Reallocating memory to expand size according to number of lines
		*tokens_per_line = realloc(*tokens_per_line,sizeof(int)*(lines+1));		
		*final_token_list = realloc(*final_token_list,sizeof(char **)*(lines+1));		

		(*tokens_per_line)[lines] = count;
		(*final_token_list)[lines] = malloc(sizeof(char*)*count);

		//Adding the tokens to the final list
		for(int i=0;i<count;i++){
			(*final_token_list)[lines][i] = malloc(strlen(tokens[i])+1);
			strcpy((*final_token_list)[lines][i],tokens[i]);
			free(tokens[i]);	
		}
		lines = lines +1;
	}
	fclose(file);
	return lines;
}
void freeall(char ****final_token_list,int **tokens_per_line,int lines){
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < (*tokens_per_line)[i]; j++) {
			free((*final_token_list)[i][j]);
		}
		free((*final_token_list)[i]);
	}
	free((*final_token_list));
	free((*tokens_per_line));
}

