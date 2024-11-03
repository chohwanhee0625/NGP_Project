#pragma once

//===========================================================================================
// 도로
class Road : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	GLint	m_inum;
	GLboolean m_bLR;
	int m_dir;
public:
	Road()
	{}
	Road(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], GLint idx)
		: BasisComponent()
		, m_inum{idx}
		, m_bLR{(bool)gBoolUniform(gRandomEngine)}
	{
		initDir(m_bLR); // 도로 방향값 인자로 줘서 -1,1 초기화
		initVertex(cube_array);
		initColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void initDir(GLboolean dir);
	void initVertex(const GLfloat rec_array[36 * 6]);
	void initColor(const GLfloat color_array[36 * 3]);
	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	void Update() override;

	void CreateCar() override;

	int GetZindex()override { return m_inum; }
	void CreateLane()override;

};

//===========================================================================================
// 차선
class RoadLane : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	GLint	m_x_idx;
	GLint   m_z_idx;

public:
	RoadLane()
	{}
	RoadLane(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], GLint x_idx, GLint z_idx)
		: BasisComponent(), m_x_idx{ x_idx }, m_z_idx{ z_idx }
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

	void Update()override {};

};