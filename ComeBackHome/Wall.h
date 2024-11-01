#pragma once
class tagWall : public Basis
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108

public:
	tagWall()
	{}
	tagWall(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3]) : Basis()
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
	void update() override;
	virtual void make_car() {};

};