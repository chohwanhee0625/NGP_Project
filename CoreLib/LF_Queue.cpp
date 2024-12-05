#include "LF_Queue.h"

LF_QUEUE::LF_QUEUE()
{
	UPDATE_DATA init;
	head = tail = new NODE(init);
}

void LF_QUEUE::clear()
{
	while (Deq() != false);
}

void LF_QUEUE::Enq(UPDATE_DATA player_data)
{
	NODE* p = new NODE(player_data);
	while (true) {
		NODE* last = tail;
		NODE* next = last->next;
		if (last != tail) continue;
		if (next == nullptr) {
			if (true == CAS(&(last->next), nullptr, p)) {
				CAS(&tail, last, p);
				size++;
				return;
			}
		}
		else CAS(&tail, last, next);
	}
}

bool LF_QUEUE::Deq()
{
	while (true) {
		NODE* first = head;
		NODE* last = tail;
		NODE* next = first->next;
		if (first != head) continue;
		if (next == nullptr) return false;
		if (first == last) {
			CAS(&tail, last, next);
			continue;
		}
		if (true == CAS(&head, first, next)) {
			size--;
			delete first;
			return true;
		}
	}
}

UPDATE_DATA LF_QUEUE::Front()
{
	NODE* p = head->next;
	return p->m_player_data;
}

UPDATE_DATA LF_QUEUE::Second()
{
	NODE* p = head->next;
	p = p->next;
	return p->m_player_data;
}

int LF_QUEUE::Size()
{
	return size;
}

bool LF_QUEUE::CAS(NODE* volatile* ptr, NODE* old_ptr, NODE* new_ptr)
{
	return std::atomic_compare_exchange_strong(
		reinterpret_cast<volatile std::atomic_llong*>(ptr),
		reinterpret_cast<long long*>(&old_ptr),
		reinterpret_cast<long long>(new_ptr)
	);
}

