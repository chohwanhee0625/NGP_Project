#pragma once
#include "usingInclude.h"

class Light
{
private:
	glm::mat4 Total_view;
	
	glm::vec3 lightPos;
	glm::vec3 lightColor;

	GLfloat sunset_t;
	GLfloat night_t;

public:
	Light() 
	{
		initLight();
	}

	void initLight();
	void setTransform();
	void update();
	void sunsetInterpolation(float t);// ���� ����
	void nightInterpolation(float t); // �� ���� 
};