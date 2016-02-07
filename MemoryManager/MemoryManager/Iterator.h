#pragma once
#include "Node.h"

class Iterator
{
private:
	Node *start;
	Node *current;

public:
	Iterator(Node *start)
	{
		this->start = this->current = start;
	}

public:
	char*  getAddressOfFreeBlock() const
	{
		return this->current->addressOfFreeBlock;
	}
	void moveToNext()
	{
		if (this->current)
		{
			this->current = this->current->next;
		}
	}
	void moveToPrevious()
	{
		if (this->current)
		{
			this->current = this->current->previous;
		}
	}
	bool end() const
	{
		return this->current == NULL;
	}
};