#pragma once
/***
*	This struct will be used to store the address of a free memory block.
*	- data - the address of the current free memory block
*	- previous - pointer to previous free memory block
*	- next - pointer to next free memory block
*/
struct Node
{
	char* const addressOfFreeBlock;
	Node *previous;
	Node *next;
};