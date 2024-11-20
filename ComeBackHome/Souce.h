#if 1
#pragma once
#include "Basis.h"

//===========================================================================================

void make_shaderProgram();
void make_vertexShaders(const char* vertex_path);
void make_fragmentShaders(const char* fragment_path);
void make_vertexShaders_1(const char* vertex_path);
void make_fragmentShaders_1(const char* fragment_path);
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
void SetgEnemyVec(bool b);

void SetChicken(bool b);
void SetGround(INIT_DATA_R road_data);
void SetWoods(INIT_DATA_W wood_data);
void SetCars(INIT_DATA_C car_data);
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