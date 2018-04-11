#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "entity.h"

//Useful entity variables
int8_t avgStatVal = 10;

//The factors for health based on stats.
uint16_t total_Health_Factor = 10;
uint16_t head_Health_Factor = 3;
uint16_t neck_Health_Factor = 2;
uint16_t torso_Health_Factor = 8;
uint16_t groin_Health_Factor = 1;
uint16_t arm_Health_Factor = 4;
uint16_t hand_Health_Factor = 2;
uint16_t leg_Health_Factor = 5;
uint16_t foot_Health_Factor = 3;

//Factors for num of initial implants.
uint8_t numInitialImplants_Head = 2;
uint8_t numInitialImplants_Sensor = 2;
uint8_t numInitialImplants_Appearance = 2;
uint8_t numInitialImplants_Gut = 2;
uint8_t numInitialImplants_Arms = 2;
uint8_t numInitialImplants_Hands = 2;
uint8_t numInitialImplants_Legs = 2;
uint8_t numInitialImplants_Feets = 2;
	
/** A "constructor" for an entity, will modify the entity to have the given
 * name, species, stats, and proficiencies.
 */
entity *createEntity(char name[], uint8_t mass, uint8_t height, char species[],
	char description[],
	uint8_t strength,
	uint8_t finesse,
	uint8_t endurance,
	uint8_t fortitude,
	uint8_t intelligence,
	uint8_t intuition,
	uint8_t charisma,
	char proficiencies[][16],
	uint8_t numberOfProficiencies) {
		
	//Malloc space for the entity and return null if that fails
	entity *newEntity = malloc(sizeof(entity));
	if (newEntity == NULL) return NULL;
	
	//Initializes level of the creature
	newEntity->level = 1;
	newEntity->exp = 0;
	
	//Put the given name into a 42 length char array.
	memcpy(newEntity->name, name, strlen(name));
	
	//Stores the description of this entity.
	memcpy(newEntity->desc, description, strlen(description));
	
	//Store the species as an int.
	if (!strcmp("human female", species)) {
		newEntity->species = 1;
		}
	else if (!strcmp("human male", species)) {
		newEntity->species = 2;
		}
	else {
		newEntity->species = 0;
		}
	
	//Zero the inventory, equiped, skills, and effects of the entity.
	memset(newEntity->abilities, 0, sizeof(newEntity->abilities));
	newEntity->numAbilities = 0;
	memset(newEntity->effects, 0, sizeof(newEntity->effects));
	newEntity->numEffects = 0;
	newEntity->space = 0;
	newEntity->weight = 0;
	for (uint8_t index; index < 7; index++) {
		newEntity->specialStorageSpace[index] = 0;
	}
	
	newEntity->bag = createStorage(99);
	
	//Parse through the given proficiencies and save them to the entities proficiencies.
	memset(newEntity->proficiencies, 0, sizeof(newEntity->proficiencies));
	newEntity->numProficiencies = numberOfProficiencies;
	for (uint8_t index = 0; index < numberOfProficiencies; index++) {
		memcpy(newEntity->proficiencies[index], proficiencies[index], strlen(proficiencies[index]));
	};
			
	//Save the stats of the entity.
	newEntity->strength = strength;
	newEntity->finesse = finesse;
	newEntity->endurance = endurance;
	newEntity->fortitude = fortitude;
	newEntity->intelligence = intelligence;
	newEntity->intuition = intuition;
	newEntity->charisma = charisma;
	newEntity->strength_Base = strength;
	newEntity->finesse_Base = finesse;
	newEntity->endurance_Base = endurance;
	newEntity->fortitude_Base = fortitude;
	newEntity->intelligence_Base = intelligence;
	newEntity->intuition_Base = intuition;
	newEntity->charisma_Base = charisma;
	
	//Sets up total health for the entity
	newEntity->total_Health = fortitude * total_Health_Factor;
	
	//Setup the health and armour of the entity
	for (uint8_t index = 0; index < 3; index++) {
		newEntity->head_Health_Max[index] = fortitude * head_Health_Factor;
		newEntity->neck_Health_Max[index] = fortitude * neck_Health_Factor;
		newEntity->torso_Health_Max[index] = fortitude * torso_Health_Factor;
		newEntity->groin_Health_Max[index] = fortitude * groin_Health_Factor;
		newEntity->right_Arm_Health_Max[index] = fortitude * arm_Health_Factor;
		newEntity->right_Hand_Health_Max[index] = fortitude * hand_Health_Factor;
		newEntity->left_Arm_Health_Max[index] = fortitude * arm_Health_Factor;
		newEntity->left_Hand_Health_Max[index] = fortitude * hand_Health_Factor;
		newEntity->right_Leg_Health_Max[index] = fortitude * leg_Health_Factor;
		newEntity->right_Foot_Health_Max[index] = fortitude * foot_Health_Factor;
		newEntity->left_Leg_Health_Max[index] = fortitude * leg_Health_Factor;
		newEntity->left_Foot_Health_Max[index] = fortitude * foot_Health_Factor;
		newEntity->head_Health_Curr[index] = fortitude * head_Health_Factor;
		newEntity->neck_Health_Curr[index] = fortitude * neck_Health_Factor;
		newEntity->torso_Health_Curr[index] = fortitude * torso_Health_Factor;
		newEntity->groin_Health_Curr[index] = fortitude * groin_Health_Factor;
		newEntity->right_Arm_Health_Curr[index] = fortitude * arm_Health_Factor;
		newEntity->right_Hand_Health_Curr[index] = fortitude * hand_Health_Factor;
		newEntity->left_Arm_Health_Curr[index] = fortitude * arm_Health_Factor;
		newEntity->left_Hand_Health_Curr[index] = fortitude * hand_Health_Factor;
		newEntity->right_Leg_Health_Curr[index] = fortitude * leg_Health_Factor;
		newEntity->right_Foot_Health_Curr[index] = fortitude * foot_Health_Factor;
		newEntity->left_Leg_Health_Curr[index] = fortitude * leg_Health_Factor;
		newEntity->left_Foot_Health_Curr[index] = fortitude * foot_Health_Factor;
	}
	
	//Setting up equipment slots
	for (uint8_t index = 0; index < 8; index++) {
		newEntity->wearableSlots[index] = NULL;
	}
	newEntity->numWearableEquipment = 0;
	
	newEntity->rightHand = NULL;
	newEntity->leftHand = NULL;
	
	//Setting up controllers for augments.
	newEntity->numCenterImplants = 0;
	newEntity->numRightImplants = 0;
	newEntity->numLeftImplants = 0;
	
	//Head stuff
	newEntity->maxNumImplants_Cranial = numInitialImplants_Head;
	
	//Sensing stuff
	newEntity->maxNumImplants_Sensory = numInitialImplants_Sensor;
	
	//Outer stuff
	newEntity->maxNumImplants_Skin = numInitialImplants_Appearance;
	
	//Midsection stuff
	newEntity->maxNumImplants_Gut = numInitialImplants_Gut;
	
	//Right arm stuff
	newEntity->maxNumImplants_Right_Arm = numInitialImplants_Arms;
	
	//Left arm stuff
	newEntity->maxNumImplants_Left_Arm = numInitialImplants_Arms;
	
	//Right hand stuff
	newEntity->maxNumImplants_Right_Hand = numInitialImplants_Hands;
	
	//Left hand stuff
	newEntity->maxNumImplants_Left_Hand = numInitialImplants_Hands;
	
	//Right leg stuff
	newEntity->maxNumImplants_Right_Leg = numInitialImplants_Legs;
	
	//Left leg stuff
	newEntity->maxNumImplants_Left_Leg = numInitialImplants_Legs;
	
	//Right foot stuff
	newEntity->maxNumImplants_Right_Foot = numInitialImplants_Feets;
	
	//Left foot stuff
	newEntity->maxNumImplants_Left_Foot = numInitialImplants_Feets;
		
	return newEntity;
};

