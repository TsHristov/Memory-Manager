#pragma once
#include <iostream>
#include "DoublyLinkedList.h"

class MemoryManager
{
private:
	//	The starting big block of memory,from which the user will allocate memory
	char *memblock;

	//	Stores all free blocks available
	DoublyLinkedList freeBlocks;

public:
	MemoryManager(size_t);
	~MemoryManager()
	{
		delete[] memblock;
	}

public:
	char *Malloc(size_t);
	void Free(char*);

public:
	//	Functions to operate on the header of the blocks
	size_t GetHeader(char * const) const;
	void SetHeader(char * const, size_t);
	char * const GetAddressOfHeader(char * const) const;

	//	Methods to operate on the footer of the blocks
	size_t GetFooter(char * const) const;
	void SetFooter(char * const, size_t);
	char * const GetAddressOfFooter(char * const) const;

	//	These return the real value of header and footer
	//	(without set highest bit)
	size_t GetHeaderRealSize(char * const) const;
	size_t GetFooterRealSize(char * const) const;

	//	These methods remove the set highest bit.
	void SetHeaderAsFree(char * const);
	void SetFooterAsFree(char * const);

	void MarkBlockAsFree(char * const);
	void MarkBlockAsAllocated(char * const);

	//	Utility method to print the free blocks available
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