#ifndef PRINTER_MODULE_H
#define PRINTER_MODULE_H

//Libraries:
#include <stdio.h>
#include <stdlib.h>

//includes:
#include "switches.h"

//Defines:

//Constants:

//Globals:

//function decleration:
int Print_step1(int* p_lines_to_print, int search_result, int parameters[]);
int Print_step2(int* p_lines_to_print, int print_flag, int parameters[],
	int byte_offset, int line_counter, char* line);
#endif // !PRINTER_MODULE_H