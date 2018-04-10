#include <unistd.h>
#include "storage.h"

/**	Creates a storage with the given maxItems.
 */
storage *createStorage(uint16_t maxItems) {
	
	//Malloc space for the item and return NULL if that fails.
	storage *newStorage = malloc(sizeof(storage));
	if (newStorage == NULL) return NULL;
	
	newStorage->numItems = 0;
	if (maxItems > 99) newStorage->maxItems = 99;
	else newStorage->maxItems = maxItems;
	
	return newStorage;
	
};

/** Checks if the storage has the given item in their bag.
 * 	returns the index of the item in the storage's bag + 1, returns a 0 if
 *  the storage does not have the item.
 */
uint16_t doesStorageHaveItem(storage *store, char itemName[]) {
	for (uint16_t index = 0; index < store->numItems; index++) {
		if (strcmp(itemName, (store->bag[index])->name) == 0) {
			return index + 1;
		}
	}
	return 0;
};

/** Iterates through the storage's bag and returns a pointer
 * 	to the item with the given name.
 */
item *getStorageItemPointer(storage *store, char itemName[]) {
	for (uint8_t index = 0; index < store->numItems; index++) {
		if (strcmp(itemName, (store->bag[index])->name) == 0) {
			return store->bag[index];
		}
	}
	return NULL;
};

/** Adds an item to the storage's bag.
 * 	returns 1 if successful, returns 0 else.
 * 	Stacks the items if the storage already has a copy of the item.
 */	
uint8_t addStorageItem(storage *store, item *thing) {
	if (store->numItems <= store->maxItems && thing != NULL) {
		uint16_t doesHave = doesStorageHaveItem(store, thing);
		if (doesHave) {
			return stackItem(store->bag[doesHave - 1], thing);
		}
		else {
			store->bag[store->numItems] = thing;
			store->numItems++;
		}
		return 1;
	}
	return 0;
};

/** Removes a given item from the storage's bag by name.
 * 	returns the item if removed successfully, NULL if not.
 */
item *removeStorageItem(storage *store, char itemName[]) {
	
	item *toReturn = NULL;
	uint16_t itemAt = doesStorageHaveItem(store, itemName);
	if (itemAt == 0) {
		return 0;
	}
	toReturn = store->bag[itemAt - 1];
	store->bag[itemAt - 1] = store->bag[store->numItems - 1];
	store->numItems--;
	return toReturn;
};

/**	Frees all items in the storage's bag then free the storage struct.
 */
void freeStorage(storage *store) {
	for (uint8_t index = 0; index < store->numItems; index++) {
		free(store->bag[index]);
	}
	free(store);
};
