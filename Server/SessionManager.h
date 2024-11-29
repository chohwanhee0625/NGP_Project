#pragma once
#include "include.h"
#include "PacketClass.h"
#include "PacketIO.h"


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




private:
	std::vector<std::thread> m_threads;
	
	
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

