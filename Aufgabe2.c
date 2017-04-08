/*
 * Aufgabe2.c
 *
 *  Created on: 05.04.2017
 *      Author: Tobias Sigmann
 */

#include <stdio.h>

typedef enum{
	OK, FAIL
}Test;

typedef struct {
	char testCase[50];
	char expected[50];
	char name[50];
} TestCase1;

typedef struct {
	char testCase[50];
	char expected[50];
	char pattern[50];
	char name[50];
} TestCase3;

Test testFuntion1(char* input, char* expected);
Test testFuntion2(char* input, char* expected);
Test testFuntion3(char* input, char* pattern, char* expected);

//---------------------------Teil 1---------------------------

/*
 * extract Findet das ende des Strings nach ::.
 * @param *input  Zeiger auf EingabeString.
 * @return String nach dem letzten ::.
 */
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

//-------Test zu Teil 1------------------------------

/*
 * runTest initialisiert den Testlauf
 * @param *test Zeiger auf Liste mit Testf�llen.
 * @param Anzahl der Tests.
 */
void runTest1(int lenght, TestCase1 *test) {
	Test t;
	int ok=0;
	int fail=0;
	for (int i = 0; i < lenght; i++) {
		printf("Test Nr.%i (%s): \n", (i+1), test[i].name);
		printf("\tInput: %s; Expected-Output: %s; ", test[i].testCase,
				test[i].expected);
		t = testFuntion1(test[i].testCase, test[i].expected);
		if (OK == t) {
			printf("\tOK \n");
			ok++;
		} else{
			printf("\tFAIL \n");
			fail++;
		}
		printf("\n");
	}
	printf("Result Tests: %i OK: %i Fails: %i\n",lenght,ok,fail);
}

/*
 * testFuntion initialisiert den test und liefert das Ergebnis zur�ck.
 * @param input Funktionsparameter.
 * @param expected erwartetes Ergebnis.
 * @return Ergebis des Tests.
 */
Test testFuntion1(char* input, char* expected){
	char* solution = extract(input);
	printf("Output: %s\n", solution);
	int same=1;
	for(;expected=='\0';){
		if(*expected!=*solution){
			same=0;
		}
		expected++;
		solution++;
	}
	if(same==1){
		return OK;
	}else{
		return FAIL;
	}
}

//---------------------------Teil 2---------------------------

/*
 * extract2 Findet das ende des Strings nach ::.
 * @param *input Zeiger EingabeString.
 * @param **output Zeiger auf dem String Zeiger nach dem letzten ::.
 */
void extract2(char* input, char** output) {
	*output = (extract(input));

}

//-------Test zu Teil 2------------------------------

/*
 * runTest initialisiert den Testlauf
 * @param *test Zeiger auf Liste mit Testf�llen.
 * @param Anzahl der Tests.
 */
void runTest2(int lenght, TestCase1 *test) {
	Test t;
	int ok=0;
	int fail=0;
	for (int i = 0; i < lenght; i++) {
		printf("Test Nr.%i (%s): \n", (i+1), test[i].name);
		printf("\tInput: %s; Expected-Output: %s; ", test[i].testCase,
				test[i].expected);
		t = testFuntion2(test[i].testCase, test[i].expected);
		if (OK == t) {
			printf("\tOK \n");
			ok++;
		} else{
			printf("\tFAIL \n");
			fail++;
		}
		printf("\n");
	}
	printf("Result Tests: %i OK: %i Fails: %i\n",lenght,ok,fail);
}

/*
 * testFuntion initialisiert den test und liefert das Ergebnis zur�ck.
 * @param input Funktionsparameter.
 * @param expected erwartetes Ergebnis.
 * @return Ergebis des Tests.
 */
Test testFuntion2(char* input, char* expected){
	char* solution;
	extract2(input, &solution);
	printf("Output: %s\n", solution);
	int same=1;
	for(;expected=='\0';){
		if(*expected!=*solution){
			same=0;
		}
		expected++;
		solution++;
	}
	if(same==1){
		return OK;
	}else{
		return FAIL;
	}
}

//---------------------------Teil 3---------------------------

/*
 * extract3 Findet das ende des Strings nach einem gewissen Strings.
 * @param *input Zeiger EingabeString.
 * @param **output Zeiger auf dem String Zeiger nach dem letzten ::.
 */
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

//-------Test zu Teil 3------------------------------

/*
 * runTest initialisiert den Testlauf
 * @param *test Zeiger auf Liste mit Testf�llen.
 * @param Anzahl der Tests.
 */
void runTest3(int lenght, TestCase3 *test) {
	Test t;
	int ok=0;
	int fail=0;
	for (int i = 0; i < lenght; i++) {
		printf("Test Nr.%i (%s): \n", (i+1), test[i].name);
		printf("\tInput: %s; Expected-Output: %s; ", test[i].testCase,
				test[i].expected);
		t = testFuntion3(test[i].testCase, test[i].expected, test[i].pattern);
		if (OK == t) {
			printf("\tOK \n");
			ok++;
		} else{
			printf("\tFAIL \n");
			fail++;
		}
		printf("\n");
	}
	printf("Result Tests: %i OK: %i Fails: %i\n",lenght,ok,fail);
}

/*
 * testFuntion initialisiert den test und liefert das Ergebnis zur�ck.
 * @param input Funktionsparameter.
 * @param expected erwartetes Ergebnis.
 * @return Ergebis des Tests.
 */
Test testFuntion3(char* input, char* pattern, char* expected){
	char* solution = extract3(input, pattern);
	printf("Output: %s\n", solution);
	int same=1;
	for(;expected=='\0';){
		if(*expected!=*solution){
			same=0;
		}
		expected++;
		solution++;
	}
	if(same==1){
		return OK;
	}else{
		return FAIL;
	}
}



int main(void) {
	int number = 4;
	printf("Teil 1:\n");
	TestCase1 test1[] = { { "Hal::lo", "lo" },
						  { "::test", "test" },
						  { "test::", "" },
						  { "h::i", "i" } };
	runTest1(number, test1);
	printf("----------------------------------- \n");
	printf("Teil 2:\n");
	TestCase1 test2[] = { { "Hal::lo", "loo" },
						  { "::test", "test" },
						  { "test::", "" },
						  { "h::i", "i" } };
	runTest2(number, test2);
	printf("----------------------------------- \n");
	printf("Teil 3:\n");
	int number3 = 4;
	TestCase3 test3[] = { { "Hal::lo", "loo", "::"},
						  { "Hallo", "Hao", "ll" },
						  { "Ich 123123 Du", "Ich  Du", "123123" },
						  { "Ha llo", "Hallo", " " } };
	runTest3(number3, test3);
	return 0;
}
