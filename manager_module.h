#ifndef MANAGER_MODULE_H
#define MANAGER_MODULE_H

//Libraries:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//includes:
#include "search_module.h"
#include "my_str_tools.h"
#include "printer_module.h"

//Defines:
/*
#define NUM_OF_PARAMETERS 8
#define SWITCH_A 0
#define SWITCH_B 1
#define SWITCH_C 2
#define SWITCH_I 3
#define SWITCH_N 4
#define SWITCH_V 5
#define SWITCH_X 6
#define SWITCH_E 7
*/

//Constants:
const char parameter_DB[NUM_OF_PARAMETERS];

//Globals:
int parameter_status[NUM_OF_PARAMETERS];

//function decleration:

//int main1(int argc, char*argv[]);
int Initialize_globals();
int *Input_to_Globals(char* input_str, char* phrase);

#endif // !MANAGER_MODULE_H