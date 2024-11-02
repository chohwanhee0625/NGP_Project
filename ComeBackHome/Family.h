#pragma once
class BasisComponent;

//========================================================================
// 몸
class tagBodyMom : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	
	int idx;
public:

	tagBodyMom(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], int i)
		: BasisComponent()
		, idx{i}
	{
		initModelLocation();
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
	void WorldMatrix();
	void initModelLocation();
	virtual void make_car() {};

	void update() override;
};

//========================================================================
// 머리
class tagHeadMom : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108
	int idx;
public:

	tagHeadMom(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3],int i)
		: BasisComponent()
		, idx{ i }
	{
		initModelLocation();
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
	void WorldMatrix();
	void initModelLocation();
	void update() override;
	virtual void make_car() {};
};

//========================================================================
// 입
class tagMouseMom : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108

	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;
	GLfloat m_far_value{ 0.002 };
	int idx;
public:

	tagMouseMom(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3],int i)
		: BasisComponent()
		, idx{ i }
	{
		initModelLocation();
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
	void WorldMatrix();

	void initModelLocation();
	void update() override;
	virtual void make_car() {};
};

//========================================================================
// 눈
class tagEyesMom : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108

	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;
	GLfloat m_far_value{ 0.00 };

	int idx;
public:

	tagEyesMom(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3],int i)
		: BasisComponent()
		, idx{ i }
	{
		initModelLocation();
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
	void WorldMatrix();
	void initModelLocation();
	void update() override;
	virtual void make_car() {};

};

//========================================================================
// 왼쪽 팔
class tagLeftArmMom : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108

	Sign sign;
	float hand_degree;
	float hand_max_degree;
	float hand_velo;

	GLfloat m_far_value;
	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;
	int idx;
public:

	tagLeftArmMom(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], int i)
		: BasisComponent(),
		sign{ MINUS },
		hand_degree{ 0.f },
		hand_velo{ 0.8f },
		hand_max_degree{ 45.f },
		m_far_value{ 0.005 },
		m_far_x{ -m_far_value },
		m_far_y{ 0.0 },
		m_far_z{ 0.0 },
		idx{ i }
	{
		initModelLocation();
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
	void WorldMatrix();
	void initModelLocation();
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void update() override;
	virtual void make_car() {};
};

//========================================================================
// 오른쪽 팔  
class tagRightArmMom : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108

	Sign sign;
	float hand_degree;
	float hand_velo;
	float hand_max_degree;

	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;
	GLfloat m_far_value{ 0.005 };

	int idx;
public:

	tagRightArmMom(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3],int i)
		: BasisComponent(),
		sign{ PLUS },
		hand_degree{ 0.f },
		hand_velo{ 0.8f },
		hand_max_degree{ 45.f },
		m_far_x{ m_far_value },
		m_far_y{ 0.0 },
		m_far_z{ 0.0 }
		, idx{i}
	{
		initModelLocation();
		initVertex(cube_array);
		initColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void initVertex(const GLfloat rec_array[36 * 6]);
	void initColor(const GLfloat color_array[36 * 3]);
	void InitBuffer();
	void DrawObject();;
	void InitMatrix4();
	void WorldMatrix();
	void initModelLocation();
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void update() override;
	virtual void make_car() {};
};

//========================================================================
// 왼쪽 다리
class tagLeftLegMom : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108

	Sign sign;
	float hand_degree;
	float hand_velo;
	float hand_max_degree;

	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;
	GLfloat m_far_value{ 0.0025 };
	int idx;
public:

	tagLeftLegMom(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], int i)
		: BasisComponent(),
		sign{ PLUS },
		hand_degree{ 0.f },
		hand_velo{ 0.8f },
		hand_max_degree{ 20.f },
		m_far_x{ -m_far_value },
		m_far_y{ 0.0 },
		m_far_z{ 0.0 },
		idx{i}
	{
		initModelLocation();
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
	void WorldMatrix();
	void initModelLocation();
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void update() override;
	virtual void make_car() {};
};

//======================================================================
// 오른쪽 다리
class tagRightLegMom : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3]; // 108

	Sign sign;
	float hand_degree;
	float hand_velo;
	float hand_max_degree;

	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;
	GLfloat m_far_value{ 0.0025 };

	int idx;
public:

	tagRightLegMom(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], int i)
		: BasisComponent(),
		sign{ MINUS },
		hand_degree{ 0.f },
		hand_velo{ 0.8f },
		hand_max_degree{ 20.f },
		m_far_x{ m_far_value },
		m_far_y{ 0.0 },
		m_far_z{ 0.0 },
		idx{ i }
	{
		initModelLocation();
		initVertex(cube_array);
		initColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void initVertex(const GLfloat rec_array[36 * 6]);
	void initColor(const GLfloat color_array[36 * 3]);
	void InitBuffer();
	void DrawObject();
	void WorldMatrix();
	void InitMatrix4();
	void initModelLocation();
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void update() override;
	virtual void make_car() {};
};

