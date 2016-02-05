#pragma once
#include "Iterator.h"

template<class T>
class DoublyLinkedList
{

private:
	Node<T> *firstNode;
	Node<T> *lastNode;

public:
	size_t size;

public:
	DoublyLinkedList() :firstNode(NULL), lastNode(NULL), size(0){}
	~DoublyLinkedList()
	{
		while (firstNode)
		{
			Node<T>* next = firstNode->next;
			delete firstNode;
			firstNode = next;
		}
	}

public:
	void insertAfter(Node<T>*, Node<T>*);

	void insertBefore(Node<T>*, Node<T>*);

	void insertAtBeginning(Node<T>*);

	void insertAtEnd(Node<T>*);

	void remove(Node<T>*);

	void print();

public:
	Iterator<T> getIterator();
	Iterator<T> getReverseIterator();

	void printWithIterator();
	//void printWithReverseIterator();
};


template<class T>
void DoublyLinkedList<T>::insertAfter(Node<T> *node, Node<T> *newNode)
{
	newNode->previous = node;
	newNode->next = node->next;
	if (!node->next)
	{
		lastNode = newNode;
	}
	else
	{
		node->next->previous = newNode;
	}
	node->next = newNode;
	++size;
}


template<class T>
void DoublyLinkedList<T>::insertBefore(Node<T> *node, Node<T> *newNode)
{
	newNode->previous = node->previous;
	newNode->next = node;
	if (!node->previous)
	{
		firstNode = newNode;
	}
	else
	{
		node->previous->next = newNode;
	}
	node->previous = newNode;
	++size;
}


template<class T>
void DoublyLinkedList<T>::insertAtBeginning(Node<T> *newNode)
{
	if (!firstNode)
	{
		firstNode = newNode;
		lastNode = newNode;
		newNode->previous = NULL;
		newNode->next = NULL;
		++size;
	}
	else
		insertBefore(firstNode, newNode);
}


template<class T>
void DoublyLinkedList<T>::insertAtEnd(Node<T> *newNode)
{
	if (!lastNode)
		insertAtBeginning(newNode);
	else
		insertAfter(lastNode, newNode);
}


template<class T>
void DoublyLinkedList<T>::remove(Node<T> *node)
{
	if (!node->previous)
		firstNode = node->next;
	else
		node->previous->next = node->next;
	if (!node->next)
		lastNode = node->previous;
	else
		node->next->previous = node->previous;
	--size;
}

template<class T>
void DoublyLinkedList<T>::print()
{
	Node<T>* temp = firstNode;
	std::cout << "Forward: ";
	while (temp)
	{
		std::cout << "Header data of free block: " << *(size_t*)(temp->data - sizeof(size_t*)) << "\n" << "\n";
		temp = temp->next;
	}
	std::cout << "\n";
}

template<class T>
Iterator<T> DoublyLinkedList<T>::getIterator()
{
	return Iterator<T>(this->firstNode);
}


template<class T>
Iterator<T> DoublyLinkedList<T>::getReverseIterator()
{
	return Iterator<T>(this->lastNode);
}

template<class T>
void DoublyLinkedList<T>::printWithIterator()
{
	for (Iterator<T> it = this->getIterator(); it.end(); it.next())
	{
		std::cout << "iterator: " << *(size_t*)(it.getCurrent() - sizeof(size_t*)) << '\n';
	}
}


/*template<class T>
void printWithReverseIterator()
{
for (Iterator<T> it = this->getReverseIterator(); it.previous(); it.end())
{
std::cout << it.getCurrent() << '\n';
}
}*/