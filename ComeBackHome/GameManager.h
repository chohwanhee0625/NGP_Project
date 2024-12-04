#pragma once
#include "include.h"
#include "PacketClass.h"
#include "PacketIO.h"
#include "Souce.h"
#include "LF_Queue.h"
#include "extern.h"
#include "usingInclude.h"

class GameManager
{
public:
	char* SERVERIP = (char*)"127.0.0.1";
	UPDATE_DATA m_playerData[2];
	S_GAME_OVER	m_winner;
	int			my_id;

	LF_QUEUE m_otherPD_queue;

	SOCKET m_sock;

public:
	GameManager();

	SOCKET WaitForOtherPlayer();
	void UpdateWorld();

	void RecvWorldData();
	void Disconnect();
};