/** Adds a proficiency to the entities list of proficiencies. */
void addProficiency(entity *being, char proficiency[]) {
	memcpy(being->proficiencies[being->numProficiencies], proficiency, strlen(proficiency));
	being->numProficiencies++;
};

/** Adds a single level to the entity. */
void levelUp(entity *being) {
	being->level++;
};

/** Adds the given amount of exp to the entity. */
void addExp(entity *being, uint16_t moarExp) {
	being->exp += moarExp;
};

/** Returns the given skill modifier for the given skill */
int8_t skillCheck(entity *being, char skill[]) {
	int8_t skillModifier = 0;
	
	if (strcmp("str skill", skill) == 0
	|| strcmp("o str skill", skill) == 0
	|| strcmp("lifting", skill) == 0) {
		skillModifier = being->strength;
	}
	else if (strcmp("int skill", skill) == 0
	|| strcmp("o int skill", skill) == 0) {
		skillModifier = being->intelligence;
	}
	
	for (uint8_t index = 0; index < being->numProficiencies; index++) {
		if (strcmp(skill, being->proficiencies[index]) == 0) {
			skillModifier++;
		}
	}
	
	return skillModifier - avgStatVal;
};

/** Determines if an entity has the given ability.
 * 	returns the index of the ability + 1 in the entity's ability array,
 * 	and a 0 if the entity does not have the ability.
 */
