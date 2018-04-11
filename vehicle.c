#include <stdint.h>
#include <unistd.h>

#include "vehicle.h"

vehicle *createVehicle(char name[], char description[],
	uint16_t size,
	uint16_t mass,
	uint16_t speeds[3],
	uint8_t submersible,
	uint8_t canStealth,
	uint8_t maxPassengers,
	uint8_t numRituralItems,
	item *ritualItems,
	uint8_t numSmallArms,
	item *smallArms,
	uint8_t numCannons,
	item *cannons,
	uint16_t maxCarryWeight,
	uint16_t maxCarryVolume,
	uint16_t haulingAbility) {
	
	//Creates space for the vehicle
	vehicle *newVehicle = malloc(sizeof(vehicle));
	
	//Saves the name, desc, size, and mass of the vehicle.
	memcpy(newVehicle->name, name, strlen(name));
	
	memcpy(newVehicle->desc, description, strlen(description));
	
	newVehicle->size = size;
	newVehicle->mass = mass;
	
	//Stores the movement info of the vehicle.
	for (uint8_t index = 0; index < 3; index++){
		newVehicle->speeds[index] = speeds[index];
	}
	
	newVehicle->submersible = submersible;
	newVehicle->canStealth = canStealth;
	
	//Stores the passenger information and creates an array to hold pointers to all passengers.
	newVehicle->maxPassengers = maxPassengers;
	newVehicle->currPassengers = 0;
	newVehicle->passengers = malloc(sizeof(entity*) * maxPassengers);
	
	newVehicle->pilot = NULL;
	
	//Stores the weapon info.
	newVehicle->ritualItems = ritualItems;
	newVehicle->numRitualItems = ritualItems;
	newVehicle->smallArms = smallArms;
	newVehicle->numSmallArms = numSmallArms;
	newVehicle->cannons = cannons;
	newVehicle->numCannons = numCannons;
	
	//Store carrying info
	newVehicle->cargo = NULL;
	newVehicle->availableSpace = maxCarryVolume;
	newVehicle->availableWeight = maxCarryWeight;
	newVehicle->haulingAbility = haulingAbility;
	
}

/**	Removes a pilot from the vehicle and returns them.
 * 	Returns NULL if no pilot in the vehicle.
 */
entity *pilotExitVehicle(vehicle *mech) {
	
	entity *pilot = mech->pilot;
	mech->pilot = NULL;
	return pilot;
	
}

/** Puts a pilot in the vehicle, returns 1 if successful, 0 else.
 */
uint8_t pilotEnterVehicle(vehicle *mech, entity *toPilot) {
	if (mech->pilot != NULL) return 0;
	
	mech->pilot = toPilot;
	
	return 1;
}
