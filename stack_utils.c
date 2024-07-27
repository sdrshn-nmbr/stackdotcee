#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "stack.h"

/*
 * These functions are provided to help you with TESTING your code.
 */

size_t count_values(Stack* a_stack) {
	size_t num_values = 0;
	for(BlockNode* curr = a_stack -> top; curr != NULL; curr = curr -> next) {
		num_values += a_stack -> num_values_per_node - curr -> num_empty_slots;
	}
	return num_values;
}

size_t count_nodes(Stack* a_stack) {
	size_t num_nodes = 0;
	for(BlockNode* curr = a_stack -> top; curr != NULL; curr = curr -> next) {
		num_nodes += 1;
	}
	return num_nodes;
}

void print_stack(Stack* a_stack) {
	if(is_empty(a_stack)) {
		printf("(empty stack)\n");
	}
	else {
		printf("TOP => ");
		bool is_first = true;
		for(BlockNode* curr = a_stack -> top; curr != NULL; curr = curr -> next) {
			size_t num_values_this_node = a_stack -> num_values_per_node - curr -> num_empty_slots;
			for(size_t i = 0; i < num_values_this_node; i++) {
				int this_value_idx = num_values_this_node - i - 1;  // goes backwards
				int value = curr -> values[this_value_idx];
				if(is_first) {
					is_first = false;
				}
				else {
					printf(" => ");
				}
				printf("[%d]", value);
			}
		}
		printf("\n");
	}
}
