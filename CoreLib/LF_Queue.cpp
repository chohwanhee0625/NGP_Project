#include "LF_Queue.h"

LF_QUEUE::LF_QUEUE()
{
	head = tail = new NODE(-1);
}

void LF_QUEUE::clear()
{
	while (Deq() != -1);
}

void LF_QUEUE::Enq(int x)
{
	NODE* p = new NODE(x);
	while (true) {
		NODE* last = tail;
		NODE* next = last->next;
		if (last != tail) continue;
		if (next == nullptr) {
			if (true == CAS(&(last->next), nullptr, p)) {
				CAS(&tail, last, p);
				return;
			}
		}
		else CAS(&tail, last, next);
	}
}

int LF_QUEUE::Deq()
{
	while (true) {
		NODE* first = head;
		NODE* last = tail;
		NODE* next = first->next;
		if (first != head) continue;
		if (next == nullptr) return -1;
		if (first == last) {
			CAS(&tail, last, next);
			continue;
		}
		int value = next->x;
		if (true == CAS(&head, first, next)) {
			delete first;
			return value;
		}
	}
}

bool LF_QUEUE::CAS(NODE* volatile* ptr, NODE* old_ptr, NODE* new_ptr)
{
	return std::atomic_compare_exchange_strong(
		reinterpret_cast<volatile std::atomic_llong*>(ptr),
		reinterpret_cast<long long*>(&old_ptr),
		reinterpret_cast<long long>(new_ptr)
	);
}

