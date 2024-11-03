#pragma once
#include "usingInclude.h"

class Light
{
private:
	glm::mat4 total_view;
	
	glm::vec3 light_pos;
	glm::vec3 light_color;

	GLfloat sunset_t;
	GLfloat night_t;

public:
	Light() 
	{
		InitLight();
	}

	void InitLight();
	void SetTransform();
	void Update();
	void SetSunsetInterpolation(float t);// 노을 보간
	void SetNightInterpolation(float t); // 밤 보간 
};