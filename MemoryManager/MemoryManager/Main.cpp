#include <iostream>
#include "MemoryManager.h"
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	{
		size_t sz = 1024;
		MemoryManager mngr(sz);

		// Allocate block of size 40 bytes
		size_t firstBlockSize = 10 * sizeof(int);

		int *pArr1 = (int*)mngr.Malloc(firstBlockSize);


		//Allocate block of size 32 bytes
		size_t secondBlockSize = 8 * sizeof(int);

		int *pArr2 = (int*)mngr.Malloc(secondBlockSize);

		std::cout << "Value of header of Block No1: " << mngr.GetHeader((char*)pArr1) << "\n";

		std::cout << "Value of footer of Block No1: " << mngr.GetFooter((char*)pArr1) << "\n";

		std::cout << "Value of header of Block No2: " << mngr.GetHeader((char*)pArr2) << "\n";

		std::cout << "Value of footer of Block No2: " << mngr.GetFooter((char*)pArr2) << "\n";


		// Free block of size 40 bytes
		mngr.Free((char*)pArr1);


		std::cout << "Value of header of Block No1 after free: " << mngr.GetHeader((char*)pArr1) << "\n";

		std::cout << "Value of footer of Block No1 after free : " << mngr.GetFooter((char*)pArr1) << "\n";

		//Allocate block of size 16 bytes, should be put at the place of pArr2
		size_t thirdBlockSize = 4 * sizeof(int);

		int *pArr3 = (int*)mngr.Malloc(thirdBlockSize);

		mngr.ForwardIteratationOverFreeBlocks();

		mngr.Free((char*)pArr3);


		std::cout << "Value of header of Block No3: " << mngr.GetHeader((char*)pArr3) << "\n";

		std::cout << "Value of footer of Block No3: " << mngr.GetFooter((char*)pArr3) << "\n";
		mngr.ForwardIteratationOverFreeBlocks();
	}
 
	_CrtDumpMemoryLeaks();
	return 0;
}