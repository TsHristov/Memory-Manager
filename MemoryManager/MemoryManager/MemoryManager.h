#pragma once
#include <iostream>
#include "DoublyLinkedList.h"

class MemoryManager
{
private:
	char *memblock;
	//Doubly Linked list to store the pointers to the free blocks
	DoublyLinkedList<char*> freeBlocks;
	size_t blockSize;

public:
	/***
	*	Start with one big free block:
	*		1.Put header information
	*		2.Put footer information
	*		3.Put its address in the freeBlocks list,so we will allocate from there.
	*/
	MemoryManager(size_t size)
	{
		blockSize = size;
		
		//Allocate big chunk of memory
		memblock = new char[blockSize];

		//Put header
		size_t *header = (size_t*)memblock;
		*header = blockSize;

		//Because the block is free put a Node structure
		Node<char*> *block = (Node<char*>*)(memblock + sizeof(size_t*));
		block->data = memblock + sizeof(size_t*);


		//Put footer
		size_t *footer = (size_t*)(block->data - sizeof(size_t*) +(blockSize - sizeof(size_t*)));
		*footer = blockSize;
		
		freeBlocks.insertAtBeginning(block);

		//freeBlocks.printWithIterator();
	}
	~MemoryManager()
	{
		if (memblock)
		delete[] memblock;
	}

public:
	char *Malloc(size_t);
	void Free(char*);

public:
	size_t GetHeader(char*) const;
	size_t GetFooter(char*) const;

	size_t GetHeaderRealSize(char*) const;
	size_t GetFooterRealSize(char*) const;

	void SetHeaderAsFree(char*);
	void SetFooterAsFree(char*);

	void MarkAsFree(char*);

	void ForwardIteratationOverFreeBlocks();
	//bool IsAllocated(char*) const;

	//void MarkAsAllocated(char*);
	//
	
	//void SetHeader();
	//void SetFooter();
};