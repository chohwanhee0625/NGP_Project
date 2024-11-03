#pragma once

//===========================================================================================
// ����
class Road : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element�� �׸��Ÿ� 4��, �ƴϸ� 6�� 
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
		initDir(m_bLR); // ���� ���Ⱚ ���ڷ� �༭ -1,1 �ʱ�ȭ
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
// ����
class RoadLane : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element�� �׸��Ÿ� 4��, �ƴϸ� 6�� 
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