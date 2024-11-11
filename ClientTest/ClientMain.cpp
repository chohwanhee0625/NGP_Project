#include "include.h"
#include "GameManager.h"
#include "PacketClass.h"

#define BUFSIZE    512

int main()
{
	S_GAME_READY s_flag;
	s_flag.Ready_Flag = true;
	std::string str = s_flag.to_json();
	std::cout << str << std::endl;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;
	GameManager GM;

	// GameStart UI

	GM.WaitForOtherPlayer();

	while (true)
	{

	}
}
