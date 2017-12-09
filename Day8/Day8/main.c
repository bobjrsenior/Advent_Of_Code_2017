#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Register {
	int value;
	char name[8];
};

enum OpCode {
	INC,
	DEC,
	INVALID_OPCODE
};

enum Condition {
	EQUAL_TO,
	NOT_EQUAL_TO,
	GREATER_THAN,
	GREATER_THAN_OR_EQUAL_TO,
	LESS_THAN,
	LESS_THAN_OR_EQUAL_TO,
	INVALID_CONDITION
};

int registerIndex(struct Register registers[256], const char *name) {
	int index = 0;
	while (registers[index].name[0] != 0) {
		if (strcmp(registers[index].name, name) == 0) {
			return index;
		}
		index++;
	}
	//printf("Register Count: %d\n", index);
	strcpy(registers[index].name, name);
	return index;
}

enum OpCode calculateOpCode(const char *name) {
	if (strcmp(name, "inc") == 0) {
		return INC;
	}
	else if (strcmp(name, "dec") == 0) {
		return DEC;
	}
	else {
		printf("Invalid Opcode: %s\n", name);
		return INVALID_OPCODE;
	}
}

enum Condition calculateCondition(const char *name) {
	if (strcmp(name, "==") == 0) {
		return EQUAL_TO;
	}
	else if (strcmp(name, "!=") == 0) {
		return NOT_EQUAL_TO;
	}
	else if (strcmp(name, ">") == 0) {
		return GREATER_THAN;
	}
	else if (strcmp(name, ">=") == 0) {
		return GREATER_THAN_OR_EQUAL_TO;
	}
	else if (strcmp(name, "<") == 0) {
		return LESS_THAN;
	}
	else if (strcmp(name, "<=") == 0) {
		return LESS_THAN_OR_EQUAL_TO;
	}
	else {
		printf("Invalid Condition: %s\n", name);
		return INVALID_CONDITION;
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

	struct Register registers[32] = { 0 };
	char registerOneBuffer[8];
	char opcodeBuffer[4];
	char registerTwoBuffer[8];
	char conditionBuffer[3];
	int maxGlobalValue = -1;

	while (!feof(input)) {
		int amount = 0;
		int conditionAmount = 0;
		fscanf(input, "%7s %3s %d if %7s %2s %d", registerOneBuffer, opcodeBuffer, &amount, registerTwoBuffer, conditionBuffer, &conditionAmount);

		//printf("%s %s %d if %s %s %d\n", registerOneBuffer, opcodeBuffer, amount, registerTwoBuffer, conditionBuffer, conditionAmount);

		int registerOneIndex = registerIndex(registers, registerOneBuffer);
		int registerTwoIndex = registerIndex(registers, registerTwoBuffer);

		enum OpCode opcode = calculateOpCode(opcodeBuffer);
		enum Condition condition = calculateCondition(conditionBuffer);

		// Check condition
		int validCondition = 0;
		switch (condition)
		{
		case EQUAL_TO:
			if (registers[registerTwoIndex].value == conditionAmount) {
				validCondition = 1;
			}
			break;
		case NOT_EQUAL_TO:
			if (registers[registerTwoIndex].value != conditionAmount) {
				validCondition = 1;
			}
			break;
		case GREATER_THAN:
			if (registers[registerTwoIndex].value > conditionAmount) {
				validCondition = 1;
			}
			break;
		case GREATER_THAN_OR_EQUAL_TO:
			if (registers[registerTwoIndex].value >= conditionAmount) {
				validCondition = 1;
			}
			break;
		case LESS_THAN:
			if (registers[registerTwoIndex].value < conditionAmount) {
				validCondition = 1;
			}
			break;
		case LESS_THAN_OR_EQUAL_TO:
			if (registers[registerTwoIndex].value <= conditionAmount) {
				validCondition = 1;
			}
			break;
		case INVALID_CONDITION:
			break;
		}

		// Apply opcode if valid instruction
		if (validCondition) {
			switch (opcode) {
			case INC:
				registers[registerOneIndex].value += amount;
				break;
			case DEC:
				registers[registerOneIndex].value -= amount;
				break;
			case INVALID_OPCODE:
				break;
			}

			if (registers[registerOneIndex].value > maxGlobalValue) {
				maxGlobalValue = registers[registerOneIndex].value;
			}
		}
	}

	// Find max register
	int maxIndex = 0;
	int maxValue = registers[0].value;
	int index = 1;
	while (registers[index].name[0] != 0) {
		if (registers[index].value > maxValue) {
			maxIndex = index;
			maxValue = registers[index].value;
		}
		index++;
	}

	printf("Max Register: %s\n", registers[maxIndex].name);
	printf("Max Value: %d\n", maxValue);

	printf("Max Global Value: %d\n", maxGlobalValue);

	fclose(input);
	return 0;
}