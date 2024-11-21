#pragma once
const GLfloat CAR_SPEED = 0.1;

//===========================================================================================
// �� ��ü 
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
		m_velocity{ speed } // �ӵ� ���� ���� 
		, m_idx{idx}, m_dir{dir}
	{
		InitVertex(cube_array);
		//InitColor(color_array);
		InitColor(R, G, B);
		InitMatrix4();
		InitBuffer();
		CreateCar();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void InitColor(float R, float G, float B);
	
	void DrawObject();
	void InitMatrix4();
	void Set_m_velocity(GLfloat f) { m_velocity = f; };
	virtual void Move(float deltatime);
	virtual void CreateCar();
	void Update(float deltatime)override;
};

//===========================================================================================
// �� �߾� 
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
		m_velocity{ velo } // �ӵ� ���� ���� 
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
// â��
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
		m_velocity{ velo } // �ӵ� ���� ���� 
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
// ���� 
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
		m_velocity{ velo } // �ӵ� ���� ���� 
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
// ����
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
		m_velocity{ velo } // �ӵ� ���� ���� 
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
// ����
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
		m_velocity{ velo } // �ӵ� ���� ���� 
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
// ����
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
		m_velocity{ velo } // �ӵ� ���� ���� 
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
// ����
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
		m_velocity{ velo } // �ӵ� ���� ���� 
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
// ����
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
		m_velocity{ velo } // �ӵ� ���� ���� 
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
// ����
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
		m_velocity{ velo } // �ӵ� ���� ���� 
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
// ����
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
		m_velocity{ velo } // �ӵ� ���� ���� 
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
