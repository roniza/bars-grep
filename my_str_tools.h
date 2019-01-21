#ifndef MY_STR_TOOLS_H
#define MY_STR_TOOLS_H

//Libraries:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//includes:

//Defines:
#define MAX_LINE_LEN 100

//Constants:

//Globals:

//function decleration:
int my_parse(char* str, char* marker, char* buff, char seperator, char ender);
int my_strcat(char*head, char* tail); int GetNumBTSpaces(char*str);
int Ten_power(int exp);
int my_strcpy(char* source, char* dest);
int my_str_len(char* str);
char* my_fnd_chr(char* str, char c);

#endif // !MY_ST_TOOLS