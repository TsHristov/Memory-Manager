#pragma once
#include "Node.h"

template<class T>
class DoublyLinkedList
{

private:
	Node<T> *head;
	size_t size;

public:
	DoublyLinkedList() :size(0), head(nullptr){}
	~DoublyLinkedList()
	{
		if (this->head)
		{
			delete head;
		}
	}

public:

	void insertAtHead(const T& x)
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
	}

	void print() const
	{
		Node<T>* temp = head;
		std::cout << "Forward: ";
		while (temp != NULL) {
			std::cout << temp->data;
			temp = temp->next;
		}
		std::cout << "\n";
	}
};