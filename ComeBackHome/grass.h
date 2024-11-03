#pragma once
// �ܵ� Ŭ����

class Grass : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element�� �׸��Ÿ� 4��, �ƴϸ� 6�� 
	//GLfloat m_color[36 * 3]; // 108
	GLint	m_index;
	bool	m_final; // ������ �ܵ�����

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

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();
	void Update() override;

	virtual int GetZindex() { return m_index; }
	bool IsFinalGrass() override{ return m_final; }
}; 
