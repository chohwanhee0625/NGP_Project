#include "include.h"

void Send(SOCKET sock, std::string j_str)
{
	u_int packet_size = j_str.size();
	char header[4];
	std::memcpy(header, &packet_size, sizeof(u_int));

	send(sock, header, sizeof(header), 0);
	send(sock, (char*)j_str.c_str(), packet_size, 0);
}

std::string Recv(SOCKET sock)
{
	char header[4];
	recv(sock, header, sizeof(header), MSG_WAITALL);

	u_int packet_size;
	std::memcpy(&packet_size, header, sizeof(u_int));

	std::string j_str;
	j_str.resize(packet_size);
	recv(sock, (char*)j_str.c_str(), packet_size, MSG_WAITALL);
}