int8_t doesHaveAbility(entity *being, char ability[]) {
	for (uint8_t index = 0; index < being->numAbilities; index++) {
		if (strcmp(ability, being->abilities[index]) == 0) {
			return index + 1;
		}
	}
	return 0;
};

/** Adds an ability to the entities list of abilities. */
void addAbility(entity *being, char ability[]) {
	memcpy(being->abilities[being->numAbilities], ability, strlen(ability));
	being->numAbilities++;
};

/** Removes an ability from the entities list of abilities.
 * 	returns a 0 if the ability is not removed successfully and a 1 if it is.
 */
uint8_t removeAbility(entity *being, char ability[]) {
	uint8_t abilityAt = doesHaveAbility(being, ability);
	if (abilityAt == 0) {
		return 0;
	}
	memcpy(being->abilities[abilityAt - 1], being->abilities[being->numAbilities], strlen(being->abilities[being->numAbilities]));
	being->numAbilities--;
	return 1;
};

/** Determines if an entity has the given effect.
 * 	returns the index of the effect + 1 in the entity's effects array,
 * 	and a 0 if the entity does not have the effect.
 */
int8_t doesHaveEffect(entity *being, char effect[]) {
	for (uint8_t index = 0; index < being->numEffects; index++) {
		if (strcmp(effect, being->effects[index]) == 0) {
			return index + 1;
		}
	}
	return 0;
};

/** Adds an effect to the entities list of effects. */
void addEffect(entity *being, char effect[]) {
	memcpy(being->effects[being->numEffects], effect, strlen(effect));
	being->numEffects++;
};

/** Removes an effect from the entities list of effects.
 * 	returns a 0 if the effect is not removed successfully and a 1 if it is.
 */
uint8_t removeEffect(entity *being, char effect[]) {
	uint8_t effectAt = doesHaveEffect(being, effect);
	if (effectAt == 0) {
		return 0;
	}
	memcpy(being->effects[effectAt - 1], being->effects[being->numEffects], strlen(being->effects[being->numEffects]));
	being->numEffects--;
	return 1;
};

/** Checks if the entity has the given item in their bag.
 * 	returns the index of the item in the entity's bag + 1, returns a 0 if
 *  the entity does not have the item.
 */
