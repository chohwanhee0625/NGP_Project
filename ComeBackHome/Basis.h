#pragma once
#include "usingInclude.h"
#include "extern.h"

class Basis
{
protected:
	GLuint  m_vao;
	GLuint  m_pos_vbo;
	GLuint  m_color_vbo;

	glm::mat4 m_Total_world;

	GLfloat m_x_degree;   // 
	GLfloat m_y_degree;   // 기본 각도
	GLfloat m_z_degree;   // 

	GLfloat m_x_distance; // 
	GLfloat m_y_distance; // 기본 위치 
	GLfloat m_z_distance; // 

	GLfloat m_x_scale;  //
	GLfloat	m_y_scale;  // 기본 스케일 
	GLfloat	m_z_scale;  //

	// --------------------------------------------------

public:
	Basis() :
		m_vao{},
		m_pos_vbo{},
		m_color_vbo{},

		m_Total_world{ 1.0f },

		m_x_degree{ 0.f },
		m_y_degree{ 0.f },
		m_z_degree{ 0.f },

		m_x_distance{ 0.f },
		m_y_distance{ 0.f },
		m_z_distance{ 0.f },

		m_x_scale{ 1.f },
		m_y_scale{ 1.f },
		m_z_scale{ 1.f }

		// ---- 기본  ---------------------------------------------
	{}

public:
	virtual void DrawObject() = 0;
	virtual void initMatrix4() = 0;
	virtual ~Basis() {}
	virtual void WorldMatrix();
	void initTotalworld() { m_Total_world = glm::mat4{ 1.0f }; }
	virtual void make_car() = 0;
	virtual void update() = 0;

	float getXmax() { return m_x_distance + m_x_scale / 2; }
	float getXmin() { return m_x_distance - m_x_scale / 2; }

	float getYmax() { return m_y_distance + m_y_scale / 2; }
	float getYmin() { return m_y_distance - m_y_scale / 2; }

	float getZmax() { return m_z_distance + m_z_scale / 2; }
	float getZmin() { return m_z_distance - m_z_scale / 2; }

	float getZdistance() { return m_z_distance; }
	float getXdistance() { return m_x_distance; }
	float GetYdistance() { return m_y_distance; }

	void SetZdistance(float _f) { m_z_distance = _f; }
	void SetYdistance(float _f) { m_y_distance = _f; }
	void SetXdistance(float _f) { m_x_distance = _f; }

	virtual void jump() { ;}
	virtual void update_yPos() { ; }
	virtual void setFaceDir(unsigned char key) { ; }
	virtual Dir Get_dir() { return STOP; }
	virtual int Get_zidx() { return 0; }
	virtual bool Is_final() { return false; }
	virtual void make_line() {};
	virtual void changeboll() {};

	virtual void upvelo() {};
	virtual void downvelo() {};

}; 
