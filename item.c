#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "item.h"

item *createOtherItem (char name[], char description[],
	uint8_t cleanliness,
	uint16_t currCondition,
	uint16_t maxCondition,
	uint16_t amount,
	uint16_t weight,
	uint16_t space) {
	
	//Malloc space for the item and return NULL if that fails.
	item *newItem = malloc(sizeof(item));
	if (newItem == NULL) return NULL;
	
	//Copies the given name into the name array of this item.
	memcpy(newItem->name, name, strlen(name));
	
	//Stores the description of this item.
	memcpy(newItem->desc, description, strlen(description));
	
	//Stores the type of this item.
	newItem->type = 0;
	
	//Sets the cleanliness of this item.
	newItem->cleanliness = cleanliness;
	
	//Stores the current and max condition of this item.
	newItem->currCondition = currCondition;
	newItem->maxCondition = maxCondition;
	
	//Stores the amount and dimensions of this item.
	newItem->amount = amount;
	newItem->weight = weight;
	newItem->space = space;
	
	return newItem;
};

item *createFooditem (char name[], char description[],
	uint8_t cleanliness,
	uint16_t currCondition,
	uint16_t maxCondition,
	uint16_t amount,
	uint16_t weight,
	uint16_t space,
	uint8_t spoilRate,
	uint8_t filling,
	uint8_t taste) {
	
	//Malloc space for the item and return NULL if that fails.
	item *newItem = malloc(sizeof(item));
	if (newItem == NULL) return NULL;
	
	//Copies the given name into the name array of this item.
	memcpy(newItem->name, name, strlen(name));
	
	//Stores the description of this item.
	memcpy(newItem->desc, description, strlen(description));
	
	//Stores the type of this item.
	newItem->type = 1;
	
	//Sets the cleanliness of this item.
	newItem->cleanliness = cleanliness;
	
	//Stores the current and max condition of this item.
	newItem->currCondition = currCondition;
	newItem->maxCondition = maxCondition;
	
	//Stores the amount and dimensions of this item.
	newItem->amount = amount;
	newItem->weight = weight;
	newItem->space = space;
	
	//Stores the food stats of the item.
	newItem->spoilRate = spoilRate;
	newItem->filling = filling;
	newItem->taste = taste;
	
	return newItem;
};

item *createPotionItem(char name[], char description[],
	uint8_t cleanliness,
	uint16_t currCondition,
	uint16_t maxCondition,
	uint16_t amount,
	uint16_t weight,
	uint16_t space,
	uint16_t damage[10],
	char extraEffects[][30],
	uint8_t numExtraEffects,
	uint16_t lengthOfEffects) {
	
	//Malloc space for the item and return NULL if that fails.
	item *newItem = malloc(sizeof(item));
	if (newItem == NULL) return NULL;
	
	//Copies the given name into the name array of this item.
	memcpy(newItem->name, name, strlen(name));
	
	//Stores the description of this item.
	memcpy(newItem->desc, description, strlen(description));
	
	//Stores the type of this item.
	newItem->type = 2;
	
	//Sets the cleanliness of this item.
	newItem->cleanliness = cleanliness;
	
	//Stores the current and max condition of this item.
	newItem->currCondition = currCondition;
	newItem->maxCondition = maxCondition;
	
	//Stores the amount and dimensions of this item.
	newItem->amount = amount;
	newItem->weight = weight;
	newItem->space = space;
	
	//Stores the effects of the potion.
	for (uint8_t index = 0; index < numExtraEffects; index++) {
		memcpy(newItem->extraEffects[index], extraEffects[index], strlen(extraEffects[index]));
	}
	newItem->numExtraEffects = numExtraEffects;
	newItem->lengthOfEffects = lengthOfEffects;
	
	//Stores the damage protections of the potion.
	for (uint8_t index = 0; index < 13; index++) {
		newItem->damage[index] = damage[index];
	}
	
	return newItem;
	
};

