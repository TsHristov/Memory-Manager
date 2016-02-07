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

public:
	Iterator<T> getIterator();
	Iterator<T> getReverseIterator();
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
Iterator<T> DoublyLinkedList<T>::getIterator()
{
	return Iterator<T>(this->firstNode);
}


template<class T>
Iterator<T> DoublyLinkedList<T>::getReverseIterator()
{
	return Iterator<T>(this->lastNode);
}