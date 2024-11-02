#pragma once
class tagWall : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element�� �׸��Ÿ� 4��, �ƴϸ� 6�� 
	GLfloat m_color[36 * 3]; // 108

public:
	tagWall()
	{}
	tagWall(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3]) : BasisComponent()
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
	void update() override;
	virtual void make_car() {};

};