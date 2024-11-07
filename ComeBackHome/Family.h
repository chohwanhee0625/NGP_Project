#pragma once
class BasisComponent;

//========================================================================
// 个
class MotherBody : public BasisComponent
{
private:	
	int idx;

public:

	MotherBody(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], int i)
		: BasisComponent()
		, idx{i}
	{
		initModelLocation();
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();
	void WorldMatrix();
	void initModelLocation();

	void Update(float deltatime) override;
};

//========================================================================
// 赣府
class MotherHead : public BasisComponent
{
private:
	int idx;

public:

	MotherHead(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3],int i)
		: BasisComponent()
		, idx{ i }
	{
		initModelLocation();
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();

	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();
	void WorldMatrix();
	void initModelLocation();
	void Update(float deltatime) override;
};

//========================================================================
// 涝
class MotherMouse : public BasisComponent
{
private:
	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;
	GLfloat m_far_value{ 0.002 };
	int idx;

public:

	MotherMouse(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3],int i)
		: BasisComponent()
		, idx{ i }
	{
		initModelLocation();
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();
	void WorldMatrix();

	void initModelLocation();
	void Update(float deltatime) override;
};

//========================================================================
// 传
class MotherEyes : public BasisComponent
{
private:
	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;
	GLfloat m_far_value{ 0.00 };

	int idx;

public:

	MotherEyes(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3],int i)
		: BasisComponent()
		, idx{ i }
	{
		initModelLocation();
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();
	void WorldMatrix();
	void initModelLocation();
	void Update(float deltatime) override;

};

//========================================================================
// 哭率 迫
class MotherLeftArm : public BasisComponent
{
private:
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

	MotherLeftArm(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], int i)
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
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();
	void WorldMatrix();
	void initModelLocation();
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void Update(float deltatime) override;
};

//========================================================================
// 坷弗率 迫  
class MotherRightArm : public BasisComponent
{
private:
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

	MotherRightArm(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3],int i)
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
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();;
	void InitMatrix4();
	void WorldMatrix();
	void initModelLocation();
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void Update(float deltatime) override;
};

//========================================================================
// 哭率 促府
class MotherLeftLeg : public BasisComponent
{
private:
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

	MotherLeftLeg(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], int i)
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
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void InitMatrix4();
	void WorldMatrix();
	void initModelLocation();
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void Update(float deltatime) override;
};

//======================================================================
// 坷弗率 促府
class MotherRightLeg : public BasisComponent
{
private:
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

	MotherRightLeg(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3], int i)
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
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

	void InitColor(const GLfloat color_array[36 * 3]) override;
	void DrawObject();
	void WorldMatrix();
	void InitMatrix4();
	void initModelLocation();
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void Update(float deltatime) override;
};

