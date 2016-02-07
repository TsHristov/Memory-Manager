#pragma once
#include "Node.h"

class Iterator
{
private:
	Node *pStart;
	Node *pCurrent;

public:
	Iterator(Node *pStart)
	{
		this->pStart = this->pCurrent = pStart;
	}

public:
	char*  getCurrent() const
	{
		return this->pCurrent->data;
	}
	/*void setCurrent(char* const & Value)
	{
		this->pCurrent->data = Value;
	}*/
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