#pragma once
#include "Souce.h"
#include "TimeManager.h"
//#include "UI.h"

extern GLchar* gVertexSource; //--- �ҽ��ڵ� ���� ����
extern GLchar* gFragmentSource;
extern GLuint gVertexShader;
extern GLuint gFragmentShader; //--- ���̴� ��ü
extern GLuint gShaderProgramID; //--- ���̴� ���α׷�

extern GLuint gUIShaderProgramID;  // UI ���̴� ���α׷�
extern GLuint gUIVertexShader;
extern GLuint gUIFragmentShader; //--- ���̴� ��ü

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

 // ��¥ ���� �߻��� -> �� ���� �õ尪���� 
extern std::mt19937 gRandomEngine; // �˰��� + ��¥ ���� �õ� :: ��¥��¥ ���� ����
extern std::uniform_int_distribution<int> gBoolUniform;
extern std::uniform_int_distribution<int> gRoadSet;
extern std::uniform_int_distribution<int> gCarspeed;
extern std::uniform_real_distribution<float> grandomcolor;



