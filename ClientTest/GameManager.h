#pragma once
#include "include.h"
#include "PacketClass.h"

class GameManager
{
public:
	GameManager() {}

	void WaitForOtherPlayer();
	void UpdateWorld(SOCKET sock);
};

