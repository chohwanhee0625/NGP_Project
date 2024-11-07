#include "usingInclude.h"
#include "extern.h"
#include "Basis.h"
#include "Wall.h"

//===========================================================================================

void Wall::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3; i += 3) {
		m_color[i + 0] = 1.f;
		m_color[i + 1] = 0.f;
		m_color[i + 2] = 0.f;
	}
}

void Wall::DrawObject()
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

void Wall::InitMatrix4()
{
	m_x_pos = -0.52f;
	m_y_pos =  0.20f;
	m_z_pos = -7.45f;

	m_x_scale = 0.05f;
	m_y_scale = 0.5f;
	m_z_scale = 15.0;
}

void Wall::Update(float deltatime)
{
}
