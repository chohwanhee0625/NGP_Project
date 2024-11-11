#include "include.h"
#include "GameManager.h"

char* SERVERIP = (char*)"127.0.0.1";
#define SERVERPORT 9000
#define BUFSIZE    512

int main()
{
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
