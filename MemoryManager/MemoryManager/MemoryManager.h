#pragma once

class MemoryManager
{
private:
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
	void *Malloc(size_t size);
	void free(void *p);
};


template<class T>
void *Malloc(size_t size)
{
	memcpy(memblock, &size, sizeof(size_t));
	
	return memblock;
}