item *createAmmunitionItem(char name[], char description[],
	uint8_t cleanliness,
	uint16_t currCondition,
	uint16_t maxCondition,
	uint16_t amount,
	uint16_t weight,
	uint16_t space,
	uint16_t damage[12],
	char extraEffects[][30],
	uint8_t numExtraEffects,
	uint16_t lengthOfEffects) {
	
	//Malloc space for the item and return NULL if that fails.
	item *newItem = malloc(sizeof(item));
	if (newItem == NULL) return NULL;
	
	//Copies the given name into the name array of this item.
	memcpy(newItem->name, name, strlen(name));
	
	//Stores the description of this item.
	memcpy(newItem->desc, description, strlen(description));
	
	//Stores the type of this item.
	newItem->type = 3;
	
	//Sets the cleanliness of this item.
	newItem->cleanliness = cleanliness;
	
	//Stores the current and max condition of this item.
	newItem->currCondition = currCondition;
	newItem->maxCondition = maxCondition;
	
	//Stores the amount and dimensions of this item.
	newItem->amount = amount;
	newItem->weight = weight;
	newItem->space = space;
	
	//Stores the effects of the potion.
	for (uint8_t index = 0; index < numExtraEffects; index++) {
		memcpy(newItem->extraEffects[index], extraEffects[index], strlen(extraEffects[index]));
	}
	newItem->numExtraEffects = numExtraEffects;
	newItem->lengthOfEffects = lengthOfEffects;
	
	//Stores the damage protections of the potion.
	for (uint8_t index = 0; index < 13; index++) {
		newItem->damage[index] = damage[index];
	}
	
	return newItem;
};


item *createWearableItem(char name[], char description[],
	uint8_t type,
	uint8_t cleanliness,
	uint16_t currCondition,
	uint16_t maxCondition,
	uint16_t amount,
	uint16_t weight,
	uint16_t space,
	uint16_t damage[12],
	char extraEffects[][30],
	uint8_t numExtraEffects,
	uint8_t charismaEffects[5],
	uint16_t storageSpace,
	uint16_t specialStorageSpace[7]) {
	
	//Malloc space for the item and return NULL if that fails.
	item *newItem = malloc(sizeof(item));
	if (newItem == NULL) return NULL;
	
	//Copies the given name into the name array of this item.
	memcpy(newItem->name, name, strlen(name));
	
	//Stores the description of this item.
	memcpy(newItem->desc, description, strlen(description));
	
	//Stores the type of this item.
	newItem->type = type;
	
	//Sets the cleanliness of this item.
	newItem->cleanliness = cleanliness;
	
	//Stores the current and max condition of this item.
	newItem->currCondition = currCondition;
	newItem->maxCondition = maxCondition;
	
	//Stores the amount and dimensions of this item.
	newItem->amount = amount;
	newItem->weight = weight;
	newItem->space = space;
	
	//Stores the effects of the item.
	for (uint8_t index = 0; index < numExtraEffects; index++) {
		memcpy(newItem->extraEffects[index], extraEffects[index], strlen(extraEffects[index]));
	}
	newItem->numExtraEffects = numExtraEffects;
	
	//Stores the damage protections of the clothing.
	for (uint8_t index = 0; index < 13; index++) {
		newItem->damage[index] = damage[index];
	}
	
	//Stores the attractiveness of the clothing.
	for (uint8_t index = 0; index < 5; index++) {
		newItem->charismaEffects[index] = charismaEffects[index];
	}
	
	//Stores the storage space of the item.
	newItem->storageSpace = storageSpace;
	//Stores the special storage of the item.
	for (uint8_t index = 0; index < 7; index++) {
		newItem->specialStorageSpace[index] = specialStorageSpace[index];
	}
	
	return newItem;
};

item *createHoldableItem(char name[], char description[],
	uint8_t type,
	uint8_t cleanliness,
	uint16_t currCondition,
	uint16_t maxCondition,
	uint16_t amount,
	uint16_t weight,
	uint16_t space,
	uint16_t damage[12],
	char extraEffects[][30],
	uint8_t numExtraEffects,
	uint16_t lengthOfEffects,
	uint16_t minRange,
	uint16_t effectiveRange,
	uint16_t maxRange,
	uint16_t ammoCapacity,
	uint16_t ammoLoaded,
	char ammoNeeded[20],
	uint16_t shotsPerUse) {
	
	//Malloc space for the item and return NULL if that fails.
	item *newItem = malloc(sizeof(item));
	if (newItem == NULL) return NULL;
	
	//Copies the given name into the name array of this item.
	memcpy(newItem->name, name, strlen(name));
	
	//Stores the description of this item.
	memcpy(newItem->desc, description, strlen(description));
	
	//Stores the type of this item.
	newItem->type = type;
	
	//Sets the cleanliness of this item.
	newItem->cleanliness = cleanliness;
	
	//Stores the current and max condition of this item.
	newItem->currCondition = currCondition;
	newItem->maxCondition = maxCondition;
	
	//Stores the amount and dimensions of this item.
	newItem->amount = amount;
	newItem->weight = weight;
	newItem->space = space;
	
	//Stores the effects of the potion.
	for (uint8_t index = 0; index < numExtraEffects; index++) {
		memcpy(newItem->extraEffects[index], extraEffects[index], strlen(extraEffects[index]));
	}
	newItem->numExtraEffects = numExtraEffects;
	newItem->lengthOfEffects = lengthOfEffects;
	
	//Stores the damage protections of the potion.
	for (uint8_t index = 0; index < 13; index++) {
		newItem->damage[index] = damage[index];
	}
	
	//Stores the weapon stats.
	newItem->minRange = minRange;
	newItem->effectiveRange = effectiveRange;
	newItem->maxRange = maxRange;
	newItem->ammoCapacity = ammoCapacity;
	newItem->ammoLoaded = ammoLoaded;
	newItem->shotsPerUse = shotsPerUse;
	
	//Copies the given necessary ammo into the name array of this item.
	memcpy(newItem->ammoNeeded, ammoNeeded, strlen(ammoNeeded));
	newItem->ammo = NULL;
	
	return newItem;
};

