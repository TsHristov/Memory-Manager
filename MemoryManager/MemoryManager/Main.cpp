#include <iostream>
#include "DoublyLinkedList.h"
//#include "Node.h"
#include "MemoryManager.h"
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


int main()
{
	{
		MemoryManager mngr(1024);

		size_t firstBlockSize = 10 * sizeof(int);

		int *pArr1 = (int*)mngr.Malloc(firstBlockSize);

		size_t secondBlockSize = 8 * sizeof(int);

		int *pArr2 = (int*)mngr.Malloc(secondBlockSize);

		std::cout << "Value of header of Block No1: " <<
			(*(size_t*)((char*)pArr1 - sizeof(size_t*)) & (~(1 << (4 * sizeof(size_t)-1)))) << "\n";

		std::cout << "Value of footer of Block No1: " <<
			(*(size_t*)((char*)pArr1 - sizeof(size_t*) + ( firstBlockSize - sizeof(size_t*))) & (~(1 << (4 * sizeof(size_t)-1)))) << "\n";

		std::cout << "Value of header of Block No2: " <<
			(*(size_t*)((char*)pArr2 - sizeof(size_t*)) & (~(1 << (4 * sizeof(size_t)-1)))) << "\n";

		std::cout << "Value of footer of Block No2: " <<
			(*(size_t*)((char*)pArr2 - sizeof(size_t*) + (secondBlockSize - sizeof(size_t*))) & (~(1 << (4 * sizeof(size_t)-1)))) << "\n";

		//mngr.Free((char*)p);

	}_CrtDumpMemoryLeaks();

	return 0;
}