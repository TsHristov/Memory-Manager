#pragma once
#include "Block.h"

class MemoryManager
{
	char *root;
public:
	MemoryManager()
	{
		root = new char[1000];
	}
	~MemoryManager()
	{
		delete root;
	}

public:
	static void *Malloc(size_t size)
	{
		root = Block<char>(size, size, 'a');
	}
	static void Free(void *pBlock);
};