#pragma once
// �� ������ �簢���̴� ���� �ɰ��� ��ȯ�� �����ϴ� ����
 
class BasisComponent;


//========================================================================
// ��
class tagBody : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element�� �׸��Ÿ� 4��, �ƴϸ� 6�� 
	GLfloat m_color[36 * 3]; // 108

	Dir face;
	GLfloat  walk_velo;
	GLfloat  face_degree;

	GLfloat  m_fgravity;
	GLfloat  m_fyvelo;

	bool	m_coll;
public:

	tagBody(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
		: BasisComponent(),
		face{ STOP },
		walk_velo{ 0.002f },
		face_degree{ 0.f },
		m_fgravity{0.00015f},
		m_fyvelo{0},
		m_coll{true}
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
	void setFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) { walk_velo += speed; }
	virtual void make_car() {};

	void update() override;
	void Collision();

	void update_yvelo();
	void Set_yvelo_zero();

	void update_yPos()override;
	void jump();

	void upvelo()override { walk_velo = 0.01f; };
	void downvelo()override { walk_velo = 0.002f; };

	Dir Get_dir()override { return face; }

	void changeboll()override {
		if (m_coll) m_coll = false;
		else m_coll = true;
	}
};

//========================================================================
// �Ӹ�
class tagHead : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element�� �׸��Ÿ� 4��, �ƴϸ� 6�� 
	GLfloat m_color[36 * 3]; // 108

	Dir face;
	GLfloat  walk_velo;
	GLfloat  face_degree;

public:

	tagHead(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
		: BasisComponent(),
		face{ STOP },
		walk_velo{ 0.002f },
		face_degree{ 0.f }
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
	void setFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) {
		walk_velo += speed;
	}
	void update() override;
	virtual void make_car() {};

	void update_yPos()override;
	void upvelo()override { walk_velo = 0.01f; };
	void downvelo()override { walk_velo = 0.002f; };
	Dir Get_dir()override { return face; }
};

//========================================================================
// ��
class tagMouse : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element�� �׸��Ÿ� 4��, �ƴϸ� 6�� 
	GLfloat m_color[36 * 3]; // 108

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

	tagMouse(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
		: BasisComponent(),
		face{ STOP },
		walk_velo{ 0.002f },
		face_degree{ 0.f },
		m_far_x{ 0.0 },
		m_far_y{ 0.0 },
		m_far_z{ m_far_value }
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

	void setFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) {
		walk_velo += speed;
	}
	void update() override;
	virtual void make_car() {};

	float Get_yvelo() { return m_fyvelo; }
	void upvelo()override { walk_velo = 0.01f; };
	void downvelo()override { walk_velo = 0.002f; };
	void update_yPos()override;
	Dir Get_dir()override { return face; }
};

//========================================================================
// ��
class tagEyes : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element�� �׸��Ÿ� 4��, �ƴϸ� 6�� 
	GLfloat m_color[36 * 3]; // 108

	Dir face;
	GLfloat  walk_velo;
	GLfloat  face_degree;

	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;
	GLfloat m_far_value{ 0.00 };


public:

	tagEyes(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
		: BasisComponent(),
		face{ STOP },
		walk_velo{ 0.002f },
		face_degree{ 0.f },
		m_far_x{ 0.0 },
		m_far_y{ 0.0 },
		m_far_z{ m_far_value }
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
	void setFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) {
		walk_velo += speed;
	}
	void update() override;
	virtual void make_car() {};
	void upvelo()override { walk_velo = 0.01f; };
	void downvelo()override { walk_velo = 0.002f; };
	void update_yPos()override;
	Dir Get_dir()override { return face; }
};

//========================================================================
// ���� ��
class tagLeftArm : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element�� �׸��Ÿ� 4��, �ƴϸ� 6�� 
	GLfloat m_color[36 * 3]; // 108

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

	tagLeftArm(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
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
	void handling();
	void setFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) { walk_velo += speed; }
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void update() override;
	virtual void make_car() {};
	void upvelo()override { walk_velo = 0.01f; };
	void downvelo()override { walk_velo = 0.002f; };
	void update_yPos()override;
	Dir Get_dir()override { return face; }
};

//========================================================================
// ������ ��  
class tagRightArm : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element�� �׸��Ÿ� 4��, �ƴϸ� 6�� 
	GLfloat m_color[36 * 3]; // 108

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

	tagRightArm(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
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
	void handling();
	void setFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) { walk_velo += speed; }
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void update() override;
	virtual void make_car() {};
	void upvelo()override { walk_velo = 0.01f; };
	void downvelo()override { walk_velo = 0.002f; };
	void update_yPos()override;
	Dir Get_dir()override { return face; }
};

//========================================================================
// ���� �ٸ�
class tagLeftLeg : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element�� �׸��Ÿ� 4��, �ƴϸ� 6�� 
	GLfloat m_color[36 * 3]; // 108

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

	tagLeftLeg(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
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
	void handling();
	void setFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) { walk_velo += speed; }
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void update() override;
	virtual void make_car() {};
	void upvelo()override { walk_velo = 0.01f; };
	void downvelo()override { walk_velo = 0.002f; };
	void update_yPos()override;
	Dir Get_dir()override { return face; }
};

//========================================================================
// ������ �ٸ�
class tagRightLeg : public BasisComponent
{
private:
	GLfloat m_vertex[36 * 6]; // Element�� �׸��Ÿ� 4��, �ƴϸ� 6�� 
	GLfloat m_color[36 * 3]; // 108

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

	tagRightLeg(const GLfloat cube_array[36 * 6], const GLfloat color_array[36 * 3])
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
	void handling();
	void setFaceDir(unsigned char key);
	void Walk();
	void setWalkVelo(float speed) { walk_velo += speed; }
	void setHandDegree(float degree) { hand_max_degree += degree; }
	void update() override;
	virtual void make_car() {};
	void upvelo()override { walk_velo = 0.01f; };
	void downvelo()override { walk_velo = 0.002f; };
	void update_yPos()override;
	Dir Get_dir()override { return face; }
};

