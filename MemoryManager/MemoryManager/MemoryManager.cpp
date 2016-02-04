#include "MemoryManager.h"
#include <iostream>

char* MemoryManager::Malloc(size_t size)
{
	//TODO
	// 2.allocate in the next free space accordingly

	// Header of the block
	size_t *header = (size_t*)memblock;
	*header = size;

	// Mark the block as allocated
	*header = (((*header ^ (1 << (4 * sizeof(size_t)-1)))));
	
	// Real size of header
	std::cout << "header: |" << (*(size_t*)memblock & (~(1 << (4 * sizeof(size_t)-1)))) << "|" << "\n";

	// Pointer to the block
	char *ptrToBlock = memblock + sizeof(size_t*);
	
	std::cout << "hdr: " << *(size_t*)(ptrToBlock - sizeof(size_t*)) << "\n";
	
	// Footer of the block
	size_t *footer = (size_t*)(memblock + sizeof(size_t*) + (size - sizeof(size_t*)) * sizeof(char));
	*footer = size;

	*footer = (((*footer ^ (1 << (4 * sizeof(size_t)-1)))));

	// Real size of footer
	std::cout << "footer: |" <<
		(*(size_t*)(memblock + sizeof(size_t*)+(size - sizeof(size_t*)) * sizeof(char)) & (~(1 << (4 * sizeof(size_t)-1))))
		<< "|" << "\n";

	return ptrToBlock;
}

void MemoryManager::Free(char *ptr)
{
	*ptr = *ptr & -2;
}