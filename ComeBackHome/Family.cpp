#include "usingInclude.h"
#include "extern.h"
#include "Basis.h"
#include "Family.h"
#include "소스.h"
#include "Camera.h"
#include "Car.h"
#include "Tree.h"

//===========================================================================================

const float v{ 0.001 };

void MotherBody::DrawObject()
{
	// --------------------------------------------------------------------------------
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

void MotherBody::InitBuffer()
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

void MotherBody::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.f;
		m_color[i + 1] = 1.0f;
		m_color[i + 2] = 1.;
	}
}

void MotherBody::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void MotherBody::InitMatrix4()
{
	m_x_scale = 0.01f * 50;
	m_y_scale = 0.01f * 50;
	m_z_scale = 0.01f * 50;

	m_x_pos = 0.f;
	m_y_pos = 0.5 * m_y_scale * 1.5;
	m_z_pos = -0.1f * idx;
}

void MotherBody::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(180.f), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴
	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void MotherBody::Update()
{
	if (gIsReach)
	{
		m_y_pos += v;
		m_z_pos += v;
	}
}

void MotherBody::initModelLocation()
{
}

//===========================================================================================

void MotherHead::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void MotherHead::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.0f;
		m_color[i + 1] = 1.0f;
		m_color[i + 2] = 1.0f;
	}
}

void MotherHead::InitBuffer()
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

void MotherHead::DrawObject()
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

void MotherHead::InitMatrix4()
{
	m_x_scale = 0.01f * 50;
	m_y_scale = 0.01f * 50;
	m_z_scale = 0.01f * 50;

	m_x_pos = 0.f;
	m_y_pos = 0.01 * 25 + 0.5 * m_y_scale * 2;
	m_z_pos = -0.1f * idx;
}

void MotherHead::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(180.f), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴
	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void MotherHead::Update()
{
	if (gIsReach)
	{
		m_y_pos += v;
		m_z_pos += v;
	}
}

void MotherHead::initModelLocation()
{
}

//===========================================================================================

void MotherMouse::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void MotherMouse::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.99607843137f;
		m_color[i + 1] = 0.43921568627f;
		m_color[i + 2] = 0.29803921568f;
	}
}

void MotherMouse::InitBuffer()
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

void MotherMouse::DrawObject()
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

void MotherMouse::InitMatrix4()
{
	m_x_scale = 0.01f / 4 * 50.f;
	m_y_scale = 0.01f / 3 * 50.f;
	m_z_scale = 0.0125f * 50.f;

	m_x_pos = 0.0f;
	m_y_pos = 0.01 * 50 + 0.5 * m_y_scale * 2;
	m_z_pos = -0.1f * idx; +0.1; //-14.90f;
}

void MotherMouse::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::rotate(m_total_world, glm::radians(m_x_degree), glm::vec3(1.0f, 0.0f, 0.0f)); // x축 회전 기본
	m_total_world = glm::rotate(m_total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 회전 기본
	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 

	m_total_world = glm::translate(m_total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(0.f), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴

	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void MotherMouse::Update()
{
	if (gIsReach)
	{
		m_y_pos += v;
		m_z_pos += v;
	}
}

void MotherMouse::initModelLocation()
{
	m_far_value = 0.002;

	m_far_x = 0.0;
	m_far_y = 0.0;
	m_far_z = m_far_value;
}

//===========================================================================================

void MotherEyes::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void MotherEyes::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.;
		m_color[i + 1] = 0.;
		m_color[i + 2] = 0.;
	}
}

void MotherEyes::InitBuffer()
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

void MotherEyes::DrawObject()
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

void MotherEyes::InitMatrix4()
{
	m_x_scale = 0.011f * 55.;
	m_y_scale = 0.01f / 5 * 50.;
	m_z_scale = 0.01f / 5 * 50.;

	m_x_pos = 0.f;
	m_y_pos = 0.0105 * 60 + 0.5 * m_y_scale * 2;
	m_z_pos = -0.1f * idx;
}

void MotherEyes::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(0.f), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴
	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void MotherEyes::Update()
{
	if (gIsReach)
	{
		m_y_pos += v;
		m_z_pos += v;
	}
}

