#pragma once
#include "include.h"
#include "PacketClass.h"


class GameManager
{
public:
	GameManager() {}

	SOCKET WaitForOtherPlayer();
	void UpdateWorld(SOCKET sock);

	void RecvWorldData(SOCKET sock);
};

