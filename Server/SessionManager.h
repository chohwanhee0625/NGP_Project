#pragma once
#include "include.h"
#include "PacketClass.h"

class PlayerData
{
public:
	int player_pos_x;
	int player_pos_y;
	int player_pos_z;
	// TODO: Player Face Dir 

	std::mutex _datalock;
	void operator=(PlayerData& rhs)
	{
		_datalock.lock();
		player_pos_x = rhs.player_pos_x;
		player_pos_y = rhs.player_pos_y;
		player_pos_z = rhs.player_pos_z;
		// TODO: Player Face Dir 
		_datalock.unlock();
	}
};

class SessionManager
{
public:
	SessionManager() {}
	~SessionManager() {}

	void			StartGame(SOCKET client_sock_1, SOCKET client_sock_2);
	void			InitWorldData();
	void			SendWorldData(SOCKET client_sock);

	DWORD WINAPI	UpdateWorld(SOCKET client_sock, int my_id);
	void			RecvMyPlayerData(int my_id, SOCKET client_sock);
	void			SendOtherPlayerData(int other_id, SOCKET client_sock);
	void			EndGame(SOCKET client_sock);

private:
	std::vector<std::thread> m_threads;

	PlayerData				m_playerData[2];
	INIT_DATA_R				m_roadData;
	INIT_DATA_C				m_carData;
	INIT_DATA_W				m_woodData;

	std::atomic<bool>		m_winner[2]{ false, false };
	std::atomic<bool>		m_endflag[2]{ false, false };
};

