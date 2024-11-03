#pragma once

//===========================================================================================
// 차 몸체 
class Car : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108

	int     m_dir;
	GLfloat m_velocity;
	int     m_idx;

public:
	Car()
	{}
	Car(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], int dir, int idx) 
		: BasisComponent(),
		m_velocity{ 0.001f} // 속도 변경 가능 
		, m_idx{idx}, m_dir{dir}
	{
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
		CreateCar();
	}

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();
	virtual void CreateCar();
	void Update()override;
};

//===========================================================================================
// 차 중앙 
class CarMiddle : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	CarMiddle()
	{}
	CarMiddle(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

//	void InitVertex(const GLfloat rec_array[36 * 6]);
//	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();

	void Update()override;
};

//===========================================================================================
// 창문
class CarWindow : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	CarWindow()
	{}
	CarWindow(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		InitVertex(cube_array);
		InitColor(m_color);
		InitMatrix4();
		InitBuffer();
	}

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();

	void Update()override;
};

//===========================================================================================
// 바퀴 
class CarWheel_1 : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	CarWheel_1()
	{}
	CarWheel_1(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		InitVertex(cube_array);
		InitColor(m_color);
		InitMatrix4();
		InitBuffer();
	}

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();

	void Update()override;
};

//===========================================================================================
// 바퀴
class CarSmallWheel_1 : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	CarSmallWheel_1()
	{}
	CarSmallWheel_1(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		InitVertex(cube_array);
		InitColor(m_color);
		InitMatrix4();
		InitBuffer();
	}

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();

	void Update()override;
};

//===========================================================================================
// 바퀴
class CarWheel_2 : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	CarWheel_2()
	{}
	CarWheel_2(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		InitVertex(cube_array);
		InitColor(m_color);
		InitMatrix4();
		InitBuffer();
	}

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();

	void Update()override;
};

//===========================================================================================
// 바퀴
class CarSmallWheel_2 : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	CarSmallWheel_2()
	{}
	CarSmallWheel_2(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		InitVertex(cube_array);
		InitColor(m_color);
		InitMatrix4();
		InitBuffer();
	}

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();

	void Update()override;
};

//===========================================================================================
// 바퀴
class CarWheel_3 : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	CarWheel_3()
	{}
	CarWheel_3(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		InitVertex(cube_array);
		InitColor(m_color);
		InitMatrix4();
		InitBuffer();
	}

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();

	void Update()override;
};

//===========================================================================================
// 바퀴
class CarSmallWheel_3 : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	CarSmallWheel_3()
	{}
	CarSmallWheel_3(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		InitVertex(cube_array);
		InitColor(m_color);
		InitMatrix4();
		InitBuffer();
	}

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();

	void Update()override;
};

//===========================================================================================
// 바퀴
class CarWheel_4 : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	CarWheel_4()
	{}
	CarWheel_4(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		InitVertex(cube_array);
		InitColor(m_color);
		InitMatrix4();
		InitBuffer();
	}

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();

	void Update()override;
};

//===========================================================================================
// 바퀴
class CarSmallWheel_4 : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	CarSmallWheel_4()
	{}
	CarSmallWheel_4(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		InitVertex(cube_array);
		InitColor(m_color);
		InitMatrix4();
		InitBuffer();
	}

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();

	void Update()override;
};
