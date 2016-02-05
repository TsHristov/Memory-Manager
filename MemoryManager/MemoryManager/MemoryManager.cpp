#include "MemoryManager.h"
#include <iostream>

char* MemoryManager::Malloc(size_t size)
{
	/***
	* pointerToBlock - the block that is going to be returned to the user.
	*/
	char *pointerToBlock = NULL;

	for (Iterator<char*> it = freeBlocks.getIterator(); !it.end(); it.next())
	{
		pointerToBlock = it.getCurrent();
	}

	// If no free block was found.
	if (!pointerToBlock)
	{
		return NULL;
	}

	size_t HEADER = *(size_t*)(pointerToBlock - sizeof(size_t*));
	size_t FOOTER = *(size_t*)(pointerToBlock - sizeof(size_t*) + (HEADER - sizeof(size_t*)));

	std::cout << "pointerToBlock header: " <<
		HEADER  << "\n";
	
	std::cout << "pointerToBlock footer : " <<
		FOOTER << "\n";

	// Header of the block
	size_t *header = (size_t*)(pointerToBlock - sizeof(size_t*));
	*header = size;

	std::cout << "pointerToBlock header after: " << *(size_t*)(pointerToBlock - sizeof(size_t*)) << "\n";

	// Mark block as allocated
	*header = (((*header ^ (1 << (4 * sizeof(size_t)-1)))));

	// Real size of header
	std::cout << "header: |" << (*(size_t*)(pointerToBlock - sizeof(size_t*)) & (~(1 << (4 * sizeof(size_t)-1)))) << "|" << "\n";

	// Footer of the block
	size_t *footer = (size_t*)(pointerToBlock - sizeof(size_t*) + (size - sizeof(size_t*)));
	*footer = size;

	//Mark block as allocated
	*footer = (((*footer ^ (1 << (4 * sizeof(size_t)-1)))));

	// Real size of footer
	std::cout << "footer: |" <<
		(*(size_t*)(pointerToBlock - sizeof(size_t*)+(size - sizeof(size_t*))) & (~(1 << (4 * sizeof(size_t)-1))))
		<< "|" << "\n";

	// Remove this block from freeBlocks
	std::cout << "Block data header: " <<
		(*(size_t*)(block->data - sizeof(size_t*))  & (~(1 << (4 * sizeof(size_t)-1)))) << "\n";

	freeBlocks.remove(block);

	blockSize -= size;

	std::cout << "what do we have here : " <<
		*(size_t*)(pointerToBlock - sizeof(size_t*)+(size - sizeof(size_t*))) << "\n";

	//Put new free block at the remaining unused space:
	size_t *hdr = (size_t*)(pointerToBlock + size - sizeof(size_t*));
	*hdr = blockSize;

	block = (Node<char*>*)(pointerToBlock + size);
	block->data = pointerToBlock + size;
	
	std::cout << "header of first free block: " <<
		*(size_t*)(block->data - sizeof(hdr)) << "\n";

	std::cout << "footer of previous: |" <<
		(*(size_t*)(block->data - sizeof(size_t*) - sizeof(size_t*)) & (~(1 << (4 * sizeof(size_t)-1))))
		<< "|" << "\n";

	size_t *ftr = (size_t*)(block->data - sizeof(size_t*) + (blockSize - sizeof(size_t*)));
	*ftr = blockSize;

	std::cout << "footer of first free block: " <<
		*(size_t*)(block->data - sizeof(size_t*) + (blockSize - sizeof(size_t*))) << "\n";
	
	freeBlocks.insertAtBeginning(block);

	// Now should mark the next block as free so next time we allocate from there
	return pointerToBlock;
}

void MemoryManager::Free(char *ptr)
{
	std::cout << "Value of header in free: " <<
		(*(size_t*)(ptr - sizeof(size_t*))) << "\n";

	// Mark block as free
	//	1.mark the header

	//	1.mark the header
	(*(size_t*)(ptr - sizeof(size_t*)) = (*(size_t*)(ptr - sizeof(size_t*)) & (~(1 << (4 * sizeof(size_t)-1)))));
	
	Node<char*> *freeBlock = (Node<char*>*)(ptr + sizeof(size_t*));
	freeBlocks.insertAtBeginning(freeBlock);
	// 2.mark the footer

	//Coalesce it with neighbours
	
	// Put it into the freeBlocks list

}