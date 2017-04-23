/*
 * Aufgabe3.c
 *
 *  Created on: 06.04.2017
 *      Author: Tobias Sigmann
 */
#include <stdio.h>

char* findWord(char *line) {
	while(*line!='\0'&&*line==' '){
		line++;
	}
	return line;
}

char* findSeperator(char *line) {
	while(*line!='\0'&&*line!=' '){
		line++;
	}
	return line;
}

int brakIntoWords(char *line, int maxWords, char *words[]) {
	int wordnumber=0;
	line=findWord(line);
	while(*line!='\0'&&wordnumber<maxWords){
		words[wordnumber]=line;
		wordnumber++;
		line = findSeperator(line);
		*line='\0';
		line++;
		line=findWord(line);
	}
	if(wordnumber<maxWords){
		for(int i = wordnumber; i<maxWords; i++){
			words[i]="\0";
		}
	}
	return wordnumber;
}

//-----------------test----------------------

int main(void) {
	int maxWords = 10;
	char line[] = "Hallo ich bin  tobi.";
	char *words[maxWords];
	int wordnumber = brakIntoWords(line, maxWords, words);
	printf("Numer of Words %i\n",wordnumber);
	for (unsigned int i = 0; i < maxWords; i++) {
		printf("%i %s\n", i, words[i]);
	}
	return 0;
}
