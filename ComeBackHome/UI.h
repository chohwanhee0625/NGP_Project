#pragma once
#include "Basis.h"
#include "Border.h"

struct Vector3 {
	float x{ 0 }, y{ 0 }, z{ 0 };
};

struct Vector2 {
	float x{ 0 }, y{ 0 };
};

class UI
{
	//static Border border;
	unsigned int texture;
	glm::mat4 world{ 1 };
public:
	void InitBuffer();
	void load(const string& img_name, const char* sound_name, bool loop = false, float volume = 0.1f);
	void draw() const;
	void resize(float sx, float sy, float sz);
	void move(float dx, float dy, float dz);
	bool isIn(float x, float y);		// press any key? or button click?
};

