#include "PacketIO.h"
#include "PacketClass.h"

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

	return j_str;
}

void SendStartFlag(SOCKET client_sock)
{
	// send Start flag Packet
	S_GAME_READY start_flag;
	start_flag.Ready_Flag = true;
	Send(client_sock, start_flag.to_json());
}

std::string RecvStartFlag(SOCKET client_sock)
{
	// send Start flag Packet
	std::string j_str;
	j_str = Recv(client_sock);
	return j_str;
}

