#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Resource functions */

/**
 * Creates a new `Resource` object.
 *
 * Allocates memory for a new `Resource` and initializes its fields.
 * The `name` is dynamically allocated.
 *
 * @param[out] resource      Pointer to the `Resource*` to be allocated and initialized.
 * @param[in]  name          Name of the resource (the string is copied).
 * @param[in]  amount        Initial amount of the resource.
 * @param[in]  max_capacity  Maximum capacity of the resource.
 */
void resource_create(Resource **resource, const char *name, int amount, int max_capacity) {
	*resource = malloc(sizeof(Resource));
	if (!*resource){
		return;
	}
	(*resource)->name = strdup(name);
	if (!(*resource)->name) {
		free(*resource);
		*resource = NULL;
		return;
	}
	(*resource)->amount = amount;
	(*resource)->max_capacity = max_capacity;

	if (sem_init(&(*resource)->semaphore, 0,1) !=0){
		free((*resource)->name);
		free(*resource);
		*resource = NULL;
	}

}
void resource_destroy(Resource *resource) {
	if (!resource) return;
	sem_destroy(&resource->semaphore);
	free(resource->name);
	free(resource);
}

void resource_amount_init(ResourceAmount *resource_amount, Resource *resource, int amount) {
    resource_amount->resource = resource;
    resource_amount->amount = amount;
}

/**
 * Initializes the `ResourceArray`.
 *
 * Allocates memory for the array of `Resource*` pointers and sets initial values.
 *
 * @param[out] array  Pointer to the `ResourceArray` to initialize.
 */
void resource_array_init(ResourceArray *array) {
	array->resources = malloc(sizeof(Resource *) * 1);
	if (!array->resources){
		return;
	}
	array->size = 0;
	array->capacity = 1;	
}

void resource_array_clean(ResourceArray *array) {
	if (!array || !array->resources){
		return;
	}
	for (int i = 0; i < array->size; i++){
		resource_destroy(array->resources[i]);
	}
	free(array->resources);
	array->resources = NULL;
	array->size = 0;
	array->capacity = 0;

}

void resource_array_add(ResourceArray *array, Resource *resource) {
	if (!array || !resource) return;
	if (array->size >= array->capacity){
		Resource **new_array = malloc(sizeof(Resource*) * array->capacity * 2);
		if (!new_array) return;
		for (int i = 0; i < array->size; i++){
			new_array[i] = array->resources[i];
		}
		free(array->resources);
		array->resources = new_array;
		array->capacity *= 2;
	}
	array->resources[array->size++] = resource;
}
