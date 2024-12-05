#if 1
#include "usingInclude.h"
#include "Souce.h"
#include "Basis.h"
#include "Camera.h"
#include "Light.h"
#include "TimeManager.h"
#include "Border.h"
#include "UI.h"
#include "GameManager.h"

//===========================================================================================

GLchar* gVertexSource;
GLchar* gFragmentSource; //--- �ҽ��ڵ� ���� ����
GLuint gVertexShader;
GLuint gFragmentShader; //--- ���̴� ��ü
GLuint gShaderProgramID; //--- ���̴� ���α׷�

GLuint gUIVertexShader;
GLuint gUIFragmentShader; //--- ���̴� ��ü
GLuint gUIShaderProgramID;  // UI ���̴� ���α׷�

int gWidth{ 800 };
int gHeight{ 600 }; 
int g_max_z{ 1000 };
// ������ ũ��

bool gIsReach{};
vector<BasisComponent*> gVec; // --> ��� ��ü�� Basis �θ� Ŭ���� �����ͷ� �������� ����� �����ϱ� ���� ����
vector<BasisComponent*> gEnemyVec; // ��� �÷��̾� �������� ����

UI gPlaybutton;
GameManager gGameManager;
bool GAME_OVER = false;

bool gToggle[(int)Toggle::END]; // ��ɾ� ��� 

Camera gCamera; // ī�޶� Ŭ���� 
Light* gLight; // ���� Ŭ���� 
Border* gBorder; // ȭ�� ���� ��� ��ũ�� ��� Ŭ����
TimeManager gTimer{};

bool gIsMovingChicken{ OFF };
bool gChickenDir[4]{};

int seednum;

std::mt19937 gRandomEngine; // �˰��� + ��¥ ���� �õ� :: ��¥��¥ ���� ����
std::uniform_int_distribution<int> gBoolUniform{ 0,1 };
std::uniform_int_distribution<int> gRoadSet{ 5, 10 };
std::uniform_int_distribution<int> gCarspeed{1,3};
std::uniform_real_distribution<float> grandomcolor{0.f,1.f};
// ���� ��� ����� �� 

//===========================================================================================

void main(int argc, char** argv)
{
	std::string SERVERIP;
	std::cout << "Enter SERVERIP: ";
	std::cin >> SERVERIP;
	gGameManager.SERVERIP = (char*)SERVERIP.c_str();

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return;

	glutInit(&argc, argv);						  // GLUT �ʱ�ȭ 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // [���̰˻� depth test �߰�]���÷��� ��� ����
	glutInitWindowPosition(100, 100);			  // �������� ��ġ ���� 
	glutInitWindowSize(gWidth, gHeight);				  // �������� ũ�� ����
	glutCreateWindow("Come back Home");				  // ������ ���� (������ �̸�)

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {				  // GLEW �ʱ�ȭ 
		std::cerr << "Unable to initalize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initalize\n";
	}

	make_shaderProgram(); // ���̴� ���α׷� �����
	ShowMenu(); // ���� �÷��� ���

	gPlaybutton.InitBuffer();
	gPlaybutton.LoadTexture("start_image.png");

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	
	// => �ݹ��Լ� ���� 
	glutDisplayFunc(DrawScene);					 // ��� �Լ��� ���� 
	glutReshapeFunc(Reshape);					 // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunction, 1);
	glutKeyboardUpFunc(KeyUpboard);

	glutMainLoop();								 // �̺�Ʈ ó�� ���� 
}


#endif