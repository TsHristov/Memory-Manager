#pragma once
#include "Iterator.h"

class DoublyLinkedList
{

private:
	Node *firstNode;
	Node *lastNode;

public:
	size_t size;

public:
	DoublyLinkedList() :firstNode(NULL), lastNode(NULL), size(0){}

public:
	void insertAfter(Node*, Node*);
	void insertBefore(Node*, Node*);
	void insertAtBeginning(Node*);
	void insertAtEnd(Node*);
	void remove(Node*);

public:
	Iterator getIterator()
	{
		return Iterator(this->firstNode);
	}

	Iterator getReverseIterator()
	{
		return Iterator(this->lastNode);
	}
};

