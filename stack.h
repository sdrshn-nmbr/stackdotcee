// DO NOT CHANGE ANYTHING IN THIS FILE (unless directed to do so in writing by instructor)

#ifndef __STACK_H__
#define __STACK_H__

typedef struct _Node {
	size_t num_empty_slots;
	struct _Node* next;
	int values[1];
} BlockNode;
/* Although the .values field is declared as int[1] (array of one int), we will treat it as if it
 * were a larger array, the size of which will depend on the .num_values_per_node in the Stack object.
 * To avoid a buffer overflow, we will allocate extra sapce.
 * we allocate (malloc) space on the heap for a BlockNode object, we will allocate more space than
 * would be necessary for just a BlockNode, so that we can treat .values as if it were a bigger array.
 */

typedef struct {
	size_t num_values_per_node;  // for convenience
	BlockNode* top;
} Stack;

bool is_empty(Stack const* a_stack);

Stack create_empty_stack(size_t max_block_size_bytes);

void push(Stack* a_stack, int value);

int pop(Stack* a_stack);

int peek_value_from_top_node(Stack const* a_stack);

void empty(Stack* a_stack);

#define MIN_NODE_BLOCK_SIZE_BYTES sizeof(BlockNode)
// MIN_NODE_BLOCK_SIZE_BYTES is the number of bytes to store a node with just one value.
//
// When calling create_empty_stack(..), max_block_size_bytes must be > MIN_NODE_BLOCK_SIZE_BYTES.
//
// Do not use sizeof(TYPE) in functions unless you have articulated why it is necessary and safe.
//
// Here is the rationale for why we use sizeof(TYPE) here:
// - Necessary:  There is no relevant BlockNode expression to refer to in this #define directive.
// - Safe: This symbol refers to the BlockNode type in its name (MIN_NODE_BLOCK_SIZE_BYTES), so anybody
//         using it in code will immediately know that it is referring to the struct BlockNode type.

/* TERMINOLOGY
 *
 * "inner stack" means one of the array-based stacks within a BlockNode object.
 *
 * "block stack" means the stack of BlockNode objects, each of which contains an inner stack.
 * 
 * "stack" (by itself, as a data structure) refers to the conceptual stack, as the caller/user
 * of your code would think about it, including all of the values from each of the inner stacks.
 */

#define __STACK_H_VERSION__ 1  // This is to help us grade fairly in the unlikely event that we
                               // have to change something in this file after the assignment is
							   // released.  If we see this, we will know you were working with
							   // version 1 of this file.
#endif /* end of include guard: __STACK_H__ */
