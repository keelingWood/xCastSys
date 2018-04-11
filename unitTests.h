#ifndef UNITTESTS_H
#define UNITTESTS_H

#include "entity.h"

int main(int argc, char* argv[]);

uint8_t testEntityCreation(entity *being);
uint8_t testEntityMethods(entity *being);
uint8_t testItemOtherCreation(item *other);
uint8_t testItemFoodCreation(item *food);
uint8_t testItemPotionCreation(item *food);
uint8_t testItemAmmunitionCreation(item *ammo);
uint8_t testItemClothesCreation(item *hat);
uint8_t testItemHoldableCreation(item *weapon);
uint8_t checkEntityBagMethods(entity *being, item *thing, item *otherThing);
uint8_t checkEntityEquipmentMethods(entity *being, item *thingOne, item *thingTwo, item *holdable);
uint8_t testAugmentCreationAndEntityMethods(augment *augOne, augment *augTwo, augment *augThree, augment *augFour, entity *being);

#endif
