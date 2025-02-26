#ifndef __MAZE_GAME_MEM_H__
#define __MAZE_GAME_MEM_H__

typedef struct array_item {
	void* object;
	struct array_item* prev;
	struct array_item* next;
} t_array_item, *h_array_item;

typedef struct array {
	h_array_item head;
	h_array_item tail;
	h_array_item cur;
	unsigned int key;
	unsigned int count;
} t_array, *h_array;

h_array array();
int push_array(h_array array, void* object);
void* pop_array(h_array array);
void set_array(h_array array, const int id, void* object);
void* get_array(h_array array, const int id);
void* get_array_first(h_array array);
void* get_array_last(h_array array);
void array_set_internal_position(h_array array, const int id);
void* array_next(h_array array);
void* array_prev(h_array array);
int array_count(h_array array);

#endif