#include "MemoryManager.h"
#include <iostream>

char* MemoryManager::Malloc(size_t size)
{
	blockSize -= size;
	/***
	* pointerToBlock - the block that is going to be returned to the user.
	*/
	char *pointerToBlock = NULL;

	for (Iterator<char*> it = freeBlocks.getIterator(); !it.end(); it.next())
	{
		size_t header = *(size_t*)(it.getCurrent() - sizeof(size_t*));

		if (header == (header & (~(1 << 31))))
		{
			std::cout << "The block is not allocated so we can allocate it now . . ." << "\n";
			
			// The address that is going to be returned to the user:
			pointerToBlock = it.getCurrent();

			// Now pointerToBlock points to the memory right after the header
		}
		std::cout << "iterator header: " << header << '\n';
	}

	// If no free block was found.
	if (!pointerToBlock)
	{
		return NULL;
	}

	std::cout << "ptrToBlock  header: " << *(size_t*)(pointerToBlock - sizeof(size_t*)) << "\n";

	//Reverse the pointer to where the header lays
	pointerToBlock = pointerToBlock - sizeof(size_t*);

	// Header of the block
	size_t *header = (size_t*)pointerToBlock;
	*header = size;

	// Mark block as allocated
	*header = (((*header ^ (1 << (4 * sizeof(size_t)-1)))));

	std::cout << "MMMMM : " << *(size_t*)memblock << "\n";

	
	
	// Real size of header
	std::cout << "header: |" << (*(size_t*)memblock & (~(1 << (4 * sizeof(size_t)-1)))) << "|" << "\n";

	
	// Footer of the block
	size_t *footer = (size_t*)(pointerToBlock + sizeof(size_t*) + (size - sizeof(size_t*)) * sizeof(char));
	*footer = size;

	//Mark block as allocated
	*footer = (((*footer ^ (1 << (4 * sizeof(size_t)-1)))));

	// Real size of footer
	std::cout << "footer: |" <<
		(*(size_t*)(pointerToBlock + sizeof(size_t*)+(size - sizeof(size_t*)) * sizeof(char)) & (~(1 << (4 * sizeof(size_t)-1))))
		<< "|" << "\n";

	// Remove tis block from freeBlocks
	freeBlocks.remove(block);

	//Put new free block at the remaining unused space:
	size_t *hdr = (size_t*)(pointerToBlock + size - sizeof(size_t*));
	*hdr = blockSize;

	block = (Node<char*>*)(pointerToBlock + size);
	block->data = pointerToBlock + size;
	
	std::cout << "header of first free block: " <<
		*(size_t*)(block->data - sizeof(hdr)) << "\n";

	size_t *ftr = (size_t*)(block->data + (blockSize - sizeof(size_t*)));
	*ftr = blockSize;

	std::cout << "footer of first free block: " <<
		*(size_t*)(memblock +1024 - sizeof(size_t*)) << "\n";
	
	freeBlocks.insertAtBeginning(block);

	// Now should mark the next block as free so next time we allocate from there
	return pointerToBlock;
}

void MemoryManager::Free(char *ptr)
{
	*ptr = *ptr & -2;
}