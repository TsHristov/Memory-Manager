#pragma once
template<class T>
/**
	This structure serves to represent the memory
	blocks,used by the allocator.
*/
struct Block
{
	size_t header;
	bool isAllocated;
	size_t footer;
	T payload;

	Block(size_t header, size_t footer, T payload)
	{
		this->header = header;
		this->footer = footer;
		this->payload = payload;
	}
};