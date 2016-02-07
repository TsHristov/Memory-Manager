#include "MemoryManager.h"
#include <iostream>

/***
*	Start with one big free block:
*		1.Put header information
*		2.Put footer information
*		3.Put its address in the freeBlocks list,so we will allocate from there.
*/
MemoryManager::MemoryManager(size_t& size)
{
	//Allocate big chunk of memory
	memblock = new char[size];

	//Put header
	size_t *header = (size_t*)memblock;
	*header = size;

	//Because the block is free put a Node structure
	Node *block = (Node*)(memblock + sizeof(size_t*));
	(char*)block->data = memblock + sizeof(size_t*);
	block->next = NULL;
	block->previous = NULL;
	

	//Put footer
	size_t *footer = (size_t*)(block->data - sizeof(size_t*)+(size - sizeof(size_t*)));
	*footer = size;

	freeBlocks.insertAtBeginning(block);
}


/***
*	Main function to allocate memory:
*		- start with big chunk of memory allocated on the heap and give it to the user
*		- on each allocation size bytes are given to the user and the others are free for future allocations
*/
char* MemoryManager::Malloc(size_t &size)
{
	char * pointerToBlock = NULL;
	size_t sizeOfFreeBlock;
	ForwardIteratationOverFreeBlocks();

	for (Iterator it = freeBlocks.getIterator(); !it.end(); it.next())
	{
		
		sizeOfFreeBlock = GetHeader(it.getCurrent());
		//If the block is large enough
		if (sizeOfFreeBlock >= size)
		{
			pointerToBlock = it.getCurrent();
			//Remove the node structure from the block so it`s payload can be used.
			freeBlocks.remove((Node*) pointerToBlock);
			break;
		}
	}
	
	

	// If no free block was found.
	if (!pointerToBlock)
	{
		return NULL;
	}

	// Set header of the block
	SetHeader(pointerToBlock, size);
	
	// Set footer of the block
	SetFooter(pointerToBlock, size);

	//Mark the block as allocated
	MarkAsAllocated(pointerToBlock);

	//The remaining bytes of the memblock
	//blockSize -= size;
	size_t freeBlockSize = sizeOfFreeBlock - size;

	//Put new free block at the remaining unused space:
	size_t *hdr = (size_t*)(pointerToBlock + size - sizeof(size_t*));
	*hdr = freeBlockSize;

	Node *block = (Node*)(pointerToBlock + size);
	(char*)block->data = pointerToBlock + size;
	block->next = NULL;
	block->previous = NULL;
	

	size_t *ftr = (size_t*)(block->data - sizeof(size_t*) + (freeBlockSize - sizeof(size_t*)));
	*ftr = freeBlockSize;
	
	freeBlocks.insertAtBeginning(block);

	// Now should mark the next block as free so next time we allocate from there
	return pointerToBlock;
}

void MemoryManager::Free(char *ptr)
{
	if (IsValidAddress(ptr))
	{
		std::cout << "yes" << "\n";
	}
	// Mark the block as free
	MarkAsFree(ptr);

	ForwardIteratationOverFreeBlocks();
	//Coalesce with neighbours
	ptr = CoalesceWithNextBlock(ptr);
	ForwardIteratationOverFreeBlocks();
	
	// Put free block structure into the unused payload space
	Node *freeBlock = (Node*)ptr;
	(char*)freeBlock->data = ptr;
	freeBlock->next = NULL;
	freeBlock->previous = NULL;

	//	Insert the freed block into the freeBlocks list:
	//			- insert at the beggining of the list of free blocks
	
	freeBlocks.insertAtBeginning(freeBlock);
	ForwardIteratationOverFreeBlocks();

}


void MemoryManager::MarkAsAllocated(char * const ptr)
{
	size_t header = (((GetHeader(ptr) ^ (1 << (4 * sizeof(size_t)-1)))));
	SetHeader(ptr, header);

	size_t footer = (((GetFooter(ptr) ^ (1 << (4 * sizeof(size_t)-1)))));
	SetFooter(ptr, footer);
}

size_t MemoryManager::GetHeader(char * const ptr) const
{
	size_t cpy = *(size_t*)(ptr - sizeof(size_t*));
	return cpy;
}

