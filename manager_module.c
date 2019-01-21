

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
	char phrase[MAX_LINE_LEN];
	char line[MAX_LINE_LEN];
	char print_buff[MAX_LINE_LEN];

	my_strcpy("", file_name);
	my_strcpy("", print_buff);
	Initialize_globals();
	//Interperate arguments:
	for (int i =1 ; i < argc; i++) {
		if ((argv[i])[0] == '-') {		//argument must be headed with '-'
			my_strcpy(argv[i], parameter_line);
			Input_to_Globals(parameter_line, NULL);
		}
		else if ((argv[i])[0] == '\"')	//search phrase must start with '\"'
			my_strcpy(argv[i], phrase);
		else
			my_strcpy(argv[i], file_name);
	}
	//Get filename from user:
	if (*file_name == '\0')
		gets(file_name);
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
		if (line_search_res == 0 && parameter_status[5] == -1) {
			lines_to_print = parameter_status[0];	//update'extra line' count according to user input (Argument -A)
			print_flag = 1;
		}
		else if (line_search_res == 1 && parameter_status[5] == 0) {	//Argument -v case
			print_flag = 1;
		}
		else {
			if (lines_to_print > 0) {		//Argument -A  print case
				print_flag = 1;
				lines_to_print--;
			}
		}
		//other Arguments:
		if (print_flag == 1 && parameter_status[4] != 0) {
			if (parameter_status[1] == 0)	//Argument -b case
				printf("%d:", byte_offset);
			if (parameter_status[2] == 0)	//Argument -c case: (not printing line itself!!!)
				printf("%d\n", line_counter);
			else
				printf("%s\n", line);		//'regular' case (-c is off)
		}
		
		if(parameter_status[4]==0) {		//in this case (-N) ANY line is printed
			printf("%d", line_counter);
			if (print_flag == 1)			//would have been printed anyhow
				printf(":");
			else
				printf("-");				//wouldn't have been printed
			printf("%s\n", line);
		}
		byte_offset += my_str_len(line) * sizeof(char);
	}
	//Close file:
	fclose(file_ptr);
	return 0;		//Successful run!
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
	if (input_str == NULL)
		return NULL;
	
	/*manipulate parameter status array (globals)*/
	while (input_str[i] != '\n' && input_str[i] != '\0') {
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
	//Acquire -E Argument from phrase (if exists):
	if (phrase!=NULL && phrase[0] == '-' && phrase[1] == 'E')
		parameter_status[7] = 0;
	return parameter_status;
}

///TODO: cut this:
//file handaling example from list project:
/*
f_ptr=fopen(argv[1], "r");

while (flag == 1) {
if (fgets(command_buffer, MAX_LINE_LENGTH, f_ptr) == NULL)
flag = 0;//Do not repete loop upon reaching the end of the file
command_serial = Command2Serial(command_buffer, user_command_arguments);
if (HandleCommand(command_serial, user_command_arguments) == 1)
flag = 0;//If an 'Exit' command was identified.
	}

	fclose(f_ptr);
	return 0;
*/