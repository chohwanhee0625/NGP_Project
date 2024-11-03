#pragma once

//===========================================================================================
// 도로
class Road : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108

	GLint	m_index;
	int     m_car_spawn_dir;

public:
	Road()
	{}
	Road(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], GLint idx)
		: BasisComponent()
		, m_index{idx}
	{
		InitCarSpawnDir(); 
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

	void InitCarSpawnDir();
	void CreateCar() override;
	void CreateLane()override;

	int GetZindex()override { return m_index; }
};

//===========================================================================================
// 차선
class RoadLane : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108
	GLint	m_x_idx;
	GLint   m_z_idx;

public:
	RoadLane()
	{}
	RoadLane(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], GLint x_idx, GLint z_idx)
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
	void InitMatrix4();
	void DrawObject();

	void Update()override {};
};