char * const MemoryManager::GetAddressOfHeader(char * const ptr) const
{
	char * const addressOfHeader = ptr - sizeof(size_t*);
	return addressOfHeader;
}


size_t MemoryManager::GetHeaderRealSize(char * const ptr) const
{
	return (GetHeader(ptr) & (~(1 << (4 * sizeof(size_t)-1))));
}


size_t MemoryManager::GetFooter(char * const ptr) const
{
	size_t blockSize = GetHeaderRealSize(ptr);
	return *(size_t*)(ptr - sizeof(size_t*)+(blockSize - sizeof(size_t*)));
}


char * const MemoryManager::GetAddressOfFooter(char * const ptr) const
{
	size_t blockSize = GetHeaderRealSize(ptr);
	char * const p = ptr - sizeof(size_t*)+(blockSize - sizeof(size_t*));
	return p;
}


size_t MemoryManager::GetFooterRealSize(char * const ptr) const
{
	return (GetFooter(ptr) & (~(1 << (4 * sizeof(size_t)-1))));
}


void MemoryManager::SetHeaderAsFree(char * const ptr)
{
	(*(size_t*)(ptr - sizeof(size_t*)) = (*(size_t*)(ptr - sizeof(size_t*))) & (~(1 << (4 * sizeof(size_t)-1))));
}


void MemoryManager::SetFooterAsFree(char* const ptr)
{
	size_t blockSize = GetHeaderRealSize(ptr);
	(*(size_t*)(ptr - sizeof(size_t*)+(blockSize - sizeof(size_t*)))) = (GetFooter(ptr) & (~(1 << (4 * sizeof(size_t)-1))));
}


void MemoryManager::MarkAsFree(char * const ptr)
{
	SetHeaderAsFree(ptr);
	SetFooterAsFree(ptr);
}


void MemoryManager::ForwardIteratationOverFreeBlocks()
{
	int counter = 0;
	for (Iterator it = freeBlocks.getIterator(); !it.end(); it.next())
	{
		counter += 1;
		std::cout << "Free block No " << counter << " : " << GetHeader(it.getCurrent()) << "\n";
	}
}


bool MemoryManager::IsBlockFree(char * const ptr) const
{
	return GetHeader(ptr) == GetHeaderRealSize(ptr);
}


bool MemoryManager::IsNextBlockFree(char * const ptr) const
{
	return IsBlockFree(GetNextBlock(ptr));
}


bool MemoryManager::IsPreviousBlockFree(char * const ptr) const
{
	return IsBlockFree(GetPreviousBlock(ptr));
}


char * const MemoryManager::GetNextBlock(char * const ptr) const
{
	char * const nextBlock = ptr + GetHeaderRealSize(ptr);
	return nextBlock;
}

char * const MemoryManager::GetPreviousBlock(char * const ptr) const
{
	size_t sizeOfPreviousBlock = *(size_t*)(ptr - 2 * sizeof(size_t*));
	sizeOfPreviousBlock = (*(size_t*)(ptr - 2 * sizeof(size_t*)) & (~(1 << (4 * sizeof(size_t)-1))));
	return ptr - sizeOfPreviousBlock;
}

char * const MemoryManager::CoalesceWithNextBlock(char * const ptr)
{
	if (IsNextBlockFree(ptr) && IsValidAddress(GetNextBlock(ptr)))
	{
		//Remove next block from free blocks
		freeBlocks.remove((Node*)GetNextBlock(ptr));
		//Update header
		size_t newHeaderData = GetHeader(ptr) + GetHeader(GetNextBlock(ptr));
		SetHeader(ptr, newHeaderData);
		//Update footer
		SetFooter(ptr, newHeaderData);
		return ptr;
	}
	else
	{
		return ptr;
	}
}


void MemoryManager::SetHeader(char * const ptr, size_t &data)
{
	*(size_t*)(GetAddressOfHeader(ptr)) = data;
}


void MemoryManager::SetFooter(char * const ptr, size_t &data)
{
	char * const p = ptr;
	*(size_t*)(GetAddressOfFooter(p)) = data;
}

bool MemoryManager::IsValidAddress(char * const ptr) const
{ 
	return ptr >= memblock && ptr <= memblock + 1024;
}