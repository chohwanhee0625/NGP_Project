#pragma once
const GLfloat CAR_SPEED = 0.1;

//===========================================================================================
// 차 몸체 
class Car : public BasisComponent
{
private:
	int     m_dir;
	GLfloat m_velocity;
	int     m_idx;

public:
	Car()
	{}
	Car(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], int dir, int idx,float speed,float R,float G,float B) 
		: BasisComponent(),
		m_velocity{ speed } // 속도 변경 가능 
		, m_idx{idx}, m_dir{dir}
	{
		InitVertex(cube_array);
		//InitColor(color_array);
		setcolor(R, G, B);
		InitMatrix4();
		InitBuffer();
		CreateCar();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	
	void setcolor(float R, float G, float B) {
		cout << "R: " << R << endl;
		cout << "G: " << G << endl;
		cout << "B: " << B << endl;

		for (int i = 0; i < 36 * 3; i += 3) {
			m_color[i + 0] = R;
			m_color[i + 1] = G;
			m_color[i + 2] = B;
		}
	};
	
	void DrawObject();
	void InitMatrix4();
	void Set_m_velocity(GLfloat f) { m_velocity = f; };
	virtual void Move(float deltatime);
	virtual void CreateCar();
	void Update(float deltatime)override;
};

//===========================================================================================
// 차 중앙 
class CarMiddle : public BasisComponent
{
private:
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

	void DrawObject();
	void InitMatrix4();

	virtual void Move(float deltatime);

	void Update(float deltatime)override;
};

//===========================================================================================
// 창문
class CarWindow : public BasisComponent
{
private:
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

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();

	virtual void Move(float deltatime);

	void Update(float deltatime)override;
};

//===========================================================================================
// 바퀴 
class CarWheel_1 : public BasisComponent
{
private:
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

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();

	virtual void Move(float deltatime);

	void Update(float deltatime)override;
};

//===========================================================================================
// 바퀴
class CarSmallWheel_1 : public BasisComponent
{
private:
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

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();

	virtual void Move(float deltatime);

	void Update(float deltatime)override;
};

//===========================================================================================
// 바퀴
class CarWheel_2 : public BasisComponent
{
private:
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

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();

	virtual void Move(float deltatime);

	void Update(float deltatime)override;
};

//===========================================================================================
// 바퀴
class CarSmallWheel_2 : public BasisComponent
{
private:
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

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();

	virtual void Move(float deltatime);

	void Update(float deltatime)override;
};

//===========================================================================================
// 바퀴
class CarWheel_3 : public BasisComponent
{
private:
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

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();

	virtual void Move(float deltatime);

	void Update(float deltatime)override;
};

//===========================================================================================
// 바퀴
class CarSmallWheel_3 : public BasisComponent
{
private:
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

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();

	virtual void Move(float deltatime);

	void Update(float deltatime)override;
};

//===========================================================================================
// 바퀴
class CarWheel_4 : public BasisComponent
{
private:
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

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();

	virtual void Move(float deltatime);

	void Update(float deltatime)override;
};

//===========================================================================================
// 바퀴
class CarSmallWheel_4 : public BasisComponent
{
private:
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

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();

	virtual void Move(float deltatime);

	void Update(float deltatime)override;
};
