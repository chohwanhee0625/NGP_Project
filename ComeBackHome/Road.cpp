#include "usingInclude.h"
#include "extern.h"
#include "Basis.h"
#include "Road.h"
#include "Car.h"

//===========================================================================================

void tagRoad::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagRoad::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3; i += 3) {
		  m_color[i + 0] = 0.2824f;
      m_color[i + 1] = 0.3059f;
      m_color[i + 2] = 0.3608f;
	}
}

void tagRoad::InitBuffer()
{
	glGenVertexArrays(1, &this->m_vao);
	glBindVertexArray(this->m_vao);

	glGenBuffers(1, &this->m_pos_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_pos_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_vertex), this->m_vertex, GL_STATIC_DRAW);

	int PosLocation = glGetAttribLocation(gShaderProgramID, "in_Position");
	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(PosLocation);

	int NormalLocation = glGetAttribLocation(gShaderProgramID, "in_Normal");
	glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(NormalLocation);

	glGenBuffers(1, &this->m_color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_color_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_color), this->m_color, GL_STATIC_DRAW);

	int ColorLocation = glGetAttribLocation(gShaderProgramID, "in_Color");
	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

}

void tagRoad::DrawObject()
{
	int PosLocation = glGetAttribLocation(gShaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(gShaderProgramID, "in_Color");
	int NormalLocation = glGetAttribLocation(gShaderProgramID, "in_Normal");

	glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미
	glEnableVertexAttribArray(ColorLocation);
	glEnableVertexAttribArray(NormalLocation);

	glBindVertexArray(this->m_vao);

	WorldMatrix();

	glDrawArrays(GL_TRIANGLES, 0, 36); // 1 앞면

	glDisableVertexAttribArray(PosLocation); // Disable 필수!
	glDisableVertexAttribArray(ColorLocation);
	glDisableVertexAttribArray(NormalLocation);

}

void tagRoad::InitMatrix4()
{
	m_x_scale = 2.5f;
	m_y_scale = 1.f;
	m_z_scale = 0.1;

	m_x_pos = 0.f;
	m_y_pos = -0.52;
	m_z_pos = -(m_inum * m_z_scale);
}

void tagRoad::Update()
{
}

void tagRoad::CreateCar()
{
	tagCar* car = new tagCar(m_vertex, m_color, m_dir, m_inum);
	gVec.push_back(car);
}

void tagRoad::initDir(GLboolean dir)
{
	if (dir == LEFT)
		m_dir = PLUS;
	else if (dir == RIGHT)
		m_dir = MINUS;
}

//===========================================================================================

void tagRoadLane::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagRoadLane::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3; i += 3) {
		m_color[i + 0] = 0.5235f;
		m_color[i + 1] = 0.5510f;
		m_color[i + 2] = 0.6569f;
	}
}

void tagRoadLane::InitBuffer()
{
	glGenVertexArrays(1, &this->m_vao);
	glBindVertexArray(this->m_vao);

	glGenBuffers(1, &this->m_pos_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_pos_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_vertex), this->m_vertex, GL_STATIC_DRAW);

	int PosLocation = glGetAttribLocation(gShaderProgramID, "in_Position");
	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(PosLocation);

	int NormalLocation = glGetAttribLocation(gShaderProgramID, "in_Normal");
	glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(NormalLocation);

	glGenBuffers(1, &this->m_color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_color_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_color), this->m_color, GL_STATIC_DRAW);

	int ColorLocation = glGetAttribLocation(gShaderProgramID, "in_Color");
	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

}

void tagRoadLane::DrawObject()
{
	int PosLocation = glGetAttribLocation(gShaderProgramID, "in_Position");
	int ColorLocation = glGetAttribLocation(gShaderProgramID, "in_Color");
	int NormalLocation = glGetAttribLocation(gShaderProgramID, "in_Normal");

	glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미
	glEnableVertexAttribArray(ColorLocation);
	glEnableVertexAttribArray(NormalLocation);

	glBindVertexArray(this->m_vao);

	WorldMatrix();

	glDrawArrays(GL_TRIANGLES, 0, 36); // 1 앞면

	glDisableVertexAttribArray(PosLocation); // Disable 필수!
	glDisableVertexAttribArray(ColorLocation);
	glDisableVertexAttribArray(NormalLocation);
}

void tagRoadLane::InitMatrix4()
{
	m_x_scale = 0.07f;
	m_y_scale = 0.01f;
	m_z_scale = 0.0115f;

	m_x_pos = -0.46 + 0.15 * m_x_idx; // m_idx 범위 (0~6), 0.15는 선 간격
	m_y_pos = -0.02458; // 고정 상수 
	m_z_pos = -(m_z_idx * 0.1 + 0.05); // +0.05는 도로 반쪽 길이만큼 더한거 -> 안하면 도로가 선 위로 주행함 
}

void tagRoad::CreateLane()
{
	tagRoadLane* pLine{};
	for (int i = -2; i < 8; ++i) {
		pLine = new tagRoadLane{ m_vertex, m_color, i ,m_inum };
		gVec.push_back(pLine);
	}
}