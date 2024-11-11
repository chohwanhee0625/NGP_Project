#include "GameManager.h"

void GameManager::WaitForOtherPlayer()
{
	// connect
	int retval;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) return 1;

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) return;

	// recv Start Flag


	std::thread networkThread(&GameManager::UpdateWorld, this, sock);

	networkThread.join();
}

void GameManager::UpdateWorld(SOCKET sock)
{
	using namespace std::chrono;

	// recv world Data

	while (true)
	{
		// send myplayer data

		// recv otherplayer data

		if (/* GameEndFlag == true */true)
			break;

		std::this_thread::sleep_for(1000ms / PACKET_FREQ);
	}

	// end Game Event
}
