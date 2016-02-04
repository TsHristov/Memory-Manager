#pragma once
#include <iostream>
#include "DoublyLinkedList.h"
#include "Node.h"

class MemoryManager
{
private:
	char *memblock;
	DoublyLinkedList<char*> freeBlocks;

public:
	/***
	*	Start with one big free block:
	*		1.Put header information
	*		2.Put footer information
	*		3.Put its address in the freeBlocks list,so we will allocate from there.
	*/
	MemoryManager(size_t size)
	{
		memblock = new char[size];
		size_t *header = (size_t*)memblock;
		*header = size;

		//Allocation status: 0

		size_t *footer = (size_t*)(memblock + sizeof(size_t*)+(size - sizeof(size_t*)) * sizeof(char));
		*footer = size;

		// Put the pointer of the first free block after the header of it.
		Node<char*> *firstBlock = (Node<char*>*)(memblock + sizeof(size_t*));
		firstBlock->data = memblock + sizeof(size_t*);

		std::cout << "header of first free block: " <<
			*(size_t*)(firstBlock->data - sizeof(header)) << "\n";

		std::cout << "footer of first free block: " <<
			*(size_t*)(firstBlock->data  + (size - sizeof(footer))) << "\n";
		
		
		freeBlocks.insertAtBeginning(firstBlock);


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