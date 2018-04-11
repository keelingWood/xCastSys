#include <unistd.h>
#include "unitTests.h"

int main(int argc, char* argv[]) {
	char testString[3][16];
	strcpy(testString[0], "ives is my name");
	strcpy(testString[1], "dive is my name");
	strcpy(testString[2], "lies is my name");
	entity *being = createEntity("ives wood", "human female", "a test subject", 7, 7, 7, 7, 7, 7, 7, testString, 3);

	if (testEntityCreation(being) != 0) {
		printf("Entity Creation test failed.\n");
	}
	if (testEntityMethods(being) != 0) {
		printf("Entity Methods failed.\n");
	}
	
	char itemEffectTestString[3][30];
	strcpy(itemEffectTestString[0], "ives is my name item");
	strcpy(itemEffectTestString[1], "dive is my name item");
	strcpy(itemEffectTestString[2], "lies is my name item");
	uint16_t itemDamageTestArray[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	uint16_t testSpecialHoldingArray[7] = {0, 1, 2, 3, 4, 5, 6};
	uint8_t itemAttractivenessArray[5] = {0, 1, 2, 3, 4};
	uint16_t augmentHealthIncreases[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	
	
	item *otherItem = createOtherItem("other", "this is an other item", 100, 69, 69, 3, 4, 5);
	item *foodItem = createFooditem("food", "some test food", 100, 68, 69, 3, 4, 5, 6, 7, 8);
	item *potionItem = createPotionItem("potion", "a test potion", 100, 69, 69, 2, 3, 4, itemDamageTestArray, itemEffectTestString, 3, 10);
	item *ammoItem = createAmmunitionItem("ammo", "a 'munition test", 100, 69, 69, 2, 3, 4, itemDamageTestArray, itemEffectTestString, 3, 10);
	item *clothesItem = createWearableItem("hat", "a wearable test", 4, 100, 69, 69, 2, 3, 4, itemDamageTestArray, itemEffectTestString, 3, itemAttractivenessArray, 5, testSpecialHoldingArray);
	item *weaponItem = createHoldableItem("sharp stick", "a fancy sharpened stick", 13, 43, 100, 100, 1, 50, 2, itemDamageTestArray, itemEffectTestString, 3, 10, 3, 6, 8, 1, 1, "none", 0);
	item *secondClothesItem = itemDeepCopy(clothesItem);
	augment *augOne = createAugment("sharp thumb tact", "a sharp thumb tact with glue", 10, 30, itemEffectTestString, 3, testSpecialHoldingArray, augmentHealthIncreases, 1, testSpecialHoldingArray);
	augment *augTwo = createAugment("dull thumb tact", "a dull thumb tact with glue", 10, 30, itemEffectTestString, 3, testSpecialHoldingArray, augmentHealthIncreases, 1, testSpecialHoldingArray);
	augment *augThree = createAugment("purple pompom", "a purple fluffy pompom", 3, 30, itemEffectTestString, 3, testSpecialHoldingArray, augmentHealthIncreases, 1, testSpecialHoldingArray);
	augment *augFour = createAugment("red pompom", "a red pompom", 4, 30, itemEffectTestString, 3, testSpecialHoldingArray, augmentHealthIncreases, 1, testSpecialHoldingArray);
	
	
	if (testItemOtherCreation(otherItem) != 0) {
		printf("Other item creation failed.\n");
	}
	if (testItemFoodCreation(foodItem) != 0) {
		printf("Food item creation failed.\n");
	}
	if (testItemPotionCreation(potionItem) != 0) {
		printf("Potion item creation failed.\n");
	}
	if (testItemAmmunitionCreation(ammoItem) != 0) {
		printf("Ammo item creation failed.\n");
	}
	if (testItemClothesCreation(clothesItem) != 0) {
		printf("Hat item creation failed.\n");
	}
	if (testItemHoldableCreation(weaponItem) != 0) {
		printf("Weapon item creation failed.\n");
	}
	if (testItemClothesCreation(secondClothesItem) != 0) {
		printf("Item cloning failed.\n");
	}
	if (checkEntityBagMethods(being, clothesItem, foodItem) != 0) {
		printf("Entity bag methods failed.\n");
	}
	if (checkEntityEquipmentMethods(being, clothesItem, secondClothesItem, weaponItem) != 0) {
		printf("Entity equipment methods failed.\n");
	}
	if (testAugmentCreationAndEntityMethods(augOne, augTwo, augThree, augFour, being) != 0) {
		printf("Augment creation and equiping methods failed.\n");
	}
	printf("Tests done.\n");
}

uint8_t testEntityCreation(entity *being) {
	
	uint8_t status = 0;
	
	if (strcmp("ives wood", being->name) != 0) {
		printf("Name incorrect.\n");
		status++;
	}
	if (being->species != 1) {
		printf("Species incorrect.\n");
		status++;
	}
	if (being->strength != 7) {
		printf("Stats incorrect.\n");
		status++;
	}
	if (strcmp("dive is my name", being->proficiencies[1])  != 0) {
		printf("Proficiencies incorrect.\n");
		status++;
	}
	if (strcmp("a test subject", being->desc) != 0) {
		printf("Description incorrect.\n");
		status++;
	}
	if (being->head_Health_Curr[1] != 21) {
		printf("Health incorrect.\n");
		status++;
	}
	
	return status;
}

uint8_t testEntityMethods(entity *being) {
	
	uint8_t status = 0;
	
	addProficiency(being, "struggling");
	if (strcmp("struggling",being->proficiencies[3])  != 0 || being->numProficiencies != 4) {
		printf("Proficiency addition incorrect.\n");
		printf(being->proficiencies[3]);
		printf(" not struggling\n");
		status++;
	}
	
	levelUp(being);
	addExp(being, 69);
	if (being->level != 2 || being->exp != 69) {
		printf("Level and exp addition not working");
		status++;
	}
	
	if (skillCheck(being, "str skill") != -3) {
		printf("Skill check failed with no proficiencies.\n");
		status++;
	}
	
	addProficiency(being, "str skill");
	if (skillCheck(being, "str skill") != -2) {
		printf("Skill check failed with a proficiency.\n");
		status++;
	}
	
	if (doesHaveAbility(being, "yes") != 0 || doesHaveAbility(being, "no") != 0) {
		printf("Ability check failed with no skills.\n");
		printf("\n");
		status++;
	}
	
	addAbility(being, "yes");
	if (doesHaveAbility(being, "yes") != 1 || doesHaveAbility(being, "no") != 0) {
		printf("Ability check failed with a skill.\n");
		status++;
	}
	
	removeAbility(being, "yes");
	if (doesHaveAbility(being, "yes") != 0 || doesHaveAbility(being, "no") != 0) {
		printf("Ability check failed with a skill removed.\n");
		status++;
	}
	
	
	return status;
};

uint8_t testItemOtherCreation(item *other) {
	
	uint8_t status = 0;
	
	if (strcmp("other", other->name) != 0) {
		printf("Other item name incorrect.\n");
		status++;
	}
	if (other->type != 0) {
		printf("Other item type incorrect.\n");
		status++;
	}
	if (other->space != 5) {
		printf("Other item space incorrect.\n");
		status++;
	}
	
	return status;
};

uint8_t testItemFoodCreation(item *food) {
	
	uint8_t status = 0;
	
	if (strcmp("food", food->name) != 0) {
		printf("Food item name incorrect.\n");
		status++;
	}
	if (food->type != 1) {
		printf("Food item type incorrect.\n");
		status++;
	}
	if (food->space != 5) {
		printf("Food item space incorrect.\n");
		status++;
	}
	
	return status;
};

uint8_t testItemPotionCreation(item *potion) {
	
	uint8_t status = 0;
	
	if (strcmp("potion", potion->name) != 0) {
		printf("Potion item name incorrect.\n");
		status++;
	}
	if (potion->type != 2) {
		printf("Potion item type incorrect.\n");
		status++;
	}
	if (potion->space != 4) {
		printf("Potion item space incorrect.\n");
		status++;
	}
	if (potion->damage[3] != 3) {
		printf("Potion item damage stats incorrect.\n");
		status++;
	}
	if (strcmp("lies is my name item", potion->extraEffects[2]) != 0) {
		printf(potion->extraEffects[2]);
		printf("|- Potion item extra effects incorrect.\n");
		status++;
	}
	
	return status;
};

uint8_t testItemAmmunitionCreation(item *ammo) {
	
	uint8_t status = 0;
	
	if (strcmp("ammo", ammo->name) != 0) {
		printf("Ammo item name incorrect.\n");
		status++;
	}
	if (ammo->type != 3) {
		printf("Ammo item type incorrect.\n");
		status++;
	}
	if (ammo->space != 4) {
		printf("Ammo item space incorrect.\n");
		status++;
	}
	if (ammo->damage[3] != 3) {
		printf("Ammo item damage stats incorrect.\n");
		status++;
	}
	if (strcmp("dive is my name item", ammo->extraEffects[1]) != 0) {
		printf(ammo->extraEffects[1]);
		printf("|- Ammo item extra effects incorrect.\n");
		status++;
	}
	
	return status;
};

uint8_t testItemClothesCreation(item *clothes) {
	
	uint8_t status = 0;
	
	if (strcmp("hat", clothes->name) != 0) {
		printf("Hat item name incorrect.\n");
		status++;
	}
	if (clothes->type != 4) {
		printf("Hat item type incorrect.\n");
		status++;
	}
	if (clothes->space != 4) {
		printf("Hat item space incorrect.\n");
		status++;
	}
	if (clothes->damage[4] != 4) {
		printf("Hat item damage stats incorrect.\n");
		status++;
	}
	if (strcmp("lies is my name item", clothes->extraEffects[2]) != 0) {
		printf("Hat item extra effects incorrect.\n");
		status++;
	}
	if (clothes->charismaEffects[2] != 2) {
		printf("Hat item charisma stats incorrect.\n");
		status++;
	}
	
	return status;
};

uint8_t testItemHoldableCreation(item *weapon) {
	
	uint8_t status = 0;
	
	if (strcmp("sharp stick", weapon->name) != 0) {
		printf("Stick item name incorrect.\n");
		status++;
	}
	if (weapon->type != 13) {
		printf("Stick item type incorrect.\n");
		status++;
	}
	if (weapon->space != 2) {
		printf("Stick item space incorrect.\n");
		status++;
	}
	if (weapon->damage[2] != 2) {
		printf("Stick item damage stats incorrect.\n");
		status++;
	}
	if (strcmp("ives is my name item", weapon->extraEffects[0]) != 0) {
		printf("Stick item extra effects incorrect.\n");
		status++;
	}
	if (strcmp("none", weapon->ammoNeeded) != 0) {
		printf("Stick ammo needed incorrect.\n");
		status++;
	}
	if (weapon->effectiveRange != 6) {
		printf("Stick effective range incorrect.\n");
		status++;
	}
	
	return status;
};

uint8_t checkEntityBagMethods(entity *being, item *thing, item *otherThing) {
	
	uint8_t status = 0;
	
	if (removeEntityItem(being, "an item") != 0 || doesEntityHaveItem(being, "hat")) {
		printf("Remove item or does have item failing with no items in bag.\n");
		status++;
	}
	
	addEntityItem(being, thing);
	if (doesEntityHaveItem(being, thing->name) != 1 || removeEntityItem(being, thing->name) != 1) {
		printf("Remove item or does have item failing with one item in bag.\n");
		status++;
	}
	
	addEntityItem(being, otherThing);
	addEntityItem(being, thing);
	if (doesEntityHaveItem(being, thing->name) != 2 || removeEntityItem(being, thing->name) != 1) {
		printf("Remove item or does have item failing with two items in bag.\n");
		status++;
	}
	
	if (getEntityItemPointer(being, otherThing->name) != otherThing) {
		printf("Get item pointer by name failed.\n");
		status++;
	}
	
	return status;
};

uint8_t checkEntityEquipmentMethods(entity *being, item *thingOne, item *thingTwo, item *holdable) {
	
	uint8_t status = 0;
	
	if (deEquipItemAt(being, 4) != NULL) {
		printf("Equiped Item not null or item dequip failed with no items.\n");
		status++;
	}
	
	if (equipItem(being, thingOne) != 1) {
		printf("Equiping item failed with no items in slot before hand.\n");
		status++;
	}
	
	if (deEquipItemAt(being, 4) != thingOne) {
		printf("Dequiping existing item failed.\n");
		status++;
	}
	
	
	if (removeItemInHand(being, 1) != NULL) {
		printf("Removing item in hand not null or item dequip failed with no items.\n");
		status++;
	}
	
	if (putItemInHand(being, holdable, 1) != 1) {
		printf("Putting item in hand failed with no items in slot before hand.\n");
		status++;
	}
	
	if (removeItemInHand(being, 1) != holdable) {
		printf("Removing existing item from hand failed.\n");
		status++;
	}
	
	
	return status;
};

uint8_t testAugmentCreationAndEntityMethods(augment *augOne, augment *augTwo, augment *augThree, augment *augFour, entity *being) {
	
	uint8_t status = 0;
	
	if (strcmp(augOne->name, "sharp thumb tact") != 0) {
		printf("Augment creation method failed.\n");
		status++;
	}
	if (removeAugment(being, "sharp thumb tact", 0) != NULL) {
		printf("Entity getting an augment with no other augments failed.\n");
	}
	if (putSingleAugemnt(being, augOne, 1) != 1) {
		printf("Putting an augment with no prior augment failed.\n");
		status++;
	}
	if (putSingleAugemnt(being, augTwo, 1) != 0) {
		printf("Putting augment in full slot failed.\n");
		status++;
	}
	if (putSingleAugemnt(being, augTwo, 0) != 1) {
		printf("Putting augment in empty slot after installing other augments failed.\n");
		status++;
	}
	if (removeAugment(being, "sharp thumb tact", 0) != NULL) {
		printf("Removing augment from wrong side failed.\n");
		status++;
	}
	if (removeAugment(being, "sharp thumb tact", 1) != augOne) {
		printf("Correct augment removal failed.\n");
		status++;
	}
	if (putSingleAugemnt(being, augThree, 3) != 1) {
		printf("Insertion of central augment failed.\n");
		status++;
	}
	if (putSingleAugemnt(being, augThree, 3) != 0) {
		printf("Insertion of duplicate central augment failed.\n");
		status++;
	}
	if (putSingleAugemnt(being, augFour, 3) != 1) {
		printf("Insertion of addional central augment failed.\n");
		status++;
	}
	
	return status;
}
