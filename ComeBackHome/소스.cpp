#if 1
#include "usingInclude.h"
#include "�ҽ�.h"
#include "�ҽ�1.h"
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
GameManager GM;
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
		std::cout << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
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
		std::cout << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
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
		std::cout << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
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
		std::cout << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
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

	cout << "w/a/s/d: ���� �ȴ´�.\n";
	cout << "t/T: ���� ���� �ѱ�\n";
	cout << "Shift : �� �ӵ��� ��������.\n";
	cout << "j/J : �����Ѵ�. ���� �Ѿ �� �ִ�. \n";
	cout << "p/P : 3��Ī/1��Ī ī�޶� ��ȯ\n";
	cout << "o/O : ���� 3��Ī ī�޶� ��ȯ\n";
	cout << "m/M : �浹 ���� ���\n";
	cout << "u/U : �� �̵��ӵ� ���� ���\n";
	cout << "i/I : �� �̵��ӵ� ���� �϶�\n";

	cout << "q/Q : ���α׷� ����\n";

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
		// 3��Ī
		gCamera.SetViewTransform_ThirdPersonViewport();
	}
	else if (gToggle[(int)Toggle::Perpective] == One) {
		// 1��Ī
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
	// ġŲ ���� ī�޶�
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
	// Border ī�޶�
	gCamera.SetViewTransform_BorderViewport();
	gLight->InitLight();

	glViewport(gWidth - 150 - 10, gHeight - 130 - 10, 140 + 20, 130 + 20);

	gBorder->DrawObject();
}

