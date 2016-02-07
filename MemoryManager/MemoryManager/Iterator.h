#pragma once
#include "Node.h"
template<class T>
class Iterator
{
private:
	Node<T> *pStart;
	Node<T> *pCurrent;

public:
	Iterator(Node<T> *pStart)
	{
		this->pStart = this->pCurrent = pStart;
	}

public:
	const T  getCurrent() const
	{
		return this->pCurrent->data;
	}
	void setCurrent(T const & Value)
	{
		this->pCurrent->data = Value;
	}
	void next()
	{
		if (this->pCurrent)
		{
			this->pCurrent = this->pCurrent->next;
		}
	}
	void previous()
	{
		if (this->pCurrent)
		{
			this->pCurrent = this->pCurrent->previous;
		}
	}
	bool end() const
	{
		return this->pCurrent == NULL;
	}
};