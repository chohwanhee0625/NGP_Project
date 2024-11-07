#pragma once
#include "usingInclude.h"
#include "extern.h"

class BasisComponent
{
protected:
	GLuint  m_vao;
	GLuint  m_pos_vbo;
	GLuint  m_color_vbo;

	GLfloat m_vertex[36 * 6]; // Element�� �׸��Ÿ� 4��, �ƴϸ� 6�� 
	GLfloat m_color[36 * 3];  // 108

	glm::mat4 m_total_world;

	GLfloat m_x_degree;   // 
	GLfloat m_y_degree;   // �⺻ ����
	GLfloat m_z_degree;   // 

	GLfloat m_x_pos; // 
	GLfloat m_y_pos; // �⺻ ��ġ 
	GLfloat m_z_pos; // 

	GLfloat m_x_scale;  //
	GLfloat	m_y_scale;  // �⺻ ������ 
	GLfloat	m_z_scale;  //

public:
	BasisComponent() :
		m_vao{},
		m_pos_vbo{},
		m_color_vbo{},

		m_total_world{ 1.0f },

		m_x_degree{ 0.f },
		m_y_degree{ 0.f },
		m_z_degree{ 0.f },

		m_x_pos{ 0.f },
		m_y_pos{ 0.f },
		m_z_pos{ 0.f },

		m_x_scale{ 1.f },
		m_y_scale{ 1.f },
		m_z_scale{ 1.f }
	{}

	virtual ~BasisComponent() {}

	void InitTotalworld() { m_total_world = glm::mat4{ 1.0f }; }

	// �ִ�, �ּ� ��� ��ȯ �Լ�
	float GetXmaxBoundary() { return m_x_pos + m_x_scale / 2; }
	float GetXminBoundary() { return m_x_pos - m_x_scale / 2; }

	float GetYmaxBoundary() { return m_y_pos + m_y_scale / 2; }
	float GetYminBoundary() { return m_y_pos - m_y_scale / 2; }

	float GetZmaxBoundary() { return m_z_pos + m_z_scale / 2; }
	float GetZminBoundary() { return m_z_pos - m_z_scale / 2; }

	// Getter, Setter Position
	float GetZpos() { return m_z_pos; }
	float GetXpos() { return m_x_pos; }
	float GetYpos() { return m_y_pos; }

	void SetZpos(float _f) { m_z_pos = _f; }
	void SetYpos(float _f) { m_y_pos = _f; }
	void SetXpos(float _f) { m_x_pos = _f; }

	// BasisComponent
	void WorldMatrix();
	//virtual void WorldMatrix();

public:
	// ���� ���� �Լ�: ��� Ŭ������ �Լ��� ������ �ϵ��� �����ϴ� ���� (�ڵ��� ��Ȯ���� �ö����� �������� ������)

	virtual void InitMatrix4() = 0;
	virtual void DrawObject() = 0;
	virtual void Update(float value) = 0;

public:
	// �Ϲ� ���� �Լ�: �Լ��� �����ǰ� �ʼ��� �ƴ� (���� Ŭ������ �Լ� ����� ����ϰų�, �ڽ� Ŭ�������� �Լ� ������ ���ɼ� ������ �� ��)

	virtual void InitVertex(const GLfloat rec_array[36 * 6]);
	virtual void InitColor(const GLfloat color_array[36 * 3]);
	virtual void InitBuffer();

	// Car
	virtual void CreateCar() {}

	// Chicken
	virtual void ChickenJump() {}
	virtual void SetChickenRunSpeed() {}
	virtual void SetChickenWalkSpeed() {}
	virtual void SetChickenFaceDir(unsigned char key) {}
	virtual Dir GetChickenDir() { return STOP; }
	virtual void SwitchCollisionState() {} // �浹 �˻� on/off

	// Road, Grass 
	virtual int GetZindex() { return 0; }

	// Grass
	virtual bool IsFinalGrass() { return false; }

	// Road
	virtual void CreateLane() {}
}; 
