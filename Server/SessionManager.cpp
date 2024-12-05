#include "SessionManager.h"
#include "PacketIO.h"

// std::random_device gRandDevice; // ��¥ ���� �߻��� -> �� ���� �õ尪����
std::random_device rd;
std::mt19937 gRandomEngine(rd()); // �˰��� + ��¥ ���� �õ� :: ��¥��¥ ���� ����

std::uniform_int_distribution<int> gBoolUniform{ 0,1 };
std::uniform_int_distribution<int> gRoadSet{ 5, 10 };
std::uniform_int_distribution<int> gCarspeed{ 1,3 };
std::uniform_real_distribution<float> gRandomColor{ 0.f,1.f };

std::mutex mtx;
// ���� ������ �ڵ� ����� ����ȭ 

//===============================================================================================

void SessionManager::StartGame(SOCKET client_sock_1, SOCKET client_sock_2)
{
	bool th_id[2] { 0, 1 };
	InitWorldData(th_id);
	
	// ������ ����
//	int flag = 1;
//	setsockopt(client_sock_1, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(flag));
//	setsockopt(client_sock_2, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(flag));

	m_threads.emplace_back(std::thread(&SessionManager::UpdateWorld, this, client_sock_1, (int)th_id[0]));
	m_threads[0].detach();
	m_threads.emplace_back(std::thread(&SessionManager::UpdateWorld, this, client_sock_2, (int)th_id[1]));
	m_threads[1].detach();

	while (true)
		if (m_endflag[0] == true && m_endflag[1] == true)
			break;

	//// ��� �����尡 ��� ���� ������ ��ٸ��� ���� -> ��� �۾��� �Ϸ�� �Ŀ� ���� �ܰ�� ����
	//for (auto& th : m_threads) 
	//	th.join();
}

std::atomic<bool> game_flag = false;
DWORD WINAPI SessionManager::UpdateWorld(SOCKET client_sock, int my_id)
{
	std::cout << "Client_" << my_id << " Thread Create" << std::endl;
	using namespace std::chrono;
	int other_id = 1 - my_id;
	m_updateData[my_id].Player_ID = my_id;
	SendWorldData(client_sock, my_id);
	
	// �غ� �Ϸ� �÷��� �ޱ�
	RecvStartFlag(client_sock);
	m_startflag[my_id] = true;
	
	// ���� ����� ���� �غ� �Ϸ� �÷��׸� ������ Ȯ���� �Ǹ� ��ȣ �ְ� while ������ => �ٸ� ������ ��ٷ��ֱ�
	while (true) {
		if (m_startflag[my_id] && m_startflag[other_id]) {	
			SendStartFlag(client_sock);
			break;
		}
	}



	std::string j_str;
	while (true) 
	{
		{
			std::lock_guard<std::mutex> lock(mtx); // ����ȭ�� ���� ��� 

			// 1. Ŭ���̾�Ʈ���� �����͸� ��Ŷ ����ü�� �����ϰ� to_json�Լ��� �����͸� Json string�������� ����
			// 2. ��Ŷ ������, string�� char*�� ��ȯ�� ������ ������ ������ Send
			// 3. char*�� ��ȯ�� �������� �����͸� ������� �������� �޾Ƽ� string�� ���� Recv 
			// 4. string�� ����� �����͸� from_json���� parse(�Ľ�) �������� string���� ����� �������� ������ ����
			//
			// from_json : ������ ���� ����
			// to_json   : ������ string���� ����

			// recv my player data
			j_str = Recv(client_sock);

			m_updateData[my_id].from_json(j_str);

			// ����� �˻�
			if (m_updateData[my_id].Player_Pos_z <= -15.f) {
				m_updateData[my_id].GameOver_Flag = true;
				m_winner.Winner_ID[my_id] = true;
				m_winner.End_Flag = true;
				game_flag = true;
			}
			else if (m_updateData[other_id].Player_Pos_z <= -15.f) {
				m_updateData[other_id].GameOver_Flag = true;
				m_winner.Winner_ID[other_id] = true;
				m_winner.End_Flag = true;
				game_flag = true;
			}

			// send other player data
			// ohter_id�� ���� �����忡�� ������Ʈ�� ������ Ŭ���̾�Ʈ�� Send
			j_str = m_updateData[other_id].to_json();
			Send(client_sock, j_str);

			// send winner flag
			j_str = m_winner.to_json();
			Send(client_sock, j_str);

			if (m_winner.End_Flag == true) {
				int winner_id = m_winner.Winner_ID[my_id] ? my_id : other_id;
				if (m_updateData[winner_id].Player_Pos_y >= MAX_HEIGHT)
					break;
			}
		}



		// �ʴ� 40������ ��Ŷ ���� �ֱ⸦ �����Ѵ�
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / PACKET_FREQ)); 
	}

	EndGame(client_sock);

	return 0;
}

