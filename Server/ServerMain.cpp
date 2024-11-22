#include "include.h"
#include "PacketClass.h"
#include "SessionManager.h"

using namespace nlohmann;


int main()
{
	using namespace std;
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return 1;

	// listen ���� ����
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) return 1;

	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = ::bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) return 1;
	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) return 1;

	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;

	queue<SOCKET> client_queue;
	SessionManager GM;
	while (true)
	{
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) continue;
		cout << "Client Connected" << endl;
		client_queue.push(client_sock);
		
		if (client_queue.size() >= 2)
		{
			auto sock1 = client_queue.front();

			client_queue.pop();
			auto sock2 = client_queue.front();
			client_queue.pop();
			GM.StartGame(sock1, sock2);

		}
	}
	// ���� �ݱ�
	closesocket(listen_sock);
	// ���� ����
	WSACleanup();
	return 0;
}
