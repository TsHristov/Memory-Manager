#include <iostream>
#include "DoublyLinkedList.h"


void DoublyLinkedList::insertAfter(Node *node, Node *newNode)
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


void DoublyLinkedList::insertBefore(Node *node, Node *newNode)
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


void DoublyLinkedList::insertAtBeginning(Node *newNode)
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


void DoublyLinkedList::insertAtEnd(Node *newNode)
{
	if (!lastNode)
		insertAtBeginning(newNode);
	else
		insertAfter(lastNode, newNode);
}


void DoublyLinkedList::remove(Node *node)
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

	