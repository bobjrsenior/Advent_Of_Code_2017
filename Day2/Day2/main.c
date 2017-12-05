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

	// Number matrix
	int numbers[16][16];

	int sum = 0;
	for (int row = 0; row < 16; row++) {
		int result = 0;
		for (int col = 0; col < 16; col++) {
			fscanf(input, " %d ", &numbers[row][col]);
			
			// Check against previous values in row
			for (int i = col - 1; i >= 0; i--) {
				if (numbers[row][col] % numbers[row][i] == 0 || numbers[row][i] % numbers[row][col] == 0) {
					if (numbers[row][col] > numbers[row][i]) {
						result = numbers[row][col] / numbers[row][i];
					}
					else {
						result = numbers[row][i] / numbers[row][col];
					}
					break;
				}
			}
		}
		sum += result;
	}
	

	printf("%d\n", sum);
	
	fclose(input);
	return 0;
}