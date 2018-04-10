#ifndef AUGMENT_H
#define AUGMENT_H

#include <stdint.h>

struct _augment {
	
	/* The name of this augment */
	char name[42];
	
	/* A physical description of this augment */
	char desc[100];
	
	/* The type of this implant.
	 * Either:
	 * 0 = head & neck structure implant;
	 * 1 = skin implant;
	 * 2 = spine structural implant;
	 * 3 = cranial implants;
	 * 4 = appearance implants;
	 * 5 = sensor implants;
	 * 6 = gut implant;
	 * 7 = eye implants;
	 * 8 = arm structural implant;
	 * 9 = hand structural implant;
	 * 10 = leg structual implant;
	 * 11 = foot structural implant;
	 * 12 = arm component implant;
	 * 13 = leg component implant;
	 * 14 = hand component implant;
	 * 15 = foot component implant;
	 */
	uint8_t type;
	
	/* The currrent and max condition of this implant */
	uint16_t currCondition;
	uint16_t maxCondition;
	
	/* The abilities given by this implant*/
	char abilities[7][30];
	uint8_t numAbilities;
	
	//What stats and health the augment increases, and wether the increases are permanent
	//or togglable.
	uint8_t statIncrease[7];
	uint16_t healthIncreases[12];
	uint8_t isPerma;
};

typedef struct _augment augment;

#endif
