#pragma once
// 닭 부위가 사각형이니 각각 쪼개어 변환을 수행하는 원리
 
class BasisComponent;


//========================================================================
// 몸
class ChickenBody : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108

	Dir face;
	GLfloat  walk_velo;
	GLfloat  face_degree;

	GLfloat  m_fgravity;
	GLfloat  m_fyvelo;

	bool	m_coll;
public:

	ChickenBody(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
		: BasisComponent(),
		face{ STOP },
		walk_velo{ 0.002f },
		face_degree{ 0.f },
		m_fgravity{0.00015f},
		m_fyvelo{0},
		m_coll{true}
	{
		initModelLocation();
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
	void WorldMatrix();

	void initModelLocation();
	void SetChickenFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) { walk_velo += speed; }

	void Update() override;
	void Collision();

	void update_yvelo();
	void Set_yvelo_zero();

	void UpdateChickenYpos();
	void ChickenJump();

	void SetChickenRunSpeed()override { walk_velo = 0.01f; };
	void SetChickenWalkSpeed()override { walk_velo = 0.002f; };

	Dir GetChickenDir()override { return face; }

	void SwitchCollisionState()override {
		// false = 무적
		// true = 일반
		if (m_coll) m_coll = false;
		else m_coll = true;
	}
};

//========================================================================
// 머리
class ChickenHead : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108

	Dir face;
	GLfloat  walk_velo;
	GLfloat  face_degree;

public:

	ChickenHead(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
		: BasisComponent(),
		face{ STOP },
		walk_velo{ 0.002f },
		face_degree{ 0.f }
	{
		initModelLocation();
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
	void WorldMatrix();

	void initModelLocation();
	void SetChickenFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) {
		walk_velo += speed;
	}
	void Update() override;

	void UpdateChickenYpos();
	void SetChickenRunSpeed()override { walk_velo = 0.01f; };
	void SetChickenWalkSpeed()override { walk_velo = 0.002f; };
	Dir GetChickenDir()override { return face; }
};

//========================================================================
// 입
class ChickenMouse : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108

	Dir face;
	GLfloat  walk_velo;
	GLfloat  face_degree;

	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;
	GLfloat m_far_value{ 0.002 };

	GLfloat  m_fgravity;
	GLfloat  m_fyvelo;
public:

	ChickenMouse(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
		: BasisComponent(),
		face{ STOP },
		walk_velo{ 0.002f },
		face_degree{ 0.f },
		m_far_x{ 0.0 },
		m_far_y{ 0.0 },
		m_far_z{ m_far_value }
	{
		initModelLocation();
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
	void WorldMatrix();

	void initModelLocation();

	void SetChickenFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) {
		walk_velo += speed;
	}
	void Update() override;

	float Get_yvelo() { return m_fyvelo; }
	void SetChickenRunSpeed()override { walk_velo = 0.01f; };
	void SetChickenWalkSpeed()override { walk_velo = 0.002f; };
	void UpdateChickenYpos();
	Dir GetChickenDir()override { return face; }
};

//========================================================================
// 눈
class ChickenEyes : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108

	Dir face;
	GLfloat  walk_velo;
	GLfloat  face_degree;

	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;
	GLfloat m_far_value{ 0.00 };


public:

	ChickenEyes(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
		: BasisComponent(),
		face{ STOP },
		walk_velo{ 0.002f },
		face_degree{ 0.f },
		m_far_x{ 0.0 },
		m_far_y{ 0.0 },
		m_far_z{ m_far_value }
	{
		initModelLocation();
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
	void WorldMatrix();

	void initModelLocation();
	void SetChickenFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) {
		walk_velo += speed;
	}
	void Update() override;

	void SetChickenRunSpeed()override { walk_velo = 0.01f; };
	void SetChickenWalkSpeed()override { walk_velo = 0.002f; };
	void UpdateChickenYpos();
	Dir GetChickenDir()override { return face; }
};

//========================================================================
// 왼쪽 팔
class ChickenLeftArm : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108

	Dir face;
	GLfloat  walk_velo;
	GLfloat  face_degree;

	Sign sign;
	float hand_degree;
	float hand_max_degree;
	float hand_velo;

	GLfloat m_far_value;
	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;

