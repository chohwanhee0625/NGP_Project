#include "include.h"
#include "GameManager.h"
#include "PacketClass.h"

#define BUFSIZE    512

int main()
{
	// 윈속 초기화
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
