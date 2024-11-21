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

UI gPlaybutton;
GameManager gGameManager;
bool GAME_START = false;

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

	if (GAME_START == false)
		gPlaybutton.Render();
	else {
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
		
		gVecUpdate(deltatime);
		gEnemyVecUpdate(deltatime);

	}
	glutPostRedisplay();				//화면 재출력
	glutTimerFunc(10, TimerFunction, 1); // 다시 호출 
}

GLvoid KeyUpboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':case 'W':
		if (gIsMovingChicken) {
			gIsMovingChicken = OFF;
			SetChickenFaceDir(STOP);
			gCamera.SetCameraFaceDir(STOP);
			SetOffGlobalDir();
		}
		break;

	case 's':case 'S':
		if (gIsMovingChicken) {
			gIsMovingChicken = OFF;
			SetChickenFaceDir(STOP);
			gCamera.SetCameraFaceDir(STOP);
			SetOffGlobalDir();
		}
		break;

	case 'a':case 'A':
		if (gIsMovingChicken) {
			gIsMovingChicken = OFF;
			SetChickenFaceDir(STOP);
			gCamera.SetCameraFaceDir(STOP);
			SetOffGlobalDir();
		}
		break;

	case 'd':case 'D':
		if (gIsMovingChicken) {
			gIsMovingChicken = OFF;
			SetChickenFaceDir(STOP);
			gCamera.SetCameraFaceDir(STOP);
			SetOffGlobalDir();
		}
		break;
	default:
		if (GAME_START == false) {
			gPlaybutton.change_img("chick.jpg");
			gPlaybutton.resize(0.5, 0.5, 1.0);
			gPlaybutton.Render();

			SOCKET sock = gGameManager.WaitForOtherPlayer();
			std::thread networkThread(&GameManager::UpdateWorld, &gGameManager, sock);
			networkThread.detach();

			GAME_START = true;
			glUseProgram(gShaderProgramID);
			SetOffAllofToggle();
			SetInitToggle();
			gCamera.InitCamera();
			gLight->InitLight();

			glutTimerFunc(10, TimerFunction, 1);
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
		glutLeaveMainLoop();
		break;
	case 'j': case 'J':
		ChickenJump();
		break;
	case 'p': case'P':
		SetPerspectiveToggle();
		break;
	

		// ---------- 리셋  ----------
	case 'r': case'R':
		SetOffAllofToggle(); 
		SetInitToggle();
		gCamera.InitCamera();
		gLight->InitLight();
		gIsMovingChicken = OFF;
		gVecClear();
		SetgVec();
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

void SetgEnemyVec(bool my_id)
{
	bool other_id = !my_id;

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
	// 플레이할 주인공 닭 만들기
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
			//bool finalGrass = (idx >= map_size - 11);
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

#if 0
	int count{};
	Road* pRoad{};
	RoadLane* pLine{};
	Grass* pFloor{};
	int idx{ 0 };
	pFloor = new Grass{ cube_vertex_array_normal, floor_color, idx ,false };
	gVec.push_back(pFloor);
	++idx;

	while(idx < 150) {
		// 랜덤 개수만큼 도로를 연속으로 만들고 잔디 한칸 만들고 다시 랜덤 개수로 도로 만들기 ( 도로 3칸 -> 잔디 1칸 -> 도로 5칸 -> 잔디 1칸 .. )
		int cnt{ gRoadSet(gRandomEngine) };

		for (int j = 0; j < cnt; ++j) {
			count++;
			
			bool carDir = gBoolUniform(gRandomEngine);
			pRoad = new Road{ cube_vertex_array_normal, floor_color, j+idx, carDir }; // 정점, 색, 지형 인덱스( 몇 번째 도로인지 ) 인수로 전달
			gVec.push_back(pRoad);
			
			pLine = new RoadLane{ cube_vertex_array_normal, floor_color, 3 ,j + idx }; // 도로 흰색 라인 
			gVec.push_back(pLine); 
		}
		idx += cnt; // 도로 개수만큼 idx 증가

		pFloor = new Grass{ cube_vertex_array_normal, floor_color, idx,false }; // 잔디 1칸 설치
		gVec.push_back(pFloor);
		++idx;
	}

	// true: 마지막 잔디 땅 표시 -> 나무 설치X, 엄마 위치( 1칸 아님 )
	pFloor = new Grass{ cube_vertex_array_normal, floor_color, idx ,true};
	gVec.push_back(pFloor);
	
	for (int i{}; i < 10; ++i)
	{
		pFloor = new Grass{ cube_vertex_array_normal, floor_color, i+idx ,true };
		gVec.push_back(pFloor);
	}
	//// 도착 지점 잔디 설치
#endif
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
	
	cout << "차 개수: " << cnt << '\n';
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
	cout << "차선 개수: " << cnt << '\n';
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
	for (auto& obj : gEnemyVec) {
		obj->DrawObject();
	}
}

void gVecUpdate(float deltatime)
{
	for (auto& obj : gVec) {
		obj->Update(deltatime);
	}
}

void gEnemyVecUpdate(float deltatime)
{
	//for (auto& obj : gEnemyVec) {
	//	obj->Update(deltatime);
	//}

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
		cout << "1인칭 카메라 : ON\n";
	}
	else if (gToggle[(int)Toggle::Perpective] == One) {
		gToggle[(int)Toggle::Perpective] = Third;
		cout << "3인칭 카메라 : ON\n";
	}
}

void SetNearFarCameraToggle()
{
	if (gToggle[(int)Toggle::NearFar] == Near) {
		gToggle[(int)Toggle::NearFar] = Far;
		cout << "먼 3인칭 카메라 : ON\n";
	}
	else if (gToggle[(int)Toggle::NearFar] == Far) {
		gToggle[(int)Toggle::NearFar] = Near;
		cout << "가까운 3인칭 카메라 : ON\n";
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

//===========================================================================================


#endif

