#include "parsing.h"
#include "command.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void recorrer1(struct List list){
	printf("Dentro del recorrer\n");
	for(struct Node* aux = list.first; aux != NULL; aux = aux->next){
		printf("%s ", aux->token);
	}
	puts("");
}


int parsing_input(char** imput_cmd, struct CMD** cmds){
	struct List list = list_create();
	char* token = strtok(*imput_cmd, DELIM);
	char* redirect_file;
	char** tokens;
	if (!strcmp(token, END_LINE))
		return 1;
	int status = 0;
	int max_len = INIT_CMD;
	int counter = 0;	
	int flag = 1;
	

	struct CMD* new_cmds = malloc(sizeof(struct CMD) * INIT_CMD);
	assert(new_cmds);


	while (flag/* && (token != NULL)*/){
		if (!strcmp(token, REDIRECT)){
			token = strtok(NULL, DELIM);
			if (!(strcmp(token, END_LINE) || strcmp(token, PIPE) || strcmp(token, REDIRECT))){
				fprintf(stderr, "MiniShell: Unexpected token %s after %s.", token, REDIRECT);
				status = 1;
				flag = 0;
			} else {
				redirect_file = token;
			}
		}	else if (!((flag = strcmp(token, END_LINE)) && strcmp(token, PIPE))) {
			printf("%d\n",flag);
			if (flag){
				token = strtok(NULL, DELIM);
				printf("%s\n", token);
				puts("Holamundo");
			}
			if (flag && !(strcmp(token, END_LINE) || strcmp(token, PIPE))){
				fprintf(stderr, "MiniShell: Unexpected token %s after %s.", token, REDIRECT);
				status = 1;
				flag = 0;
			} else {
				recorrer1(list);
				tokens = list_to_cmd(list);
				new_cmds[counter++] = make_cmd(&tokens, &redirect_file);
				list_destroy(&list);
				if ( counter == max_len )
					assert((new_cmds = realloc(new_cmds, sizeof(struct List) * (max_len *= 2))));
			}
		} else {
			list = list_add(list, &token, TAIL);
			token = strtok(NULL, DELIM);
		}
	}
	if (status)
		free(new_cmds);
	else
		*cmds = new_cmds;
	return status;
}