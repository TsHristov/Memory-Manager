#pragma once

class MemoryManager
{
private:
	//DoublyLinkedList<MemoryBlock<Node<int>>> freeBlocks;
	char *memblock;

public:
	MemoryManager()
	{
		memblock = new char[1000];
	}
	~MemoryManager()
	{
		delete[] memblock;
	}

public:
	void *Malloc(size_t);
	//void free(void*);
};