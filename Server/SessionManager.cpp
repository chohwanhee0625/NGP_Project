#include "SessionManager.h"

void SessionManager::StartGame(SOCKET client_sock_1, SOCKET client_sock_2)
{
	InitWorldData();
	SendWorldData(client_sock_1);
	SendWorldData(client_sock_2);

	int th_id = 0;
	m_threads.emplace_back(std::thread(&SessionManager::UpdateWorld, this, client_sock_1, th_id++));
	m_threads.emplace_back(std::thread(&SessionManager::UpdateWorld, this, client_sock_2, th_id++));	
	
	while (true)
		if (m_endflag[0] == true && m_endflag[1] == true)
			break;

	for (auto& th : m_threads) 
		th.join();
}

void SessionManager::InitWorldData()
{
}

void SessionManager::SendWorldData(SOCKET client_sock)
{
}

DWORD __stdcall SessionManager::UpdateWorld(SOCKET client_sock, int my_id)
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

void SessionManager::RecvMyPlayerData(int my_id, SOCKET client_sock)
{

}

void SessionManager::SendOtherPlayerData(int other_id, SOCKET client_sock)
{
}

void SessionManager::EndGame(SOCKET client_sock)
{
}
