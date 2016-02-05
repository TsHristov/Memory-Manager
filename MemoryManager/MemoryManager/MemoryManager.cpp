#include "MemoryManager.h"
#include <iostream>

char* MemoryManager::Malloc(size_t size)
{
	/***
	* pointerToBlock - the block that is going to be returned to the user.
	*/
	char *pointerToBlock = NULL;

	ForwardIteratationOverFreeBlocks();

	for (Iterator<char*> it = freeBlocks.getIterator(); !it.end(); it.next())
	{
		
		size_t sizeOfFreeBlock = GetHeader(it.getCurrent());
		//If the block is large enough
		if (sizeOfFreeBlock >= size)
		{
			pointerToBlock = it.getCurrent();
			break;
		}
	}

	// If no free block was found.
	if (!pointerToBlock)
	{
		return NULL;
	}

	// Header of the block
	size_t *header = (size_t*)(pointerToBlock - sizeof(size_t*));
	*header = size;

	// Mark block as allocated
	*header = (((*header ^ (1 << (4 * sizeof(size_t)-1)))));


	// Footer of the block
	size_t *footer = (size_t*)(pointerToBlock - sizeof(size_t*) + (size - sizeof(size_t*)));
	*footer = size;

	//Mark block as allocated
	*footer = (((*footer ^ (1 << (4 * sizeof(size_t)-1)))));


	// Remove this block from freeBlocks
	freeBlocks.remove((Node<char*>*) pointerToBlock);

	blockSize -= size;

	//Put new free block at the remaining unused space:
	size_t *hdr = (size_t*)(pointerToBlock + size - sizeof(size_t*));
	*hdr = blockSize;

	Node<char*> * block = (Node<char*>*)(pointerToBlock + size);
	block->data = pointerToBlock + size;
	

	size_t *ftr = (size_t*)(block->data - sizeof(size_t*) + (blockSize - sizeof(size_t*)));
	*ftr = blockSize;
	
	freeBlocks.insertAtBeginning(block);

	// Now should mark the next block as free so next time we allocate from there
	return pointerToBlock;
}

void MemoryManager::Free(char *ptr)
{
	MarkAsFree(ptr);
	
	Node<char*> *freeBlock = (Node<char*>*)ptr;
	freeBlock->data = ptr;

	/***
	*	Insert the freed block into the freeBlocks list:s
	*		- LIFO policy:
	*			- insert at the beggining of the list of free blocks
	*/

	freeBlocks.insertAtBeginning(freeBlock);

}


size_t MemoryManager::GetHeader(char *ptr) const
{
	return *(size_t*)(ptr - sizeof(size_t*));
}


size_t MemoryManager::GetHeaderRealSize(char *ptr) const
{
	return (GetHeader(ptr) & (~(1 << (4 * sizeof(size_t)-1))));
}


size_t MemoryManager::GetFooter(char *ptr) const
{
	size_t blockSize = GetHeaderRealSize(ptr);
	return *(size_t*)(ptr - sizeof(size_t*)+(blockSize - sizeof(size_t*)));
}


size_t MemoryManager::GetFooterRealSize(char *ptr) const
{
	return (GetHeader(ptr) & (~(1 << (4 * sizeof(size_t)-1))));
}


void MemoryManager::SetHeaderAsFree(char *ptr)
{
	(*(size_t*)(ptr - sizeof(size_t*)) = (*(size_t*)(ptr - sizeof(size_t*))) & (~(1 << (4 * sizeof(size_t)-1))));
}


void MemoryManager::SetFooterAsFree(char* ptr)
{
	(*(size_t*)(ptr - sizeof(size_t*)+(blockSize - sizeof(size_t*)))) = 
		(*(size_t*)(ptr - sizeof(size_t*)+(blockSize - sizeof(size_t*)))) & (~(1 << (4 * sizeof(size_t)-1)));
}


void MemoryManager::MarkAsFree(char *ptr)
{
	SetHeaderAsFree(ptr);
	SetFooterAsFree(ptr);
}


void MemoryManager::ForwardIteratationOverFreeBlocks()
{
	int counter = 0;
	for (Iterator<char*> it = freeBlocks.getIterator(); !it.end(); it.next())
	{
		counter += 1;
		std::cout << "Free block No " << counter << " : " << GetHeader(it.getCurrent()) << "\n";
	}
}