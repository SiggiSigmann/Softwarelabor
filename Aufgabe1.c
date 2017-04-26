#include <stdio.h>
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define RED   "\x1B[12m"
#define BLUE  "\x1B[12m"
#define RESET "\x1B[0m"

//Todo: farbe anpassen;

typedef enum {
	Stop = 0, Start = 1, Finish = 5, Fail = 255
} Status;

typedef enum {
	One = 1, Fifteen = 15, Last = 255
} Numbers;

typedef enum {
	OK, FAIL
} Test;

typedef struct {
	unsigned short int testCase;
	unsigned short int expected;
	char name[50];
} TestCaseHighLow;

typedef struct {
	Numbers number;
	Status status;
	unsigned short int code;
	char name[50];
} TestCaseSD;

Test testHighLow(unsigned short int input, unsigned short int expected);
Test testSD(Numbers number, Status status, unsigned short int code);

//---------------------------Teil1---------------------------
/*
 * switchLowHighByte tauscht die ersten zwei Bytes mit den letzten zwei Bytes.
 * @param i enthält die zu vertauschenden Bytes.
 * @return Vertauschte Bytes als zahl.
 */
short int switchLowHighByte(short int i) {
	unsigned short int part1 = i & 0xff;
	unsigned short int part2 = i & 0xff00;
	part1 = part1 << 8;
	part2 = part2 >> 8;
	return (part1 | part2);
}

//-------Test zu Teil1------------------------------
/*
 * runTestHighLow initialisiert den Testlauf
 * @param *test Zeiger auf Liste mit Testfällen.
 * @param Anzahl der Tests.
 */
void runTestHighLow(int lenght, TestCaseHighLow *test) {
	Test t;
	int ok = 0;
	int fail = 0;
	for (int i = 0; i < lenght; i++) {
		printf("Test Nr.%i (%s): \n", (i + 1), test[i].name);
		printf("\tInput: '%#x', Expected-Output: '%#x', ", test[i].testCase,
				test[i].expected);
		t = testHighLow(test[i].testCase, test[i].expected);
		if (OK == t) {
			printf("\tOK \n");
			ok++;
		} else {
			printf("\tFAIL \n");
			fail++;
		}
		printf("\n");
	}
	printf("Result Tests: %i OK: %i Fails: %i\n", lenght, ok, fail);
}

/*
 * testHighLow tested die Funktion.
 * @param input Eingabewert an die Funktion.
 * @param expected erwartetes Ergebnis.
 * @return Ergebnis des Tests.
 */
Test testHighLow(unsigned short int input, unsigned short int expected) {
	Test t;
	unsigned short int soultion = switchLowHighByte(input);
	printf("Output: '%#x'\n", soultion);
	if (soultion == expected) {
		t = OK;
	} else {
		t = FAIL;
	}
	return t;
}
//---------------------------Teil2----------------------------

/*
 * serialize Codiert Status und Nummer in eine Zahl.
 * @param s Status
 * @param n Number
 * @param *data Speicherplatz des Codes
 */
void serialize(Status s, Numbers n, unsigned short int* data) {
	*data = (unsigned) n << 8 | (unsigned) s;
}

/*
 * deserialize errecht aus dem Code die Number und den Status.
 * @param data Code.
 * @param s Status
 * @param n Number
 */
void deserialize(unsigned short int data, Status* s, Numbers* n) {
	*s = data & 0xff;
	*n = data >> 8;
}
//-----------------------Test zu Teil 2------------------------------------
/*
 * runTestHighLow initialisiert den Testlauf
 * @param *test Zeiger auf Liste mit Testfällen.
 * @param Anzahl der Tests.
 */
void runTestSD(int lenght, TestCaseSD *test) {
	Test t;
	int ok = 0;
	int fail = 0;

	for (int i = 0; i < lenght; i++) {
		printf("Test Nr.%i (%s): \n", (i + 1), test[i].name);
		printf("\tNumbers: '%#x', Status: '%#x', Expected-Code: '%#x' \n", test[i].number, test[i].status, test[i].code);
		t = testSD(test[i].number, test[i].status, test[i].code);

		if (OK == t) {
			printf("\tOK \n");
			ok++;
		} else {
			printf("\tFAIL \n");
			fail++;
		}
		printf("\n");
	}
	printf("Result Tests: %i OK: %i Fails: %i\n", lenght, ok, fail);
}

/**
 * test SD tested die Funktion der Methoden.
 * @param number Numbers.
 * @param status Status.
 * @param code erwarteter Code.
 * @return Ergenis des Tests.
 */
Test testSD(Numbers number, Status status, unsigned short int code) {
	Test t;
	Numbers newNumber;
	Status newStatus;
	unsigned short int packet;

	serialize(status, number, &packet);
	deserialize(packet, &newStatus, &newNumber);

	printf("\tOutput: '%#x', Calc-Number: '%#x', Calc-Status: '%#x'\n", packet, newNumber, newStatus);
	if ((number == newNumber) && (status == newStatus) && (code == packet)) {
		t = OK;
	} else {
		t = FAIL;
	}
	return t;
}
//---------------------------------------------------
int main(void) {
	printf("Teil 1:\n");
	int numberHighLow = 5;
	TestCaseHighLow testHighLow[] = { { 0x0001, 0x0100, "Test 1" }, { 0x1234,
			0x3412, "Test 2" }, { 0x1010, 0x1010, "Test 3" }, { 0xffab, 0xabff,
			"Test 4" }, { 0xff00, 0x00ff, "Test 5" } };
	runTestHighLow(numberHighLow, testHighLow);
	printf("----------------------------------- \n");
	printf("Teil 2:\n");
	int numberSD = 12;
	TestCaseSD testSD[] = { { Stop, One, 0x1}, { Stop, Fifteen, 0xf }, { Stop, Last, 0xff }, {
			Start, One, 0x101 }, { Start, Fifteen, 0x10f}, { Start, Last, 0x1ff }, { Finish, One , 0x501},
			{ Finish, Fifteen, 0x50f }, { Finish, Last, 0x5ff }, { Fail, One, 0xff01 }, { Fail,
					Fifteen, 0xff0f }, { Fail, Last, 0xffff } };
	runTestSD(numberSD, testSD);
	return 1;
}
