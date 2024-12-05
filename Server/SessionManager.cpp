#include "SessionManager.h"
#include "PacketIO.h"

// std::random_device gRandDevice; // 진짜 난수 발생기 -> 이 값을 시드값으로
std::random_device rd;
std::mt19937 gRandomEngine(rd()); // 알고리즘 + 진짜 난수 시드 :: 진짜진짜 난수 생성

std::uniform_int_distribution<int> gBoolUniform{ 0,1 };
std::uniform_int_distribution<int> gRoadSet{ 5, 10 };
std::uniform_int_distribution<int> gCarspeed{ 1,3 };
std::uniform_real_distribution<float> gRandomColor{ 0.f,1.f };

std::mutex mtx;
// 여러 변수나 코드 블록의 동기화 

//===============================================================================================

void SessionManager::StartGame(SOCKET client_sock_1, SOCKET client_sock_2)
{
	bool th_id[2] { 0, 1 };
	InitWorldData(th_id);
	
	// 고광신이 지움
//	int flag = 1;
//	setsockopt(client_sock_1, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(flag));
//	setsockopt(client_sock_2, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(flag));

	m_threads.emplace_back(std::thread(&SessionManager::UpdateWorld, this, client_sock_1, (int)th_id[0]));
	m_threads[0].detach();
	m_threads.emplace_back(std::thread(&SessionManager::UpdateWorld, this, client_sock_2, (int)th_id[1]));
	m_threads[1].detach();

	while (true)
		if (m_endflag[0] == true && m_endflag[1] == true)
			break;

	//// 멤버 스레드가 모두 끝날 때까지 기다리는 역할 -> 모든 작업이 완료된 후에 다음 단계로 간다
	//for (auto& th : m_threads) 
	//	th.join();
}

std::atomic<bool> game_flag = false;
DWORD WINAPI SessionManager::UpdateWorld(SOCKET client_sock, int my_id)
{
	std::cout << "Client_" << my_id << " Thread Create" << std::endl;
	using namespace std::chrono;
	int other_id = 1 - my_id;
	m_updateData[my_id].Player_ID = my_id;
	SendWorldData(client_sock, my_id);
	
	// 준비 완료 플래그 받기
	RecvStartFlag(client_sock);
	m_startflag[my_id] = true;
	
	// 나와 상대편 각각 준비가 완료 플래그를 받은게 확인이 되면 신호 주고 while 나가기 => 다른 스레드 기다려주기
	while (true) {
		if (m_startflag[my_id] && m_startflag[other_id]) {	
			SendStartFlag(client_sock);
			break;
		}
	}



	std::string j_str;
	while (true) 
	{
		{
			std::lock_guard<std::mutex> lock(mtx); // 동기화를 위한 잠금 

			// 1. 클라이언트에서 데이터를 패킷 구조체에 저장하고 to_json함수로 데이터를 Json string형식으로 저장
			// 2. 패킷 사이즈, string을 char*로 변환한 데이터 정보를 서버로 Send
			// 3. char*로 변환된 가변길이 데이터를 순서대로 서버에서 받아서 string에 저장 Recv 
			// 4. string에 저장된 데이터를 from_json에서 parse(파싱) 과정으로 string으로 저장된 데이터의 원본을 복원
			//
			// from_json : 데이터 원본 복원
			// to_json   : 데이터 string으로 저장

			// recv my player data
			j_str = Recv(client_sock);

			m_updateData[my_id].from_json(j_str);

			// 우승자 검사
			if (m_updateData[my_id].Player_Pos_z <= -15.f) {
				m_updateData[my_id].GameOver_Flag = true;
				m_winner.Winner_ID[my_id] = true;
				m_winner.End_Flag = true;
				game_flag = true;
			}
			else if (m_updateData[other_id].Player_Pos_z <= -15.f) {
				m_updateData[other_id].GameOver_Flag = true;
				m_winner.Winner_ID[other_id] = true;
				m_winner.End_Flag = true;
				game_flag = true;
			}

			// send other player data
			// ohter_id를 맡은 스레드에서 업데이트한 정보를 클라이언트에 Send
			j_str = m_updateData[other_id].to_json();
			Send(client_sock, j_str);

			// send winner flag
			j_str = m_winner.to_json();
			Send(client_sock, j_str);

			if (m_winner.End_Flag == true) {
				int winner_id = m_winner.Winner_ID[my_id] ? my_id : other_id;
				if (m_updateData[winner_id].Player_Pos_y >= MAX_HEIGHT)
					break;
			}
		}



		// 초당 40번으로 패킷 전송 주기를 유지한다
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / PACKET_FREQ)); 
	}

	EndGame(client_sock);

	return 0;
}