uint8_t doesEntityHaveItem(entity *being, char itemName[]) {
	return doesStorageHaveItem(being->bag, itemName);
};

/** Returns a pointer to the item with the given name.
 */
item *getEntityItemPointer(entity *being, char itemName[]) {
	return getStorageItemPointer(being->bag, itemName);
};

/** Adds an item to the entity's bag.
 * 	Returns 1 if successful, 0 else.
 */
uint8_t addEntityItem(entity *being, item *thing) {
	return addStorageItem(being->bag, thing);
};

/** Removes a given item from the entity's bag by index.
 * 	returns 1 if the item is removed successfully, 0 if not.
 */
uint8_t removeEntityItem(entity *being, char itemName[]) {
	item *wasRemoved = removeStorageItem(being->bag, itemName);
	if (wasRemoved != NULL) {
		being->space += wasRemoved->space;
		being->weight += wasRemoved->weight;
		return 1;
	}
	else return 0;
};

/** Clears all items in the entity's bag and equiped
 * 	and frees the entity.
 */
 void freeEntity(entity *being) {
	freeStorage(being->bag);
	
	
	
	free(being);
 };

/** Puts the given item in the given entity's slot corresponding to the item type.
 * 	If the item is an equipable, it is placed in the correct slot, regardless of the value passed to whichHand.
 * 	If the item is other wise (and correctly built) it will be placed in the corresponding hand slot.
 *  0 for right hand, 1 for left, 4 - 11 for an equipment slot.
 * 	If the available slot isn't empty (null) then the item is not placed into the slot and a 0 is returned.
 * 	Else a 1 is returned.
 */
uint8_t equipItem(entity *being, item *thing) {
	
	if (getIndexOfItem(being, thing->type)) return 0;
	
	if (thing->type < 4 || thing->type > 11) return 0;
	
	being->wearableSlots[being->numWearableEquipment] = thing;
	being->numWearableEquipment++;
	
	return 1;
}

/** Takes the item in the given slot,
 *  0 for right hand, 1 for left,
 *  4 - 11 for equipment,
 *  2, 3, & > 11 are not used,
 *  and sets the being slot to NULL and returns the item.
 *  Returns the item if it is successfuly removed, and NULL else.
 */
item *deEquipItemAt(entity *being, uint8_t type) {
	
	item *itemToReturn = NULL;
	
	uint8_t indexOfItem = getIndexOfItem(being, type);
	if (indexOfItem == 0) return NULL;
	
	indexOfItem--;
	itemToReturn = being->wearableSlots[indexOfItem];
	being->wearableSlots[indexOfItem] = being->wearableSlots[being->numWearableEquipment];
	being->numWearableEquipment--;
	
	return itemToReturn;
}

/** Swaps the given item pointer and the item pointer in the
 *  correct being's item slot.
 *  0 for right hand, 1 for left, 2 for an equipment slot.
 *  Returns NULL if where is invalid.
 * 	Can also return null if the item is not correctly equiped but the
 *  item in the origional slot is correctly placed.
 */
item *swapItem(entity *being, item *thing) {
	
	item *oldThing = NULL;
	
	uint8_t indexOfItem = getIndexOfItem(being, thing->type);
	if (indexOfItem == 0) {
		equipItem(being, thing);
		
		return oldThing;
	}
	indexOfItem--;
	oldThing = being->wearableSlots[indexOfItem];
	
	deEquipItemAt(being, oldThing->type);
	equipItem(being, thing);
	
	return oldThing;
}

/**	Finds the index + 1 of a wearable item by slot.
 */
uint8_t getIndexOfItem(entity *being, uint8_t type) {
	
	for (uint8_t index = 0; index < being->numWearableEquipment; index++) {
		if (being->wearableSlots[index]->type == type) {
			return index + 1;
		}
	}
	
	return 0;
}

/** Puts an item into the entity's hand, depending on which hand is designated.
 * 	Returns a 1 if successful, 0 else.
 */
