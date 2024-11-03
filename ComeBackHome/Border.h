#pragma once
#include "usingInclude.h"

class Border : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108

public:
	Border()
	{}
	Border(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
		: BasisComponent()
	{
		initVertex(cube_array);
		initColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void initVertex(const GLfloat rec_array[36 * 6]);
	void initColor(const GLfloat color_array[36 * 3]);
	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	void Update()override;
};
