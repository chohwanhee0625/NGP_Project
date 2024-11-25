#pragma once
#include "include.h"


void Send(SOCKET sock, std::string j_str);
std::string Recv(SOCKET sock);

void SendStartFlag(SOCKET client_sock);
std::string RecvStartFlag(SOCKET client_sock);