void SessionManager::EndGame(SOCKET client_sock)
{
	int result = shutdown(client_sock, SD_BOTH);
	closesocket(client_sock);
}

void SessionManager::InitWorldData(bool p_id[2])
{
	//-----------------------------------------------------------------------------------------
	// Init Player Data

	m_InitPlayerData[0].Player_ID = { 0 };
	m_InitPlayerData[1].Player_ID = { 1 };

	//-----------------------------------------------------------------------------------------
	// Init Roads Data 

	// �ܵ� + ���� �ε��� ���� ( �� ũ�� )
	const int max_tiles{ 150 };
	int index{ 0 };

	// �޸� �̸� Ȯ��, size = 0, capacity = maxTiles
	// ���� Grass
	m_roadData.Roads_Flags.reserve(max_tiles);
	m_roadData.Roads_Flags.emplace_back(GRASS);
	++index;

	while (index < max_tiles) {
		int roads_build_count{ gRoadSet(gRandomEngine) };

		// index�� max_tiles�� �ʰ����� �ʵ��� roads_build_count�� ����
		if (index + roads_build_count > max_tiles) {
			roads_build_count = max_tiles - index; // ���� ������ŭ�� ���θ� �߰�
		}

		// ���θ� �����ϰ�, �� ���� ����Ʈ ����
		for (int j = 0; j < roads_build_count; ++j) {
			m_roadData.Roads_Flags.emplace_back(ROAD); 

			bool car_spawn_point{ (bool)gBoolUniform(gRandomEngine) };

			if (car_spawn_point == LEFT) { 
				m_roadData.Dir_Flags.emplace_back(LEFT);  
			}
			else if (car_spawn_point == RIGHT) {
				m_roadData.Dir_Flags.emplace_back(RIGHT); 
			}
		}

		index += roads_build_count;

		m_roadData.Roads_Flags.emplace_back(GRASS); 
		++index;
	}

	// ��� Grass - ���� �� ��
	for (int i = 0; i < 10; ++i) {
		m_roadData.Roads_Flags.emplace_back(GRASS); 
	}

	//-----------------------------------------------------------------------------------------
	// Init Cars Data
	
	// ������� ����ŭ ����
	for (int i = 0; i < m_roadData.Roads_Flags.size(); ++i)
	{
		// ���� ���θ� �������� ����
		if (ROAD == m_roadData.Roads_Flags[i])
		{
			// �ε����� �����༭ �ӵ� ����
			m_carData.Cars_Velocity.emplace_back(0.1 + i * 0.002 * gCarspeed(gRandomEngine));
			
			// �ѱ� �� ���� �� ���� �ʱ�ȭ
			std::array<float, static_cast<int>(RGB::END)> tempRGB{ gRandomColor(gRandomEngine),gRandomColor(gRandomEngine),gRandomColor(gRandomEngine) };
			
			// �߰�
			m_carData.Cars_Color_RGB.emplace_back(tempRGB);
		}
	}

	//-----------------------------------------------------------------------------------------
	// Init Woods Data

	const int max_wood = 12;
	// �ִ� ���� ����

	for (int i = 0; i < m_roadData.Roads_Flags.size(); ++i) {
		if (m_roadData.Roads_Flags[i] == GRASS) {

			std::array<bool, 12> wood_line{};  
			// �� �ٿ� ���� ��ġ ���θ� ���� �迭 

			for (int j = 0; j < max_wood; ++j) {
				bool should_plan_wood{ (bool)gBoolUniform(gRandomEngine) };

				// ������ ���� ��� 1, �ƴϸ� 0���� ����
				wood_line[j] = should_plan_wood; 
			}

			m_woodData.Woods_Flags.emplace_back(wood_line);  // �� ���� ���� �迭�� Woods_Flags�� �߰�
		}
	}
	//-----------------------------------------------------------------------------------------
}

void SessionManager::SendWorldData(SOCKET client_sock, int id)
{
	// send Player Data
	int other = 1 - id;
	Send(client_sock, m_InitPlayerData[id].to_json());
	//Send(client_sock, m_InitPlayerData[other].to_json());
	
	// send Roads Data
	Send(client_sock, m_roadData.to_json());

	// send Cars Data
	Send(client_sock, m_carData.to_json());

	// send Woods Data
	Send(client_sock, m_woodData.to_json());
}