public:

	ChickenLeftArm(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
		: BasisComponent(),
		sign{ MINUS },
		hand_degree{ 0.f },
		hand_velo{ 0.8f },
		hand_max_degree{ 45.f },
		face{ STOP },
		walk_velo{ 0.002f },
		face_degree{180.f },
		m_far_value{0.005},
		m_far_x{ -m_far_value },
		m_far_y{ 0.0 },
		m_far_z{ 0.0 }
	{
		initModelLocation();
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
	void WorldMatrix();

	void initModelLocation();
	void handling();
	void SetChickenFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) { walk_velo += speed; }
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void Update() override;

	void SetChickenRunSpeed()override { walk_velo = 0.01f; };
	void SetChickenWalkSpeed()override { walk_velo = 0.002f; };
	void UpdateChickenYpos();
	Dir GetChickenDir()override { return face; }
};

//========================================================================
// 오른쪽 팔  
class ChickenRightArm : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108

	Sign sign;
	float hand_degree;
	float hand_velo;
	float hand_max_degree;

	Dir face;
	GLfloat  walk_velo;
	GLfloat  face_degree;

	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;
	GLfloat m_far_value{ 0.005 };


public:

	ChickenRightArm(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
		: BasisComponent(),
		sign{ PLUS },
		hand_degree{ 0.f },
		hand_velo{ 0.8f },
		hand_max_degree{ 45.f },
		face{ STOP },
		walk_velo{ 0.002f },
		face_degree{ 0.f },
		m_far_x{ m_far_value },
		m_far_y{ 0.0 },
		m_far_z{ 0.0 }
	{
		initModelLocation();
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();;
	void InitMatrix4();
	void WorldMatrix();

	void initModelLocation();
	void handling();
	void SetChickenFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) { walk_velo += speed; }
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void Update() override;

	void SetChickenRunSpeed()override { walk_velo = 0.01f; };
	void SetChickenWalkSpeed()override { walk_velo = 0.002f; };
	void UpdateChickenYpos();
	Dir GetChickenDir()override { return face; }
};

//========================================================================
// 왼쪽 다리
class ChickenLeftLeg : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108

	Sign sign;
	float hand_degree;
	float hand_velo;
	float hand_max_degree;

	Dir face;
	GLfloat  walk_velo;
	GLfloat  face_degree;

	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;
	GLfloat m_far_value{ 0.0025 };

public:

	ChickenLeftLeg(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
		: BasisComponent(),
		sign{ PLUS },
		hand_degree{ 0.f },
		hand_velo{ 0.8f },
		hand_max_degree{ 20.f },
		face{ STOP },
		walk_velo{ 0.002f },
		face_degree{ 0.f },
		m_far_x{ -m_far_value },
		m_far_y{ 0.0 },
		m_far_z{ 0.0 }
	{
		initModelLocation();
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
	void WorldMatrix();

	void initModelLocation();
	void handling();
	void SetChickenFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) { walk_velo += speed; }
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void Update() override;

	void SetChickenRunSpeed()override { walk_velo = 0.01f; };
	void SetChickenWalkSpeed()override { walk_velo = 0.002f; };
	void UpdateChickenYpos();
	Dir GetChickenDir()override { return face; }
};

//========================================================================
// 오른쪽 다리
class ChickenRightLeg : public BasisComponent
{
private:
	//GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	//GLfloat m_color[36 * 3]; // 108

	Sign sign;
	float hand_degree;
	float hand_velo;
	float hand_max_degree;

	Dir face;
	GLfloat  walk_velo;
	GLfloat  face_degree;

	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;
	GLfloat m_far_value{ 0.0025 };

	GLfloat  m_fgravity;
	GLfloat  m_fyvelo;
public:

	ChickenRightLeg(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
		: BasisComponent(),
		sign{ MINUS },
		hand_degree{ 0.f },
		hand_velo{ 0.8f },
		hand_max_degree{ 20.f },
		face{ STOP },
		walk_velo{ 0.002f },
		face_degree{ 0.f },
		m_far_x{ m_far_value },
		m_far_y{ 0.0 },
		m_far_z{ 0.0 }
	{
		initModelLocation();
		InitVertex(cube_array);
		InitColor(color_array);
		InitMatrix4();
		InitBuffer();
	}

//	void InitVertex(const GLfloat rec_array[36 * 6]);
	void InitColor(const GLfloat color_array[36 * 3]) override;
//	void InitBuffer();
	void DrawObject();
	void WorldMatrix();
	void InitMatrix4();

	void initModelLocation();
	void handling();
	void SetChickenFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) { walk_velo += speed; }
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void Update() override;

	void SetChickenRunSpeed()override { walk_velo = 0.01f; };
	void SetChickenWalkSpeed()override { walk_velo = 0.002f; };
	void UpdateChickenYpos();
	Dir GetChickenDir()override { return face; }
};

