#if 1
#include "usingInclude.h"
#include "Souce.h"
#include "Souce1.h"
#include "Basis.h"
#include "Chicken.h"
#include "grass.h"
#include "extern.h"
#include "Road.h"
#include "Wall.h"
#include "Camera.h"
#include "Car.h"
#include "Light.h"
#include "TimeManager.h"
#include "Border.h"
#include "Tree.h"
#include "Family.h"
#include "UI.h"
#include "GameManager.h"
#include "PacketIO.h"

bool GAME_START = false;
std::mutex g_lock;
bool Interpolated = true;

//===========================================================================================

void make_shaderProgram()
{
	make_vertexShaders("vertex2.glsl");
	make_fragmentShaders("fragment2.glsl");
	gShaderProgramID = glCreateProgram();
	glAttachShader(gShaderProgramID, gVertexShader);
	glAttachShader(gShaderProgramID, gFragmentShader);
	glLinkProgram(gShaderProgramID);
	glDeleteShader(gVertexShader);
	glDeleteShader(gFragmentShader);

	make_vertexShaders_1("vertex3.glsl");
	make_fragmentShaders_1("fragment3.glsl");
	gUIShaderProgramID = glCreateProgram();
	glAttachShader(gUIShaderProgramID, gUIVertexShader);
	glAttachShader(gUIShaderProgramID, gUIFragmentShader);
	glLinkProgram(gUIShaderProgramID);
	glDeleteShader(gUIVertexShader);
	glDeleteShader(gUIFragmentShader);
	glUseProgram(gUIShaderProgramID);
}

