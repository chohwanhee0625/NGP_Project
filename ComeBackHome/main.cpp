#if 1
#include "usingInclude.h"
#include "소스.h"
#include "Basis.h"
#include "Camera.h"
#include "Light.h"
#include "Border.h"

GLchar* gVertexSource;
GLchar* gFragmentSource; //--- 소스코드 저장 변수
GLuint gVertexShader;
GLuint gFragmentShader; //--- 세이더 객체
GLuint gShaderProgramID; //--- 셰이더 프로그램

int gWidth{ 800 };
int gHeight{ 600 }; 
int max_z{};
// 윈도우 크기

bool isreach{};
vector<Basis*> gVec; // --> 모든 객체를 Basis 부모 클래스 포인터로 다형성을 사용해 관리하기 위한 변수
bool gToggle[(int)Toggle::END]; // 명령어 토글 

Camera gCamera; // 카메라 클래스 
Light* gLight; // 조명 클래스 
Border* gBorder; // 화면 우측 상단 핑크색 경계 클래스

bool isMoveChicken{ OFF };
bool B_Dir[4]{};

int seednum;

std::random_device gRandDevice; // 진짜 난수 발생기 -> 이 값을 시드값으로
std::mt19937 gRandomEngine; // 알고리즘 + 진짜 난수 시드 :: 진짜진짜 난수 생성
std::uniform_int_distribution<int> gBoolUniform{ 0,1 };
std::uniform_int_distribution<int> gRoadSet{ 5, 10 };
std::uniform_int_distribution<int> gCarspeed{1,3};
std::uniform_real_distribution<float> grandomcolor{0.f,1.f};
// 랜덤 기능 사용할 때 

//bool ConnectScene()
//{
//	// 플레이 버튼 UI 그림
//
//	if (play_button->Isin(x, y))
//		// 플레이 버튼 UI 삭제
//		while (true)
//		{
//			// 로딩중 UI 그림
//			// 서버로부터 상대 클라이언트 접속 recv
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
	// 고광신 왔다 감 ㅅㄱㅂ(11/01 - 4:40)
	// gwangsin branch test (11/01 - 4:40)


	glutInit(&argc, argv);						  // GLUT 초기화 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // [깊이검사 depth test 추가]디스플레이 모드 설정
	glutInitWindowPosition(100, 100);			  // 윈도우의 위치 지정 
	glutInitWindowSize(gWidth, gHeight);				  // 윈도우의 크기 지정
	glutCreateWindow("Come back Home");				  // 윈도우 생성 (윈도우 이름)

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {				  // GLEW 초기화 
		std::cerr << "Unable to initalize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initalize\n";
	}

	seednum = 2020;
	gRandomEngine = std::mt19937(static_cast<unsigned int>(seednum));

	make_shaderProgram(); // 쉐이더 프로그램 만들기
	ShowMenu(); // 게임 플레이 방법
	setInitToggle(); // 토글 초기화 
	initLight(); // 조명 초기 세팅

	//while (ConnectScene() == false);

	initBorder(); // 우측 상단 핑크색 경계 만들기 
	SetgVec(); // 초기 객체 만들기 

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	
	// => 콜백함수 설정 
	glutDisplayFunc(drawScene);					 // 출력 함수의 지정 
	glutReshapeFunc(Reshape);					 // 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunction, 1);
	glutKeyboardUpFunc(KeyUpboard);
	// TODO : 마우스 이벤트 함수 추가


	glutMainLoop();								 // 이벤트 처리 시작 
}


#endif