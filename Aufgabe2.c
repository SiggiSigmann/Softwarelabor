/*
 * Aufgabe2.c
 *
 *  Created on: 05.04.2017
 *      Author: Tobias Sigmann
 */

#include <stdio.h>

char* extract(char* input) {
	char* last;
	for (; *input != '\0'; input++) {
		if (*input == ':') {
			if (*(input + 1) == ':') {
				last = (input + 1);
			}
		}
	}
	last++;
	return last;
}

char* extract3(char* input, char* pattern) {
	char* last;
	int same;
	for (; *input != '\0'; input++) {
		same=0;
		for (int add = 0; *(pattern + add) != '\0'; add++) {
			if(*(pattern + add)!=*(input + add)){
				same++;
			}
		}
		if(same==0){
			last=input;
			for (int add = 0; *(pattern + add) != '\0'; add++) {
				last++;
			}
		}
	}
	return last;
}

void extract2(char* input, char** output) {
	*output = (extract(input));

}

int main(void) {
	char test[] = "Ha::ll::456o";
	printf("%s\n", extract(test));
	char* test2;
	extract2(test, &test2);
	printf("%s\n", test2);
	printf("%s\n", extract3(test,"ll::"));
	return 0;
}
