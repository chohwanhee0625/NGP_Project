#pragma once
#include "Souce.h"
#include "TimeManager.h"
//#include "UI.h"

extern GLchar* gVertexSource; //--- 소스코드 저장 변수
extern GLchar* gFragmentSource;
extern GLuint gVertexShader;
extern GLuint gFragmentShader; //--- 세이더 객체
extern GLuint gShaderProgramID; //--- 셰이더 프로그램

extern GLuint gUIShaderProgramID;  // UI 셰이더 프로그램
extern GLuint gUIVertexShader;
extern GLuint gUIFragmentShader; //--- 세이더 객체

extern int gWidth;
extern int gHeight;

extern int g_max_z;

extern vector<BasisComponent*> gVec;
extern vector<BasisComponent*> gEnemyVec;

extern bool gToggle[(int)Toggle::END];
extern Camera gCamera;
extern Light* gLight;
extern Border* gBorder;
extern TimeManager gTimer;

extern bool gIsMovingChicken;
extern bool gChickenDir[4];
extern bool gIsReach;


//===========================================================================================
extern const GLfloat cube_vertex_array[36 * 3];
extern const GLfloat colors[36];
extern const GLfloat cube_color[36 * 3];
extern const GLfloat floor_color[36 * 3];
extern const GLfloat cube_vertex_array_normal[36 * 6];

 // 진짜 난수 발생기 -> 이 값을 시드값으로 
extern std::mt19937 gRandomEngine; // 알고리즘 + 진짜 난수 시드 :: 진짜진짜 난수 생성
extern std::uniform_int_distribution<int> gBoolUniform;
extern std::uniform_int_distribution<int> gRoadSet;
extern std::uniform_int_distribution<int> gCarspeed;
extern std::uniform_real_distribution<float> grandomcolor;



