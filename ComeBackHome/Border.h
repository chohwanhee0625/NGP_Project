#pragma once
#include "usingInclude.h"

class Border : public BasisComponent
{
public:
	Border()
	{}
	Border(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
		: BasisComponent()
	{
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();

	void Update()override;
};
