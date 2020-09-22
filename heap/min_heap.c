#include <stdio.h>
#include <stdlib.h>
#include "heap_obj.h"

/*
	min heap of integer type
*/
int min_compare(void* left, void* right) {
	return left < right ? 0 : 1;
}

/*
	max heap of integer type
*/
int max_compare(void* left, void* right) {
	return left > right ? 0 : 1;
}

int main() {

	heap_obj_t* hop = create_heapobj(min_compare);

	add_element2heapobj(hop, 20);
	add_element2heapobj(hop, 10);
	add_element2heapobj(hop, 15);
	add_element2heapobj(hop, 10);
	add_element2heapobj(hop, 7);
	add_element2heapobj(hop, 6);
	add_element2heapobj(hop, 21);
	add_element2heapobj(hop, 7);
	add_element2heapobj(hop, 3);
	add_element2heapobj(hop, 9);
	del_elementisvalue(hop, 3);
	
	destroy_heapobj(hop);
	return 0;
}