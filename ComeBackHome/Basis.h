#pragma once
#include "usingInclude.h"
#include "extern.h"

class BasisComponent
{
protected:
	GLuint  m_vao;
	GLuint  m_pos_vbo;
	GLuint  m_color_vbo;

	GLfloat m_vertex[36 * 6]; // Element로 그릴거면 4개, 아니면 6개 
	GLfloat m_color[36 * 3];  // 108

	glm::mat4 m_total_world;

	GLfloat m_x_degree;   // 
	GLfloat m_y_degree;   // 기본 각도
	GLfloat m_z_degree;   // 

	GLfloat m_x_pos; // 
	GLfloat m_y_pos; // 기본 위치 
	GLfloat m_z_pos; // 

	GLfloat m_x_scale;  //
	GLfloat	m_y_scale;  // 기본 스케일 
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

	// 최대, 최소 경계 반환 함수
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
	// 순수 가상 함수: 모든 클래스가 함수를 재정의 하도록 강제하는 역할 (코드의 명확성이 올라가지만 유연성이 떨어짐)

	virtual void InitMatrix4() = 0;
	virtual void DrawObject() = 0;
	virtual void Update(float value) = 0;

public:
	// 일반 가상 함수: 함수의 재정의가 필수가 아님 (상위 클래스의 함수 기능을 사용하거나, 자신 클래스에서 함수 재정의 가능성 열고자 할 때)

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
	virtual void SwitchCollisionState() {} // 충돌 검사 on/off

	// Road, Grass 
	virtual int GetZindex() { return 0; }

	// Grass
	virtual bool IsFinalGrass() { return false; }

	// Road
	virtual void CreateLane() {}
}; 
