#if 1
#include "usingInclude.h"
#include "�ҽ�.h"
#include "Basis.h"
#include "Camera.h"
#include "Light.h"
#include "Border.h"

GLchar* gVertexSource;
GLchar* gFragmentSource; //--- �ҽ��ڵ� ���� ����
GLuint gVertexShader;
GLuint gFragmentShader; //--- ���̴� ��ü
GLuint gShaderProgramID; //--- ���̴� ���α׷�

int gWidth{ 800 };
int gHeight{ 600 }; 
int max_z{};
// ������ ũ��

bool isreach{};
vector<Basis*> gVec; // --> ��� ��ü�� Basis �θ� Ŭ���� �����ͷ� �������� ����� �����ϱ� ���� ����
bool gToggle[(int)Toggle::END]; // ��ɾ� ��� 

Camera gCamera; // ī�޶� Ŭ���� 
Light* gLight; // ���� Ŭ���� 
Border* gBorder; // ȭ�� ���� ��� ��ũ�� ��� Ŭ����

bool isMoveChicken{ OFF };
bool B_Dir[4]{};

int seednum;

std::random_device gRandDevice; // ��¥ ���� �߻��� -> �� ���� �õ尪����
std::mt19937 gRandomEngine; // �˰��� + ��¥ ���� �õ� :: ��¥��¥ ���� ����
std::uniform_int_distribution<int> gBoolUniform{ 0,1 };
std::uniform_int_distribution<int> gRoadSet{ 5, 10 };
std::uniform_int_distribution<int> gCarspeed{1,3};
std::uniform_real_distribution<float> grandomcolor{0.f,1.f};
// ���� ��� ����� �� 

//bool ConnectScene()
//{
//	// �÷��� ��ư UI �׸�
//
//	if (play_button->Isin(x, y))
//		// �÷��� ��ư UI ����
//		while (true)
//		{
//			// �ε��� UI �׸�
//			// �����κ��� ��� Ŭ���̾�Ʈ ���� recv
//			if (other_connect == true)
//				return true;
//		}
//	// 
//
//
//}
//
void main(int argc, char** argv)
{
	// ���� �Դ� �� ������(11/01 - 4:40)
	// gwangsin branch test (11/01 - 4:40)


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

	seednum = 2020;
	gRandomEngine = std::mt19937(static_cast<unsigned int>(seednum));

	make_shaderProgram(); // ���̴� ���α׷� �����
	ShowMenu(); // ���� �÷��� ���
	setInitToggle(); // ��� �ʱ�ȭ 
	initLight(); // ���� �ʱ� ����

	//while (ConnectScene() == false);

	initBorder(); // ���� ��� ��ũ�� ��� ����� 
	SetgVec(); // �ʱ� ��ü ����� 

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	
	// => �ݹ��Լ� ���� 
	glutDisplayFunc(drawScene);					 // ��� �Լ��� ���� 
	glutReshapeFunc(Reshape);					 // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunction, 1);
	glutKeyboardUpFunc(KeyUpboard);
	// TODO : ���콺 �̺�Ʈ �Լ� �߰�


	glutMainLoop();								 // �̺�Ʈ ó�� ���� 
}


#endif