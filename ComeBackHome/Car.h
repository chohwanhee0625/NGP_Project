#pragma once

//===========================================================================================
// 차 몸체 
class tagCar : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108

	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	tagCar()
	{}
	tagCar(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], int dir, int idx) 
		: BasisComponent(),
		m_velocity{ 0.001f} // 속도 변경 가능 
		, m_idx{idx}, m_dir{dir}
	{
	//	initDir(gBoolUniform(gRandomEngine));
	//	cout << "차 index: " << m_idx << '\n';
		initVertex(cube_array);
		initColor(color_array);
		InitMatrix4();
		InitBuffer();
		make_car();
	}

	void initVertex(const GLfloat rec_array[36 * 6]);
	void initColor(const GLfloat color_array[36 * 3]);
	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();
	virtual void make_car();
	void update()override;
};

//===========================================================================================
// 차 중앙 
class tagCarMiddle : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	tagCarMiddle()
	{}
	tagCarMiddle(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
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

	virtual void Move();
	virtual void make_car() {};
	void update()override;
};

//===========================================================================================
// 창문
class tagCarWindow : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	tagCarWindow()
	{}
	tagCarWindow(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		initVertex(cube_array);
		initColor();
		InitMatrix4();
		InitBuffer();
	}

	void initVertex(const GLfloat rec_array[36 * 6]);
	void initColor();
	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();
	virtual void make_car() {};
	void update()override;
};

//===========================================================================================
// 바퀴 
class tagCarWheel_1 : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	tagCarWheel_1()
	{}
	tagCarWheel_1(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		initVertex(cube_array);
		initColor();
		InitMatrix4();
		InitBuffer();
	}

	void initVertex(const GLfloat rec_array[36 * 6]);
	void initColor();
	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();
	virtual void make_car() {};
	void update()override;
};

//===========================================================================================
// 바퀴
class tagCarWheel_1_small : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	tagCarWheel_1_small()
	{}
	tagCarWheel_1_small(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		initVertex(cube_array);
		initColor();
		InitMatrix4();
		InitBuffer();
	}

	void initVertex(const GLfloat rec_array[36 * 6]);
	void initColor();
	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();
	virtual void make_car() {};
	void update()override;
};

//===========================================================================================
// 바퀴
class tagCarWheel_2 : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	tagCarWheel_2()
	{}
	tagCarWheel_2(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		initVertex(cube_array);
		initColor();
		InitMatrix4();
		InitBuffer();
	}

	void initVertex(const GLfloat rec_array[36 * 6]);
	void initColor();
	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();
	virtual void make_car() {};
	void update()override;
};

//===========================================================================================
// 바퀴
class tagCarWheel_2_small : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	tagCarWheel_2_small()
	{}
	tagCarWheel_2_small(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		initVertex(cube_array);
		initColor();
		InitMatrix4();
		InitBuffer();
	}

	void initVertex(const GLfloat rec_array[36 * 6]);
	void initColor();
	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();
	virtual void make_car() {};
	void update()override;
};

//===========================================================================================
// 바퀴
class tagCarWheel_3 : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	tagCarWheel_3()
	{}
	tagCarWheel_3(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		initVertex(cube_array);
		initColor();
		InitMatrix4();
		InitBuffer();
	}

	void initVertex(const GLfloat rec_array[36 * 6]);
	void initColor();
	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();
	virtual void make_car() {};
	void update()override;
};

//===========================================================================================
// 바퀴
class tagCarWheel_3_small : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	tagCarWheel_3_small()
	{}
	tagCarWheel_3_small(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		initVertex(cube_array);
		initColor();
		InitMatrix4();
		InitBuffer();
	}

	void initVertex(const GLfloat rec_array[36 * 6]);
	void initColor();
	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();
	virtual void make_car() {};
	void update()override;
};

//===========================================================================================
// 바퀴
class tagCarWheel_4 : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	tagCarWheel_4()
	{}
	tagCarWheel_4(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		initVertex(cube_array);
		initColor();
		InitMatrix4();
		InitBuffer();
	}

	void initVertex(const GLfloat rec_array[36 * 6]);
	void initColor();
	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();
	virtual void make_car() {};
	void update()override;
};

//===========================================================================================
// 바퀴
class tagCarWheel_4_small : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	int m_dir;
	GLfloat m_velocity;
	int m_idx;

public:
	tagCarWheel_4_small()
	{}
	tagCarWheel_4_small(const GLfloat cube_array[36 * 6], int dir, int idx, GLfloat velo)
		: BasisComponent(),
		m_velocity{ velo } // 속도 변경 가능 
		, m_idx{ idx }, m_dir{ dir }
	{
		initVertex(cube_array);
		initColor();
		InitMatrix4();
		InitBuffer();
	}

	void initVertex(const GLfloat rec_array[36 * 6]);
	void initColor();
	void InitBuffer();
	void DrawObject();
	void InitMatrix4();

	virtual void Move();
	virtual void make_car() {};
	void update()override;
};
