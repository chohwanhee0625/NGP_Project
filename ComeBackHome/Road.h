#pragma once

//===========================================================================================
// 도로
class Road : public BasisComponent
{
private:
	GLint	m_index;
	int     m_car_spawn_dir;

public:
	Road()
	{}
	Road(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], GLint idx, bool carDir)
		: BasisComponent()
		, m_index{idx}
	{
		InitCarSpawnDir(carDir); 
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();
	void Update(float deltatime) override;

	void InitCarSpawnDir(bool carDir);
	void CreateCar() override;
	void CreateLane()override;

	int GetZindex()override { return m_index; }
};

//===========================================================================================
// 차선
class RoadLane : public BasisComponent
{
private:
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

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void InitMatrix4();
	void DrawObject();

	void Update(float deltatime)override {};
};