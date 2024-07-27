#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "stack.h"

bool is_empty(Stack const *a_stack)
{
	return a_stack->top == NULL;
}

Stack create_empty_stack(size_t max_block_size_bytes)
{
	BlockNode dummy;

	size_t block_node_size = sizeof(dummy);
	size_t remaining_size = max_block_size_bytes - block_node_size + sizeof(dummy.values[0]);
	size_t num_bytes_per_val = sizeof(dummy.values[0]);
	size_t max_values_per_node = remaining_size / num_bytes_per_val;

	return (Stack){.num_values_per_node = max_values_per_node, .top = NULL};
}

void push(Stack *a_stack, int value)
{
	if (a_stack != NULL)
	{
		// If the stack is empty or the current block node is full, create a new block node
		if (is_empty(a_stack) || a_stack->top->num_empty_slots == 0)
		{
			BlockNode *new_node = malloc(sizeof(BlockNode) + (a_stack->num_values_per_node - 1) * sizeof(new_node->values[0]));

			new_node->num_empty_slots = a_stack->num_values_per_node - 1;
			new_node->next = a_stack->top;
			new_node->values[new_node->num_empty_slots] = value; // Not using compound literal as C does not allow using a non-constant array index such as 'values[new_node->num_empty_slots] = value' within a compound literal

			a_stack->top = new_node;
		}
		else
		{
			// Else, push onto the current block node
			a_stack->top->num_empty_slots--;
			a_stack->top->values[a_stack->top->num_empty_slots] = value;
		}
	}

	assert(!is_empty(a_stack)); // Post-condition: stack must not be empty when function exits
}

int pop(Stack *a_stack)
{
	assert(!is_empty(a_stack)); // Pre-condition: stack must not be empty when function begins
	int value = a_stack->top->values[a_stack->top->num_empty_slots];
	if (a_stack->top->num_empty_slots == a_stack->num_values_per_node - 1)
	{
		BlockNode *old_top = a_stack->top; // temp pointer to block node with empty values array
		a_stack->top = a_stack->top->next; // assign a_stack->top to next block node
		free(old_top);					   // free block node with empty values array using temp pointer
	}
	else
	{
		a_stack->top->num_empty_slots++; // simply increment # empty slots
	}

	return value;
}

void empty(Stack *a_stack)
{
	if (a_stack == NULL)
	{
		return;
	}
	while (a_stack->top != NULL)
	{
		BlockNode *current = a_stack->top;

		a_stack->top = current->next;

		free(current);
	}
	a_stack->top = NULL;

	assert(is_empty(a_stack)); // Post-condition: stack must be empty when function exits
}

int peek_value_from_top_node(Stack const *a_stack)
{
	assert(!is_empty(a_stack)); // Pre-condition: stack must not be empty
	return a_stack->top->values[a_stack->top->num_empty_slots];
}

#define STACK_C_VERSION_2 // Do not delete or modify this line.  It helps us track any updates.
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
