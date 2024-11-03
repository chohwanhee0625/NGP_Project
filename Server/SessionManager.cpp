#include "SessionManager.h"

void SessionManager::StartGame(SOCKET client_sock_1, SOCKET client_sock_2)
{
	InitWorldData();
	SendWorldData(client_sock_1);
	SendWorldData(client_sock_2);

	int th_id = 0;
	m_threads.emplace_back(UpdateWorld, client_sock_1, th_id++);
	m_threads.emplace_back(UpdateWorld, client_sock_2, th_id++);

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
}

void SessionManager::RecvMyPlayerData(int my_id, SOCKET client_sock)
{
}

void SessionManager::SendOtherPlayerData(int other_id, SOCKET client_sock)
{
}

void SessionManager::EndGame()
{
}
