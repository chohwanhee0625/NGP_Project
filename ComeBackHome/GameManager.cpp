#include "GameManager.h"


GameManager::GameManager()
{
	//UPDATE_DATA init_data;
	//init_data.Player_ID = 1;
	//m_otherPD_queue.Enq(init_data);
	//m_otherPD_queue.Enq(init_data);
}

SOCKET GameManager::WaitForOtherPlayer()
{
	// connect
	int retval;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) exit(1);
	
	// 고광신이 지움
	//int flag = 1;
	//setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(flag));

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) exit(1);
	cout << "Server Connected" << endl;

	m_sock = sock;

	// recv world Data
	RecvWorldData();

	return sock;
}

unsigned int render_counter;
void GameManager::UpdateWorld()
{	
	cout << "UpdateWorld" << std::endl;
	
	while (true)
	{
		// send myplayer data
		std::string j_str;
		j_str = m_playerData[(int)ID::ME].to_json();


		Send(m_sock, j_str);

		// recv otherplayer data
		j_str = Recv(m_sock);
		m_playerData[(int)ID::ENERMY].from_json(j_str);
		if (m_otherPD_queue.Size() > 2)
			m_otherPD_queue.Deq();
		m_otherPD_queue.Enq(m_playerData[(int)ID::ENERMY]);
		render_counter = 0;
		
		// recv winner flag
		j_str = Recv(m_sock);
		m_winner.from_json(j_str);

		if (GAME_OVER == true)
			break;

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / PACKET_FREQ));
	}

	// end Game Event
	Disconnect();
}

void GameManager::RecvWorldData()
{
	//===========================================================
	// recv Player Data
	INIT_DATA_P m_InitPlayerData;

	std::string j_str = Recv(m_sock);
	m_InitPlayerData.from_json(j_str);		// MY Player Data
	SetChicken(m_InitPlayerData.Player_ID);
	//m_InitPlayerData.from_json(j_str);		// Other Player Data
	SetgEnemyVec(m_InitPlayerData.Player_ID);

	my_id = m_InitPlayerData.Player_ID;
	cout << "Set Chicken" << endl;
	//=============================================================
	// recv Roads Data
	INIT_DATA_R m_roadData;

	j_str = Recv(m_sock);
	m_roadData.from_json(j_str);

	std::vector<bool> Roads_Flags = m_roadData.Roads_Flags;
	std::vector<bool> Dir_Flags = m_roadData.Dir_Flags;
	// 0: Road
	// 1: Grass 
	// 0 : LEFT  -> PLUS  -> 왼쪽에서 태어나서 오른쪽으로 이동
	// 1 : RIGHT -> MINUS -> 오른쪽에서 태어나서 왼쪽으로 이동
	SetGround(m_roadData);

	cout << "Set Roads" << endl;

	//=============================================================
	// recv Cars Data
	INIT_DATA_C m_carData;
	j_str = Recv(m_sock);
	m_carData.from_json(j_str);

	SetCars(m_carData);

	std::vector<float>	Cars_Velocity = m_carData.Cars_Velocity;
	std::vector<std::array<float, 3>> Cars_Color_RGB = m_carData.Cars_Color_RGB;	

	cout << "Set Cars" << endl;

	//=============================================================
	// recv Woods Data
	INIT_DATA_W m_woodData;
	j_str = Recv(m_sock);
	m_woodData.from_json(j_str);
	SetWoods(m_woodData);

	cout << "Set Woods" << endl;

	//=============================================================

	SetRoadLane(); // 도로 흰색 라인 만들기
	SetMother(); // 도착지점 엄마 닭 만들기
}

void GameManager::Disconnect()
{
	int result = shutdown(m_sock, SD_BOTH);
	closesocket(m_sock);
	WSACleanup();
	return;
}

