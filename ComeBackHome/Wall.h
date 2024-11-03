#pragma once
class Wall : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108

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


	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]);
	void InitBuffer();
	void DrawObject();
	void InitMatrix4();
	void Update() override;
};