#if 1
#pragma once
#include "Basis.h"


//===========================================================================================

void make_shaderProgram();
void make_vertexShaders();
void make_fragmentShaders();
char* filetobuf(const char*);

GLvoid DrawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid KeyUpboard(unsigned char key, int x, int y);
void TimerFunction(int value);

void ShowMenu();
void main_viewport();
void chicken_viewport();
void border_viewport();

//===========================================================================================

void InitLight();
void InitBorder();

void gVecClear();
void gVecDraw();
void gEnemyVecDraw();

void gVecUpdate(float deltatime);
void gEnemyVecUpdate(float deltatime);

void SetgVec();
void SetgEnemyVec();

void SetChicken();
void SetGround();
void SetWoods();
void SetCars();
void SetRoadLane();
void SetMother();

//===========================================================================================

void SetInitToggle();
void SetOffAllofToggle(); // 안씀
void SetLightToggle();
void SetPerspectiveToggle();
void SetNearFarCameraToggle(); // 가까운 3인칭 카메라 토글

//===========================================================================================

void SetChickenFaceDir(unsigned char key);
void SetOffGlobalDir();

void ChickenHandling(float deltatime);
void EnemyChickenHandling(float deltatime);
void ChickenMove(float deltatime);

void ChickenRun();
void ChickenWalk();
void ChickenJump();

//===========================================================================================

#endif