GLvoid DrawScene()
{
	glClearColor(0.5294f, 0.8078f, 0.9804f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ���� ���� Ŭ����

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
	gCamera.Move();
	gTimer.update();
	float deltatime = gTimer.getDeltaTime();

	gVecUpdate(deltatime);
	gEnemyVecUpdate(deltatime);

	glutPostRedisplay();				//ȭ�� �����
	glutTimerFunc(10, TimerFunction, 1); // �ٽ� ȣ�� 
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

			SOCKET sock = GM.WaitForOtherPlayer();
			std::thread networkThread(&GameManager::UpdateWorld, &GM, sock);
			networkThread.detach();

			GAME_START = true;
			glUseProgram(gShaderProgramID);
			SetOffAllofToggle();
			SetInitToggle();
			gCamera.InitCamera();
			gLight->InitLight();
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
		// ���α׷� ����
	case 'q': case 'Q':
		glutLeaveMainLoop();
		break;
	case 'j': case 'J':
		ChickenJump();
		break;
	case 'p': case'P':
		SetPerspectiveToggle();
		break;
	

		// ---------- ����  ----------
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

void SetgVec() // ����ü, ���ü ó�� ��ġ - �� �� 10��
{
	SetChicken();
	//SetGround(); // ���� + �ܵ� �����
	//SetCars(); // �� �����
	//SetWoods(); // ���� �����
	//SetRoadLane(); // ���� ��� ���� �����
	//SetMother(); // �������� ���� �� �����
	
	//tagWall* pWall = new tagWall{ cube_vertex_array_normal, floor_color}; // 9
	//gVec.push_back(pWall);
}

void SetgEnemyVec()
{
	ChickenBody* body = new ChickenBody{ cube_vertex_array_normal, cube_color }; // 0 - ��
	gEnemyVec.push_back(body);
	ChickenHead* head = new ChickenHead{ cube_vertex_array_normal, cube_color }; // 1 - �Ӹ�
	gEnemyVec.push_back(head);
	ChickenMouse* mouse = new ChickenMouse{ cube_vertex_array_normal, cube_color }; // 2 - �ֵ���
	gEnemyVec.push_back(mouse);
	ChickenEyes* eyes = new ChickenEyes{ cube_vertex_array_normal, cube_color }; // 3 - ��
	gEnemyVec.push_back(eyes);

	ChickenLeftArm* Larm = new ChickenLeftArm{ cube_vertex_array_normal, cube_color }; // 4 - ����
	gEnemyVec.push_back(Larm);
	ChickenRightArm* Rarm = new ChickenRightArm{ cube_vertex_array_normal, cube_color }; // 5 - ������
	gEnemyVec.push_back(Rarm);

	ChickenLeftLeg* Lleg = new ChickenLeftLeg{ cube_vertex_array_normal, cube_color }; // 6 - �޴ٸ�
	gEnemyVec.push_back(Lleg);
	ChickenRightLeg* Rleg = new ChickenRightLeg{ cube_vertex_array_normal, cube_color }; // 7 - �����ٸ�
	gEnemyVec.push_back(Rleg);
}

void SetChicken()
{
	// �÷����� ���ΰ� �� �����
	ChickenBody* body = new ChickenBody{ cube_vertex_array_normal, cube_color }; // 0 - ��
	gVec.push_back(body);
	ChickenHead* head = new ChickenHead{ cube_vertex_array_normal, cube_color }; // 1 - �Ӹ�
	gVec.push_back(head);
	ChickenMouse* mouse = new ChickenMouse{ cube_vertex_array_normal, cube_color }; // 2 - �ֵ���
	gVec.push_back(mouse);
	ChickenEyes* eyes = new ChickenEyes{ cube_vertex_array_normal, cube_color }; // 3 - ��
	gVec.push_back(eyes);

	ChickenLeftArm* Larm = new ChickenLeftArm{ cube_vertex_array_normal, cube_color }; // 4 - ����
	gVec.push_back(Larm);
	ChickenRightArm* Rarm = new ChickenRightArm{ cube_vertex_array_normal, cube_color }; // 5 - ������
	gVec.push_back(Rarm);

	ChickenLeftLeg* Lleg = new ChickenLeftLeg{ cube_vertex_array_normal, cube_color }; // 6 - �޴ٸ�
	gVec.push_back(Lleg);
	ChickenRightLeg* Rleg = new ChickenRightLeg{ cube_vertex_array_normal, cube_color }; // 7 - �����ٸ�
	gVec.push_back(Rleg);
}

void SetGround(INIT_DATA_R road_data)
{
	// �� ����� ( �ܵ�, ���� )

	//Road* pRoad{};
	//RoadLane* pLine{};
	//Grass* pFloor{};

	//int map_size = road_data.Roads_Flags.size();
	//int idx = 0;
	//while (idx < map_size)
	//{
	//	bool isGrass = road_data.Roads_Flags[idx];
	//	bool carDir = road_data.Dir_Flags[idx];

	//	if (isGrass == GRASS) {
	//		//bool finalGrass = (idx >= map_size - 11);
	//		pFloor = new Grass{ cube_vertex_array_normal, floor_color, idx, false }; // �ܵ� 1ĭ ��ġ
	//		gVec.push_back(pFloor);
	//	}
	//	else if (isGrass == ROAD) {
	//		pRoad = new Road{ cube_vertex_array_normal, floor_color, idx, carDir }; // ����, ��, ���� �ε���( �� ��° �������� ), �� ���� �μ��� ����
	//		gVec.push_back(pRoad);

	//		pLine = new RoadLane{ cube_vertex_array_normal, floor_color, 3 , idx }; // ���� ��� ���� 
	//		gVec.push_back(pLine);
	//	}

	//	++idx;
	//}

	int count{};
	Road* pRoad{};
	RoadLane* pLine{};
	Grass* pFloor{};
	int idx{ 0 };
	pFloor = new Grass{ cube_vertex_array_normal, floor_color, idx ,false };
	gVec.push_back(pFloor);
	++idx;

	while(idx < 150) {
		// ���� ������ŭ ���θ� �������� ����� �ܵ� ��ĭ ����� �ٽ� ���� ������ ���� ����� ( ���� 3ĭ -> �ܵ� 1ĭ -> ���� 5ĭ -> �ܵ� 1ĭ .. )
		int cnt{ gRoadSet(gRandomEngine) };

		for (int j = 0; j < cnt; ++j) {
			count++;
			
			bool carDir = gBoolUniform(gRandomEngine);
			pRoad = new Road{ cube_vertex_array_normal, floor_color, j+idx, carDir }; // ����, ��, ���� �ε���( �� ��° �������� ) �μ��� ����
			gVec.push_back(pRoad);
			
			pLine = new RoadLane{ cube_vertex_array_normal, floor_color, 3 ,j + idx }; // ���� ��� ���� 
			gVec.push_back(pLine); 
		}
		idx += cnt; // ���� ������ŭ idx ����

		pFloor = new Grass{ cube_vertex_array_normal, floor_color, idx,false }; // �ܵ� 1ĭ ��ġ
		gVec.push_back(pFloor);
		++idx;
	}

	// true: ������ �ܵ� �� ǥ�� -> ���� ��ġX, ���� ��ġ( 1ĭ �ƴ� )
	pFloor = new Grass{ cube_vertex_array_normal, floor_color, idx ,true};
	gVec.push_back(pFloor);
	
	for (int i{}; i < 10; ++i)
	{
		pFloor = new Grass{ cube_vertex_array_normal, floor_color, i+idx ,true };
		gVec.push_back(pFloor);
	}
	// ���� ���� �ܵ� ��ġ
}

void SetCars(/*INIT_DATA_C car_data*/)
{
	int cnt{};
	int size{ int(gVec.size()) };
	for (int i{}; i < size; ++i)
	{
		if (dynamic_cast<Road*>(gVec[i]) != nullptr)
		{
			cnt++;
			gVec.at(i)->CreateCar();
		}
	}
	cout << "�� ����: " << cnt << '\n';
}

void SetWoods(INIT_DATA_W wood_data)
{
	int cnt{};
	int size{ int(gVec.size()) };


	for (int i{}; i < size; ++i)
	{
		if (dynamic_cast<Grass*>(gVec[i]) != nullptr && !gVec.at(i)->IsFinalGrass())
		{
			for (int j = 1; j < 13; ++j) {
				bool TF = wood_data.Woods_Flags[i][j-1];

				if (TF) {
					Wood* pWood = new Wood{ cube_vertex_array_normal, floor_color, j , gVec[i]->GetZindex() };
					WoodLeaf_1* pGrass1 = new WoodLeaf_1{ cube_vertex_array_normal, floor_color, j , gVec[i]->GetZindex() };
					WoodLeaf_2* pGrass2 = new WoodLeaf_2{ cube_vertex_array_normal, floor_color, j , gVec[i]->GetZindex() };
					WoodLeaf_3* pGrass3 = new WoodLeaf_3{ cube_vertex_array_normal, floor_color, j , gVec[i]->GetZindex() }; // grass�� inum�ʿ� 

					gVec.push_back(pWood);
					gVec.push_back(pGrass1);
					gVec.push_back(pGrass2);
					gVec.push_back(pGrass3);

					cnt++;
				}
			}

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
	cout << "���� ����: " << cnt << '\n';
}

void SetMother()
{
	int size{ int(gVec.size()) };

	for (int i{}; i < size; ++i)
	{
		if (dynamic_cast<Grass*>(gVec[i]) != nullptr && !gVec.at(i)->IsFinalGrass()) 
		{ 
			g_max_z = gVec[i]->GetZindex(); // �� ������ �ܵ��� �ε����� ��� -> �������� ��ġ �ʱ�ȭ�� ����
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
	// ���� �����ϱ� ���� ��ü �����
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
	unsigned int light_on = glGetUniformLocation(gShaderProgramID, "u_lightOn"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������

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
		cout << "1��Ī ī�޶� : ON\n";
	}
	else if (gToggle[(int)Toggle::Perpective] == One) {
		gToggle[(int)Toggle::Perpective] = Third;
		cout << "3��Ī ī�޶� : ON\n";
	}
}

void SetNearFarCameraToggle()
{
	if (gToggle[(int)Toggle::NearFar] == Near) {
		gToggle[(int)Toggle::NearFar] = Far;
		cout << "�� 3��Ī ī�޶� : ON\n";
	}
	else if (gToggle[(int)Toggle::NearFar] == Far) {
		gToggle[(int)Toggle::NearFar] = Near;
		cout << "����� 3��Ī ī�޶� : ON\n";
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

