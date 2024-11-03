#include "usingInclude.h"
#include "extern.h"
#include "Basis.h"
#include "Border.h"

//===========================================================================================

void Border::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3; i += 3) {
		m_color[i + 0] = 1.f;
		m_color[i + 1] = 0.50196f;
		m_color[i + 2] = 0.70196f;
	}
}

void Border::DrawObject()
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

void Border::InitMatrix4()
{

	m_x_scale = 1.f;
	m_y_scale = 0.1f;
	m_z_scale = 1.f;

	m_x_pos = 0.f;
	m_y_pos = 0.1;
	m_z_pos = 30.f;


}

void Border::Update()
{
}
