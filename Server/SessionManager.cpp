#include "SessionManager.h"

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
	// Init Player Data
	// # 나중에 수정 -> ChickenBody::InitMatrix4()  
	const float x_offset = 0.5f;

	m_playerData[p_id[0]].player_pos_x = 0.0f + p_id[0] * x_offset; 
	m_playerData[p_id[0]].player_pos_y = 0.0f; 
	m_playerData[p_id[0]].player_pos_z = 0.0f;
	
	m_playerData[p_id[1]].player_pos_x = 0.0f + p_id[1] * x_offset; 
	m_playerData[p_id[1]].player_pos_y = 0.0f; 
	m_playerData[p_id[1]].player_pos_z = 0.0f;

	INIT_DATA_P player_1 { p_id[0], m_playerData[p_id[0]].player_pos_x,m_playerData[p_id[0]].player_pos_y, m_playerData[p_id[0]].player_pos_z };
	INIT_DATA_P player_2 { p_id[1], m_playerData[p_id[1]].player_pos_x,m_playerData[p_id[1]].player_pos_y, m_playerData[p_id[1]].player_pos_z };


	// Init Roads Data 
	INIT_DATA_R roads;
	// vector<bool> Roads_Flags : 0(road), 1(grass)
	// vector<bool> Dir_Flags : car( 0: left spawn, Plus, 1: right spawn, Minus )
#if 0
	// Left Right 변수를 수정
	Road::InitCarSpawnDir()
	{
		// 0 : LEFT  -> +1 -> 왼쪽에서 태어나서 오른쪽으로 이동
		// 1 : RIGHT -> -1 -> 오른쪽에서 태어나서 왼쪽으로 이동
		GLboolean bLeftOrRight{ (bool)gBoolUniform(gRandomEngine) };

		if (bLeftOrRight == LEFT)
			m_car_spawn_dir = PLUS;
		else if (bLeftOrRight == RIGHT)
			m_car_spawn_dir = MINUS;
}
#endif

	// Init Cars Data
	INIT_DATA_C cars; 
	// vector<bool> Roads_Flags;
	// vector<bool> Dir_Flags;
	
	
	// Init Woods Data
	INIT_DATA_W woods; 
	// vector<std::array<bool, 20>> Woods_Flags;	
	// // 한 줄에 나무 최대 몇개? 임시로 20

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

