#include "SessionManager.h"

std::random_device gRandDevice; // ��¥ ���� �߻��� -> �� ���� �õ尪����
std::mt19937 gRandomEngine(gRandDevice); // �˰��� + ��¥ ���� �õ� :: ��¥��¥ ���� ����

std::uniform_int_distribution<int> gBoolUniform{ 0,1 };
std::uniform_int_distribution<int> gRoadSet{ 5, 10 };
std::uniform_int_distribution<int> gCarspeed{ 1,3 };
std::uniform_real_distribution<float> gRandomColor{ 0.f,1.f };

//===============================================================================================

void SessionManager::StartGame(SOCKET client_sock_1, SOCKET client_sock_2)
{
	bool th_id[2] { 0, 1 };
	SendStartFlag(client_sock_1);
	SendStartFlag(client_sock_2);
	InitWorldData(th_id);
	SendWorldData(client_sock_1);
	SendWorldData(client_sock_2);

	m_threads.emplace_back(std::thread(&SessionManager::UpdateWorld, this, client_sock_1, (int)th_id[0]));
	m_threads.emplace_back(std::thread(&SessionManager::UpdateWorld, this, client_sock_2, (int)th_id[1]));
	
	while (true)
		if (m_endflag[0] == true && m_endflag[1] == true)
			break;

	for (auto& th : m_threads) 
		th.join();
}

DWORD WINAPI SessionManager::UpdateWorld(SOCKET client_sock, int my_id)
{
	int other_id = 1 - my_id;

	while (true)
	{
		RecvMyPlayerData(my_id, client_sock);
		if (m_playerData[my_id].player_pos_z >= 150.f)		// TODO: goal line z pos
			m_winner[my_id] = true;

		SendOtherPlayerData(other_id, client_sock);
		if (m_playerData[other_id].player_pos_z >= 150.f)	// goal line z pos
			m_winner[other_id] = true;

		if (m_winner[my_id] || m_winner[other_id])
			break;
	}

	EndGame(client_sock);

	return 0;
}

void SessionManager::EndGame(SOCKET client_sock)
{
	SendGameOverFlag(client_sock);

}

void SessionManager::SendStartFlag(SOCKET client_sock)
{
	// send Start flag Packet

}

void SessionManager::InitWorldData(bool p_id[2])
{
	//-----------------------------------------------------------------------------------------
	// Init Player Data 
	//		# ������ �� 
	//		( SetChicken )
	//		( ChickenBody::InitMatrix4() )  
	const float x_offset = 0.5f;

	m_playerData[p_id[0]].player_pos_x = 0.0f + p_id[0] * x_offset; 
	m_playerData[p_id[0]].player_pos_y = 0.0f; 
	m_playerData[p_id[0]].player_pos_z = 0.0f;
	
	m_playerData[p_id[1]].player_pos_x = 0.0f + p_id[1] * x_offset; 
	m_playerData[p_id[1]].player_pos_y = 0.0f; 
	m_playerData[p_id[1]].player_pos_z = 0.0f;

	// send �Լ����� ȣ���ؼ� ���
	INIT_DATA_P player_1 { p_id[0], m_playerData[p_id[0]].player_pos_x,m_playerData[p_id[0]].player_pos_y, m_playerData[p_id[0]].player_pos_z };
	INIT_DATA_P player_2 { p_id[1], m_playerData[p_id[1]].player_pos_x,m_playerData[p_id[1]].player_pos_y, m_playerData[p_id[1]].player_pos_z };

	//-----------------------------------------------------------------------------------------
	// Init Roads Data 
	//		# ������ �� 
	//		( SetGround )
	//		( Road::Road(), Road::InitCarSpawnDir )  
	
	// �ܵ� + ���� �ε��� ���� ( �� ũ�� )
	const int max_tiles{ 150 };
	int index{ 0 };

	// �޸� �̸� Ȯ��, size = 0, capacity = maxTiles
	// �� ó�� �� Grass
	m_roadData.Roads_Flags.reserve(max_tiles);
	m_roadData.Roads_Flags.emplace_back(GRASS); 
	++index; 
	
	while( index < max_tiles) {
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
	m_carData;
	// vector<bool> Roads_Flags;
	// vector<bool> Dir_Flags;
	
	
	//-----------------------------------------------------------------------------------------
	// Init Woods Data
	m_woodData;
	// vector<std::array<bool, 20>> Woods_Flags;	
	// // �� �ٿ� ���� �ִ� �? �ӽ÷� 20


	//-----------------------------------------------------------------------------------------
}

void SessionManager::SendWorldData(SOCKET client_sock)
{
	// send Player Data

	// send Roads Data

	// send Cars Data

	// send Woods Data

}

void SessionManager::RecvMyPlayerData(int my_id, SOCKET client_sock)
{

}

void SessionManager::SendOtherPlayerData(int other_id, SOCKET client_sock)
{
}

void SessionManager::SendGameOverFlag(SOCKET client_sock)
{

}

