#pragma once
#include "include.h"
#include "PacketClass.h"

class NODE
{
public:
	int x;
	NODE* next;
	NODE(int x) : x(x), next(nullptr) {}
};

class LF_QUEUE
{
	NODE* volatile head;
	NODE* volatile tail;
	bool CAS(NODE* volatile* ptr, NODE* old_ptr, NODE* new_ptr);

public:
	LF_QUEUE();
	void clear();

	void Enq(int x);
	int Deq();
};

