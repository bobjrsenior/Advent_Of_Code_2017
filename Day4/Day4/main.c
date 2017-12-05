#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
#define restrict __restrict
#endif

int isAnagram(char * restrict wordOne, char * restrict wordTwo) {
	char charCount[26] = { 0 };

	// Count word occurences
	while (*wordOne != '\0') {
		charCount[(*wordOne) - 'a']++;
		wordOne++;
	}

	// Subtract word occurences
	while (*wordTwo != '\0') {
		charCount[(*wordTwo) - 'a']--;
		wordTwo++;
	}


	// Validate
	for (int i = 0; i < 26; i++) {
		if (charCount[i]) {
			return 0;
		}
	}

	return 1;	
}

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

	int numValid = 0;
	char lineBuffer[512];

	while (!feof(input)) {
		if (fgets(lineBuffer, 512, input) != lineBuffer) {
			puts("Error reading from file");
			return -1;
		}

		int valid = 1;
		int doneWithWord = 1;
		int numWords = 0;
		int wordIndices[32] = { 0 };
		int lineLength = strlen(lineBuffer);

		for (int i = 0; i < lineLength; i++) {
			// If at end of word
			if (lineBuffer[i] == ' ' || lineBuffer[i] == '\n') {
				doneWithWord = 1;
				lineBuffer[i] = '\0';

				// Check if the completed word matches any other words in the line
				for (int wordIndex = 0; wordIndex < numWords - 1; wordIndex++) {
					if (isAnagram(&lineBuffer[wordIndices[wordIndex]], &lineBuffer[wordIndices[numWords - 1]])) {
						valid = 0;
						goto end;
					}
				}
			}
			else {
				if (doneWithWord) {
					doneWithWord = 0;
					wordIndices[numWords] = i;
					numWords++;
				}
			}
		}
	end:
		if (valid) {
			numValid++;
		}

	}

	printf("Number of valid passwords: %d\n", numValid);

	return 0;
}