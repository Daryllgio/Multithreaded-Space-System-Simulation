#include "defs.h"
#include <stdlib.h>
#include <stdio.h>

/* Event functions */

/**
 * Initializes an `Event` structure.
 *
 * Sets up an `Event` with the provided system, resource, status, priority, and amount.
 *
 * @param[out] event     Pointer to the `Event` to initialize.
 * @param[in]  system    Pointer to the `System` that generated the event.
 * @param[in]  resource  Pointer to the `Resource` associated with the event.
 * @param[in]  status    Status code representing the event type.
 * @param[in]  priority  Priority level of the event.
 * @param[in]  amount    Amount related to the event (e.g., resource amount).
 */
void event_init(Event *event, System *system, Resource *resource, int status, int priority, int amount) {
    event->system = system;
    event->resource = resource;
    event->status = status;
    event->priority = priority;
    event->amount = amount;
}

/* EventQueue functions */

/**
 * Initializes the `EventQueue`.
 *
 * Sets up the queue for use, initializing any necessary data (e.g., semaphores when threading).
 *
 * @param[out] queue  Pointer to the `EventQueue` to initialize.
 */
void event_queue_init(EventQueue *queue) {
	if (!queue) return;
	queue->head = NULL;
	queue->size = 0;
	if (sem_init(&queue->semaphore, 0, 1) != 0){
		exit(EXIT_FAILURE);
	}
}

/**
 * Cleans up the `EventQueue`.
 *
 * Frees any memory and resources associated with the `EventQueue`.
 * 
 * @param[in,out] queue  Pointer to the `EventQueue` to clean.
 */
void event_queue_clean(EventQueue *queue) {
	if (!queue) return;
	sem_wait(&queue->semaphore);
	
	EventNode *current = queue->head;
	while (current){
		EventNode *temp = current;
		current = current->next;
		free(temp);
	}
	queue->head = NULL;
	queue->size = 0;
	sem_post(&queue->semaphore);
	sem_destroy(&queue->semaphore);
}


void event_queue_push(EventQueue *queue, const Event *event) {
	if (!queue || !event) return;
	
	EventNode *new_node = (EventNode *)malloc(sizeof(EventNode));
	
	if (!new_node) return; 
	
	new_node->event = *event;
	new_node->next = NULL;
	
	sem_wait(&queue->semaphore);
	
	EventNode *currNode = queue->head;
	EventNode *prevNode = NULL;
	
	while (currNode != NULL && currNode->event.priority >= event->priority){
		prevNode = currNode;
		currNode = currNode->next;
	}
	
	if (prevNode == NULL){
		queue->head = new_node;
	} else {
		prevNode->next = new_node;
	}
	new_node->next = currNode;
	queue->size++;
	sem_post(&queue->semaphore);
}

/**
 * Pops an `Event` from the `EventQueue`.
 *
 * Removes the highest priority event from the queue in a thread-safe manner.
 *
 * @param[in,out] queue  Pointer to the `EventQueue`.
 * @param[out]    event  Pointer to the `Event` structure to store the popped event.
 * @return               Non-zero if an event was successfully popped; zero otherwise.
 */
int event_queue_pop(EventQueue *queue, Event *event){
	if (!queue || !event) return 0;
	sem_wait(&queue->semaphore);
	if (!queue->head){
		sem_post(&queue->semaphore);
	 	return 0;
	}
	EventNode *temp = queue->head;
	*event = temp->event;
	queue->head = temp->next;
	free(temp);
	queue->size--;
	
	sem_post(&queue->semaphore);
	return 1;	
}
