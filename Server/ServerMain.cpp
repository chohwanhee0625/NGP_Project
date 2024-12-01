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
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return 999;

	// listen ���� ����
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) return 888;

	int optval = 1;
	// ������ ����
//	setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));

	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = ::bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) return 222;
	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) return 1;

	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;

	queue<SOCKET> client_queue;
	vector<thread> game_threads;
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
			SessionManager GM;

			auto sock1 = client_queue.front();

			client_queue.pop();
			auto sock2 = client_queue.front();
			client_queue.pop();

			game_threads.emplace_back(&SessionManager::StartGame, &GM, sock1, sock2);
		}
	}

	for (auto& t : game_threads) {
		t.join();
	}

	// ���� �ݱ�
	closesocket(listen_sock);
	// ���� ����
	WSACleanup();
	return 0;
}
