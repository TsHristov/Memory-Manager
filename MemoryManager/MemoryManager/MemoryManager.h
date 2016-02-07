#pragma once
#include <iostream>
#include "DoublyLinkedList.h"

class MemoryManager
{
private:
	//The starting big block of memory
	char *memblock;

	//Doubly Linked list to store the pointers to the free blocks
	DoublyLinkedList freeBlocks;

public:
	MemoryManager(size_t&);
	~MemoryManager()
	{
		//The only allocated memory in the project.
		if (memblock)
		{
			delete[] memblock;
		}
	}

public:
	char *Malloc(size_t&);
	void Free(char*);

public:
	//Get value of header
	size_t GetHeader(char * const) const;
	void SetHeader(char * const, size_t&);
	//Get address of header
	char * const GetAddressOfHeader(char * const) const;

	//Get value of footer
	size_t GetFooter(char * const) const;
	void SetFooter(char * const, size_t&);
	//Get address of footer
	char * const GetAddressOfFooter(char * const) const;

	size_t GetHeaderRealSize(char * const) const;
	size_t GetFooterRealSize(char * const) const;

	void SetHeaderAsFree(char * const);
	void SetFooterAsFree(char * const);

	void MarkAsFree(char * const);
	void MarkAsAllocated(char * const);

	void ForwardIteratationOverFreeBlocks();

	bool IsBlockFree(char * const) const;
	bool IsNextBlockFree(char * const) const;
	bool IsPreviousBlockFree(char * const) const;
	bool IsValidAddress(char * const) const;

	char * const GetNextBlock(char * const) const;
	char * const GetPreviousBlock(char * const) const;

	char * const CoalesceWithNeighbours(char * const);
	char * const CoalesceWithNextBlock(char * const);
	char * const CoalesceWithPreviousBlock(char * const);
};