#include "GameManager.h"
#include "PacketIO.h"

char* SERVERIP = (char*)"127.0.0.1";

SOCKET GameManager::WaitForOtherPlayer()
{
	using namespace std;
	// connect
	int retval;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) exit(1);

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) exit(1);
	cout << "Server Connected" << endl;

	// recv Start Flag
	std::string start_falg = Recv(sock);

	std::cout << "게임 시작 가능?" << std::endl;
	return sock;
}

void GameManager::UpdateWorld(SOCKET sock)
{
	using namespace std::chrono;

	std::cout << "UpdateWorld" << std::endl;

	// recv world Data


	while (true)
	{
		std::cout << "akakak" << std::endl;
		// send myplayer data

		// recv otherplayer data

		//if (/* GameEndFlag == true */true)
		//	break;

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / PACKET_FREQ));
	}

	// end Game Event
}

void GameManager::RecvWorldData()
{

}

void GameManager::SetWorldData()
{
}

void GameManager::RecvOtherPlayerData()
{
}

void GameManager::SendMyPlayerData()
{
}
