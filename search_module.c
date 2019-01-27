#include "search_module.h"

/*Defines:*/

/*Constants:*/

/*Globals:*/

/*Functions:*/

/*	Name			:	int* SearchInLine(char* line, char* keyword, int* parameter_status)
	Input			:	char* line				-line being searched in
						char* keyword			-string searched for in line
						int* parameter_status	-array of parameters defining search preferences
	Output			:	(-1) for error (0) for found and (1) for not found
	Functionality	:	Searches for first ocation of the phrase
						Works recursively in case of RegExes*/
int SearchInLine(char* line, char* keyword, int* parameter_status) {
	//return values would be -1 for error 0 for found and 1 for not found;
	int i = 0, j = 0, k = 0;	/*Loop indexes: (k) - main in-line comparison begining index
												(i) and (j) - in-comparison followage indexes
												for the line and keyword respectedly */
	int def_flag = 0;						//flag for backslahed case (\\ \[ \( \. \) \] )
	int parse_res = 0, search_res = -1;		//Result containers, error flags
	char upper, lower;						//Boundaries for RegEx case [c1-c2]
	char buff[99];	///TODO: define later	//string mannipulations buffer
	char *old_m;			//where to start current parsing
	char *new_m;			//where to start next parsing
	char *ender;			//god knows...

	//line loop:
	while (1) {
		if (line[k] == '\n' || line[k] == '\0')	/*	End of line/string. If got here =>
													keyword not foundn in line => return 1*/
			return 1;  // SERACH_NOT_FOUND
		i = k;		//begin comparison on correct/updated place(index)
		j = 0;		//initialize keyword index to begining
		//keyword loop:
		while (1) {
			//initialize search boundaries for [c1-c2] case (in case its not the case...)
			lower = keyword[j];
			upper = keyword[j];
			if (keyword[j] == '\n' || keyword[j] == '\0') {		//phrase must end in "
				printf("Error: Invalid search phrase!");
				return -1;
			}
			//end of phrase:
			if (keyword[j] == '\"') {
				if (parameter_status[SWITCH_X] == 0 && line[i] != '\n' && line[i] != '\0')
					return 1;
				else
					return 0;						/*if got to end of phrase => no mismatch in
												search => found! => return 0*/

			}
			//RegEx (str1|str2| ... |strM) case:
			if (keyword[j] == '(') {
				//RegEx switch check:
				if (parameter_status[SWITCH_E] != 0) {
					printf("Error:RegEx switch is off");
					return -1;
				}
				old_m = &(keyword[j + 1]);
				new_m = &(keyword[j + 1]);
				ender = my_fnd_chr(old_m, ')');

				/*parse procedure*/
				while (parse_res == 0) {
					my_strcpy("", buff);	//clean buffer
					parse_res = my_parse(old_m, &new_m, buff, '|', ')');	//fill buffer with next optional
					old_m = new_m;										//prepare next iteration
					my_strcat(buff, ender);								//connect the rest of the key word
					/*recursive call for search: continue search from where stopped
												 with updated keyword: one degree of freedom eliminated
												 same search preferences*/
					search_res = SearchInLine(&(line[i]), buff, parameter_status);
					if (search_res != 1)		//if not found => try next option (procceed iteration)
						return search_res;		//propagate results thru recursion levels
				}
				break;	/*if not found at all (only way to get here)
						goto k++ (next iteration in line loop*/
			}
			//RegEx [c1 - c2] case:
			if (keyword[j] == '[') {
				//RegEx switch check:
				if (parameter_status[SWITCH_E] != 0) {
					printf("Error:RegEx switch is off");
					return -1;
				}
				if (keyword[j + 2] != '-' || keyword[j + 4] != ']') {	//validity check
					printf("Error: illegal syntax\n");
					return -1;
				}
				//update boundaries:
				upper = keyword[j + 3];
				lower = keyword[j + 1];
				if (upper < lower) {	//range validity check
					printf("Error: illegal range\n");
					return -1;
				}
				j += 4;		//point to end of statement (']')
			}
			//'Defended' case (backslashed spacial characters):
			if (keyword[j] == '\\') {
				j++;				//skip backslash
				def_flag = 1;		//flag it!
				//update bounds
				lower = keyword[j];
				upper = keyword[j];
			}

			//Comparison:
			if ((line[i] > upper || line[i] < lower) &&
				(keyword[j] != '.' || def_flag != 0 ||
					parameter_status[SWITCH_E] != 0)) {	//line character is out of range
				if (parameter_status[SWITCH_I] == 0) {	//only if requiered to ignore capitalization
					if ((line[i] > upper + 'A' - 'a' || line[i] < lower + 'A' - 'a') &&
						(line[i] > upper - 'A' - 'a' || line[i] < lower - 'A' - 'a')) { //out of capitalized range
						break;
					}
				}
				else
					break;
			}
			//comparison continues!
			i++;
			j++;
		}
		//mismatch found:
		if (parameter_status[SWITCH_X] == 0)	//in case of -x switch
			return 1;
		k++;
	}
}