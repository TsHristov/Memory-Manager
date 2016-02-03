#include <iostream>
#include "DoublyLinkedList.h"
#include "Node.h"
#include "MemoryManager.h"
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


int main()
{
	{
		char *memblock = new char[1000]; //1000 bytes available now
		std::cout << "Address of memblock: " << &memblock << "\n";

		size_t size = 8;

		memcpy(memblock, &size, sizeof(size_t));

		void *ptr = memblock + sizeof(size_t);
		size_t *sz = (size_t*)memblock;
		std::cout << *sz << "\n";

		memcpy(memblock + size *sizeof(char), &size, sizeof(size_t));

		size_t *szg = (size_t*)(memblock + size*sizeof(char));
		std::cout << *szg << "\n";

		int *pArr1 = (int*)ptr;
		*pArr1 = 457;

		delete[] memblock;
	}_CrtDumpMemoryLeaks();

	return 0;
}