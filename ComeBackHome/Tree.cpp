#include "usingInclude.h"
#include "extern.h"
#include "Basis.h"
#include "Tree.h"

//===========================================================================================

void Wood::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3; i += 3) {
		m_color[i + 0] = 0.3059f;
		m_color[i + 1] = 0.1373f;
		m_color[i + 2] = 0.1765f;
	}
}

void Wood::DrawObject()
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

void Wood::InitMatrix4()
{
	m_x_scale = 0.03f;
	m_y_scale = 0.15f;
	m_z_scale = 0.03f;

	m_x_pos = -0.46 + 0.07 * m_x_idx;
	m_y_pos = 0.;
	m_z_pos = -(m_z_idx * 0.1);
}

void Wood::Update()
{
}

//===========================================================================================

void WoodLeaf_1::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3; i += 3) {
		m_color[i + 0] = 0.7098f;
		m_color[i + 1] = 0.8392f;
		m_color[i + 2] = 0.1373f;
	}
}

void WoodLeaf_1::DrawObject()
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

void WoodLeaf_1::InitMatrix4()
{
	m_x_scale = 0.05f;
	m_y_scale = 0.03f;
	m_z_scale = 0.05f;

	m_x_pos = -0.46 + 0.07 * m_x_idx;
	m_y_pos = 0.05;
	m_z_pos = -(m_z_idx * 0.1);
}

void WoodLeaf_1::Update()
{
	m_y_degree += 0.2;
}

void WoodLeaf_1::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴
	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

//===========================================================================================

void WoodLeaf_2::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3; i += 3) {
		m_color[i + 0] = 0.4549f;
		m_color[i + 1] = 0.5451f;
		m_color[i + 2] = 0.0902f;
	}
}

void WoodLeaf_2::DrawObject()
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

void WoodLeaf_2::InitMatrix4()
{
	m_x_scale = 0.05f;
	m_y_scale = 0.03f;
	m_z_scale = 0.05f;
	
	m_x_pos = -0.46 + 0.07 * m_x_idx;
	m_y_pos = 0.05 +  m_y_scale ;
	m_z_pos = -(m_z_idx * 0.1);
}

void WoodLeaf_2::Update()
{
	m_y_degree += 0.2;
}

void WoodLeaf_2::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴
	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

//===========================================================================================

void WoodLeaf_3::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3; i += 3) {
		m_color[i + 0] = 0.7098f;
		m_color[i + 1] = 0.8392f;
		m_color[i + 2] = 0.1373f;
	}
}

void WoodLeaf_3::DrawObject()
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

void WoodLeaf_3::InitMatrix4()
{
	m_x_scale = 0.05f;
	m_y_scale = 0.03f;
	m_z_scale = 0.05f;

	m_x_pos = -0.46 + 0.07 * m_x_idx;
	m_y_pos = 0.05 + m_y_scale * 2;
	m_z_pos = -(m_z_idx * 0.1);
}

void WoodLeaf_3::Update()
{
	m_y_degree += 0.2;
}

void WoodLeaf_3::WorldMatrix()
{
	
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴
	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}
