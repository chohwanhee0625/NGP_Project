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

	// UI 교체
	// gPlaybutton.change_iamge("aljsdf.png");
	// gPlaybutton.Render();

	// recv Start Flag
	std::string start_flag = Recv(sock);

	// recv world Data
	RecvWorldData(sock);

	std::cout << "게임 시작 가능?" << std::endl;
	return sock;
}

void GameManager::UpdateWorld(SOCKET sock)
{
	using namespace std::chrono;

	std::cout << "UpdateWorld" << std::endl;

	while (true)
	{
		// send myplayer data

		// recv otherplayer data

		//if (/* GameEndFlag == true */)
		//	break;

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / PACKET_FREQ));
	}

	// end Game Event
}

void GameManager::RecvWorldData(SOCKET sock)
{
	using namespace std;

	// recv Player Data
	INIT_DATA_P m_InitPlayerData[2];
	std::string j_str = Recv(sock);
	m_InitPlayerData[0].from_json(j_str);		// MY Player Data
	j_str = Recv(sock);
	m_InitPlayerData[1].from_json(j_str);		// Other Player Data
	cout << j_str << endl;

	// recv Roads Data
	INIT_DATA_R m_roadData;
	j_str = Recv(sock);
	m_roadData.from_json(j_str);
	cout << j_str << endl;

	// recv Cars Data
	INIT_DATA_C m_carData;
	j_str = Recv(sock);
	m_carData.from_json(j_str);
	cout << j_str << endl;

	// recv Woods Data
	INIT_DATA_W m_woodData;
	j_str = Recv(sock);
	m_woodData.from_json(j_str);
	cout << j_str << endl;
}

void GameManager::SetWorldData()
{

}

void GameManager::RecvOtherPlayerData(SOCKET sock)
{
}

void GameManager::SendMyPlayerData(SOCKET sock)
{
}
