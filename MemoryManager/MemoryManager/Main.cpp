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

		size_t blockSize = 10 * sizeof(int);

		int *p = (int*)mngr.Malloc(blockSize);
		*p = 3;

		std::cout << "Value of header: " <<
			*(size_t*)((char*)p - sizeof(size_t*)) << "\n";

		size_t valueOfFooter = *(size_t*)((char*)p + blockSize - sizeof(size_t*));
		//std::cout << "valueOfFooter: " << valueOfFooter << "\n";

		std::cout << "valueOfFooter: " << 
			(*(size_t*)((char*)p + blockSize - sizeof(size_t*)) & (~(1 << (4 * sizeof(size_t)-1)))) << "\n";

	}_CrtDumpMemoryLeaks();

	return 0;
}