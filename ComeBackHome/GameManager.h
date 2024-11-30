#pragma once
#include "include.h"
#include "PacketClass.h"
#include "PacketIO.h"
#include "Souce.h"
#include "LF_Queue.h"

class GameManager
{
public:
	char* SERVERIP = (char*)"127.0.0.1";
	UPDATE_DATA m_playerData[2];
	LF_QUEUE m_otherPlayer;

public:
	GameManager();

	SOCKET WaitForOtherPlayer();
	void UpdateWorld(SOCKET sock);

	void RecvWorldData(SOCKET sock);
};

