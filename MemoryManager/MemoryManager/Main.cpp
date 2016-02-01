#include <iostream>
#include "DoublyLinkedList.h"
#include "Node.h"
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	{
		DoublyLinkedList<int> a;
		Node<int> *newNode = new Node<int>(1);
		a.insertAtBeginning(newNode);
		Node<int> *newNode2 = new Node<int>(2);
		a.insertAfter(newNode, newNode2);
		Node<int> *newNode3 = new Node<int>(3);
		a.insertBefore(newNode, newNode3);
		Node<int> *newNode4 = new Node<int>(4);
		a.insertAfter(newNode3, newNode4);
		a.remove(newNode4);
		//delete newNode4;
		a.print();
	}_CrtDumpMemoryLeaks();

	return 0;
}