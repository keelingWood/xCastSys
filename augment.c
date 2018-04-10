#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "augment.h"

augment *createAugment(char name[], char description[],
	uint8_t type,
	uint8_t condition,
	char abilities[][30],
	uint8_t numAbilities,
	uint8_t statIncrease[7],
	uint16_t healthIncreases[12],
	uint8_t isPerma) {
	
	augment *newAug = malloc(sizeof(augment));
	
	memcpy(newAug->name, name, strlen(name));
	memcpy(newAug->desc, description, strlen(description));
	
	newAug->type = type;
	newAug->currCondition = condition;
	newAug->maxCondition = condition;
	
	for (uint8_t index = 0; index < numAbilities; index++) {
		memcpy(newAug->abilities[index], abilities[index], strlen(abilities[index]));
	};
	newAug->numAbilities = numAbilities;
	
	for (uint8_t index = 0; index < 7; index++) {
		newAug->statIncrease[index] = statIncrease[index];
	};
	
	for (uint8_t index = 0; index < 12; index++) {
		newAug->healthIncreases[index] = healthIncreases[index];
	};
	
	newAug->isPerma = isPerma;
	
	return newAug;
	
};
