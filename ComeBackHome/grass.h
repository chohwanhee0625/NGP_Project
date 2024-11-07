#pragma once
// 잔디 클래스

class Grass : public BasisComponent
{
private:
	GLint	m_index;
	bool	m_final; // 마지막 잔디인지

public:
	Grass()
	{}

	Grass(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], GLint idx, bool b)
		: BasisComponent()
		, m_index{ idx }
		, m_final{b}
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

	virtual int GetZindex() { return m_index; }
	bool IsFinalGrass() override{ return m_final; }
}; 
