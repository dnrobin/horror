#include "shared.h"
#include "mem.h"

#include <stdlib.h>

h_array array() {
	
	h_array array;
	
	// allocate new array struct
	if( (array = (h_array)malloc(sizeof(t_array))) == NULL ) {
		printf("Error while allocating new array!\n");
		return NULL;
	}
	
	array->head = NULL;
	array->tail = NULL;
	array->cur = NULL;
	
	array->count = 0;
	array->key = -1;
	
	return array;
}

int push_array(h_array array, void* object) {
	
	h_array_item item;
	
	if( (item = (h_array_item)malloc(sizeof(t_array_item))) == NULL ) {
		printf("Error while trying to allocate array item!\n");
		return -1;
	}
	
	// set array item pointer to object
	item->object = object;
	
	// add object to end of array
	if ( array->count == 0 ) {
		
		// set item pointers
		item->next = NULL;
		item->prev = NULL;
		
		// link item to array
		array->head = item;
		array->tail = item;
		array->cur = item;
		
	} else {
		
		// set item pointers
		item->next = NULL;
		item->prev = array->tail;
		
		// link item to array
		array->tail->next = item;
		array->tail = item;
		
		// set cursor to tail
		array->cur = array->tail;
		
	}
	
	// increment array item count
	array->count ++;
	
	// set the internal key to the last item id
	array->key = array->count - 1;
	
	return array->key;
}

void* pop_array(h_array array) {
	
	// prevent accessing empty array!
	if ( array->count == 0 ) {
		printf("Error: cannot pop array of size 0\n");
		return NULL;
	}
	
	h_array_item item = array->tail;
	
	// get the object ptr
	void* object = item->object;
	
	if ( array->count == 1 ) {
		
		// unlink only array item
		array->tail = NULL;
		array->head = NULL;
		array->cur = NULL;
		
	} else {
		
		// unlink last item
		array->tail = array->tail->prev;
		array->cur = array->tail;
		
	}
	
	// distroy item
	free( item );
	
	// decrement array item count
	array->count --;
	
	// set curent key
	array->key = array->count - 1;
	
	return object;
}

void set_array(h_array array, const int id, void* object) {
	
	// prevent accessing empty array!
	if ( array->count == 0 ) {
		printf("Error: (set) cannot set array of size 0\n");
		return;
	}
	
	int i;
	
	// verify valid id
	if ( id >= array->count || id < 0 ) {
		printf("Error: array index out of range\n");
		return;
	}
	
	// if cur item return cur
	if ( id == array->key ) {
		array->cur->object = object;
		return;
	}
	
	// set cursor to start
	array->cur = array->head;
	
	// move to item
	for ( i = 0; i < id; i ++ ) {
		array->cur = array->cur->next;
	}
	
	// set curent key
	array->key = id;
	
	// set new value
	array->cur->object = object;
}

void* get_array(h_array array, const int id) {
	
	// prevent accessing empty array!
	if ( array->count == 0 ) {
		printf("Error: (get) cannot get array of size 0\n");
		return NULL;
	}
	
	int i;
	
	// verify valid id
	if ( id >= array->count || id < 0 ) {
		printf("Error: array index out of range\n");
		return NULL;
	}
	
	// if cur item return cur
	if ( id == array->key )
		return array->cur->object;
	
	// set cursor to start
	array->cur = array->head;
	
	// move to item
	for ( i = 0; i < id; i ++ ) {
		array->cur = array->cur->next;
	}
	
	// set curent key
	array->key = id;
	
	return array->cur->object;
}

void* get_array_first(h_array array) {
	// prevent accessing empty array!
	if ( array->count == 0 ) {
		printf("Error: (first) cannot get array of size 0\n");
		return NULL;
	}
	
	return get_array(array, 0);
}

void* get_array_last(h_array array) {
	// prevent accessing empty array!
	if ( array->count == 0 ) {
		printf("Error: (last) cannot get array of size 0\n");
		return NULL;
	}
	
	return get_array(array, array->count - 1);
}

void array_set_internal_position(h_array array, const int id) {
	// prevent accessing empty array!
	if ( array->count == 0 ) {
		printf("Error: (set_internal_position) cannot set array of size 0\n");
		return;
	}
	
	if ( id >= array->count || id < 0 ) {
		printf("Error: cannot set array position for index out of range!\n");
		return;
	}
	
	int i;
	
	// start cursor at head
	array->cur = array->head;
	
	for ( i = 0; i < id; i ++ ) {
		array->cur = array->cur->next;
	}
	
	// set key
	array->key = id;
}
void* array_next(h_array array) {
	// prevent accessing empty array!
	if ( array->count == 0 ) {
		printf("Error: (next) cannot get array of size 0\n");
		return NULL;
	}
	
	void* object = array->cur->object;
	
	array->key++;
	
	if ( array->key >= array->count ) {
		
		// cur will stay at tail
		array->key = array->count - 1;
		
	} else {
		
		array->cur = array->cur->next;
		
	}
	
	return object;
}
void* array_prev(h_array array) {
	// prevent accessing empty array!
	if ( array->count == 0 ) {
		printf("Error: (prev) cannot get array of size 0\n");
		return NULL;
	}
	
	void* object = array->cur->object;
	
	array->key--;
	
	if ( array->key < 0 ) {
		array->key = 0;
	} else {
		array->cur = array->cur->prev;
	}
	
	return object;
}

int array_count(h_array array) {
	return array->count;
}