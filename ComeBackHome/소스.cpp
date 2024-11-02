#if 1
#include "usingInclude.h"
#include "소스.h"
#include "소스1.h"
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
		std::cout << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
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

	cout << "w/a/s/d: 닭이 걷는다.\n";
	cout << "t/T: 조명 끄고 켜기\n";
	cout << "Shift : 닭 속도가 빨라진다.\n";
	cout << "j/J : 점프한다. 차를 넘어갈 수 있다. \n";
	cout << "p/P : 3인칭/1인칭 카메라 변환\n";
	cout << "o/O : 근접 3인칭 카메라 변환\n";
	cout << "m/M : 충돌 무시 토글\n";
	cout << "u/U : 닭 이동속도 대폭 상승\n";
	cout << "i/I : 닭 이동속도 대폭 하락\n";

	cout << "q/Q : 프로그램 종료\n";

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 깊이 버퍼 클리어

	// TODO: 여기서 서버와 send/recv, 일단 매 프레임마다 보내기로, 아니면 1초에 30번정도?
	// 일단 보류 : 전역으로 TickCount 설정해서 TickCount % 30 == 0 했을 때 send/recv

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
	glutPostRedisplay();				//화면 재출력
	glutTimerFunc(10, TimerFunction, 1); // 다시 호출 
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
		// 프로그램 종료
	case 'q': case 'Q':
		glutLeaveMainLoop();
		break;
	case 'j':
		ChickenJump();
		break;
	case 'p': case'P':
		SetPerspectiveToggle();
		break;
	

		// ---------- 리셋  ----------
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

void SetgVec() // 육면체, 사면체 처음 위치 - 면 총 10개
{
	SetChicken(); 
	SetGround(); // 도로 + 잔디 만들기
	SetCars(); // 차 만들기
	SetWoods(); // 나무 만들기
	SetRoadLane(); // 도로 흰색 라인 만들기
	SetMother(); // 도착지점 엄마 닭 만들기
	
	//tagWall* pWall = new tagWall{ cube_vertex_array_normal, floor_color}; // 9
	//gVec.push_back(pWall);
}

void SetChicken()
{
	// 플레이할 주인공 닭 만들기  
	tagBody* body = new tagBody{ cube_vertex_array_normal, cube_color }; // 0 - 몸
	gVec.push_back(body);
	tagHead* head = new tagHead{ cube_vertex_array_normal, cube_color }; // 1 - 머리
	gVec.push_back(head);
	tagMouse* mouse = new tagMouse{ cube_vertex_array_normal, cube_color }; // 2 - 주둥이
	gVec.push_back(mouse);
	tagEyes* eyes = new tagEyes{ cube_vertex_array_normal, cube_color }; // 3 - 눈
	gVec.push_back(eyes);

	tagLeftArm* Larm = new tagLeftArm{ cube_vertex_array_normal, cube_color }; // 4 - 왼팔
	gVec.push_back(Larm);
	tagRightArm* Rarm = new tagRightArm{ cube_vertex_array_normal, cube_color }; // 5 - 오른팔
	gVec.push_back(Rarm);

	tagLeftLeg* Lleg = new tagLeftLeg{ cube_vertex_array_normal, cube_color }; // 6 - 왼다리
	gVec.push_back(Lleg);
	tagRightLeg* Rleg = new tagRightLeg{ cube_vertex_array_normal, cube_color }; // 7 - 오른다리
	gVec.push_back(Rleg);
}

void SetGround()
{
	// 땅 만들기 ( 잔디, 도로 )

	int count{};
	tagRoad* pRoad{};
	tagRoadLane* pLine{};
	tagGrass* pFloor{};
	int idx{ 0 };
	pFloor = new tagGrass{ cube_vertex_array_normal, floor_color, idx ,false };
	gVec.push_back(pFloor);
	++idx;

	while(idx < 150) {
		// 랜덤 개수만큼 도로를 연속으로 만들고 잔디 한칸 만들고 다시 랜덤 개수로 도로 만들기 ( 도로 3칸 -> 잔디 1칸 -> 도로 5칸 -> 잔디 1칸 .. )
		int cnt{ gRoadSet(gRandomEngine) };

		for (int j = 0; j < cnt; ++j) {
			count++;
			
			pRoad = new tagRoad{ cube_vertex_array_normal, floor_color, j+idx}; // 정점, 색, 지형 인덱스( 몇 번째 도로인지 ) 인수로 전달
			gVec.push_back(pRoad);
			
			pLine = new tagRoadLane{ cube_vertex_array_normal, floor_color, 3 ,j + idx }; // 도로 흰색 라인 
			gVec.push_back(pLine); 
		}
		idx += cnt; // 도로 개수만큼 idx 증가

		pFloor = new tagGrass{ cube_vertex_array_normal, floor_color, idx,false }; // 잔디 1칸 설치
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
	// 도착 지점 잔디 설치
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
	cout << "차 개수: " << cnt << '\n';
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
					tagLeafthree* pGrass3 = new tagLeafthree{ cube_vertex_array_normal, floor_color, j , gVec[i]->Get_zidx() }; // grass의 inum필요 

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
	cout << "차선 개수: " << cnt << '\n';
}

void SetMother()
{
	int size{ int(gVec.size()) };

	for (int i{}; i < size; ++i)
	{
		if (dynamic_cast<tagGrass*>(gVec[i]) != nullptr && !gVec.at(i)->Is_final()) 
		{ 
			g_max_z = gVec[i]->Get_zidx(); // 맨 마지막 잔디의 인덱스를 얻기 -> 엄마닭의 위치 초기화를 위함
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

