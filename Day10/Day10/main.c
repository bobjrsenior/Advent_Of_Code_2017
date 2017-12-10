#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void reverse(int list[256], int index, int length) {
	for (int i = 0; i < length / 2; i++) {
		int temp = list[(index + i) % 256];
		list[(index + i) % 256] = list[(index + length - 1 - i) % 256];
		list[(index + length - 1 - i) % 256] = temp;
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		return 0;
	}

	/// Part 1
	// Open file
	FILE *input = fopen(argv[1], "r");
	if (input == NULL) {
		puts("File not found");
		return -1;
	}

	// Initialilize list
	int list[256];
	for (int i = 0; i < 256; i++) {
		list[i] = i;
	}

	// Go through input values
	int index = 0;
	int skip = 0;
	while (!feof(input)) {
		int length = 0;
		if (fscanf(input, " %d ", &length) != 1) {
			break;
		}
		
		// Reverse list and move forward
		reverse(list, index, length);
		index += length + skip;
		skip++;


		// Eat comma if it exists
		getc(input);
	}
	
	printf("Result: %d\n", list[0] * list[1]);

	fclose(input);

	/// Part 2
	input = fopen(argv[1], "r");
	if (input == NULL) {
		puts("File not found");
		return -1;
	}

	// Initialize values
	for (int i = 0; i < 256; i++) {
		list[i] = i;
	}

	int numHashValues = 0;
	int hashValues[256];
	
	// Initialize hash values
	int c = 0;
	while (1) {
		c = getc(input);
		if (c == EOF)
			break;
		if (isspace(c))
			continue;
		hashValues[numHashValues++] = c;
	}

	hashValues[numHashValues++] = 17;
	hashValues[numHashValues++] = 31;
	hashValues[numHashValues++] = 73;
	hashValues[numHashValues++] = 47;
	hashValues[numHashValues++] = 23;
	

	index = 0;
	skip = 0;
	// Iterate through hash values 64 times
	for (int iteration = 0; iteration < 64; iteration++) {
		for (int i = 0; i < numHashValues; i++) {
			int length = hashValues[i];

			reverse(list, index, length);
			index += length + skip;
			skip++;
		}
	}

	// Condense into 16 XORed values
	int condensed[16];
	for (int i = 0; i < 16; i++) {
		condensed[i] = list[i * 16];
		for (int j = i * 16 + 1; j < (i * 16) + 16; j++) {
			condensed[i] ^= list[j];
		}
		
	}

	// Print
	printf("Final Value: ");
	for (int i = 0; i < 16; i++) {
		printf("%02x", condensed[i]);
	}
	printf("\n");
	return 0;
}