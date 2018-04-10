#ifndef ITEM_H
#define ITEM_H

#include <stdint.h>

struct _item {
	
	/* The name of this item */
	char name[20];
	
	/* A description of this item */
	char desc[100];
	
	/* The type of this item. ( ~ means can be held in a special space)
	 * Either:
	 * 0 = nonusable or consumable;
	 * 1 = 0~food;
	 * 2 = 1~potion;
	 * 3 = 2~ammunition;
	 * 4 = head slot;
	 * 5 = face slot;
	 * 6 = neck slot;
	 * 7 = torso slot;
	 * 8 = hands slot;
	 * 9 = pants slot;
	 * 10 = feet slot;
	 * 11 = bag slot;
	 * --- hand equipable ---
	 * 12 = 3~ritural item;
	 * 13 = 4~blade;
	 * 14 = blunt;
	 * 15 = 5~pistol;
	 * 16 = 5~smg;
	 * 17 = machine gun;
	 * 18 = rifle;
	 * 19 = shotgun;
	 * 20 = cannon;
	 * 21 = special weapon (usually a sprayer);
	 * 22 = 6~medical;
	 */
	uint8_t type;
	
	/* The currrent and max condition of this item
	 * (For weapons and clothing) */
	uint16_t currCondition;
	uint16_t maxCondition;
	/* The extra effects of this item
	 * (For weapons, ammuntion, clothing, and potions) */
	char extraEffects[7][30];
	uint8_t numExtraEffects;
	/* The length of the effects */
	uint16_t lengthOfEffects;
	/* The current cleanliness of this item (max of 100)
	 * (For all items) */
	uint8_t cleanliness;
	/* The amount of stack of this item */
	uint16_t amount;
	/* The weight and space of this item */
	uint16_t weight;
	uint16_t space;
	/* The effects of this item */
	/* For weapons (and ammuntion) */
	uint16_t minRange;
	uint16_t effectiveRange;
	uint16_t maxRange;
	uint16_t ammoCapacity;
	uint16_t ammoLoaded;
	char ammoNeeded[20];
	struct _item *ammo;
	uint16_t shotsPerUse;
	/* For weapons (damage) and clothing (protection)
	 * Types of damage and protection (by index);
	 * 0 = bullet		|-Physical---
	 * 1 = slash		|
	 * 2 = stab			|
	 * 3 = blunt		|
	 * 4 = fire			|-Temp---
	 * 5 = cold			|
	 * 6 = chemical		|-Other---
	 * 7 = radiation	|
	 * 8 = electrical	|
	 * 9 = holy			|-Total---
	 * 10 = curse		|
	 * 11 = stun		|
	 * 12 = psychic		|
	 */
	uint16_t damage[13];
	/* For food */
	uint8_t spoilRate;
	uint8_t filling;
	uint8_t taste;
	/* For clothing 
	 * Charisma effects (by index);
	 * 0 = cute
	 * 1 = sharp
	 * 2 = cool
	 * 3 = intimidation
	 * 4 = strange
	 */
	uint8_t charismaEffects[5];
	/* For clothing and bag items */
	uint16_t storageSpace;
	uint16_t specialStorageSpace[7];
	
};

typedef struct _item item;


item *createOtherItem (char name[], char description[],
	uint8_t cleanliness,
	uint16_t currCondition,
	uint16_t maxCondition,
	uint16_t amount,
	uint16_t weight,
	uint16_t space);
	
item *createFooditem (char name[], char description[],
	uint8_t cleanliness,
	uint16_t currCondition,
	uint16_t maxCondition,
	uint16_t amount,
	uint16_t weight,
	uint16_t space,
	uint8_t spoilRate,
	uint8_t filling,
	uint8_t taste);

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
	uint16_t lengthOfEffects);
	
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
	uint16_t lengthOfEffects);
	
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
	uint16_t specialStorageSpace[7]);
	
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
	char ammoNeeded[16],
	uint16_t shotsPerUse);
	
item *itemDeepCopy(item *oldItem);

item *itemSplitStack(item *oldItem, uint16_t newStackSize);

uint8_t stackItem(item *itemOne, item *itemTwo);

#endif
