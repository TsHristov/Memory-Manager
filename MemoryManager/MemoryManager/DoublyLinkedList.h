#pragma once
#include "Iterator.h"
#include "Node.h"

template<class T>
class DoublyLinkedList
{

private:
	Node<T> *firstNode;
	Node<T> *lastNode;
	size_t size;

public:
	DoublyLinkedList():firstNode(NULL), lastNode(NULL), size(0){}
	~DoublyLinkedList()
	{
		if (this->firstNode)
		{
			delete firstNode;
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
	void printWithReverseIterator();
};


template<class T>
void insertAfter(Node<T> *node, Node<T> *newNode)
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
}


template<class T>
void insertBefore(Node<T> *node, Node<T> *newNode)
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
}


template<class T>
void insertAtBeginning(Node<T> *newNode)
{
	if (!firstNode)
	{
		firstNode = newNode;
		lastNode = newNode;
		newNode->previous = NULL;
		newNode->next = NULL;
	}
	else
		insertBefore(firstNode, newNode);
}


template<class T>
void insertAtEnd(Node<T> *newNode)
{
	if (!lastNode)
		insertAtBeginning(newNode);
	else
		insertAfter(lastNode, newNode);
}


template<class T>
void remove(Node<T> *node)
{
	if (!node->previous)
		firstNode = node->next;
	else
		node->previous->next = node->next;
	if (!node->next)
		lastNode = node->previous;
	else
		node->next->previous = node->previous;
}

template<class T>
void print()
{
	Node<T>* temp = firstNode;
	std::cout << "Forward: ";
	while (temp)
	{
		std::cout << temp->data;
		temp = temp->next;
	}
	std::cout << "\n";
}

template<class T>
Iterator<T> getIterator()
{
	return Iterator<T>(this->firstNode);
}


template<class T>
Iterator<T> getReverseIterator()
{
	return Iterator<T>(this->lastNode);
}

/*template<class T>
void printWithIterator()
{
	for (Iterator<T> it = this->getIterator(); it.next(); it.end())
	{
		std::cout << it.getCurrent() << '\n';
	}
}*/


/*template<class T>
void printWithReverseIterator()
{
	for (Iterator<T> it = this->getReverseIterator(); it.previous(); it.end())
	{
		std::cout << it.getCurrent() << '\n';
	}
}*/