#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <assert.h>
#include <random>

#include <thread>
#include <mutex>
#include <atomic>

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