uint8_t putItemInHand(entity *being, item *thing, uint8_t isLeft) {
	
	if (!isLeft) {
		if (being->rightHand == NULL) {
			being->rightHand = thing;
			return 1;
		}
	}
	else {
		if (being->leftHand == NULL) {
			being->leftHand = thing;
			return 1;
		}
	}
	
	return 0;
}

/** Removes an item from an entity's hand and returns that item.
 */
item *removeItemInHand(entity *being, uint8_t isLeft) {
	
	item *inHand = NULL;
	
	if (!isLeft) {
		if (being->rightHand != NULL) {
			inHand = being->rightHand;
			being->rightHand = NULL;
		}
	}
	else {
		if (being->leftHand != NULL) {
			inHand = being->leftHand;
			being->leftHand = NULL;
		}
	}
	
	return inHand;
}

/** Given an item and which hand, the item is put in the designated hand
 * 	and returns the old item in the hand.
 */
item *swapItemFromHand(entity *being, item *thing, uint8_t isLeft) {
	
	item *inHand = NULL;
	
	if (!isLeft) {
		if (being->rightHand != NULL) {
			inHand = being->rightHand;
			being->rightHand = thing;
		}
	}
	else {
		if (being->leftHand != NULL) {
			inHand = being->leftHand;
			being->leftHand = thing;
		}
	}
	
	return inHand;
	
}

/**	Adds a single augment to the creature if the slot is empty or if the max
 * 	number of augments hasn't been reached.
 *  isLefl, 0 == right, 1 == left.
 * 	returns 0 if aug cannot be added, if it is.
 */
uint8_t putSingleAugemnt(entity *being, augment *aug, uint8_t isLeft) {
	
	uint8_t maxAugments = getMaxAugmentsByType(being, aug->type, isLeft);
	uint8_t currNumAugs;
	
	if (aug->type > 6) {
		if (!isLeft) {
			currNumAugs = getCurrNumberAugmentsByType(being->rightImplants, being->numRightImplants, aug->type);
			if (aug->type > 11) {
				if (!doesHaveAugmentByName(being->rightImplants, being->numRightImplants, aug->name) && (currNumAugs < maxAugments)) {
					being->rightImplants[being->numRightImplants] = aug;
					being->numRightImplants++;
					return 1;
				}
				else return 0;
			}
			else {
				if (!currNumAugs) {
					being->rightImplants[being->numRightImplants] = aug;
					being->numRightImplants++;
					return 1;
				}
				else return 0;
			}
		}
		else {
			currNumAugs = getCurrNumberAugmentsByType(being->leftImplants, being->numLeftImplants, aug->type);
			if (aug->type > 11) {
				if (!doesHaveAugmentByName(being->leftImplants, being->numLeftImplants, aug->name) && (currNumAugs < maxAugments)) {
					being->leftImplants[being->numLeftImplants] = aug;
					being->numLeftImplants++;
					return 1;
				}
				else return 0;
			}
			else {
				if (!currNumAugs) {
					being->leftImplants[being->numLeftImplants] = aug;
					being->numLeftImplants++;
					return 1;
				}
				else return 0;
			}
		}
	}
	else {
		currNumAugs = getCurrNumberAugmentsByType(being->centerImplants, being->numCenterImplants, aug->type);
			if (aug->type > 2) {
				if (!doesHaveAugmentByName(being->centerImplants, being->numCenterImplants, aug->name) && (currNumAugs < maxAugments)) {
					being->centerImplants[being->numCenterImplants] = aug;
					being->numCenterImplants++;
					return 1;
				}
				else return 0;
			}
			else {
				if (!currNumAugs) {
					being->centerImplants[being->numCenterImplants] = aug;
					being->numCenterImplants++;
					return 1;
				}
				else return 0;
			}
	}
	
	return 0;
}