void SessionManager::EndGame(SOCKET client_sock)
{
	int result = shutdown(client_sock, SD_BOTH);
	closesocket(client_sock);
}

void SessionManager::InitWorldData(bool p_id[2])
{
	//-----------------------------------------------------------------------------------------
	// Init Player Data

	m_InitPlayerData[0].Player_ID = { 0 };
	m_InitPlayerData[1].Player_ID = { 1 };

	//-----------------------------------------------------------------------------------------
	// Init Roads Data 

	// 잔디 + 도로 인덱스 개수 ( 맵 크기 )
	const int max_tiles{ 150 };
	int index{ 0 };

	// 메모리 미리 확보, size = 0, capacity = maxTiles
	// 시작 Grass
	m_roadData.Roads_Flags.reserve(max_tiles);
	m_roadData.Roads_Flags.emplace_back(GRASS);
	++index;

	while (index < max_tiles) {
		int roads_build_count{ gRoadSet(gRandomEngine) };

		// index가 max_tiles를 초과하지 않도록 roads_build_count를 제한
		if (index + roads_build_count > max_tiles) {
			roads_build_count = max_tiles - index; // 남은 공간만큼만 도로를 추가
		}

		// 도로를 생성하고, 차 스폰 포인트 설정
		for (int j = 0; j < roads_build_count; ++j) {
			m_roadData.Roads_Flags.emplace_back(ROAD); 

			bool car_spawn_point{ (bool)gBoolUniform(gRandomEngine) };

			if (car_spawn_point == LEFT) { 
				m_roadData.Dir_Flags.emplace_back(LEFT);  
			}
			else if (car_spawn_point == RIGHT) {
				m_roadData.Dir_Flags.emplace_back(RIGHT); 
			}
		}

		index += roads_build_count;

		m_roadData.Roads_Flags.emplace_back(GRASS); 
		++index;
	}

	// 장외 Grass - 엄마 닭 땅
	for (int i = 0; i < 10; ++i) {
		m_roadData.Roads_Flags.emplace_back(GRASS); 
	}

	//-----------------------------------------------------------------------------------------
	// Init Cars Data
	
	// 만들어진 땅만큼 돌림
	for (int i = 0; i < m_roadData.Roads_Flags.size(); ++i)
	{
		// 땅이 도로면 차데이터 만듬
		if (ROAD == m_roadData.Roads_Flags[i])
		{
			// 인덱스에 편차줘서 속도 설정
			m_carData.Cars_Velocity.emplace_back(0.1 + i * 0.002 * gCarspeed(gRandomEngine));
			
			// 넘길 차 색상 값 선언 초기화
			std::array<float, static_cast<int>(RGB::END)> tempRGB{ gRandomColor(gRandomEngine),gRandomColor(gRandomEngine),gRandomColor(gRandomEngine) };
			
			// 추가
			m_carData.Cars_Color_RGB.emplace_back(tempRGB);
		}
	}

	//-----------------------------------------------------------------------------------------
	// Init Woods Data

	const int max_wood = 12;
	// 최대 나무 개수

	for (int i = 0; i < m_roadData.Roads_Flags.size(); ++i) {
		if (m_roadData.Roads_Flags[i] == GRASS) {

			std::array<bool, 12> wood_line{};  
			// 한 줄에 나무 배치 여부를 담을 배열 

			for (int j = 0; j < max_wood; ++j) {
				bool should_plan_wood{ (bool)gBoolUniform(gRandomEngine) };

				// 나무를 심을 경우 1, 아니면 0으로 설정
				wood_line[j] = should_plan_wood; 
			}

			m_woodData.Woods_Flags.emplace_back(wood_line);  // 한 줄의 나무 배열을 Woods_Flags에 추가
		}
	}
	//-----------------------------------------------------------------------------------------
}

void SessionManager::SendWorldData(SOCKET client_sock, int id)
{
	// send Player Data
	int other = 1 - id;
	Send(client_sock, m_InitPlayerData[id].to_json());
	//Send(client_sock, m_InitPlayerData[other].to_json());
	
	// send Roads Data
	Send(client_sock, m_roadData.to_json());

	// send Cars Data
	Send(client_sock, m_carData.to_json());

	// send Woods Data
	Send(client_sock, m_woodData.to_json());
}
