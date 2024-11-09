#include "GameManager.h"

void GameManager::WaitForOtherPlayer()
{
	// connect
	SOCKET sock;

	// recv Start Flag

	std::thread networkThread(&GameManager::UpdateWorld, this, sock);

	networkThread.join();
}

void GameManager::UpdateWorld(SOCKET sock)
{
	using namespace std::chrono;

	// recv world Data

	while (true)
	{
		// send myplayer data

		// recv otherplayer data

		if (/* GameEndFlag == true */true)
			break;

		std::this_thread::sleep_for(1000ms / PACKET_FREQ);
	}

	// end Game Event
}
