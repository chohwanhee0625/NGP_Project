#include "SessionManager.h"

std::random_device gRandDevice; // 진짜 난수 발생기 -> 이 값을 시드값으로
std::mt19937 gRandomEngine(gRandDevice); // 알고리즘 + 진짜 난수 시드 :: 진짜진짜 난수 생성

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
	//		# 수정할 것 
	//		( SetChicken )
	//		( ChickenBody::InitMatrix4() )  
	const float x_offset = 0.5f;

	m_playerData[p_id[0]].player_pos_x = 0.0f + p_id[0] * x_offset; 
	m_playerData[p_id[0]].player_pos_y = 0.0f; 
	m_playerData[p_id[0]].player_pos_z = 0.0f;
	
	m_playerData[p_id[1]].player_pos_x = 0.0f + p_id[1] * x_offset; 
	m_playerData[p_id[1]].player_pos_y = 0.0f; 
	m_playerData[p_id[1]].player_pos_z = 0.0f;

	// send 함수에서 호출해서 사용
	INIT_DATA_P player_1 { p_id[0], m_playerData[p_id[0]].player_pos_x,m_playerData[p_id[0]].player_pos_y, m_playerData[p_id[0]].player_pos_z };
	INIT_DATA_P player_2 { p_id[1], m_playerData[p_id[1]].player_pos_x,m_playerData[p_id[1]].player_pos_y, m_playerData[p_id[1]].player_pos_z };

	//-----------------------------------------------------------------------------------------
	// Init Roads Data 
	//		# 수정할 것 
	//		( SetGround )
	//		( Road::Road(), Road::InitCarSpawnDir )  
	
	// 잔디 + 도로 인덱스 개수 ( 맵 크기 )
	const int max_tiles{ 150 };
	int index{ 0 };

	// 메모리 미리 확보, size = 0, capacity = maxTiles
	// 맨 처음 땅 Grass
	m_roadData.Roads_Flags.reserve(max_tiles);
	m_roadData.Roads_Flags.emplace_back(GRASS); 
	++index; 
	
	while( index < max_tiles) {
		int roads_build_count{ gRoadSet(gRandomEngine) };
		
		// index가 max_tiles를 초과하지 않도록 roads_build_count를 제한
		if (index + roads_build_count > max_tiles) {
			roads_build_count = max_tiles - index; // 남은 공간만큼만 도로를 추가
		}

		// 도로를 생성하고, 차 스폰 포인트 설정
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

	// 장외 Grass - 엄마 닭 땅
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
	// // 한 줄에 나무 최대 몇개? 임시로 20


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

