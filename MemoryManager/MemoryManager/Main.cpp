#include <iostream>
//#include "DoublyLinkedList.h"
//#include "Node.h"
#include "MemoryManager.h"
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


int main()
{
	{
		MemoryManager mngr;

		int *pArr1 = (int*)mngr.Malloc(2 * sizeof(int));
		*pArr1 = 457;

		/*char *memblock = new char[1000];
		std::cout << "Address of memblock: " << &memblock << "\n";

		size_t size = 8;

		memcpy(memblock, &size, sizeof(size_t));

		void *ptr = memblock + sizeof(size_t);
		size_t *sz = (size_t*)memblock;
		std::cout << *sz << "\n";

		memcpy(memblock + size * sizeof(char), &size, sizeof(size_t));

		size_t *szg = (size_t*)(memblock + size*sizeof(char));
		std::cout << *szg << "\n";

		int *pArr1 = (int*)ptr;
		*pArr1 = 457;

		double *pArr2 = (double*)ptr;
		*pArr2 = 333;

		double *p = (double*)(memblock + sizeof(size_t));
		std::cout << *p << "\n";

		size_t *b = (size_t*)(memblock + sizeof(size_t));
		std::cout << *b << "\n";

		delete[] memblock;*/
	}_CrtDumpMemoryLeaks();

	return 0;
}