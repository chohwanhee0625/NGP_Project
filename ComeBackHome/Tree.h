#pragma once

//===========================================================================================
// ³ª¹«
class Wood: public BasisComponent
{
private:
	GLint	m_x_idx;
	GLint   m_z_idx;

public:
	Wood()
	{}
	Wood(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], GLint x_idx, GLint z_idx)
		: BasisComponent(), m_x_idx{x_idx}, m_z_idx{z_idx}
	{
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();
	void Update() override;
};

//===========================================================================================
// ÀÙ 1
class WoodLeaf_1 : public BasisComponent
{
private:
	GLint	m_x_idx;
	GLint   m_z_idx;

public:
	WoodLeaf_1()
	{}
	WoodLeaf_1(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], GLint x_idx, GLint z_idx)
		: BasisComponent(), m_x_idx{ x_idx }, m_z_idx{ z_idx }
	{
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();
	void Update() override;

	void WorldMatrix();
};

//===========================================================================================
// ÀÙ2
class WoodLeaf_2 : public BasisComponent
{
private:
	GLint	m_x_idx;
	GLint   m_z_idx;

public:
	WoodLeaf_2()
	{}
	WoodLeaf_2(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], GLint x_idx, GLint z_idx)
		: BasisComponent(), m_x_idx{ x_idx }, m_z_idx{ z_idx }
	{
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();
	void Update() override;

	void WorldMatrix();
};

//===========================================================================================
// ÀÙ3
class WoodLeaf_3 : public BasisComponent
{
private:
	GLint	m_x_idx;
	GLint   m_z_idx;

public:
	WoodLeaf_3()
	{}
	WoodLeaf_3(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], GLint x_idx, GLint z_idx)
		: BasisComponent(), m_x_idx{ x_idx }, m_z_idx{ z_idx }
	{
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();
	void Update() override;

	void WorldMatrix();
};