/*
 * Aufgabe3.c
 *
 *  Created on: 06.04.2017
 *      Author: Tobias Sigmann
 */
#include <stdio.h>

typedef enum {
	OK, FAIL
} Test;

typedef struct {
	char testCase[50];
	char* expectedWords[10];
	int expectedWordNumbers;
	int maxWords;
	char name[50];
} TestCase;

Test testFuntion(char input[50], char* expectedWords[10],
		int expectedWordNumbers, int maxWords);

//---------------------Aufgabe-----------------------------------------------

/**
 * findWord schiebt den Zeiger inerhalb des Satzes bis an den Anfang des nächsten Wortes.
 * @param line Zeiger auf den Satzt.
 * @return Zeiger auf das nächste wort.
 */
char* findWord(char *line) {
	while (*line != '\0' && *line == ' ') {
		line++;
	}
	return line;
}

/**
 * findSeperator liefert einen Zeiger auf den ersten Seperator zurück.
 * @param line Zeiger auf den Satzt.
 * @return Zeiger auf das nächste Seperator.
 */
char* findSeperator(char *line) {
	while (*line != '\0' && *line != ' ') {
		line++;
	}
	return line;
}

/**
 * breakInToWords schreibt die Worter aus dem satz in ein Array.
 * @param Zeiger auf den Satz(Chararray).
 * @param Anzahl der mazimalen Wörter.
 * @param Zeiger auf die Specherstelle der Wörter.
 * @return Anzahl der Wörter.
 */
int breakInToWords(char *line, int maxWords, char *words[]) {
	int wordnumber = 0;
	line = findWord(line);
	while (*line != '\0' && wordnumber < maxWords) {
		words[wordnumber] = line;
		wordnumber++;
		line = findSeperator(line);
		*line = '\0';
		line++;
		line = findWord(line);
	}
	if (wordnumber < maxWords) {
		for (int i = wordnumber; i < maxWords; i++) {
			words[i] = "\0";
		}
	}
	return wordnumber;
}

//-----------------test----------------------

/*
 * runTest initialisiert den Testlauf
 * @param *test Zeiger auf Liste mit Testfällen.
 * @param Anzahl der Tests.
 */
void runTest(int lenght, TestCase *test) {
	Test t;
	int ok = 0;
	int fail = 0;
	for (int i = 0; i < lenght; i++) {
		printf("Test Nr.%i (%s): \n", (i + 1), test[i].name);
		printf("\tInput: '%s'; \n\tExpected-Wordnumbers: '%i';\n\tExpected-Output: \n", test[i].testCase, test[i].expectedWordNumbers);
		for (unsigned int j = 0; j < test[i].maxWords; j++) {
			printf("\t\t%i '%s'\n", j, test[i].expectedWords[j]);
		}
		t = testFuntion(test[i].testCase, test[i].expectedWords,
				test[i].expectedWordNumbers, test[i].maxWords);
		if (OK == t) {
			printf("\tOK \n");
			ok++;
		} else {
			printf("\tFAIL \n");
			fail++;
		}
		printf("\n");
	}
	printf("From %i Tests: OK: %i Fails: %i\n", lenght, ok, fail);
}

/*
 * testFuntion initialisiert den test und liefert das Ergebnis zurück.
 * @param input Funktionsparameter.
 * @param expected erwartetes Ergebnis(Wörter).
 * @param expected erwartetes Ergebnis(wortanzahl).
 * @param maximale anzahl der Wörter.
 * @return Ergebis des Tests.
 */
Test testFuntion(char input[50], char* expectedWords[10],
		int expectedWordNumbers, int maxWords) {
	char *words[maxWords+100];
	int wordNumbers = breakInToWords(input, maxWords, words);
	short int equal = 0;
	printf("\tOutput Word Numbers: '%i';\n", wordNumbers);
	printf("\tOutput: \n");
	for (unsigned int j = 0; j < maxWords; j++) {
		printf("\t\t%i '%s'\n", j, words[j]);
	}
	if (wordNumbers == expectedWordNumbers) {
		if (maxWords > 0) {
			for (int x = 0; x < maxWords; x++) {
				for (; *words[x] != '\0';) {
					if (*words[x] != *expectedWords[x]) {
						equal = 1;
					}
					words[x]++;
					expectedWords[x]++;
				}
			}
		}

		if (equal == 0) {
			return OK;
		} else {
			return FAIL;
		}
	} else {
		return FAIL;
	}
}

//------------------------------------------------------------------------------------------------

int main(void) {
	int number = 9;
	TestCase test[] = { { "Hallo ich bin Tobias",
							{ "Hallo", "ich", "bin", "Tobias", "", "", "", "", "", "" },
							4, 10 },
						{"Matrikelnummer:    57915",
							{ "Matrikelnummer:", "57915", "", "","", "", "", "", "", "" },
							2, 10 },
						{" der Nachnahme ist Sigmann",
							{ "der", "Nachnahme", "ist","Sigmann", "", "", "", "", "", "" },
							4, 10 },
						{"Heute ist der 27 April 2017 ",
							{ "Heute", "ist", "der", "27","April", "2017", "", "", "", "" },
							6, 10 },
						{ " ", { "", "","", "", "", "", "", "", "", "" }, 0, 10 },
						{ "   ", { "", "", "","", "", "", "", "", "", "" }, 0, 10 },
						{ "", { "", "", "", "", "","", "", "", "", "" }, 0, 10 },
						{ "1 2 3 4 5", { "1", "2", "3","4", "", "", "", "", "", "" }, 4, 4 },
						{ "test 1 hallo huhu hi", { "", "", "", "", "","", "", "", "", "" }, 0, 0 }};
	runTest(number, test);
	return 0;
}
