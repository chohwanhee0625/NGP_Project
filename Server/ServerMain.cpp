#include "include.h"
#include "PacketClass.h"

// Test test;

int main()
{
	PacketClass test1(0, 1, 2);
	test1.colors.push_back({ 0.1f, 0.5f, 0.9f });
	test1.colors.push_back({ 0.2f, 0.6f, 0.0f });
	test1.colors.push_back({ 0.3f, 0.7f, 0.1f });
	test1.colors.push_back({ 0.4f, 0.8f, 0.2f });

	std::string j_str = test1.to_json();
	
	PacketClass test2;
	test2.from_json(j_str);
	test2.print();
}
