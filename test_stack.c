#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "stack.h"
#include "stack_utils.h" // Do not include in stack.c

#define report_test_passed() (printf("%sPASSED: %s%s\n\n", "\x1b[32m", __func__, "\x1b[0m"))

void test_minimum_block_size_empty_stack()
{
	Stack stack = create_empty_stack(MIN_NODE_BLOCK_SIZE_BYTES);
	assert(stack.top == NULL);
	assert(stack.num_values_per_node == 1);
	assert(is_empty(&stack));
	report_test_passed();
}

void test_minimum_block_size_1_value()
{
	Stack stack = create_empty_stack(MIN_NODE_BLOCK_SIZE_BYTES);
	assert(stack.top == NULL);
	assert(stack.num_values_per_node == 1);
	assert(is_empty(&stack));

	push(&stack, 5);
	assert(!is_empty(&stack));
	assert(count_nodes(&stack) == 1);
	assert(count_values(&stack) == 1);

	int popped_value = pop(&stack);
	assert(popped_value == 5);
	assert(is_empty(&stack));

	report_test_passed();
}

void test_minimum_block_size_1_value_peek()
{
	Stack stack = create_empty_stack(MIN_NODE_BLOCK_SIZE_BYTES);
	assert(is_empty(&stack));

	push(&stack, 5);
	assert(!is_empty(&stack));
	print_stack(&stack); // TOP => 5

	int top_value = peek_value_from_top_node(&stack);
	// printf("\n%d\n", top_value);
	assert(top_value == 5);

	int popped_value = pop(&stack);
	assert(popped_value == 5);
	assert(is_empty(&stack));

	report_test_passed();
}

void test_32_bytes_per_block_node_empty_stack()
{
	Stack stack = create_empty_stack(32);
	assert(is_empty(&stack));
	printf("\n%ld\n", stack.num_values_per_node);
	assert(stack.num_values_per_node == 3); // value was determined by instructor

	report_test_passed();
}

void test_32_bytes_per_block_node_1_value()
{
	Stack stack = create_empty_stack(32);
	assert(stack.top == NULL);
	assert(stack.num_values_per_node == 3); // determined by instructor
	assert(is_empty(&stack));

	push(&stack, 5);
	assert(!is_empty(&stack));
	print_stack(&stack);

	int popped_value = pop(&stack);
	assert(popped_value == 5);
	assert(is_empty(&stack));

	report_test_passed();
}

void test_32_bytes_per_block_node_3_values()
{
	Stack stack = create_empty_stack(32);
	assert(stack.top == NULL);
	assert(stack.num_values_per_node == 3); // determined by instructor
	assert(is_empty(&stack));
	print_stack(&stack); // (empty stack)

	push(&stack, 5);
	assert(!is_empty(&stack));
	assert(count_values(&stack) == 1);
	assert(count_nodes(&stack) == 1);
	print_stack(&stack); // TOP => [5]

	push(&stack, 6);
	assert(!is_empty(&stack));
	assert(count_values(&stack) == 2);
	// printf("\n%ld\n", count_nodes(&stack));
	assert(count_nodes(&stack) == 1);
	print_stack(&stack); // TOP => [6] => [5]

	push(&stack, 7);
	assert(!is_empty(&stack));
	assert(count_values(&stack) == 3);
	assert(count_nodes(&stack) == 1);
	print_stack(&stack); // TOP => [7] => [6] => [5]

	int popped_value = pop(&stack);
	assert(popped_value == 7);
	assert(!is_empty(&stack));
	assert(count_values(&stack) == 2);
	assert(count_nodes(&stack) == 1);
	print_stack(&stack); // TOP => [6] => [5]

	popped_value = pop(&stack);
	assert(popped_value == 6);
	assert(!is_empty(&stack));
	assert(count_values(&stack) == 1);
	assert(count_nodes(&stack) == 1);
	print_stack(&stack); // TOP => [5]

	popped_value = pop(&stack);
	assert(popped_value == 5);
	assert(is_empty(&stack));
	assert(count_values(&stack) == 0);
	assert(count_nodes(&stack) == 0);
	print_stack(&stack); // (empty stack)

	report_test_passed();
}

void test_32_bytes_per_block_node_8_values()
{
	Stack stack = create_empty_stack(32);
	for (int i = 0; i < 8; i++)
	{
		push(&stack, i + 5);
		assert(peek_value_from_top_node(&stack) == i + 5);
	}
	assert(peek_value_from_top_node(&stack) == 8 - 1 + 5);
	assert(count_values(&stack) == 8);
	assert(count_nodes(&stack) == 3);
	print_stack(&stack);

	for (int i = 0; i < 8; i++)
	{
		pop(&stack);
	}
	assert(is_empty(&stack));

	report_test_passed();
}

void test_32_bytes_per_block_node_12_values()
{
	Stack stack = create_empty_stack(32);
	for (int i = 0; i < 12; i++)
	{
		push(&stack, i + 5);
		assert(peek_value_from_top_node(&stack) == i + 5);
	}
	assert(peek_value_from_top_node(&stack) == 12 - 1 + 5);
	assert(count_values(&stack) == 12);
	assert(count_nodes(&stack) == 4);
	print_stack(&stack);

	for (int i = 0; i < 12; i++)
	{
		pop(&stack);
	}
	assert(is_empty(&stack));

	report_test_passed();
}

void test_empty_function()
{
	Stack stack = create_empty_stack(32);

	for (int i = 0; i < 5; i++)
	{
		push(&stack, i);
	}
	assert(!is_empty(&stack));
	print_stack(&stack);
	empty(&stack);
	assert(is_empty(&stack));
	report_test_passed();
}

// TODO:  Add tests for other values of max_block_size_bytes (parameter to create_empty_stack(..))

int main(int argc, char *argv[])
{
	test_minimum_block_size_empty_stack();
	test_minimum_block_size_1_value();
	test_minimum_block_size_1_value_peek();
	test_32_bytes_per_block_node_empty_stack();
	test_32_bytes_per_block_node_1_value();
	test_32_bytes_per_block_node_3_values();
	test_32_bytes_per_block_node_8_values();
	test_32_bytes_per_block_node_12_values();
	test_empty_function();

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
