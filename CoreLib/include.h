#pragma once

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

enum class Toggle
{
	Perpective = 0, // Ω√¡°
	Light = 1,
	NearFar = 2,
	END = 10,
};

enum Dir
{
	STOP = 0,
	South = 1,
	West = 2,
	North = 3,
	East = 4,
};

enum myEnum
{
	OFF = 0,
	ON = 1,

	MINUS = -1,
	PLUS = 1,

	Third = 0,
	One = 1,

	LEFT = 0,
	RIGHT = 1,

	Near = 1,
	Far = 0,

	ROAD = 0,
	GRASS = 1,
};

typedef int Sign;

enum class RGB
{
	R,
	G,
	B
};
