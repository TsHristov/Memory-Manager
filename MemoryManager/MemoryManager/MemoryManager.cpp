#include "MemoryManager.h"
#include <iostream>

void* MemoryManager::Malloc(size_t size)
{
	// Puts the header of the block
	memcpy(memblock, &size, sizeof(size_t));

	//Puts the footer of the block, so that we have size bytes available
	memcpy(memblock + size * sizeof(char), &size, sizeof(size_t));

	void *ptr = memblock + sizeof(size_t);

	return ptr;
}