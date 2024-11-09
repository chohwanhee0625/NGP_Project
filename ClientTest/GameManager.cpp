#include "GameManager.h"

void GameManager::WaitForOtherPlayer()
{
	// connect
	SOCKET sock;

	// recv Start Flag

	std::thread NetworkThread(&GameManager::UpdateWorld, this, sock);
}

void GameManager::UpdateWorld(SOCKET sock)
{
}
