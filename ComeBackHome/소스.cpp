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
#include "Border.h"
#include "Tree.h"
#include "Family.h"


//===========================================================================================

void make_shaderProgram()
{
	make_vertexShaders();
	make_fragmentShaders();
	gShaderProgramID = glCreateProgram();
	glAttachShader(gShaderProgramID, gVertexShader);
	glAttachShader(gShaderProgramID, gFragmentShader);
	glLinkProgram(gShaderProgramID);
	glDeleteShader(gVertexShader);
	glDeleteShader(gFragmentShader);
	glUseProgram(gShaderProgramID);
}

void make_vertexShaders()
{
	gVertexSource = filetobuf("vertex2.glsl");
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

void make_fragmentShaders()
{
	gFragmentSource = filetobuf("fragment2.glsl");
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
	if (gToggle[(int)Toggle::Perpective] == Third)
		gCamera.setViewTransform_firstVeiwPort();
	else if (gToggle[(int)Toggle::Perpective] == One)
		gCamera.setViewTransform_firstVeiwPort_One();
	gLight->update();

	gVecDraw();
}

void chicken_viewport()
{
	int g_window_w = gWidth;
	int g_window_h = gHeight;

	glViewport(gWidth - 150, gHeight - 130, 140, 120);

	gCamera.PerspectiveProjection();
	gCamera.setViewTransform_secondVeiwPort();
	gLight->update();

	gVecDraw();
}

void border_viewport()
{
	int g_window_w = gWidth;
	int g_window_h = gHeight;

	gCamera.PerspectiveProjection();
	gCamera.setViewTransform_thirdVeiwPort();
	gLight->initLight();

	glViewport(gWidth - 150 - 10, gHeight - 130 - 10, 140 + 20, 130 + 20);

	gBorder->DrawObject();
}

GLvoid DrawScene()
{
	glClearColor(0.5294f, 0.8078f, 0.9804f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ���� ���� Ŭ����

	// TODO: ���⼭ ������ send/recv, �ϴ� �� �����Ӹ��� �������, �ƴϸ� 1�ʿ� 30������?
	// �ϴ� ���� : �������� TickCount �����ؼ� TickCount % 30 == 0 ���� �� send/recv

	main_viewport();
	border_viewport();
	chicken_viewport();

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

	gVecUpdate();
	glutPostRedisplay();				//ȭ�� �����
	glutTimerFunc(10, TimerFunction, 1); // �ٽ� ȣ�� 
}

GLvoid KeyUpboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		if (gIsMovingChicken) {
			gIsMovingChicken = OFF;
			SetChickenFaceDir(STOP);
			gCamera.setFaceDir(STOP);
			SetOffGlobalDir();
		}
		break;

	case 's':
		if (gIsMovingChicken) {
			gIsMovingChicken = OFF;
			SetChickenFaceDir(STOP);
			gCamera.setFaceDir(STOP);
			SetOffGlobalDir();
		}
		break;

	case 'a':
		if (gIsMovingChicken) {
			gIsMovingChicken = OFF;
			SetChickenFaceDir(STOP);
			gCamera.setFaceDir(STOP);
			SetOffGlobalDir();
		}
		break;

	case 'd':
		if (gIsMovingChicken) {
			gIsMovingChicken = OFF;
			SetChickenFaceDir(STOP);
			gCamera.setFaceDir(STOP);
			SetOffGlobalDir();
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
		gVec.at(0)->changeboll();
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
	case 'j':
		ChickenJump();
		break;
	case 'p': case'P':
		SetPerspectiveToggle();
		break;
	

		// ---------- ����  ----------
	case 'r': case'R':
		SetOffAllofToggle(); 
		SetInitToggle();
		gCamera.initCamera();
		gLight->initLight();
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
	SetGround(); // ���� + �ܵ� �����
	SetCars(); // �� �����
	SetWoods(); // ���� �����
	SetRoadLane(); // ���� ��� ���� �����
	SetMother(); // �������� ���� �� �����
	
	//tagWall* pWall = new tagWall{ cube_vertex_array_normal, floor_color}; // 9
	//gVec.push_back(pWall);
}

void SetChicken()
{
	// �÷����� ���ΰ� �� �����  
	tagBody* body = new tagBody{ cube_vertex_array_normal, cube_color }; // 0 - ��
	gVec.push_back(body);
	tagHead* head = new tagHead{ cube_vertex_array_normal, cube_color }; // 1 - �Ӹ�
	gVec.push_back(head);
	tagMouse* mouse = new tagMouse{ cube_vertex_array_normal, cube_color }; // 2 - �ֵ���
	gVec.push_back(mouse);
	tagEyes* eyes = new tagEyes{ cube_vertex_array_normal, cube_color }; // 3 - ��
	gVec.push_back(eyes);

	tagLeftArm* Larm = new tagLeftArm{ cube_vertex_array_normal, cube_color }; // 4 - ����
	gVec.push_back(Larm);
	tagRightArm* Rarm = new tagRightArm{ cube_vertex_array_normal, cube_color }; // 5 - ������
	gVec.push_back(Rarm);

	tagLeftLeg* Lleg = new tagLeftLeg{ cube_vertex_array_normal, cube_color }; // 6 - �޴ٸ�
	gVec.push_back(Lleg);
	tagRightLeg* Rleg = new tagRightLeg{ cube_vertex_array_normal, cube_color }; // 7 - �����ٸ�
	gVec.push_back(Rleg);
}

void SetGround()
{
	// �� ����� ( �ܵ�, ���� )

	int count{};
	tagRoad* pRoad{};
	tagRoadLane* pLine{};
	tagGrass* pFloor{};
	int idx{ 0 };
	pFloor = new tagGrass{ cube_vertex_array_normal, floor_color, idx ,false };
	gVec.push_back(pFloor);
	++idx;

	while(idx < 150) {
		// ���� ������ŭ ���θ� �������� ����� �ܵ� ��ĭ ����� �ٽ� ���� ������ ���� ����� ( ���� 3ĭ -> �ܵ� 1ĭ -> ���� 5ĭ -> �ܵ� 1ĭ .. )
		int cnt{ gRoadSet(gRandomEngine) };

		for (int j = 0; j < cnt; ++j) {
			count++;
			
			pRoad = new tagRoad{ cube_vertex_array_normal, floor_color, j+idx}; // ����, ��, ���� �ε���( �� ��° �������� ) �μ��� ����
			gVec.push_back(pRoad);
			
			pLine = new tagRoadLane{ cube_vertex_array_normal, floor_color, 3 ,j + idx }; // ���� ��� ���� 
			gVec.push_back(pLine); 
		}
		idx += cnt; // ���� ������ŭ idx ����

		pFloor = new tagGrass{ cube_vertex_array_normal, floor_color, idx,false }; // �ܵ� 1ĭ ��ġ
		gVec.push_back(pFloor);
		++idx;
	}

	pFloor = new tagGrass{ cube_vertex_array_normal, floor_color, idx ,true};
	gVec.push_back(pFloor);
	
	for (int i{}; i < 10; ++i)
	{
		pFloor = new tagGrass{ cube_vertex_array_normal, floor_color, i+idx ,true };
		gVec.push_back(pFloor);
	}
	// ���� ���� �ܵ� ��ġ
}

void SetCars()
{
	int cnt{};
	int size{ int(gVec.size()) };
	for (int i{}; i < size; ++i)
	{
		if (dynamic_cast<tagRoad*>(gVec[i]) != nullptr)
		{
			cnt++;
			gVec.at(i)->make_car();
		}
	}
	cout << "�� ����: " << cnt << '\n';
}

void SetWoods()
{
	int cnt{};
	int size{ int(gVec.size()) };



	for (int i{}; i < size; ++i)
	{
		if (dynamic_cast<tagGrass*>(gVec[i]) != nullptr && !gVec.at(i)->Is_final())
		{
			for (int j = 1; j < 13; ++j) {
				bool TF{ (bool)gBoolUniform(gRandomEngine) };

				if (TF) {
					tagWood* pWood = new tagWood{ cube_vertex_array_normal, floor_color, j , gVec[i]->Get_zidx() };
					tagLeafone* pGrass1 = new tagLeafone{ cube_vertex_array_normal, floor_color, j , gVec[i]->Get_zidx() };
					tagLeaftwo* pGrass2 = new tagLeaftwo{ cube_vertex_array_normal, floor_color, j , gVec[i]->Get_zidx() };
					tagLeafthree* pGrass3 = new tagLeafthree{ cube_vertex_array_normal, floor_color, j , gVec[i]->Get_zidx() }; // grass�� inum�ʿ� 

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
		if (dynamic_cast<tagRoad*>(gVec[i]) != nullptr)
		{
			cnt++;
			gVec.at(i)->make_line();
		}
	}
	cout << "���� ����: " << cnt << '\n';
}

void SetMother()
{
	int size{ int(gVec.size()) };

	for (int i{}; i < size; ++i)
	{
		if (dynamic_cast<tagGrass*>(gVec[i]) != nullptr && !gVec.at(i)->Is_final()) 
		{ 
			g_max_z = gVec[i]->Get_zidx(); // �� ������ �ܵ��� �ε����� ��� -> �������� ��ġ �ʱ�ȭ�� ����
		}
	}

	tagBodyMom* body = new tagBodyMom{ cube_vertex_array_normal, cube_color ,g_max_z + 5 }; // 0
	gVec.push_back(body);
	tagHeadMom* head = new tagHeadMom{ cube_vertex_array_normal, cube_color,g_max_z + 5 }; // 1
	gVec.push_back(head);
	tagMouseMom* mouse = new tagMouseMom{ cube_vertex_array_normal, cube_color,g_max_z + 5 }; // 2
	gVec.push_back(mouse);
	tagEyesMom* eyes = new tagEyesMom{ cube_vertex_array_normal, cube_color ,g_max_z + 5 }; // 3
	gVec.push_back(eyes);
	tagLeftArmMom* Larm = new tagLeftArmMom{ cube_vertex_array_normal, cube_color,g_max_z + 5 }; // 4
	gVec.push_back(Larm);
	tagRightArmMom* Rarm = new tagRightArmMom{ cube_vertex_array_normal, cube_color ,g_max_z +5 }; // 5
	gVec.push_back(Rarm);
	tagLeftLegMom* Lleg = new tagLeftLegMom{ cube_vertex_array_normal, cube_color ,g_max_z + 5 }; // 6
	gVec.push_back(Lleg);
	tagRightLegMom* Rleg = new tagRightLegMom{ cube_vertex_array_normal, cube_color,g_max_z +5 }; // 7
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

void gVecUpdate()
{
	for (auto& obj : gVec) {
		obj->update();
	}
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
	gVec.at(0)->jump();
}

void ChickenRun()
{
	for (int i{}; i < 8; ++i)
	{
		gVec.at(i)->upvelo();
	}
}

void ChickenWalk()
{
	for (int i{}; i < 8; ++i)
	{
		gVec.at(i)->downvelo();
	}
}

//===========================================================================================


#endif

