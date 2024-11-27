#pragma once
#include "include.h"
#include "PacketClass.h"
#include "PacketIO.h"

class PlayerData
{
public:
	float player_pos_x;
	float player_pos_y;
	float player_pos_z;
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
	void operator=(UPDATE_DATA& rhs)
	{
		_datalock.lock();
		//player_pos_x = rhs.Other_Player_Pos_x;
		//player_pos_y = rhs.Other_Player_Pos_y;
		//player_pos_z = rhs.Other_Player_Pos_z;
		_datalock.unlock();
	}
};

class SessionManager
{
public:
	SessionManager() {}
	~SessionManager() {}

	void			StartGame(SOCKET client_sock_1, SOCKET client_sock_2);
	DWORD WINAPI	UpdateWorld(SOCKET client_sock, int my_id);
	void			EndGame(SOCKET client_sock);

	void			InitWorldData(bool p_id[2]);
	void			SendWorldData(SOCKET client_sock,int id);
	void			RecvMyPlayerData(int my_id, SOCKET client_sock);
	void			SendOtherPlayerData(int other_id, SOCKET client_sock);
	void			SendGameOverFlag(SOCKET client_sock);




private:
	std::vector<std::thread> m_threads;
	

	// Å×½ºÆ®
	PlayerData				m_playerData[2];
	
	// ¾µ²¨
	UPDATE_DATA				m_updateData[2];
	INIT_DATA_P				m_InitPlayerData[2];
	INIT_DATA_R				m_roadData;
	INIT_DATA_C				m_carData;
	INIT_DATA_W				m_woodData;

	volatile std::atomic<bool>		m_winner[2]{ false, false };
	volatile std::atomic<bool>		m_endflag[2]{ false, false };
	volatile std::atomic<bool>		m_startflag[2]{ false, false };
};

