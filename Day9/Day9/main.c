#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		return 0;
	}

	// Open file
	FILE *input = fopen(argv[1], "r");
	if (input == NULL) {
		puts("File not found");
		return -1;
	}

	int stackPosition = 0;
	int inGarbage = 0;
	int ignoreNextChar = 0;
	int score = 0;
	int numGarbage = 0;

	char c;
	while ((c = getc(input)) != EOF) {

		if (ignoreNextChar) {
			ignoreNextChar = 0;
		}
		else if (inGarbage) {
			if (c == '>') {
				inGarbage = 0;
			}
			else if (c == '!') {
				ignoreNextChar = 1;
			}
			else {
				numGarbage++;
			}
		}
		else {
			switch (c) {
			case '{':
				stackPosition++;
				break;
			case '}':
				score += stackPosition;
				stackPosition--;
				break;
			case '!':
				ignoreNextChar = 1;
				break;
			case '<':
				inGarbage = 1;
				break;
			}
		}
	}

	printf("Score: %d\n", score);
	printf("Amount of Garbage: %d\n", numGarbage);

	fclose(input);
	return 0;
}