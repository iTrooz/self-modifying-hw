// Inspired by: https://stackoverflow.com/a/10266596

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

void doSomeStuff();

int SIKE(int a, int b) {
	return 2;
}

int pure(int a, int b) {
	return 1;
}

int main (int argc, char **argv) {
	printf("Result: %i\n", pure(1, 2));
	doSomeStuff();
	printf("Result: %i\n", pure(1, 2));

	return 0;
}

void doSomeStuff() {
	// get something in the text section (hopefully in the beginning)
	long long text_section = (long long)main;

	// align
	while(text_section % 4096 != 0) text_section--;

	if (mprotect((void*) text_section, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC) == -1) {
		perror("mprotect() 2");
		exit(1);
	}

	// overwrite.. function code, I guess ?
	memcpy(pure, SIKE, 20); // hopefully 20 is enough ? lol
}