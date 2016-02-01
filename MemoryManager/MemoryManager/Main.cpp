#include <iostream>
#include "DoublyLinkedList.h"
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	{
		DoublyLinkedList<int> a;
		//int c = 4;
		a.insertAtHead(1);
		a.insertAtHead(2);
		a.insertAtHead(3);
		a.insertAtHead(4);

		a.insertAtTail(1);
		a.insertAtTail(2);
		a.insertAtTail(3);
		a.insertAtTail(4);
		a.print();
	}_CrtDumpMemoryLeaks();

	return 0;
}