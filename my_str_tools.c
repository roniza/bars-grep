/*includes:*/
#include "my_str_tools.h"

/*Defines:*/

/*Constants:*/

/*Globals:*/

/*Functions:*/

/*	Name			:	int GetNumBTSpaces(char*str)
	Input			:	char*str -str to translate to integer
	Output			:	integer corresponding to input string
	Functionality	:	atoi - numerical string to integer translation*/
int GetNumBTSpaces(char*str) {
	int i = 0, sum = 0, exp = 0;

	while (str[i] >= '0' && str[i] <= '9') {//count exponention level(number of digits)
		exp++;
		i++;
	}
	for (i = 0; exp > 0; exp--) {
		sum += ((int)str[i] - (int)'0')*Ten_power(exp-1);	//single digit atoi
		exp--;
	}
	return sum;
}


/*	Name			:	int Ten_power(int exp)
	Input			:	int exp	-an integer to take 10 by power of
	Output			:	integer, a power of 10
	Functionality	:	returns an integer equivalent to 10^(input)*/
int Ten_power(int exp) {
	int result = 1;
	for (int i = 0; i < exp; i++)
		result *= 10;
	return result;
}
///TODOTODOTODO
/*	Name			:	int my_strcpy(char* source, char* dest)
	Input			:	char* source	-a string to copy
						char* dest		-a string to contain
	Output			:	integer, a power of 10
	Functionality	:	returns an integer equivalent to 10^(input)*/
int my_strcpy(char* source, char* dest) {
	int i;
	if (source == NULL || dest == NULL)
		return-1;
	for (i = 0; (source[i] != '\0'/* && source[i]!='\n'*/); i++)	///optional
		(dest)[i] = source[i];
	(dest)[i] = '\0';
	return i;
}

int my_strcat(char*head, char* tail) {
	int i = 0, j = 0;
	while (head[i] != '\0')
		i++;
	while (1) {
		head[i + j] = tail[j];
		if (tail[j] == '\0')
			return 0;
		j++;
	}
}

int my_parse(char* str, char* marker, char* buff, char seperator, char ender) {
	int i = 0;

	if (str == NULL || seperator == 0)
		return -1;

	for (i = 0; str[i] != ender && str[i] != '\0'; i++) {
		if (str[i] == seperator) {
			buff[i] = '\0';
			marker = &(str[i + 1]);
			return 0;
		}
		buff[i] = str[i];
	}
	marker = &(str[i]);
	buff[i] = '\0';
	return 1;
}

int my_str_len(char* str) {
	int i = 0;
	if (str == NULL)
		return-1;
	while (1) {
		if (str[i] == '\0'||str[i]=='\n')
			return i + 1;
		i++;
	}
}

char* my_fnd_chr(char* str, char c) {
	char* p_c = NULL;
	for(int i=0;str[i]!='\0';i++)
	{
		if (str[i] == c) {
			p_c = &str[i + 1];
			break;
		}
	}
	return p_c;
}
