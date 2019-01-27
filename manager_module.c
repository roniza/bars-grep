/*includes:*/
#include "manager_module.h"

/*Defines:*/

/*Constants:*/
const char parameter_DB[NUM_OF_PARAMETERS] = { 'A','b','c','i','n','v','x', 'E' };//Parameter names

/*Globals:*/

/*Functions:*/
int main(int argc,char* argv[]) {
	int eof_flag = 1, print_flag = 0, line_search_res = 0;
	int lines_to_print = 0, line_counter = 0, byte_offset = 0;
	FILE* file_ptr;
	char file_name[MAX_LINE_LEN];
	char parameter_line[MAX_LINE_LEN];
	char phrase_buff[MAX_LINE_LEN];
	char line[MAX_LINE_LEN];
	char print_buff[MAX_LINE_LEN];
	char *phrase = phrase_buff;

	my_strcpy("", file_name);
	my_strcpy("", print_buff);
	Initialize_globals();
	//Interperate arguments:
	for (int i =1 ; i < argc; i++) {
		if ((argv[i])[0] == '-') {		//argument must be headed with '-'
			my_strcpy(argv[i], parameter_line);
			Input_to_Globals(parameter_line, NULL);
		}
		else if ((argv[i])[0] == '\"') {//search phrase must start with '\"'
			my_strcpy(argv[i], phrase);
			Input_to_Globals(NULL, phrase);
			if (parameter_status[SWITCH_E] == 0)
				phrase = &(phrase[2]);
			/*else
				phrase = &(phrase[1]);*/
		}
		else
			my_strcpy(argv[i], file_name);
	}
	///TODO:
	//Get filename from user:
	/*if (*file_name == '\0')
		gets(file_name);*/
	//open file:
	fopen_s(&file_ptr,file_name, "r");
	if (file_ptr == NULL) {
		printf("\nError: Couldn't load file.");
		return 1;
	}
	while (eof_flag == 1/*not reached last line*/) {
		line_counter++;
		print_flag = 0;
		//EOF case:
		if (fgets(line, MAX_LINE_LEN, file_ptr) == NULL)
			eof_flag = 0;
		//search:
		line_search_res = SearchInLine(line, &(phrase[1]), parameter_status);
		//print:
		print_flag=Print_step1(&lines_to_print,line_search_res,parameter_status);
		Print_step2(&lines_to_print, print_flag, parameter_status,byte_offset,line_counter,line);
		
		byte_offset += my_str_len(line) * sizeof(char);
	}
	//Close file:
	fclose(file_ptr);
	return (0);		//Successful run!
}

/*	Name			:	int Initialize_globals()
	Input			:	void
	Output			:	0
	Functionality	:	Set parameter_status array values to -1 (off)*/
int Initialize_globals() {
	/*initializing globals:*/
	for (int i = 0; i < NUM_OF_PARAMETERS; i++)
		parameter_status[i] = -1;
	return 0;
}

/*	Name			:	int* Input_to_globals(char* input_str, char* phrase)
	Input			:	char* input_str	-recently acquired input string
						char* phrase	-phrase string, in order to resolve -E switch
	Output			:	updated parameter_status array or NULL for failiour
	Functionality	:	Set parameter_status array values to -1 (off)*/
int* Input_to_Globals(char* input_str, char* phrase) {
	int i = 0, j = 0;
	
	//Acquire -E Argument from phrase (if exists):
	if (phrase != NULL) {
		if (phrase[1] == '-' && phrase[2] == 'E')
			parameter_status[SWITCH_E] = 0;
		return parameter_status;
	}
	
	/*manipulate parameter status array (globals)*/
	while (input_str[i] != '\n' && input_str[i] != '\0' && input_str != NULL) {
		if (input_str[i] == '-') {
			for (j = 0; j < NUM_OF_PARAMETERS; j++) {
				if (input_str[i + 1] == parameter_DB[j]) {
					parameter_status[j] = 0;
					break;
				}
			}
			if (j == 0)	//in case acquired parameter is -A number is expected
				parameter_status[j] = GetNumBTSpaces(&(input_str[i + 2]));
		}
		i++;	//if arguments were not spaced, they 'hide' in the same string
	}
	return parameter_status;
}