#pragma once
#include "include.h"
#include "PacketClass.h"
#include "PacketIO.h"


class SessionManager
{
public:
	void			StartGame(SOCKET client_sock_1, SOCKET client_sock_2);
	DWORD WINAPI	UpdateWorld(SOCKET client_sock, int my_id);
	void			EndGame(SOCKET client_sock);

	void			InitWorldData(bool p_id[2]);
	void			SendWorldData(SOCKET client_sock,int id);

private:
	std::vector<std::thread> m_threads;
	
	
	// 쓸꺼
	UPDATE_DATA				m_updateData[2];
	S_GAME_OVER				m_winner;

	INIT_DATA_P				m_InitPlayerData[2];
	INIT_DATA_R				m_roadData;
	INIT_DATA_C				m_carData;
	INIT_DATA_W				m_woodData;

	// atomic : 하나의 스레드가 작업을 끝내기 전까지, 대기해준다( 간단한 변수의 안전한 접근 )
	//		-> 변수(메모리)의 일부 접근(작업)에 대해 atomic한 동작을 보장한다. (대기하면 Blocking임)
	std::atomic<bool>		m_endflag {false};
	std::atomic<bool>		m_startflag[2]{ false, false };
};

