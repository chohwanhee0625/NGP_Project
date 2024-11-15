#include "include.h"
#include "GameManager.h"
#include "PacketClass.h"

#define BUFSIZE    512

int main()
{
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;
	GameManager GM;

	// GameStart UI

	SOCKET sock = GM.WaitForOtherPlayer();

	std::thread networkThread(&GameManager::UpdateWorld, &GM, sock);

	while (true)
	{

	}
	networkThread.join();
}
