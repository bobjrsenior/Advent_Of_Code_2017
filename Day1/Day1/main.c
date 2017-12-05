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

	// Check filesize
	fseek(input, 0, SEEK_END);
	long filesize = ftell(input);
	rewind(input);

	// Allocate buffer
	char *buffer = malloc(sizeof(char) * filesize);
	if (buffer == NULL) {
		puts("Couldn't allocate memory");
		return -1;
	}

	// Fill buffer
	if (fread(buffer, sizeof(char), filesize, input) != filesize) {
		puts("Error reading file");
		return -1;
	}

	// Calculate sum
	long long int sum = 0;
	long halfDistance = filesize >> 1;
	for (long i = 0; i < halfDistance; i++) {
		if (buffer[i] == buffer[i + halfDistance]) {
			sum += (buffer[i] - '0') << 1;
		}
	}

	printf("%lld", sum);

	free(buffer);

	return 0;
}