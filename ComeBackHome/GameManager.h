#pragma once
#include "include.h"
#include "PacketClass.h"
#include "PacketIO.h"
#include "Souce.h"

class GameManager
{
public:
	GameManager() {}

	SOCKET WaitForOtherPlayer();
	void UpdateWorld(SOCKET sock);

	void RecvWorldData(SOCKET sock);
	void SetWorldData();
	void RecvOtherPlayerData(SOCKET sock);
	void SendMyPlayerData(SOCKET sock);
};

