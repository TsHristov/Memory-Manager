#include <iostream>
#include "DoublyLinkedList.h"
#include "Node.h"
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

struct Block
{
	size_t header;
	int data;
	size_t footer;

	Block(const int& data)
	{
		this->data = data;
		this->header = this->footer = sizeof(data);
	}
};


int main()
{
	{
		char *memblock = new char[1000];
		std::cout << "First: " << &memblock << '\n';
		
		Block *block1 = new Block(1);
		memcpy(&memblock, &block1, sizeof(block1));

		char *a = memblock;
		a += sizeof(block1);
		std::cout << "After block1: " << &a << '\n';
		Block *one = (Block*)(memblock + a);
		std::cout << "block1: " << one->data << '\n';

		Block *block2 = new Block(2);
		memcpy(&memblock, &block2, sizeof(block2));

		char *b = memblock;
		b += sizeof(block2);
		std::cout << "After block2: " << &b << '\n';

		Block *block3 = new Block(3);
		memcpy(&memblock, &block3, sizeof(block3));

		char *c = memblock;
		c += sizeof(block3);
		std::cout << "After block3: " << &c << '\n';

		std::cout << "Memblock at address: " << &memblock << '\n';
		
	}_CrtDumpMemoryLeaks();

	return 0;
}