void MotherEyes::initModelLocation()
{
	m_far_value = 0.0;

	m_far_x = 0.0;
	m_far_y = 0.0;
	m_far_z = m_far_value;
}

//===========================================================================================

void MotherLeftArm::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void MotherLeftArm::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.9f;
		m_color[i + 1] = 0.9f;
		m_color[i + 2] = 0.9f;
	}
}

void MotherLeftArm::InitBuffer()
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

void MotherLeftArm::DrawObject()
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

void MotherLeftArm::InitMatrix4()
{
	m_x_scale = 0.00125f * 50.f;
	m_y_scale = 0.005f * 60.f;
	m_z_scale = 0.005f * 60.f;

	m_x_pos = 0.0;
	m_y_pos = 0.0005f * 50+ 0.5 * m_y_scale * 2;
	m_z_pos = -0.1f * idx;

}

void MotherLeftArm::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::rotate(m_total_world, glm::radians(m_x_degree), glm::vec3(1.0f, 0.0f, 0.0f)); // x축 회전 기본
	m_total_world = glm::rotate(m_total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 회전 기본 
	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 

	m_total_world = glm::translate(m_total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(0.f), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴

	m_total_world = glm::translate(m_total_world, glm::vec3(0, 0.125 * 0.025, 0)); // 기본 이동
	m_total_world = glm::rotate(m_total_world, glm::radians(hand_degree), glm::vec3(0.0f, 0.0f, 1.0f));
	m_total_world = glm::translate(m_total_world, glm::vec3(0, -0.125 * 0.025, 0)); // 기본 이동

	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void MotherLeftArm::Update()
{
	if (sign == PLUS && hand_degree >= hand_max_degree) {
		sign = MINUS;
	}
	if (sign == MINUS && hand_degree <= 0) {
		sign = PLUS;
	}

	hand_degree += hand_velo * sign;

	if (gIsReach)
	{
		m_y_pos += v;
		m_z_pos += v;
	}
}

void MotherLeftArm::initModelLocation()
{
	sign = MINUS;
	hand_degree = 0.f;
	hand_velo = 0.4f;
	hand_max_degree = 45.f;

	m_far_value = 0.005 * 55;

	m_far_x = m_far_value;
	m_far_y = 0.0;
	m_far_z = 0.0;
}

//===========================================================================================

void MotherRightArm::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void MotherRightArm::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.9f;
		m_color[i + 1] = 0.9f;
		m_color[i + 2] = 0.9f;
	}
}

void MotherRightArm::InitBuffer()
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

void MotherRightArm::DrawObject()
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

void MotherRightArm::InitMatrix4()
{
	m_x_scale = 0.00125f * 50;
	m_y_scale = 0.005f * 60.f;
	m_z_scale = 0.005f * 60.f;

	m_x_pos = 0.0;
	m_y_pos = 0.0005f * 50 + 0.5 * m_y_scale * 2;
	m_z_pos = -0.1f * idx;

}

void MotherRightArm::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 

	m_total_world = glm::translate(m_total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(0.f), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴

	m_total_world = glm::translate(m_total_world, glm::vec3(0, 0.125 * 0.025, 0)); // 기본 이동
	m_total_world = glm::rotate(m_total_world, glm::radians(-hand_degree), glm::vec3(0.0f, 0.0f, 1.0f));
	m_total_world = glm::translate(m_total_world, glm::vec3(0, -0.125 * 0.025, 0)); // 기본 이동

	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void MotherRightArm::Update()
{
	if (sign == PLUS && hand_degree >= hand_max_degree) {
		sign = MINUS;
	}
	if (sign == MINUS && hand_degree <= 0) {
		sign = PLUS;
	}

	hand_degree += hand_velo * sign;

	if (gIsReach)
	{
		m_y_pos += v;
		m_z_pos += v;
	}
}

void MotherRightArm::initModelLocation()
{
	sign = PLUS;
	hand_degree = 0.f;
	hand_velo = 0.4f;
	hand_max_degree = 45.f;

	m_far_value = 0.005 * 55;

	m_far_x = -m_far_value;
	m_far_y = 0.0;
	m_far_z = 0.0;
}

//===========================================================================================

void MotherLeftLeg::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void MotherLeftLeg::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.0f;
		m_color[i + 1] = 0.47843137254f;
		m_color[i + 2] = 0.34509803921f;
	}
}

