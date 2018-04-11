#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include "storage.h"
#include "augment.h"


struct _entity {
	
	/* The name of this entity */
	char name[42];
	/* The mass and height of this entity in kg and cm */
	uint16_t mass;
	uint16_t height;
	
	/* A physical description of this entity */
	char desc[100];
	
	/* Current level and exp of this entity */
	uint8_t level;
	uint16_t exp;
	
	/* The identifier for this entities species.
	 * Defines how to handles this entity
	 */
	uint8_t species;
	
	/* The items currently on this entity, holds the names of the
	 * items currently in the entities possession.
	 */
	storage *bag;
	uint16_t space;
	uint16_t weight;
	
	/* Special holding space for specific items
	 * 0 = Food;
	 * 1 = potion;
	 * 2 = ammo;
	 * 3 = ritural item;
	 * 4 = blade;
	 * 5 = small gun;
	 * 6 = medical;
	 */
	uint16_t specialStorageSpace[7];
	
	
	/* The items slots of this entity */
	item *wearableSlots[8];
	uint8_t numWearableEquipment;
	
	item *rightHand;
	item *leftHand;
	
	/* The proficiencies of this entity */
	char proficiencies[60][16];
	uint8_t numProficiencies;
	
	/* The statuses and effects of this entity */
	char effects[60][30];
	uint8_t numEffects;
	
	/* The current skills of this entity */
	char abilities[60][30];
	uint8_t numAbilities;
	
	/* The stats of this entity */
	uint8_t strength;
	uint8_t finesse;
	uint8_t endurance;
	uint8_t fortitude;
	uint8_t intelligence;
	uint8_t intuition;
	uint8_t charisma;
	uint8_t strength_Base;
	uint8_t finesse_Base;
	uint8_t endurance_Base;
	uint8_t fortitude_Base;
	uint8_t intelligence_Base;
	uint8_t intuition_Base;
	uint8_t charisma_Base;
	
	/* The health of this entity */
	uint16_t total_Health;
	
	/* 0 = physical;
	 * 1 = temp;
	 * 2 = other;
	 */
	uint16_t head_Health_Max[3];
	uint16_t neck_Health_Max[3];
	uint16_t torso_Health_Max[3];
	uint16_t groin_Health_Max[3];
	uint16_t right_Arm_Health_Max[3];
	uint16_t right_Hand_Health_Max[3];
	uint16_t left_Arm_Health_Max[3];
	uint16_t left_Hand_Health_Max[3];
	uint16_t right_Leg_Health_Max[3];
	uint16_t right_Foot_Health_Max[3];
	uint16_t left_Leg_Health_Max[3];
	uint16_t left_Foot_Health_Max[3];
	uint16_t head_Health_Curr[3];
	uint16_t neck_Health_Curr[3];
	uint16_t torso_Health_Curr[3];
	uint16_t groin_Health_Curr[3];
	uint16_t right_Arm_Health_Curr[3];
	uint16_t right_Hand_Health_Curr[3];
	uint16_t left_Arm_Health_Curr[3];
	uint16_t left_Hand_Health_Curr[3];
	uint16_t right_Leg_Health_Curr[3];
	uint16_t right_Foot_Health_Curr[3];
	uint16_t left_Leg_Health_Curr[3];
	uint16_t left_Foot_Health_Curr[3];
	
	/*	Implant slots */
	//Space for the implants
	augment *centerImplants[30];
	uint8_t numCenterImplants;
	augment *rightImplants[30];
	uint8_t numRightImplants;
	augment *leftImplants[30];
	uint8_t numLeftImplants;
	
	//Implant max number trackers	
	uint8_t maxNumImplants_Cranial;
	uint8_t maxNumImplants_Sensory;
	uint8_t maxNumImplants_Skin;
	uint8_t maxNumImplants_Gut;
	uint8_t maxNumImplants_Right_Arm;
	uint8_t maxNumImplants_Left_Arm;
	uint8_t maxNumImplants_Right_Hand;
	uint8_t maxNumImplants_Left_Hand;
	uint8_t maxNumImplants_Right_Leg;
	uint8_t maxNumImplants_Left_Leg;
	uint8_t maxNumImplants_Right_Foot;
	uint8_t maxNumImplants_Left_Foot;
};

typedef struct _entity entity;

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
	uint8_t numberOfProficiencies);

void addProficiency(entity *being, char proficiency[]);

void levelUp(entity *being);

void addExp(entity *being, uint16_t moarExp);

int8_t skillCheck(entity *being, char skill[]);

int8_t doesHaveAbility(entity *being, char ability[]);

void addAbility(entity *being, char ability[]);

uint8_t removeAbility(entity *being, char ability[]);

int8_t doesHaveEffect(entity *being, char effect[]);

void addEffect(entity *being, char effect[]);

uint8_t doesEntityHaveItem(entity *being, char itemName[]);

item *getEntityItemPointer(entity *being, char itemName[]);

uint8_t addEntityItem(entity *being, item *thing);

uint8_t removeEntityItem(entity *being, char itemName[]);

void freeEntity(entity *being);

uint8_t equipItem(entity *being, item *thing);

item *deEquipItemAt(entity *being, uint8_t type);

item *swapItem(entity *being, item *thing);

uint8_t getIndexOfItem(entity *being, uint8_t type);

item *removeItemInHand(entity *being, uint8_t isLeft);

uint8_t putItemInHand(entity *being, item *thing, uint8_t isLeft);
	
uint8_t putSingleAugemnt(entity *being, augment *aug, uint8_t isLeft);

uint8_t getMaxAugmentsByType(entity *being, uint8_t type, uint8_t isLeft);

uint8_t getCurrNumberAugmentsByType(augment *augArray[30], uint8_t numAugs, uint8_t type);

uint8_t doesHaveAugmentOfType(augment *augArray[30], uint8_t numAugs, uint8_t type);

uint8_t doesHaveAugmentByName(augment *augArray[30], uint8_t numAugs, char name[]);
	
augment *removeAugment(entity *being, char name[], uint8_t onLeft);
#endif
