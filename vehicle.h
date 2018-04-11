#ifndef VEHICLE_H
#define VEHICLE_H

#include <stdint.h>
#include "entity.h"

struct _vehicle {
	
	char name[42];
	
	char desc[100];
	
	uint16_t size;
	uint16_t mass;
	/* Speed of the vehicle. (Distance in one turn).
	 * 0 = land;
	 * 1 = air;
	 * 2 = sea;
	 */
	uint16_t speeds[3];
	/* Can go underwater */
	uint8_t submersible;
	/* Can stealth */
	uint8_t canStealth;
	
	uint8_t maxPassengers;
	uint8_t currPassengers;
	
	entity *pilot;
	
	entity *passengers;
	
	storage *ritualItems;
	uint8_t numRitualItems;
	storage *smallArms;
	uint8_t numSmallArms;
	storage *cannons;
	uint8_t numCannons;
	
	storage *cargo;
	
	//The available space and weight of the vehicle
	//Adding items and people reduces this.
	uint16_t availableSpace;
	uint16_t availableWeight;
	//The travel distance reduced by each kg or weight.
	uint16_t haulingAbility;
	
};

typedef struct _vehicle vehicle;

#endif
