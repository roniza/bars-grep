#include "search_module.h"

/*Defines:*/

/*Constants:*/

/*Globals:*/

/*Functions:*/
/*	Name			:	int Print_step1(int* p_lines_to_print, int search_result, int parameters[])
	Input			:	int* p_lines_to_print	-pointer to lines_to_print counter
						int search_result		-line search result
						int parameters[]		-array of parameters defining printing preferences
	Output			:	(1) if line should be printed (0) otherwise
	Functionality	:	resolves if line should be printed or not, considering search result and
						printing preferences.*/
int Print_step1(int* p_lines_to_print, int search_result, int parameters[]) {
	int print_flag = 0;
	if (search_result == 0 && parameters[SWITCH_V] == -1) {
		*p_lines_to_print = parameters[SWITCH_A];	//update'extra line' count according to user input (Argument -A)
		print_flag = 1;
	}
	else if (search_result == 1 && parameters[SWITCH_V] == 0) {	//Argument -v case
		print_flag = 1;
	}
	else {
		if (*p_lines_to_print > 0) {		//Argument -A  print case
			print_flag = 1;
			*p_lines_to_print--;
		}
	}
	return print_flag;
}

/*	Name			:	int Print_step2(int* p_lines_to_print, int print_flag, int parameters[],
										int byte_offset, int line_counter, char* line);
	Input			:	int* p_lines_to_print	-pointer to lines_to_print counter
						int print_flag			-indicates to print
						int parameters[]		-array of parameters defining printing preferences
						int byte_offset			-byte count from file head
						int line counter		-line number
						char* line				-the line itself to print
	Output			:	0 in any case
	Functionality	:	prints the line according to specifications, to search result and to preferences.*/
int Print_step2(int* p_lines_to_print, int print_flag, int parameters[],
				int byte_offset, int line_counter, char* line) {
	if (print_flag == 1 && parameters[SWITCH_N] != 0) {
		if (parameters[SWITCH_B] == 0)	//Argument -b case
			printf("%d:", byte_offset);
		if (parameters[SWITCH_C] == 0)	//Argument -c case: (not printing line itself!!!)
			printf("%d\n", line_counter);
		else
			printf("%s\n", line);		//'normal' case (-c is off)
	}

	if (parameters[SWITCH_N] == 0) {		//in this case (-N) ANY line is printed
		printf("%d", line_counter);
		if (print_flag == 1)			//would have been printed anyhow
			printf(":");
		else
			printf("-");				//wouldn't have been printed
		printf("%s\n", line);
	}
	return 0;
}