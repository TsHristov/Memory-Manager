#pragma once
#include <iostream>
#include "DoublyLinkedList.h"

class MemoryManager
{
private:
	char *memblock;
	DoublyLinkedList<char*> freeBlocks;
	Node<char*> *block;
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
		block = (Node<char*>*)(memblock + sizeof(size_t*));
		block->data = memblock + sizeof(size_t*);

		std::cout << "header of first free block: " <<
			*(size_t*)(block->data - sizeof(header)) << "\n";

		//Put footer
		size_t *footer = (size_t*)(block->data +(blockSize - sizeof(size_t*)));
		*footer = blockSize;

		std::cout << "footer of first free block: " <<
			*(size_t*)(block->data + (blockSize - sizeof(footer))) << "\n";
		
		
		freeBlocks.insertAtBeginning(block);

		freeBlocks.printWithIterator();
	}
	~MemoryManager()
	{
		if (memblock)
		delete[] memblock;
	}

public:
	char *Malloc(size_t);
	void Free(char*);
};