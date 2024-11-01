#if 1
#pragma once
#include "Basis.h"


void ShowMenu();
void make_shaderProgram();
void make_vertexShaders();
void make_fragmentShaders();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
char* filetobuf(const char*);
GLvoid Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

//========================================================================

void gVecClear();
void gVecDraw();
void gVecupdate();
void SetgVec();
void Set_Ground();
void initLight();
void initBorder();
void first_viewport();
void second_viewport();
void third_viewport();

//========================================================================

void setInitToggle();
void setOffAllofToggle(); // ¾È¾¸
void setLightToggle();
void setPerspectiveToggle();
GLvoid KeyUpboard(unsigned char key, int x, int y);

//========================================================================

void SetFaceDir(unsigned char key);
void ChickenHandling();
void ChickenWalk();
void maketrees();
void makecars();
void makelines();
void Chickenrun();
void Chickenrwalk();
void Chicken_jump();
void Dir_false();
void setNearFarToggle();
void makeMom();

#endif