void make_vertexShaders(const char* vertex_path)
{
	gVertexSource = filetobuf(vertex_path);
	gVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(gVertexShader, 1, (const GLchar**)&gVertexSource, 0);
	glCompileShader(gVertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(gVertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(gVertexShader, 512, NULL, errorLog);
		std::cout << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void make_vertexShaders_1(const char* vertex_path)
{
	gVertexSource = filetobuf(vertex_path);
	gUIVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(gUIVertexShader, 1, (const GLchar**)&gVertexSource, 0);
	glCompileShader(gUIVertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(gUIVertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(gUIVertexShader, 512, NULL, errorLog);
		std::cout << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShaders(const char* fragment_path)
{
	gFragmentSource = filetobuf(fragment_path);
	gFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(gFragmentShader, 1, (const GLchar**)&gFragmentSource, 0);
	glCompileShader(gFragmentShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(gFragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(gFragmentShader, 512, NULL, errorLog);
		std::cout << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShaders_1(const char* fragment_path)
{
	gFragmentSource = filetobuf(fragment_path);
	gUIFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(gUIFragmentShader, 1, (const GLchar**)&gFragmentSource, 0);
	glCompileShader(gUIFragmentShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(gUIFragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(gUIFragmentShader, 512, NULL, errorLog);
		std::cout << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb");
	if (!fptr)
		return NULL;
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;
	return buf;
}

void ShowMenu()
{
	cout << "=================================\n";

	cout << "w/a/s/d: chcken run.\n";
	cout << "t/T: Light on/off \n";
	cout << "Shift : Speed up.\n";
	cout << "j/J : jump \n";
	cout << "p/P : 3/1view camera\n";
	cout << "o/O : near 3view camera\n";
	cout << "m/M : collision off\n";
	cout << "u/U : very fase\n";
	cout << "i/I : very slow\n";

	cout << "q/Q : program off\n";

	cout << "=================================\n";
}

//===========================================================================================

void main_viewport()
{	
	int g_window_w = gWidth;
	int g_window_h = gHeight;

	glViewport(0, 0, g_window_w, g_window_h); // 800, 600

	gCamera.PerspectiveProjection();
	
	if (gToggle[(int)Toggle::Perpective] == Third) {
		// 3인칭
		gCamera.SetViewTransform_ThirdPersonViewport();
	}
	else if (gToggle[(int)Toggle::Perpective] == One) {
		// 1인칭
		gCamera.SetViewTransform_FirstPersonViewport();
	}

	gLight->Update();

	gVecDraw();
	gEnemyVecDraw();
}

void chicken_viewport()
{
	int g_window_w = gWidth;
	int g_window_h = gHeight;

	glViewport(gWidth - 150, gHeight - 130, 140, 120);

	gCamera.PerspectiveProjection();
	// 치킨 고정 카메라
	gCamera.SetViewTransform_ChickenViewport();
	gLight->Update();

	gVecDraw();
	gEnemyVecDraw();
}

void border_viewport()
{
	int g_window_w = gWidth;
	int g_window_h = gHeight;

	gCamera.PerspectiveProjection();
	// Border 카메라
	gCamera.SetViewTransform_BorderViewport();
	gLight->InitLight();

	glViewport(gWidth - 150 - 10, gHeight - 130 - 10, 140 + 20, 130 + 20);

	gBorder->DrawObject();
}

GLvoid DrawScene()
{
	glClearColor(0.5294f, 0.8078f, 0.9804f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 깊이 버퍼 클리어

	if (GAME_START == false or GAME_OVER == true)
		gPlaybutton.Render();
	if (GAME_START == true and GAME_OVER == false) {
		main_viewport();
		border_viewport();
		chicken_viewport();
	}

	glutSwapBuffers();
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void TimerFunction(int value)
{
	if (GAME_START) {
		
		gCamera.Move();
		gTimer.update();
		float deltatime = gTimer.getDeltaTime();
		
		//deltatime = std::min(deltatime, 0.2f);
		//cout << deltatime << endl;


		gEnemyVecUpdate(deltatime);
		gVecUpdate(deltatime);

		glutPostRedisplay();				//화면 재출력
		glutTimerFunc(15, TimerFunction, 1); // 다시 호출 
	}
}

GLvoid KeyUpboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':case 'W':
		if (gIsMovingChicken) {
			gIsMovingChicken = OFF;
			SetChickenFaceDir((char)Dir::STOP);
			gCamera.SetCameraFaceDir((char)Dir::STOP);
			SetOffGlobalDir();
		}
		break;

	case 's':case 'S':
		if (gIsMovingChicken) {
			gIsMovingChicken = OFF;
			SetChickenFaceDir((char)Dir::STOP);
			gCamera.SetCameraFaceDir((char)Dir::STOP);
			SetOffGlobalDir();
		}
		break;

	case 'a':case 'A':
		if (gIsMovingChicken) {
			gIsMovingChicken = OFF;
			SetChickenFaceDir((char)Dir::STOP);
			gCamera.SetCameraFaceDir((char)Dir::STOP);
			SetOffGlobalDir();
		}
		break;

	case 'd':case 'D':
		if (gIsMovingChicken) {
			gIsMovingChicken = OFF;
			SetChickenFaceDir((char)Dir::STOP);
			gCamera.SetCameraFaceDir((char)Dir::STOP);
			SetOffGlobalDir();
		}
		break;
	default:
		if (GAME_START == false) {
			SOCKET sock = gGameManager.WaitForOtherPlayer();
			gGameManager.m_sock = sock;

			glUseProgram(gShaderProgramID);

			SetOffAllofToggle();
			SetInitToggle();
			InitBorder(); // 우측 상단 핑크색 경계 만들기 
			InitLight();
			gLight->InitLight();
			gCamera.InitCamera();

			// 준비 완료 플래그 서버에 보내기
			SendStartFlag(sock);
			std::cout << "Send My Read Flag\n" << std::endl;
			// 상대편까지 모두 준비 완료 플래그 -> 게임 시작 
			RecvStartFlag(sock);
			std::cout << "Recv Other Ready Flag\n" << std::endl;

			GAME_START = true;
			std::thread networkThread(&GameManager::UpdateWorld, &gGameManager);
			networkThread.detach();

			gTimer.starttimer();
			glutTimerFunc(1, TimerFunction, 1);
		}
		break;
	}
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'w': case 'W':
		if (!gChickenDir[0]) {
			gChickenDir[0] = true;
			gIsMovingChicken = ON;
			SetChickenFaceDir('w');
		}
		break;

	case 's': case 'S':
		if (!gChickenDir[1]) {
			gChickenDir[1] = true;
			gIsMovingChicken = ON;
			SetChickenFaceDir('s');
		}
		break;

	case 'a': case 'A':
		if (!gChickenDir[2]) {
			gChickenDir[2] = true;
			gIsMovingChicken = ON;
			SetChickenFaceDir('a');
		}
		break;

	case 'd': case 'D':
		if (!gChickenDir[3]) {
			gChickenDir[3] = true;
			gIsMovingChicken = ON;
			SetChickenFaceDir('d');
		}
		break;

	case 't': case'T':
		SetLightToggle();
		break;
	
	case 'm': case'M':
		gVec.at(0)->SwitchCollisionState();
		break;
	case 'u': case'U':
		ChickenRun();
		break;
	case 'i': case'I':
		ChickenWalk();
		break;
	case 'o': case'O':
		SetNearFarCameraToggle();
		break;
		// 프로그램 종료
	case 'q': case 'Q':
		GAME_OVER = true;
		glutLeaveMainLoop();
		break;
	case 'j': case 'J':
		ChickenJump();
		break;
	case 'p': case'P':
		SetPerspectiveToggle();
		break;
	case 'e' : case 'E':
		Interpolated = !Interpolated;
		if (Interpolated == false)
			std::cout << "Interpolated Off" << std::endl;
		else
			std::cout << "Interpolated On" << std::endl;
		break;

		// ---------- 리셋  ----------
	case 'r': case'R':
		SetOffAllofToggle(); 
		SetInitToggle();
		gCamera.InitCamera();
		gLight->InitLight();
		gIsMovingChicken = OFF;
	//	gVecClear();
	//	SetgVec();
		for (int j{}; j < 8; ++j) 
		{
			gVec.at(j)->InitMatrix4(); 
		}
		break;
	}
	glutPostRedisplay();
}

//===========================================================================================

void InitLight()
{
	gLight = new Light();
}

void InitBorder()
{
	gBorder = new Border{ cube_vertex_array_normal, cube_color };
}

void SetgVec() // 육면체, 사면체 처음 위치 - 면 총 10개
{
	//SetChicken();
	//SetGround(); // 도로 + 잔디 만들기
	//SetCars(); // 차 만들기
	//SetWoods(); // 나무 만들기
	//SetRoadLane(); // 도로 흰색 라인 만들기
	//SetMother(); // 도착지점 엄마 닭 만들기
	
	//tagWall* pWall = new tagWall{ cube_vertex_array_normal, floor_color}; // 9
	//gVec.push_back(pWall);
}

const float g_offset_x {0.07f};

void SetgEnemyVec(bool my_id)
{
	bool other_id = !my_id;

	// UPDATE_DATA : bool player id, float xyz, char player Face, bool overflag  

	UPDATE_DATA other_player;
	other_player.Player_ID = other_id;
	other_player.Player_Pos_x = 0.0f;
	
	// 상대가 1번 플레이어면 == true면 -> 오프셋 적용( 0.07f )
	if (!my_id)
		other_player.Player_Pos_x += g_offset_x;
	
	other_player.Player_Pos_y = 0.0f;
	other_player.Player_Pos_z = 0.0f;
	other_player.Player_FaceDegree = 180.f; // enum값 확인
	other_player.GameOver_Flag = false;

	// 클라이언트 게임 매니저에 데이터 저장
	gGameManager.m_playerData[(int)ID::ENERMY] = other_player;

	// Enemy Chicken 생성
	ChickenBody* body = new ChickenBody{ cube_vertex_array_normal, cube_color, other_id }; // 0 - 몸
	gEnemyVec.push_back(body);
	ChickenHead* head = new ChickenHead{ cube_vertex_array_normal, cube_color, other_id }; // 1 - 머리
	gEnemyVec.push_back(head);
	ChickenMouse* mouse = new ChickenMouse{ cube_vertex_array_normal, cube_color, other_id }; // 2 - 주둥이
	gEnemyVec.push_back(mouse);
	ChickenEyes* eyes = new ChickenEyes{ cube_vertex_array_normal, cube_color, other_id }; // 3 - 눈 
	gEnemyVec.push_back(eyes);

	ChickenLeftArm* Larm = new ChickenLeftArm{ cube_vertex_array_normal, cube_color, other_id }; // 4 - 왼팔 
	gEnemyVec.push_back(Larm);
	ChickenRightArm* Rarm = new ChickenRightArm{ cube_vertex_array_normal, cube_color,other_id }; // 5 - 오른팔 
	gEnemyVec.push_back(Rarm);

	ChickenLeftLeg* Lleg = new ChickenLeftLeg{ cube_vertex_array_normal, cube_color, other_id }; // 6 - 왼다리 
	gEnemyVec.push_back(Lleg); 
	ChickenRightLeg* Rleg = new ChickenRightLeg{ cube_vertex_array_normal, cube_color,other_id }; // 7 - 오른다리 
	gEnemyVec.push_back(Rleg);
}

void SetChicken(bool my_id)
{
	UPDATE_DATA my_player;
	my_player.Player_ID = my_id;
	my_player.Player_Pos_x = 0.0;

	// 내가 1번 플레이어면 == true면 -> 오프셋 적용( 0.07f )
	if (my_id)
		my_player.Player_Pos_x += g_offset_x;
	
	my_player.Player_Pos_y = 0.0f;
	my_player.Player_Pos_z = 0.0f;
	my_player.Player_FaceDegree = 180.f; 
	my_player.GameOver_Flag = false;

	// 클라이언트 게임 매니저에 데이터 저장
	gGameManager.m_playerData[(int)ID::ME] = my_player;

	// Player Chicken 생성
	ChickenBody* body = new ChickenBody{ cube_vertex_array_normal, cube_color, my_id }; // 0 - 몸 
	gVec.push_back(body);
	ChickenHead* head = new ChickenHead{ cube_vertex_array_normal, cube_color, my_id }; // 1 - 머리
	gVec.push_back(head);
	ChickenMouse* mouse = new ChickenMouse{ cube_vertex_array_normal, cube_color,my_id }; // 2 - 주둥이
	gVec.push_back(mouse);
	ChickenEyes* eyes = new ChickenEyes{ cube_vertex_array_normal, cube_color, my_id }; // 3 - 눈
	gVec.push_back(eyes);

	ChickenLeftArm* Larm = new ChickenLeftArm{ cube_vertex_array_normal, cube_color, my_id }; // 4 - 왼팔
	gVec.push_back(Larm);
	ChickenRightArm* Rarm = new ChickenRightArm{ cube_vertex_array_normal, cube_color, my_id }; // 5 - 오른팔
	gVec.push_back(Rarm);

	ChickenLeftLeg* Lleg = new ChickenLeftLeg{ cube_vertex_array_normal, cube_color, my_id }; // 6 - 왼다리
	gVec.push_back(Lleg);
	ChickenRightLeg* Rleg = new ChickenRightLeg{ cube_vertex_array_normal, cube_color,my_id }; // 7 - 오른다리
	gVec.push_back(Rleg);
}

void SetGround(INIT_DATA_R road_data)
{
	// 땅 만들기 ( 잔디, 도로 )

	Road* pRoad{};
	RoadLane* pLine{};
	Grass* pFloor{};

	int map_size = road_data.Roads_Flags.size() - 10;
	int idx = 0;
	while (idx < map_size)
	{
		bool isGrass = road_data.Roads_Flags[idx];

		if (isGrass == GRASS) {
			pFloor = new Grass{ cube_vertex_array_normal, floor_color, idx, false }; // 잔디 1칸 설치
			gVec.push_back(pFloor);
		}
		else if (isGrass == ROAD) {
			bool carDir = road_data.Dir_Flags[idx];

			pRoad = new Road{ cube_vertex_array_normal, floor_color, idx, carDir }; // 정점, 색, 지형 인덱스( 몇 번째 도로인지 ), 차 방향 인수로 전달
			gVec.push_back(pRoad);

			pLine = new RoadLane{ cube_vertex_array_normal, floor_color, 3 , idx }; // 도로 흰색 라인 
			gVec.push_back(pLine);
		}

		++idx;
	}

	for (int i{}; i < 10; ++i) 
	{
		pFloor = new Grass{ cube_vertex_array_normal, floor_color, i + idx ,true }; 
		gVec.push_back(pFloor); 
	}
}

void SetCars(INIT_DATA_C car_data)
{
	int cnt{};
	int size{ int(gVec.size()) };
	
	for (int i{}; i < size; ++i)
	{
		if (dynamic_cast<Road*>(gVec[i]) != nullptr)
		{
			float speed = car_data.Cars_Velocity[cnt];
			float R = car_data.Cars_Color_RGB[cnt][(int)RGB::R];
			float G = car_data.Cars_Color_RGB[cnt][(int)RGB::G];
			float B = car_data.Cars_Color_RGB[cnt][(int)RGB::B];
			
			cnt++;
			gVec.at(i)->CreateCar(speed,R,G,B);

		}
	}
	
	cout << "Cars Count: " << cnt << '\n';
}

void SetWoods(INIT_DATA_W wood_data)
{
	int grass_cnt{};

	for (int i{}; i < gVec.size(); ++i) 
	{
		if (dynamic_cast<Grass*>(gVec[i]) != nullptr && !gVec.at(i)->IsFinalGrass())
		{
			for (int j = 1; j < 13; ++j) {
				bool should_place_wood = wood_data.Woods_Flags[grass_cnt][j-1];

				if (should_place_wood) {
					Wood* pWood = new Wood{ cube_vertex_array_normal, floor_color, j , gVec[i]->GetZindex() };
					WoodLeaf_1* pGrass1 = new WoodLeaf_1{ cube_vertex_array_normal, floor_color, j , gVec[i]->GetZindex() };
					WoodLeaf_2* pGrass2 = new WoodLeaf_2{ cube_vertex_array_normal, floor_color, j , gVec[i]->GetZindex() };
					WoodLeaf_3* pGrass3 = new WoodLeaf_3{ cube_vertex_array_normal, floor_color, j , gVec[i]->GetZindex() }; // grass의 inum필요 

					gVec.push_back(pWood);
					gVec.push_back(pGrass1);
					gVec.push_back(pGrass2);
					gVec.push_back(pGrass3);
				}
			}
			grass_cnt++;
		}
	}
}

void SetRoadLane()
{
	int cnt{};
	int size{ int(gVec.size()) };
	for (int i{}; i < size; ++i)
	{
		if (dynamic_cast<Road*>(gVec[i]) != nullptr)
		{
			cnt++;
			gVec.at(i)->CreateLane();
		}
	}
	cout << "RoadLane Count: " << cnt << '\n';
}

void SetMother()
{
	int size{ int(gVec.size()) };

	for (int i{}; i < size; ++i)
	{
		if (dynamic_cast<Grass*>(gVec[i]) != nullptr && !gVec.at(i)->IsFinalGrass()) 
		{ 
			g_max_z = gVec[i]->GetZindex(); // 맨 마지막 잔디의 인덱스를 얻기 -> 엄마닭의 위치 초기화를 위함
		}
	}

	MotherBody* body = new MotherBody{ cube_vertex_array_normal, cube_color ,g_max_z + 5 }; // 0
	gVec.push_back(body);

	MotherHead* head = new MotherHead{ cube_vertex_array_normal, cube_color,g_max_z + 5 }; // 1
	gVec.push_back(head);
	MotherMouse* mouse = new MotherMouse{ cube_vertex_array_normal, cube_color,g_max_z + 5 }; // 2
	gVec.push_back(mouse);
	MotherEyes* eyes = new MotherEyes{ cube_vertex_array_normal, cube_color ,g_max_z + 5 }; // 3
	gVec.push_back(eyes);

	MotherLeftArm* Larm = new MotherLeftArm{ cube_vertex_array_normal, cube_color,g_max_z + 5 }; // 4
	gVec.push_back(Larm);
	MotherRightArm* Rarm = new MotherRightArm{ cube_vertex_array_normal, cube_color ,g_max_z +5 }; // 5
	gVec.push_back(Rarm);

	MotherLeftLeg* Lleg = new MotherLeftLeg{ cube_vertex_array_normal, cube_color ,g_max_z + 5 }; // 6
	gVec.push_back(Lleg);
	MotherRightLeg* Rleg = new MotherRightLeg{ cube_vertex_array_normal, cube_color,g_max_z +5 }; // 7
	gVec.push_back(Rleg);

}

//===========================================================================================

void gVecClear()
{
	// 새로 시작하기 위해 객체 지우기
	for (auto& obj : gVec) {
		delete obj;
	}
	gVec.clear(); 
}

void gVecDraw()
{
	for (auto& obj : gVec) {
		obj->DrawObject();
	}
}

void gEnemyVecDraw()
{
	if (gIsReach == true) return;
	// 게임 끝난 시점이면 적 대신 플레이어만 그리기

	for (auto& obj : gEnemyVec) {
		obj->DrawObject();
	}
}

void gVecUpdate(float deltatime)
{
	for (auto& obj : gVec) {
		obj->Update(deltatime);
	}

	// Player의 위치, 방향을 업데이트 한다 -> GameManager에서 Json으로 묶어서 Send하게 된다
	g_lock.lock();
	gGameManager.m_playerData[(int)ID::ME].Player_Pos_x = gVec[0]->GetXpos();
	gGameManager.m_playerData[(int)ID::ME].Player_Pos_y = gVec[0]->GetYpos();
	gGameManager.m_playerData[(int)ID::ME].Player_Pos_z = gVec[0]->GetZpos();
	gGameManager.m_playerData[(int)ID::ME].Player_FaceDegree = (gVec[0]->GetChickenFaceDegree());
	//cout << gGameManager.m_playerData[(int)ID::ME].Player_Face << endl;
	
	g_lock.unlock();

}

void gEnemyVecUpdate(float deltatime)
{
	EnemyChickenUpdatePos(deltatime);

	EnemyChickenHandling(deltatime);
}

//===========================================================================================

void SetOffAllofToggle()
{
	for (auto& toggle_element : gToggle)
		toggle_element = OFF;
}

void SetOffGlobalDir()
{
	gChickenDir[0] = false;
	gChickenDir[1] = false;
	gChickenDir[2] = false;
	gChickenDir[3] = false;
}

void SetInitToggle()
{
	gToggle[(int)Toggle::Perpective] = Third;
	SetLightToggle();
}

void SetLightToggle()
{
	unsigned int light_on = glGetUniformLocation(gShaderProgramID, "u_lightOn"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	if (gToggle[(int)Toggle::Light] == OFF) {
		gToggle[(int)Toggle::Light] = ON;
		glUniform1i(light_on, ON);
		cout << "light : ON\n";
	}
	else if (gToggle[(int)Toggle::Light] == ON) {
		gToggle[(int)Toggle::Light] = OFF;
		glUniform1i(light_on, OFF);
		cout << "light : OFF\n";
	}
}

void SetPerspectiveToggle()
{
	if (gToggle[(int)Toggle::Perpective] == Third) {
		gToggle[(int)Toggle::Perpective] = One;
		cout << "First Person Camera : ON\n";
	}
	else if (gToggle[(int)Toggle::Perpective] == One) {
		gToggle[(int)Toggle::Perpective] = Third;
		cout << "Third Person Camera : ON\n";
	}
}

void SetNearFarCameraToggle()
{
	if (gToggle[(int)Toggle::NearFar] == Near) {
		gToggle[(int)Toggle::NearFar] = Far;
		cout << "Far Third Person Camera : ON\n";
	}
	else if (gToggle[(int)Toggle::NearFar] == Far) {
		gToggle[(int)Toggle::NearFar] = Near;
		cout << "Near Third Person Camera : ON\n";
	}
}

//===========================================================================================

void ChickenJump()
{
	gVec.at(0)->ChickenJump();
}

void ChickenRun()
{
	for (int i{}; i < 8; ++i)
	{
		gVec.at(i)->SetChickenRunSpeed();
	}
}

void ChickenWalk()
{
	for (int i{}; i < 8; ++i)
	{
		gVec.at(i)->SetChickenWalkSpeed();
	}
}

void SetChickenFaceDir(unsigned char key)
{
	ChickenBody* body = dynamic_cast<ChickenBody*>(gVec[0]);
	body->SetChickenFaceDir(key);
	ChickenHead* head = dynamic_cast<ChickenHead*>(gVec[1]);
	head->SetChickenFaceDir(key);
	ChickenMouse* mouse = dynamic_cast<ChickenMouse*>(gVec[2]);
	mouse->SetChickenFaceDir(key);
	ChickenEyes* eyes = dynamic_cast<ChickenEyes*>(gVec[3]);
	eyes->SetChickenFaceDir(key);

	ChickenLeftArm* Larm = dynamic_cast<ChickenLeftArm*>(gVec[4]);
	Larm->SetChickenFaceDir(key);

	ChickenRightArm* Rarm = dynamic_cast<ChickenRightArm*>(gVec[5]);
	Rarm->SetChickenFaceDir(key);

	ChickenLeftLeg* Lleg = dynamic_cast<ChickenLeftLeg*>(gVec[6]);
	Lleg->SetChickenFaceDir(key);

	ChickenRightLeg* Rleg = dynamic_cast<ChickenRightLeg*>(gVec[7]);
	Rleg->SetChickenFaceDir(key);

	gCamera.SetCameraFaceDir(key);
}

void ChickenHandling(float deltatime)
{
	ChickenLeftArm* Larm = dynamic_cast<ChickenLeftArm*>(gVec[4]);
	Larm->handling();

	ChickenRightArm* Rarm = dynamic_cast<ChickenRightArm*>(gVec[5]);
	Rarm->handling();

	ChickenLeftLeg* Lleg = dynamic_cast<ChickenLeftLeg*>(gVec[6]);
	Lleg->handling();

	ChickenRightLeg* Rleg = dynamic_cast<ChickenRightLeg*>(gVec[7]);
	Rleg->handling();
}

void ChickenMove(float deltatime)
{
	ChickenBody* body = dynamic_cast<ChickenBody*>(gVec[0]);
	body->Walk(deltatime);
	ChickenHead* head = dynamic_cast<ChickenHead*>(gVec[1]);
	head->Walk(deltatime);
	ChickenMouse* mouse = dynamic_cast<ChickenMouse*>(gVec[2]);
	mouse->Walk(deltatime);
	ChickenEyes* eyes = dynamic_cast<ChickenEyes*>(gVec[3]);
	eyes->Walk(deltatime);

	ChickenLeftArm* Larm = dynamic_cast<ChickenLeftArm*>(gVec[4]);
	Larm->Walk(deltatime);
	ChickenRightArm* Rarm = dynamic_cast<ChickenRightArm*>(gVec[5]);
	Rarm->Walk(deltatime);
	ChickenLeftLeg* Lleg = dynamic_cast<ChickenLeftLeg*>(gVec[6]);
	Lleg->Walk(deltatime);
	ChickenRightLeg* Rleg = dynamic_cast<ChickenRightLeg*>(gVec[7]);
	Rleg->Walk(deltatime);

}

//===========================================================================================

void EnemyChickenHandling(float deltatime)  
{
	ChickenLeftArm* Larm = dynamic_cast<ChickenLeftArm*>(gEnemyVec[4]);
	Larm->handling();

	ChickenRightArm* Rarm = dynamic_cast<ChickenRightArm*>(gEnemyVec[5]);
	Rarm->handling();

	ChickenLeftLeg* Lleg = dynamic_cast<ChickenLeftLeg*>(gEnemyVec[6]);
	Lleg->handling();

	ChickenRightLeg* Rleg = dynamic_cast<ChickenRightLeg*>(gEnemyVec[7]);
	Rleg->handling();
}

extern std::atomic<unsigned int> render_counter;
void EnemyChickenUpdatePos(float deltatime)
{
	UPDATE_DATA other_player{};
	other_player = gGameManager.m_playerData[(int)ID::ENERMY];

	float dir = other_player.Player_FaceDegree;

	for (auto& obj : gEnemyVec) {
		obj->SetEnemyFace(dir);
	}

	float enemy_body_x = other_player.Player_Pos_x;
	float enemy_body_y = other_player.Player_Pos_y;
	float enemy_body_z = other_player.Player_Pos_z;

#if 1
	if (Interpolated == true) {
		if (gGameManager.m_otherPD_queue.Size() >= 2) {
			other_player = gGameManager.m_otherPD_queue.Front();
			enemy_body_x = other_player.Player_Pos_x;
			enemy_body_y = other_player.Player_Pos_y;
			enemy_body_z = other_player.Player_Pos_z;

			UPDATE_DATA previous_player = gGameManager.m_otherPD_queue.Front();

			UPDATE_DATA current_player = gGameManager.m_otherPD_queue.Second();

			float alpha = (15.0f / (1000.0f / PACKET_FREQ)) * render_counter * deltatime * 12 * (30.f / PACKET_FREQ);	// WiFi Delay and HardWare Performance

			float interpolated_x = alpha * (current_player.Player_Pos_x - previous_player.Player_Pos_x);
			float interpolated_y = alpha * (current_player.Player_Pos_y - previous_player.Player_Pos_y);
			float interpolated_z = alpha * (current_player.Player_Pos_z - previous_player.Player_Pos_z);

			enemy_body_x += interpolated_x;
			enemy_body_y += interpolated_y;
			enemy_body_z += interpolated_z;

			render_counter++;
		}
	}
#endif

	enum chicken_model { body = 0, head, mouse, eyes, leftarm, rightarm, leftleg, rightleg };

	gEnemyVec[body]->SetXpos(enemy_body_x);
	gEnemyVec[body]->SetYpos(enemy_body_y);
	gEnemyVec[body]->SetZpos(enemy_body_z);

	gEnemyVec[head]->SetXpos(enemy_body_x);
	gEnemyVec[head]->SetYpos(enemy_body_y + 0.01);
	gEnemyVec[head]->SetZpos(enemy_body_z);

	gEnemyVec[mouse]->SetXpos(enemy_body_x);
	gEnemyVec[mouse]->SetYpos(enemy_body_y + 0.01);
	gEnemyVec[mouse]->SetZpos(enemy_body_z);

	gEnemyVec[eyes]->SetXpos(enemy_body_x);
	gEnemyVec[eyes]->SetYpos(enemy_body_y + 0.0105);
	gEnemyVec[eyes]->SetZpos(enemy_body_z);

	gEnemyVec[leftarm]->SetXpos(enemy_body_x);
	gEnemyVec[leftarm]->SetYpos(enemy_body_y - 0.0005f);
	gEnemyVec[leftarm]->SetZpos(enemy_body_z);

	gEnemyVec[rightarm]->SetXpos(enemy_body_x);
	gEnemyVec[rightarm]->SetYpos(enemy_body_y + 0.0005f);
	gEnemyVec[rightarm]->SetZpos(enemy_body_z);

	gEnemyVec[leftleg]->SetXpos(enemy_body_x);
	gEnemyVec[leftleg]->SetYpos(enemy_body_y - 0.005f);
	gEnemyVec[leftleg]->SetZpos(enemy_body_z);

	gEnemyVec[rightleg]->SetXpos(enemy_body_x);
	gEnemyVec[rightleg]->SetYpos(enemy_body_y - 0.005f);
	gEnemyVec[rightleg]->SetZpos(enemy_body_z);
}

//===========================================================================================

#endif

