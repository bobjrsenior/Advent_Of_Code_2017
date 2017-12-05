#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		return 0;
	}

	int jumpTableCount = 0;
	int jumpTable[2048] = { 0 };

	// Open file
	FILE *input = fopen(argv[1], "r");
	if (input == NULL) {
		puts("File not found");
		return -1;
	}

	// Fill jump table
	while (!feof(input)) {
		if (fscanf(input, "%d", &jumpTable[jumpTableCount]) != 1) {
			break;
		}
		jumpTableCount++;
	}

	// Step through jump table
	int steps = 0;
	int tablePosition = 0;
	while (((unsigned)tablePosition) < jumpTableCount) {
		int temp = jumpTable[tablePosition];

		if (temp >= 3) {
			jumpTable[tablePosition]--;
		}
		else {
			jumpTable[tablePosition]++;
		}
		tablePosition += temp;

		steps++;
	}

	printf("Steps to escape: %d\n", steps);

	return 0;
}