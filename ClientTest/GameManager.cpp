#include "GameManager.h"

char* SERVERIP = (char*)"127.0.0.1";

void GameManager::WaitForOtherPlayer()
{
	// connect
	int retval;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) return;

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) return;

	// recv Start Flag
	std::string start_flag(512, 0);
	recv(sock, (char*)start_flag.c_str(), sizeof(start_flag), MSG_WAITALL);

	std::cout << "게임 시작 가능?" << std::endl;

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

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / PACKET_FREQ));
	}

	// end Game Event
}
