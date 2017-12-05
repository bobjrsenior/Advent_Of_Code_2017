#include <stdio.h>
#include <stdlib.h>

#define GRID_SIZE 312
#define HALF_GRID_SIZE GRID_SIZE / 2

struct Position {
	int x;
	int y;
};

int findValue(int grid[][GRID_SIZE], int xPosition, int yPosition) {
	int sum = 0;
	for (int xOff = -1; xOff <= 1; xOff++) {
		for (int yOff = -1; yOff <= 1; yOff++) {
			sum += grid[xPosition + xOff][yPosition + yOff];
		}
	}

	return sum;
}

int main(int argc, char *argv[]) {
	int positionToFind = 0;

	if (scanf(" %d", &positionToFind) != 1) {
		puts("Unable to read input");
		return -1;
	}

	int result = 1;
	int grid[GRID_SIZE][GRID_SIZE] = { 0 };

	int xPosition = HALF_GRID_SIZE;
	int yPosition = HALF_GRID_SIZE;

	grid[xPosition][yPosition] = 1;
	xPosition++;

	int dimension = 3;

	while (1) {

		// Right side
		for (; yPosition <= HALF_GRID_SIZE + (dimension / 2); yPosition++) {
			grid[xPosition][yPosition] = findValue(grid, xPosition, yPosition);
			if (grid[xPosition][yPosition] > positionToFind) {
				result = grid[xPosition][yPosition];
				goto done;
			}
		}

		// Top side
		yPosition--; // Counter last increment
		xPosition--; // Ignore top-right corner
		for (; xPosition >= HALF_GRID_SIZE - (dimension / 2); xPosition--) {
			grid[xPosition][yPosition] = findValue(grid, xPosition, yPosition);
			if (grid[xPosition][yPosition] > positionToFind) {
				result = grid[xPosition][yPosition];
				goto done;
			}
		}

		// Left side
		xPosition++; // Counter last increment
		yPosition--; // Ignore top-left corner
		for (; yPosition >= HALF_GRID_SIZE - (dimension / 2); yPosition--) {
			grid[xPosition][yPosition] = findValue(grid, xPosition, yPosition);
			if (grid[xPosition][yPosition] > positionToFind) {
				result = grid[xPosition][yPosition];
				goto done;
			}
		}

		// Bottom side
		yPosition++; // COunter last increment
		xPosition++; // Ignore top-right corner
		for (; xPosition <= HALF_GRID_SIZE + (dimension / 2); xPosition++) {
			grid[xPosition][yPosition] = findValue(grid, xPosition, yPosition);
			if (grid[xPosition][yPosition] > positionToFind) {
				result = grid[xPosition][yPosition];
				goto done;
			}
		}

		dimension += 2;
	}

	done:
	printf("Answer: %d\n", result);

	return 0;
}