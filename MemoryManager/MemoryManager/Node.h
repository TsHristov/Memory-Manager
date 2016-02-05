#pragma once
template<class T>
struct Node
{
	T data;
	Node<T> *previous;
	Node<T> *next;

public:
	Node() :previous(NULL), next(NULL){}
	Node(const T& data)
	{
		this->data = data;
		this->previous = NULL;
		this->next = NULL;
	}
	Node(const T& data, Node<T> *previous, Node<T> *next)
	{
		this->data = data;
		this->previous = previous;
		this->next = next;
	}
};