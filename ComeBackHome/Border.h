#pragma once
#include "usingInclude.h"

class Border : public Basis
{
private:
	GLfloat m_vertex[36 * 6]; // Element�� �׸��Ÿ� 4��, �ƴϸ� 6�� 
	GLfloat m_color[36 * 3]; // 108

public:
	Border()
	{}
	Border(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
		: Basis()
	{
		initVertex(cube_array);
		initColor(color_array);
		initMatrix4();
		InitBuffer();
	}

	void initVertex(const GLfloat rec_array[36 * 6]);
	void initColor(const GLfloat color_array[36 * 3]);
	void InitBuffer();
	void DrawObject();
	void initMatrix4();
	virtual void make_car() {};
	void update()override;
};
