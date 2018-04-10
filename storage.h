#ifndef STORAGE_H
#define STORAGE_H

#include <stdint.h>
#include "item.h"

struct _storage {
	
	item *bag[99];
	uint16_t numItems;
	uint16_t maxItems;
	
};

typedef struct _storage storage;

storage *createStorage(uint16_t maxItems);

uint16_t doesStorageHaveItem(storage *store, char itemName[]);

item *getStorageItemPointer(storage *store, char itemName[]);

uint8_t addStorageItem(storage *store, item *thing);

item *removeStorageItem(storage *store, char itemName[]);

void freeStorage(storage *store);
#endif
