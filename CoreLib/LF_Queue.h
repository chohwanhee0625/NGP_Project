#pragma once
#include "include.h"
#include "PacketClass.h"

class NODE
{
public:
	UPDATE_DATA m_player_data;
	NODE* next;
	NODE(UPDATE_DATA player_data) : m_player_data(player_data), next(nullptr) {}
};

class LF_QUEUE
{
	NODE* volatile head;
	NODE* volatile tail;
	std::atomic<int> size = 0;

	bool CAS(NODE* volatile* ptr, NODE* old_ptr, NODE* new_ptr);

public:
	LF_QUEUE();
	void clear();

	void Enq(UPDATE_DATA player_data);
	bool Deq();
	UPDATE_DATA Front();
	int Size();
};