/** Gets the max number of augments of a single type.
 */
uint8_t getMaxAugmentsByType(entity *being, uint8_t type, uint8_t isLeft) {
	if (type == 3) { 
		return being->maxNumImplants_Cranial;
	}
	else if (type == 4) { 
		return being->maxNumImplants_Skin;
	}
	else if (type == 5) { 
		return being->maxNumImplants_Sensory;
	}
	else if (type == 6) { 
		return being->maxNumImplants_Gut;
	}
	else if (type == 12 && !isLeft) { 
		return being->maxNumImplants_Right_Arm;
	}
	else if (type == 13 && !isLeft) { 
		return being->maxNumImplants_Right_Leg;
	}
	else if (type == 14 && !isLeft) { 
		return being->maxNumImplants_Right_Hand;
	}
	else if (type == 15 && !isLeft) { 
		return being->maxNumImplants_Right_Foot;
	}
	else if (type == 12) { 
		return being->maxNumImplants_Left_Arm;
	}
	else if (type == 13) { 
		return being->maxNumImplants_Left_Leg;
	}
	else if (type == 14) { 
		return being->maxNumImplants_Left_Hand;
	}
	else if (type == 15) { 
		return being->maxNumImplants_Left_Foot;
	}
	return 0;
}

/** Finds how many augments there are of a given type in a augment array.
 */
uint8_t getCurrNumberAugmentsByType(augment *augArray[30], uint8_t numAugs, uint8_t type) {
	
	uint8_t toReturn;
	
	for (uint8_t index = 0; index < numAugs; index++) {
		if (augArray[index]->type == type) {
			toReturn++;
		}
	}
	
	return toReturn;
}

/**	Searches through an array of augments and finds the index + 1 of the augment if
 * 	the array contains an augment of hte given type. 0 else.
 */
uint8_t doesHaveAugmentOfType(augment *augArray[30], uint8_t numAugs, uint8_t type) {
	
	for (uint8_t index = 0; index < numAugs; index++) {
		if (augArray[index]->type == type) {
			return index + 1;
		}
	}
	
	return 0;
}

/**	Searches through an array of augments and finds the index + 1 of the augment if
 * 	the array contains an augment of the given name. 0 else.
 */
uint8_t doesHaveAugmentByName(augment *augArray[30], uint8_t numAugs, char name[]) {
	
	for (uint8_t index = 0; index < numAugs; index++) {
		if (strcmp(augArray[index]->name, name) == 0) {
			return index + 1;
		}
	}
	
	return 0;
}

/** Removes an augment by the given name.
 */
augment *removeAugment(entity *being, char name[], uint8_t onLeft) {
	
	augment *augToReturn = NULL;
	
	uint8_t indexOfAugment;
	
	indexOfAugment = doesHaveAugmentByName(being->centerImplants, being->numCenterImplants, name);
	
	if (indexOfAugment) {
		indexOfAugment--;
		augToReturn = being->centerImplants[indexOfAugment];
		being->centerImplants[indexOfAugment] = being->centerImplants[being->numCenterImplants];
		being->numCenterImplants--;
	}
	
	if (!onLeft) {
		
		indexOfAugment = doesHaveAugmentByName(being->rightImplants, being->numRightImplants, name);
		if (indexOfAugment) {
			indexOfAugment--;
			augToReturn = being->rightImplants[indexOfAugment];
			being->rightImplants[indexOfAugment] = being->rightImplants[being->numRightImplants];
			being->numRightImplants--;
		}
	}
	else {
		
		indexOfAugment = doesHaveAugmentByName(being->leftImplants, being->numLeftImplants, name);
		if (indexOfAugment) {
			indexOfAugment--;
			augToReturn = being->leftImplants[indexOfAugment];
			being->leftImplants[indexOfAugment] = being->leftImplants[being->numLeftImplants];
			being->numLeftImplants--;
		}
	}
	
	return augToReturn;
};
