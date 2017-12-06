#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int equalMemory(const uint8_t *memoryOne, const uint8_t *memoryTwo) {
	for (int i = 0; i < 16; i++) {
		if (memoryOne[i] != memoryTwo[i]) {
			return 0;
		}
	}
	return 1;
}

int historyIncludes(uint8_t blockHistory[][16], int historyCount, const uint8_t *blocks) {
	for (int i = 0; i < historyCount; i++) {
		if (equalMemory(blockHistory[i], blocks)) {
			return i;
		}
	}
	return 0;
}

void writeHistory(uint8_t blockHistory[][16], int historyCount, const uint8_t *blocks) {
	for (int i = 0; i < 16; i++) {
		blockHistory[historyCount][i] = blocks[i];
	}
}

void partOne(char *filename) {
	// Open file
	FILE *input = fopen(filename, "r");
	if (input == NULL) {
		puts("File not found");
		return;
	}

	int numBlocks = 0;
	uint8_t blocks[32] = { 0 };
	// Fill blocks
	while (!feof(input)) {
		if (fscanf(input, "%" PRIu8, &blocks[numBlocks]) != 1) {
			break;
		}
		numBlocks++;
	}
	fclose(input);

	int historyCount = 1;
	uint8_t blockHistory[16000][16] = { 0 };
	writeHistory(blockHistory, 0, blocks);

	while (1) {
		// Find max block
		int maxIndex = 0;
		for (int i = 1; i < numBlocks; i++) {
			if (blocks[i] > blocks[maxIndex]) {
				maxIndex = i;
			}
		}

		// Distribute
		int maxValue = blocks[maxIndex];
		blocks[maxIndex] = 0;
		for (int i = 1; i < maxValue + 1; i++) {
			blocks[(maxIndex + i) % numBlocks]++;
		}

		if (historyIncludes(blockHistory, historyCount, blocks)) {
			break;
		}
		writeHistory(blockHistory, historyCount, blocks);
		historyCount++;

		if (historyCount == 16000) {
			break;
		}
	}

	printf("Num Distributions: %d\n", historyCount);
}

void partTwo(char *filename) {
	// Open file
	FILE *input = fopen(filename, "r");
	if (input == NULL) {
		puts("File not found");
		return;
	}

	int numBlocks = 0;
	uint8_t blocks[32] = { 0 };
	// Fill blocks
	while (!feof(input)) {
		if (fscanf(input, "%" PRIu8, &blocks[numBlocks]) != 1) {
			break;
		}
		numBlocks++;
	}
	fclose(input);

	int historyCount = 1;
	uint8_t blockHistory[16000][16] = { 0 };
	writeHistory(blockHistory, 0, blocks);

	while (1) {
		// Find max block
		int maxIndex = 0;
		for (int i = 1; i < numBlocks; i++) {
			if (blocks[i] > blocks[maxIndex]) {
				maxIndex = i;
			}
		}

		// Distribute
		int maxValue = blocks[maxIndex];
		blocks[maxIndex] = 0;
		for (int i = 1; i < maxValue + 1; i++) {
			blocks[(maxIndex + i) % numBlocks]++;
		}

		int result = historyIncludes(blockHistory, historyCount, blocks);
		if (result) {
			printf("Length of Loop: %d\n", historyCount - result);
			break;
		}
		writeHistory(blockHistory, historyCount, blocks);
		historyCount++;

		if (historyCount == 16000) {
			break;
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		return 0;
	}

	partOne(argv[1]);
	partTwo(argv[1]);

	return 0;
}