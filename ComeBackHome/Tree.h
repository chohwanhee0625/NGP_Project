#pragma once

class tagWood: public Basis
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	GLint	m_x_idx;
	GLint   m_z_idx;

public:
	tagWood()
	{}
	tagWood(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], GLint x_idx, GLint z_idx)
		: Basis(), m_x_idx{x_idx}, m_z_idx{z_idx}
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
	void make_car()override {};

	
};


// --------------------------------------------------------------------------

class tagLeafone : public Basis
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	GLint	m_x_idx;
	GLint   m_z_idx;

public:
	tagLeafone()
	{}
	tagLeafone(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], GLint x_idx, GLint z_idx)
		: Basis(), m_x_idx{ x_idx }, m_z_idx{ z_idx }
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
	virtual void Move() {  };
	void make_car()override {};

	void WorldMatrix() override;
};

// --------------------------------------------------------------------------

class tagLeaftwo : public Basis
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	GLint	m_x_idx;
	GLint   m_z_idx;

public:
	tagLeaftwo()
	{}
	tagLeaftwo(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], GLint x_idx, GLint z_idx)
		: Basis(), m_x_idx{ x_idx }, m_z_idx{ z_idx }
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
	
	void make_car()override {};

	void WorldMatrix() override;
};

// --------------------------------------------------------------------------

class tagLeafthree : public Basis
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	GLint	m_x_idx;
	GLint   m_z_idx;

public:
	tagLeafthree()
	{}
	tagLeafthree(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], GLint x_idx, GLint z_idx)
		: Basis(), m_x_idx{ x_idx }, m_z_idx{ z_idx }
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
	void make_car()override {};
	void WorldMatrix() override;
};