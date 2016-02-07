#include "MemoryManager.h"
#include <iostream>

///	Start with one big free block:
///		1.Put header
///		2.Put its address in the freeBlocks list
///		3.Put footer
MemoryManager::MemoryManager(size_t size)
{
	//	Allocate big block of memory
	memblock = new char[size];

	//	Put header
	size_t *header = (size_t*)memblock;
	*header = size;

	//	Because the block is free put
	//	Node structure right after the header
	Node *block = (Node*)(memblock + sizeof(size_t*));
	(char*)block->addressOfFreeBlock = memblock + sizeof(size_t*);
	block->next = NULL;
	block->previous = NULL;
	

	//	Put footer
	size_t *footer = (size_t*)(block->addressOfFreeBlock - sizeof(size_t*)+(size - sizeof(size_t*)));
	*footer = size;

	//	Insert the inital first big free block into the list of free blocks
	freeBlocks.insertAtBeginning(block);
}


///	Main function to allocate memory:
///
char* MemoryManager::Malloc(size_t size)
{
	char * pointerToBlock = NULL;
	size_t sizeOfFreeBlock;
	ForwardIteratationOverFreeBlocks();

	for (Iterator it = freeBlocks.getIterator(); !it.end(); it.moveToNext())
	{
		
		sizeOfFreeBlock = GetHeader(it.getAddressOfFreeBlock());
		//	If the block is large enough
		if (sizeOfFreeBlock >= size)
		{
			pointerToBlock = it.getAddressOfFreeBlock();
			//	Remove the Node  from the block`s payload area so it can be used
			freeBlocks.remove((Node*) pointerToBlock);
			break;
		}
	}

	//	If no free block was found
	if (!pointerToBlock)
	{
		return NULL;
	}

	//	Set header of the block
	SetHeader(pointerToBlock, size);
	
	//	Set footer of the block
	SetFooter(pointerToBlock, size);

	//	Mark the block as allocated (set it`s highest bit)
	MarkBlockAsAllocated(pointerToBlock);

	//	The remaining size of the returned free block
	size_t freeBlockSize = sizeOfFreeBlock - size;

	//	Put new free block at the remaining unused payload area
	//		1.Put header
	//		2.Put its address after the header
	//		3.Put footer
	//		4.Insert free block into free blocks list

	//	1.Put header
	size_t *header = (size_t*)(pointerToBlock + size - sizeof(size_t*));
	*header = freeBlockSize;

	//	2.Put its address after the header
	Node *freeBlock = (Node*)(pointerToBlock + size);
	(char*)freeBlock->addressOfFreeBlock = pointerToBlock + size;
	freeBlock->next = NULL;
	freeBlock->previous = NULL;
	
	//	3.Put footer
	size_t *footer = (size_t*)(freeBlock->addressOfFreeBlock - sizeof(size_t*) + (freeBlockSize - sizeof(size_t*)));
	*footer = freeBlockSize;

	//	4.Insert free block into free blocks list
	freeBlocks.insertAtBeginning(freeBlock);

	return pointerToBlock;
}


void MemoryManager::Free(char *ptr)
{

	//	Mark the block as free
	MarkBlockAsFree(ptr);

	//	Coalesce with neighbours
	ptr = CoalesceWithNextBlock(ptr);
	
	// Put free block structure into the unused payload space
	Node *freeBlock = (Node*)ptr;
	(char*)freeBlock->addressOfFreeBlock = ptr;
	freeBlock->next = NULL;
	freeBlock->previous = NULL;

	//	LIFO policy:
	//		- always insert most recently freed block at the beggining of the list
	freeBlocks.insertAtBeginning(freeBlock);
}


void MemoryManager::MarkBlockAsAllocated(char * const ptr)
{
	size_t header = (((GetHeader(ptr) ^ (1 << (4 * sizeof(size_t)-1)))));
	SetHeader(ptr, header);

	size_t footer = (((GetFooter(ptr) ^ (1 << (4 * sizeof(size_t)-1)))));
	SetFooter(ptr, footer);
}


size_t MemoryManager::GetHeader(char * const ptr) const
{
	return *(size_t*)(ptr - sizeof(size_t*));
}


char * const MemoryManager::GetAddressOfHeader(char * const ptr) const
{
	return ptr - sizeof(size_t*);
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
	return ptr - sizeof(size_t*)+(blockSize - sizeof(size_t*));
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


void MemoryManager::MarkBlockAsFree(char * const ptr)
{
	SetHeaderAsFree(ptr);
	SetFooterAsFree(ptr);
}


void MemoryManager::ForwardIteratationOverFreeBlocks()
{
	int counter = 0;
	for (Iterator it = freeBlocks.getIterator(); !it.end(); it.moveToNext())
	{
		counter += 1;
		std::cout << "Free block No " << counter << " : " << GetHeader(it.getAddressOfFreeBlock()) << "\n";
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
	return ptr + GetHeaderRealSize(ptr);
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


void MemoryManager::SetHeader(char * const ptr, size_t data)
{
	*(size_t*)(GetAddressOfHeader(ptr)) = data;
}


void MemoryManager::SetFooter(char * const ptr, size_t data)
{
	*(size_t*)(GetAddressOfFooter(ptr)) = data;
}


bool MemoryManager::IsValidAddress(char * const ptr) const
{ 
	return ptr >= memblock && ptr <= memblock + 1024;
}