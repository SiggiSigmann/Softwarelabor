#include <stdio.h>
//---------------------------Teil1---------------------------
short int switchLowHighByte(short int i) {
	unsigned short int part1 = i & 0xff;
	unsigned short int part2 = i & 0xff00;
	part1 = part1 << 8;
	part2 = part2 >> 8;
	return (part1 | part2);
}
//---------------------------Teil2----------------------------
typedef enum {
	Stop = 0,
	Start = 1,
	Finish = 5,
	Fail = 255
} Status;

typedef enum {
	One = 1,
	Fifteen = 15,
	Last = 255
} Numbers;

void serialize(Status s, Numbers n, unsigned short int* data) {
	*data = (unsigned)n << 8 | (unsigned)s;
}

void deserialize(unsigned short int data, Status* s, Numbers* n) {
	*s = data & 0xff;
	*n = data >> 8;
}
//-----------------------Test1--------------------------------
enum TestEnum {
	OK,
	FAIL
};

typedef enum TestEnum Test;

void testLowHigh(short int i) {
	Test t;
	if (i == switchLowHighByte(switchLowHighByte(i)))
		printf("OK \n");
	else
		printf("FAIL \n");
}
//-----------------------Test2------------------------------------
void testSD(Status s, Numbers n) {
	Test t;
	short int data;
	Status s2;
	Numbers n2;
	serialize(s, n, &data);
	deserialize(data, &s2, &n2);
	if (s2 == s && n2 == n) {
		printf("OK\n");
	}
	else {
		printf("FAIL\n");
	}
}
//---------------------------------------------------
int main(void) {
	unsigned short int zahl;
	unsigned short int paket = 0;
	Status status= Finish;
	Numbers number=Last;
	zahl = 0x1234;
	printf("Aufgabe1: \n");
	printf("----------------------------------- \n");
	printf("Teil1: \n");
	printf("%#x \n", zahl);
	zahl = switchLowHighByte(zahl);
	printf("%#x\n", zahl);
	testLowHigh(0x1);
	testLowHigh(0x100);
	testLowHigh(0xffff);
	testLowHigh(0xabcd);
	testLowHigh(0x0000);
	testLowHigh(0x1337);
	testLowHigh(0x4242);
	printf("----------------------------------- \n");
	printf("Teil2: \n");
	printf("status: %#x  number: %#x \n", status, number);
	serialize(status, number, &paket);
	printf("Ser: %#x \n", paket);
	deserialize(paket, &status, &number);
	printf("status: %#x  number: %#x \n", status, number);
	testSD(Stop, One);
	testSD(Stop, Fifteen);
	testSD(Stop, Last);
	testSD(Start, One);
	testSD(Start, Fifteen);
	testSD(Start, Last);
	testSD(Finish, One);
	testSD(Finish, Fifteen);
	testSD(Finish, Last);
	testSD(Fail, One);
	testSD(Fail, Fifteen);
	testSD(Fail, Last);
	return 1;
}
