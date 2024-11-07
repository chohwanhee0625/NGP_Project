#pragma once
class Wall : public BasisComponent
{
public:
	Wall()
	{}
	Wall(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3]) : BasisComponent()
	{
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();
	void Update(float deltatime) override;
};