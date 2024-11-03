#pragma once

//===========================================================================================
// 나무
class Wood: public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108
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

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();
	void Update() override;
};

//===========================================================================================
// 잎 1
class WoodLeaf_1 : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108
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

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();
	void Update() override;

	void WorldMatrix();
};

//===========================================================================================
// 잎2
class WoodLeaf_2 : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108
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

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();
	void Update() override;

	void WorldMatrix();
};

//===========================================================================================
// 잎3
class WoodLeaf_3 : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108
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

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();
	void Update() override;

	void WorldMatrix();
};