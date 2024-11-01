#include "usingInclude.h"
#include "extern.h"
#include "Basis.h"
#include "Tree.h"

// --------------------------------------------------------------------------

void tagWood::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagWood::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3; i += 3) {
		m_color[i + 0] = 0.3059f;
		m_color[i + 1] = 0.1373f;
		m_color[i + 2] = 0.1765f;
	}
}

void tagWood::InitBuffer()
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

void tagWood::DrawObject()
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

void tagWood::initMatrix4()
{
	m_x_scale = 0.03f;
	m_y_scale = 0.15f;
	m_z_scale = 0.03f;

	m_x_distance = -0.46 + 0.07 * m_x_idx;
	m_y_distance = 0.;
	m_z_distance = -(m_z_idx * 0.1);
}

void tagWood::update()
{
}

// --------------------------------------------------------------------------

void tagLeafone::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagLeafone::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3; i += 3) {
		m_color[i + 0] = 0.7098f;
		m_color[i + 1] = 0.8392f;
		m_color[i + 2] = 0.1373f;
	}
}

void tagLeafone::InitBuffer()
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

void tagLeafone::DrawObject()
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

void tagLeafone::initMatrix4()
{
	m_x_scale = 0.05f;
	m_y_scale = 0.03f;
	m_z_scale = 0.05f;

	m_x_distance = -0.46 + 0.07 * m_x_idx;
	m_y_distance = 0.05;
	m_z_distance = -(m_z_idx * 0.1);
}

void tagLeafone::update()
{
	m_y_degree += 0.2;
}

void tagLeafone::WorldMatrix()
{
	initTotalworld();

	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_x_distance, m_y_distance, m_z_distance)); // 기본 이동 
	m_Total_world = glm::rotate(m_Total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴
	m_Total_world = glm::scale(m_Total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_Total_world));
}

// --------------------------------------------------------------------------

void tagLeaftwo::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagLeaftwo::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3; i += 3) {
		m_color[i + 0] = 0.4549f;
		m_color[i + 1] = 0.5451f;
		m_color[i + 2] = 0.0902f;
	}
}

void tagLeaftwo::InitBuffer()
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

void tagLeaftwo::DrawObject()
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

void tagLeaftwo::initMatrix4()
{
	m_x_scale = 0.05f;
	m_y_scale = 0.03f;
	m_z_scale = 0.05f;
	
	m_x_distance = -0.46 + 0.07 * m_x_idx;
	m_y_distance = 0.05 +  m_y_scale ;
	m_z_distance = -(m_z_idx * 0.1);
}

void tagLeaftwo::update()
{
	m_y_degree += 0.2;
}

void tagLeaftwo::WorldMatrix()
{
	initTotalworld();

	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_x_distance, m_y_distance, m_z_distance)); // 기본 이동 
	m_Total_world = glm::rotate(m_Total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴
	m_Total_world = glm::scale(m_Total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_Total_world));
}

// --------------------------------------------------------------------------

void tagLeafthree::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagLeafthree::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3; i += 3) {
		m_color[i + 0] = 0.7098f;
		m_color[i + 1] = 0.8392f;
		m_color[i + 2] = 0.1373f;
	}
}

void tagLeafthree::InitBuffer()
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

void tagLeafthree::DrawObject()
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

void tagLeafthree::initMatrix4()
{
	m_x_scale = 0.05f;
	m_y_scale = 0.03f;
	m_z_scale = 0.05f;

	m_x_distance = -0.46 + 0.07 * m_x_idx;
	m_y_distance = 0.05 + m_y_scale * 2;
	m_z_distance = -(m_z_idx * 0.1);
}

void tagLeafthree::update()
{
	m_y_degree += 0.2;
}

void tagLeafthree::WorldMatrix()
{
	
	initTotalworld();

	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_x_distance, m_y_distance, m_z_distance)); // 기본 이동 
	m_Total_world = glm::rotate(m_Total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴
	m_Total_world = glm::scale(m_Total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_Total_world));
}