void MotherLeftLeg::InitBuffer()
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

void MotherLeftLeg::DrawObject()
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

void MotherLeftLeg::InitMatrix4()
{
	m_x_scale = 0.00125f * 50.;
	m_y_scale = 0.0125f * 50.;
	m_z_scale = 0.00125f * 50.;

	m_x_pos = 0.f;
	m_y_pos = -0.005f + 0.15 * m_y_scale;
	m_z_pos = -0.1f * idx;
}

void MotherLeftLeg::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동

	m_total_world = glm::translate(m_total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(0.f), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴

	m_total_world = glm::translate(m_total_world, glm::vec3(0, 0.125 * 0.025, 0)); // 기본 이동
	m_total_world = glm::rotate(m_total_world, glm::radians(hand_degree), glm::vec3(1.0f, 0.0f, 0.0f));
	m_total_world = glm::translate(m_total_world, glm::vec3(0, -0.125 * 0.025, 0)); // 기본 이동

	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void MotherLeftLeg::Update()
{
	if (sign == PLUS && hand_degree >= hand_max_degree) {
		sign = MINUS;
	}
	if (sign == MINUS && hand_degree <= -hand_max_degree) {
		sign = PLUS;
	}


	hand_degree += hand_velo * sign;

	if (gIsReach)
	{
		m_y_pos += v;
		m_z_pos += v;
	}
}

void MotherLeftLeg::initModelLocation()
{
	sign = PLUS;
	hand_degree = 0.f;
	hand_velo = 0.4f;
	hand_max_degree = 20.f;

	m_far_value = 0.0025 * 50;

	m_far_x = m_far_value;
	m_far_y = 0.0;
	m_far_z = 0.0;
}

//===========================================================================================

void MotherRightLeg::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void MotherRightLeg::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.0f;
		m_color[i + 1] = 0.47843137254f;
		m_color[i + 2] = 0.34509803921f;
	}
}

void MotherRightLeg::InitBuffer()
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

void MotherRightLeg::DrawObject()
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

void MotherRightLeg::InitMatrix4()
{
	m_x_scale = 0.00125f * 50.;
	m_y_scale = 0.0125f * 50.;
	m_z_scale = 0.00125f * 50.;

	m_x_pos = 0.f;
	m_y_pos = -0.005f + 0.15 * m_y_scale;
	m_z_pos = -0.1f * idx;
}

void MotherRightLeg::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::rotate(m_total_world, glm::radians(m_x_degree), glm::vec3(1.0f, 0.0f, 0.0f)); // x축 회전 기
	m_total_world = glm::rotate(m_total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 회전 기본 
	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 

	m_total_world = glm::translate(m_total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(0.f), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴

	m_total_world = glm::translate(m_total_world, glm::vec3(0, 0.125 * 0.025, 0)); // 기본 이동
	m_total_world = glm::rotate(m_total_world, glm::radians(hand_degree), glm::vec3(1.0f, 0.0f, 0.0f));
	m_total_world = glm::translate(m_total_world, glm::vec3(0, -0.125 * 0.025, 0)); // 기본 이동

	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void MotherRightLeg::Update()
{
	if (sign == PLUS && hand_degree >= hand_max_degree) {
		sign = MINUS;
	}
	if (sign == MINUS && hand_degree <= -hand_max_degree) {
		sign = PLUS;
	}


	hand_degree += hand_velo * sign;

	if (gIsReach)
	{
		m_y_pos += v;
		m_z_pos += v;
	}
}

void MotherRightLeg::initModelLocation()
{
	sign = MINUS;
	hand_degree = 0.f;
	hand_velo = 0.4f;
	hand_max_degree = 20.f;

	m_far_value = 0.0025 * 50;

	m_far_x = -m_far_value;
	m_far_y = 0.0;
	m_far_z = 0.0;
}
