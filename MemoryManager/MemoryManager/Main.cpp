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
		MemoryManager mngr(1024);

		size_t firstBlockSize = 10 * sizeof(int);

		int *pArr1 = (int*)mngr.Malloc(firstBlockSize);

		size_t secondBlockSize = 8 * sizeof(int);

		int *pArr2 = (int*)mngr.Malloc(secondBlockSize);

		/*std::cout << "Value of header of Block No1: " << mngr.GetHeader((char*)pArr1) << "\n";

		std::cout << "Value of footer of Block No1: " << mngr.GetFooter((char*)pArr1) << "\n";

		std::cout << "Value of header of Block No2: " << mngr.GetHeaderRealSize((char*)pArr2) << "\n";

		std::cout << "Value of footer of Block No2: " << mngr.GetFooterRealSize((char*)pArr2) << "\n";*/

		mngr.Free((char*)pArr1);

		/*std::cout << "Value of header of Block No1 after free: " << mngr.GetHeader((char*)pArr1) << "\n";

		std::cout << "Value of footer of Block No1 after free : " << mngr.GetFooter((char*)pArr1) << "\n";*/

		mngr.Free((char*)pArr2);

		size_t thirdBlockSize = 4 * sizeof(int);

		int *pArr3 = (int*)mngr.Malloc(thirdBlockSize);

		/*DoublyLinkedList<int> *test = new DoublyLinkedList<int>;

		Node<int> *n1 = new Node<int>(1);
		test->insertAtBeginning(n1);

		Node<int> *n2 = new Node<int>(2);
		test->insertAtBeginning(n2);

		Node<int> *n3 = new Node<int>(3);
		test->insertAtBeginning(n3);

		Node<int> *n4 = new Node<int>(4);
		test->insertAtBeginning(n4);

		for (Iterator<int> it = test->getReverseIterator(); !it.end(); it.previous())
		{
			std::cout << it.getCurrent() << "\n";
		}

		delete test;*/

	}_CrtDumpMemoryLeaks();

	return 0;
}