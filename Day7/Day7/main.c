#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
	int parent;
	int weight;
	int numChildren;
	int children[16];
	char name[16];
};

int getWeight(struct Node nodes[1400], int root) {
	int weight = nodes[root].weight;

	for (int i = 0; i < nodes[root].numChildren; i++) {
		weight += getWeight(nodes, nodes[root].children[i]);
	}

	return weight;
}

int findNewWeight(struct Node nodes[1400], int root, int change) {

	int weightOne = 0;
	int weightTwo = 0;
	int weightOneCount = 0;
	int weightTwoCount = 0;
	int weights[16];

	// No children == no balance
	if (nodes[root].numChildren == 0) {
		return 0;
	}

	// Find all weights of children
	// ONly 1 offweight means a max of two distinct values
	for (int i = 0; i < nodes[root].numChildren; i++) {
		int weight = getWeight(nodes, nodes[root].children[i]);
		if (weightOneCount == 0) {
			weightOne = weight;
			weightOneCount++;
		}
		else if (weightOne == weight) {
			weightOneCount++;
		}
		else {
			weightTwo = weight;
			weightTwoCount++;
		}

		weights[i] = weight;
	}

	// All match
	if (weightTwoCount == 0) {
		// If we are in an offweight tree, return corrected weight
		if (change != 0) {
			return nodes[root].weight + change;
		}
		return 0;
	}
	else {
		// FInd offWeight and difference
		int offWeight = weightOne;
		int difference = weightTwo - weightOne;
		if (weightOneCount > 1) {
			offWeight = weightTwo;
			difference = weightOne - weightTwo;
		}

		// Find correction for the off child
		for (int i = 0; i < nodes[root].numChildren; i++) {
			if (weights[i] == offWeight) {
				return findNewWeight(nodes, nodes[root].children[i], difference);
			}
		}
		return 0;
	}

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

	int numNodes = 0;
	struct Node nodes[1400] = { 0 };
	for (int i = 0; i < 1400; i++) {
		nodes[i].parent = -1;
	}

	char buffer[256] = { 0 };
	while (!feof(input)) {
		int curNode = numNodes;
		// Grab name and weight
		fscanf(input, "%s (%d)", nodes[curNode].name, &nodes[curNode].weight);
		// If node already exists, use that
		for (int i = 0; i < curNode; i++) {
			if (strcmp(nodes[i].name, nodes[curNode].name) == 0) {
				nodes[i].weight = nodes[curNode].weight;
				curNode = i;
				numNodes--;
				break;
			}
		}
		numNodes++;

		// Read rest of line
		fgets(buffer, 256, input);

		// Look for children
		int inWord = 0;
		int startWord = 0;
		int endWord = 0;
		int index = 0;
		while (buffer[index] != '\0') {
			char c = buffer[index];
			// Ignore leading whitespace and control characters
			if (!isspace(c) && c != ',' && c != '\r' && c != '\n' && c != '-' && c != '>') {
				// If this isn't a space and we are not inWord, it's the beginning of a word
				if (!inWord) {
					inWord = 1;
					startWord = index;
				}
			}
			else {
				// If we are at a space while InWord, we are at the end of the word
				if (inWord) {
					inWord = 0;
					endWord = index;
					buffer[index] = '\0';

					// Check if this child already exists
					int found = 0;
					for (int i = 0; i < numNodes; i++) {
						if (strcmp(nodes[i].name, &buffer[startWord]) == 0) {
							nodes[i].parent = curNode;
							nodes[curNode].children[nodes[curNode].numChildren] = i;
							nodes[curNode].numChildren++;
							found = 1;
							break;
						}
					}

					// If not, add it
					if (!found) {
						strcpy(nodes[numNodes].name, &buffer[startWord]);
						nodes[numNodes].parent = curNode;
						nodes[curNode].children[nodes[curNode].numChildren] = numNodes;
						nodes[curNode].numChildren++;
						numNodes++;
					}
				}

			}

			index++;
		}

	}

	// Find root
	int curIndex = 0;
	while (nodes[curIndex].parent != -1) {
		curIndex = nodes[curIndex].parent;
	}

	// Part One
	printf("Num Nodes: %d\n", numNodes);
	printf("Root Index: %d\n", curIndex);
	printf("Root Name: %s\n", nodes[curIndex].name);
	printf("Root Num Children: %d\n", nodes[curIndex].numChildren);

	// Part Two
	printf("Needed weight: %d\n", findNewWeight(nodes, curIndex, 0));

	return 0;
}