/** Returns a new item identical to the given item.
 */
item *itemDeepCopy(item *oldItem) {
	
	//Malloc space for the item and return NULL if that fails.
	item *newItem = malloc(sizeof(item));
	if (newItem == NULL || oldItem == NULL) return NULL;
	
	//Copies the given name into the name array of this item.
	memcpy(newItem->name, oldItem->name, strlen(oldItem->name));
	
	//Stores the description of this item.
	memcpy(newItem->desc, oldItem->desc, strlen(oldItem->desc));
	
	//Stores the type of this item.
	newItem->type = oldItem->type;
	
	//Sets the cleanliness of this item.
	newItem->cleanliness = oldItem->cleanliness;
	
	//Stores the current and max condition of this item.
	newItem->currCondition = oldItem->currCondition;
	newItem->maxCondition = oldItem->maxCondition;
	
	//Stores the amount and dimensions of this item.
	newItem->amount = oldItem->amount;
	newItem->weight = oldItem->weight;
	newItem->space = oldItem->space;
	
	//Stores the effects of the item.
	for (uint8_t index = 0; index < oldItem->numExtraEffects; index++) {
		memcpy(newItem->extraEffects[index], oldItem->extraEffects[index], strlen(oldItem->extraEffects[index]));
	}
	newItem->numExtraEffects = oldItem->numExtraEffects;
	newItem->lengthOfEffects = oldItem->lengthOfEffects;
	
	//Stores the damage protections of the item.
	for (uint8_t index = 0; index < 13; index++) {
		newItem->damage[index] = oldItem->damage[index];
	}
	
	//Stores the weapon stats.
	newItem->minRange = oldItem->minRange;
	newItem->effectiveRange = oldItem->effectiveRange;
	newItem->maxRange = oldItem->maxRange;
	newItem->ammoCapacity = oldItem->ammoCapacity;
	newItem->ammoLoaded = oldItem->ammoLoaded;
	newItem->shotsPerUse = oldItem->shotsPerUse;
	
	//Copies the given necessary ammo into the name array of this item.
	memcpy(newItem->ammoNeeded, oldItem->ammoNeeded, strlen(oldItem->ammoNeeded));
	
	//Stores the attractiveness of the clothing.
	for (uint8_t index = 0; index < 5; index++) {
		newItem->charismaEffects[index] = oldItem->charismaEffects[index];
	}
	
	//Stores the food stats of the item.
	newItem->spoilRate = oldItem->spoilRate;
	newItem->filling = oldItem->filling;
	newItem->taste = oldItem->taste;
	
	//Stores the storage space of the item.
	newItem->storageSpace = oldItem->storageSpace;
	
	return newItem;
};

/** Splits a stack into two identical items and returns the new
 * 	item with an amount equal to the given stack size and subtracts
 * 	the given stack amount from the old item amount.
 */
item *itemSplitStack(item *oldItem, uint16_t newStackSize) {
	
	//Checks that there is enough amount of the old item for a new stack.
	if (oldItem->amount <= newStackSize) return NULL;
	
	//Creates the new item identical to the old item.
	item *newItem = itemDeepCopy(oldItem);
	
	//Checks the new item isn't null.
	if (newItem == NULL || oldItem == NULL) return NULL;
	
	//Shuffles the amount in the stack of items.
	newItem->amount = newStackSize;
	oldItem->amount = (oldItem->amount - newStackSize);
	
	return newItem;
};

/** Stacks two items with the same name into one item
 * 	then frees the SECOND item passed to it.
 * 	Returns 1 if the stack is successful, 0 if not.
 */
uint8_t stackItem(item *itemOne, item *itemTwo) {
	
	if (itemOne == NULL || itemTwo == NULL || strcmp(itemOne->name, itemTwo->name) != 0) {
		return 0;
	}
	
	itemOne->amount += itemTwo->amount;
	free(itemTwo);
	return 1;
};
