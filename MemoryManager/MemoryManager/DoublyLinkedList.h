#pragma once
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

	void insertAtEnd(Node<T> *newNode)
	{
		if (!lastNode)
			insertAtBeginning(newNode);
		else
			insertAfter(lastNode, newNode);
	}

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

	/*void insertAtHead(const T& x)
	{
		Node<T> *newNode = new Node<T>(x, NULL, NULL);
		if (head == NULL)
		{
			head = newNode;
			return;
		}
		head->previous = newNode;
		newNode->next = head;
		head = newNode;
	}

	void insertAtTail(const T& x) 
	{
		Node<T>* temp = head;
		Node<T>* newNode = new Node<T>(x, NULL, NULL);
		if (head == NULL) {
			head = newNode;
			return;
		}
		while (temp->next != NULL)
		{
			temp = temp->next; // Go To last Node
		}
		temp->next = newNode;
		newNode->previous = temp;
	}*/

	void print() const
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
};