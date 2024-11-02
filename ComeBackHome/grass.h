#pragma once
// 잔디 클래스

class tagGrass : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	GLint	m_inum;
	bool	m_final; // 마지막 잔디인지

public:
	tagGrass()
	{}

	tagGrass(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], GLint idx, bool b)
		: BasisComponent()
		, m_inum{ idx }
		, m_final{b}
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
	virtual int Get_zidx() { return m_inum; }
	bool Is_final() override{ return m_final; }
}; 
