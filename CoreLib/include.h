#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <random>

#include <thread>
#include <mutex>
#include <queue>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <mmsystem.h>

#include "nlohmann/json.hpp"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#pragma comment(lib, "winmm.lib")

//using namespace std;
using namespace nlohmann;


class Test;

enum CustomEnum
{
	OFF = 0,
	ON = 1,

	MINUS = -1,
	PLUS = 1,

	LEFT = 0,
	RIGHT = 1,

	ROAD = 0,
	GRASS = 1,
};
