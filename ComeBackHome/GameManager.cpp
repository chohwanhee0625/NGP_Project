#include "GameManager.h"
#include "PacketIO.h"
#include "소스.h"

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
	//SetChicken(m_InitPlayerData[0]);
	j_str = Recv(sock);
	m_InitPlayerData[1].from_json(j_str);		// Other Player Data
	//SetgEnemyVec(m_InitPlayerData[1]);
	cout << "Set Chicken" << endl;

	// recv Roads Data
	INIT_DATA_R m_roadData;
	j_str = Recv(sock);
	m_roadData.from_json(j_str);
	SetGround(m_roadData);
	cout << "Set Roads" << endl;

	// recv Cars Data
	INIT_DATA_C m_carData;
	j_str = Recv(sock);
	m_carData.from_json(j_str);
	//SetCars(m_carData);
	SetCars(m_carData);
	cout << "Set Cars" << endl;

	// recv Woods Data
	INIT_DATA_W m_woodData;
	j_str = Recv(sock);
	m_woodData.from_json(j_str);
	SetWoods(m_woodData);
	cout << "Set Woods" << endl;

	SetRoadLane(); // 도로 흰색 라인 만들기
	SetMother(); // 도착지점 엄마 닭 만들기
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
