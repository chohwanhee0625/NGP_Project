#include "usingInclude.h"
#include "Basis.h"
#include "Car.h"
#include "extern.h"

//===========================================================================================

void Car::Move()
{
	// 0 : LEFT  -> PLUS -> 왼쪽에서 태어나서 오른쪽으로 이동
	// 1 : RIGHT -> MINUS -> 오른쪽에서 태어나서 왼쪽으로 이동

	// Plus [+1] : 왼쪽에서 생성    -> 이동방향 + 오른쪽
	// Minus[-1] : 오른쪽에서 생성  -> 이동방향 - 왼쪽

	m_x_pos += m_velocity * m_dir;

	if (m_dir == PLUS  && m_x_pos > 0.55 )
		m_x_pos = -0.55f;
	else if (m_dir == MINUS && m_x_pos < -0.55)
		m_x_pos = 0.55f;
}

void Car::Update()
{
	Move();
}

void Car::InitColor(const GLfloat color_array[36 * 3])
{
	float R = grandomcolor(gRandomEngine);
	float G = grandomcolor(gRandomEngine);
	float B = grandomcolor(gRandomEngine);

	for (int i = 0; i < 36 * 3; i += 3) {
		m_color[i + 0] = R;
		m_color[i + 1] = G;
		m_color[i + 2] = B;
	}
}

void Car::DrawObject()
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

void Car::InitMatrix4()
{
	m_x_scale = 0.07f;
	m_y_scale = 0.025f;
	m_z_scale = 0.05;

	m_x_pos = -0.55f * m_dir;
	m_y_pos = 0.005;
	m_z_pos = -0.1 * m_idx; //(0.1f + (0.1 * (float)m_idx)); //* m_idx;
//	m_z_distance = -0.5f * m_idx;

	m_velocity = m_velocity + (m_idx * 0.000015 * gCarspeed(gRandomEngine));
}

void Car::CreateCar()
{
	CarMiddle* middle = new CarMiddle(m_vertex, m_color, m_dir, m_idx, m_velocity);
	gVec.push_back(middle);

	CarWindow* winodw = new CarWindow(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(winodw);

	// 왼쪽 앞
	CarWheel_1* wheel_1 = new CarWheel_1(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_1);
	CarSmallWheel_1* wheel_1_small = new CarSmallWheel_1(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_1_small);

	// 왼쪽 뒤 
	CarWheel_2* wheel_2 = new CarWheel_2(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_2);
	CarSmallWheel_2* wheel_2_small = new CarSmallWheel_2(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_2_small);

	// 오른쪽 앞
	CarWheel_3* wheel_3 = new CarWheel_3(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_3);
	CarSmallWheel_3* wheel_3_small = new CarSmallWheel_3(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_3_small);

	// 오른쪽 뒤
	CarWheel_4* wheel_4 = new CarWheel_4(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_4);
	CarSmallWheel_4* wheel_4_small = new CarSmallWheel_4(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_4_small);
}

//===========================================================================================

void CarMiddle::Move()
{
	m_x_pos += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_pos > 0.55)
		m_x_pos = -0.55f;
	else if (m_dir == MINUS && m_x_pos < -0.55)
		m_x_pos = 0.55f;
}

void CarMiddle::Update()
{
	Move();
}

void CarMiddle::DrawObject()
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

void CarMiddle::InitMatrix4()
{
	m_x_scale = 0.04f;
	m_y_scale = 0.03f;
	m_z_scale = 0.05;

	m_x_pos = -0.55f * m_dir;
	m_y_pos = 0.005 + 0.5 * m_y_scale;
	m_z_pos = -0.1 * m_idx; //(0.1f + (0.1 * (float)m_idx)); //* m_idx;
	//	m_z_distance = -0.5f * m_idx;
}

//===========================================================================================

void CarWindow::Move()
{
	m_x_pos += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_pos > 0.55)
		m_x_pos = -0.55f;
	else if (m_dir == MINUS && m_x_pos < -0.55)
		m_x_pos = 0.55f;
}

void CarWindow::Update()
{
	Move();
}

void CarWindow::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.6294f; // 0.5294f;
		m_color[i + 1] = 0.9078f; // 0.8078f;
		m_color[i + 2] = 0.9216;
	}
}

void CarWindow::DrawObject()
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

void CarWindow::InitMatrix4()
{
	m_x_scale = 0.03f;
	m_y_scale = 0.017f;
	m_z_scale = 0.05001;

	m_x_pos = -0.55f * m_dir;
	m_y_pos = 0.013 + 0.5 * m_y_scale;
	m_z_pos = -0.1 * m_idx; //(0.1f + (0.1 * (float)m_idx)); //* m_idx;
	//	m_z_distance = -0.5f * m_idx;
}

//===========================================================================================

void CarWheel_1::Move()
{
	m_x_pos += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_pos > 0.55)
		m_x_pos = -0.55f;
	else if (m_dir == MINUS && m_x_pos < -0.55)
		m_x_pos = 0.55f;
}

void CarWheel_1::Update()
{
	Move();
}

void CarWheel_1::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.f; // 0.5294f;
		m_color[i + 1] = 0.f; // 0.8078f;
		m_color[i + 2] = 0.f;
	}
}

void CarWheel_1::DrawObject()
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

void CarWheel_1::InitMatrix4()
{
	m_x_scale = 0.015f;
	m_y_scale = 0.015f;
	m_z_scale = 0.015f;

	m_x_pos = -0.55f * m_dir - 0.02;
	m_y_pos = -0.01;
	m_z_pos = -0.1 * m_idx + 0.018; 
}

//===========================================================================================

void CarSmallWheel_1::Move()
{
	m_x_pos += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_pos > 0.55)
		m_x_pos = -0.55f;
	else if (m_dir == MINUS && m_x_pos < -0.55)
		m_x_pos = 0.55f;
}

void CarSmallWheel_1::Update()
{
	Move();
}

void CarSmallWheel_1::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.f; // 0.5294f;
		m_color[i + 1] = 1.f; // 0.8078f;
		m_color[i + 2] = 1.f;
	}
}

void CarSmallWheel_1::DrawObject()
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

void CarSmallWheel_1::InitMatrix4()
{
	m_x_scale = 0.0075f;
	m_y_scale = 0.0075f;
	m_z_scale = 0.01501f;

	m_x_pos = -0.55f * m_dir - 0.02;
	m_y_pos = -0.01;
	m_z_pos = -0.1 * m_idx + 0.018;
}

//===========================================================================================

void CarWheel_2::Move()
{
	m_x_pos += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_pos > 0.55)
		m_x_pos = -0.55f;
	else if (m_dir == MINUS && m_x_pos < -0.55)
		m_x_pos = 0.55f;
}

void CarWheel_2::Update()
{
	Move();
}

void CarWheel_2::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.f; // 0.5294f;
		m_color[i + 1] = 0.f; // 0.8078f;
		m_color[i + 2] = 0.f;
	}
}

void CarWheel_2::DrawObject()
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

void CarWheel_2::InitMatrix4()
{
	m_x_scale = 0.015f;
	m_y_scale = 0.015f;
	m_z_scale = 0.015f;

	m_x_pos = -0.55f * m_dir - 0.02;
	m_y_pos = -0.01;
	m_z_pos = -0.1 * m_idx - 0.018;
}

//===========================================================================================

void CarSmallWheel_2::Move()
{
	m_x_pos += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_pos > 0.55)
		m_x_pos = -0.55f;
	else if (m_dir == MINUS && m_x_pos < -0.55)
		m_x_pos = 0.55f;
}

void CarSmallWheel_2::Update()
{
	Move();
}

void CarSmallWheel_2::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.f; // 0.5294f;
		m_color[i + 1] = 1.f; // 0.8078f;
		m_color[i + 2] = 1.f;
	}
}

void CarSmallWheel_2::DrawObject()
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

void CarSmallWheel_2::InitMatrix4()
{
	m_x_scale = 0.0075f;
	m_y_scale = 0.0075f;
	m_z_scale = 0.01501f;

	m_x_pos = -0.55f * m_dir - 0.02;
	m_y_pos = -0.01;
	m_z_pos = -0.1 * m_idx - 0.018;
}

//===========================================================================================

void CarWheel_3::Move()
{
	m_x_pos += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_pos > 0.55)
		m_x_pos = -0.55f;
	else if (m_dir == MINUS && m_x_pos < -0.55)
		m_x_pos = 0.55f;
}

void CarWheel_3::Update()
{
	Move();
}

void CarWheel_3::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.f; // 0.5294f;
		m_color[i + 1] = 0.f; // 0.8078f;
		m_color[i + 2] = 0.f;
	}
}

void CarWheel_3::DrawObject()
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

void CarWheel_3::InitMatrix4()
{
	m_x_scale = 0.015f;
	m_y_scale = 0.015f;
	m_z_scale = 0.015f;

	m_x_pos = -0.55f * m_dir + 0.02;
	m_y_pos = -0.01;
	m_z_pos = -0.1 * m_idx + 0.018;
}

//===========================================================================================

void CarSmallWheel_3::Move()
{
	m_x_pos += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_pos > 0.55)
		m_x_pos = -0.55f;
	else if (m_dir == MINUS && m_x_pos < -0.55)
		m_x_pos = 0.55f;
}

void CarSmallWheel_3::Update()
{
	Move();
}

void CarSmallWheel_3::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.f; // 0.5294f;
		m_color[i + 1] = 1.f; // 0.8078f;
		m_color[i + 2] = 1.f;
	}
}

void CarSmallWheel_3::DrawObject()
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

void CarSmallWheel_3::InitMatrix4()
{
	m_x_scale = 0.0075f;
	m_y_scale = 0.0075f;
	m_z_scale = 0.01501f;

	m_x_pos = -0.55f * m_dir + 0.02;
	m_y_pos = -0.01;
	m_z_pos = -0.1 * m_idx + 0.018;
}

//===========================================================================================

void CarWheel_4::Move()
{
	m_x_pos += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_pos > 0.55)
		m_x_pos = -0.55f;
	else if (m_dir == MINUS && m_x_pos < -0.55)
		m_x_pos = 0.55f;
}

void CarWheel_4::Update()
{
	Move();
}

void CarWheel_4::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.f; // 0.5294f;
		m_color[i + 1] = 0.f; // 0.8078f;
		m_color[i + 2] = 0.f;
	}
}

void CarWheel_4::DrawObject()
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

void CarWheel_4::InitMatrix4()
{
	m_x_scale = 0.015f;
	m_y_scale = 0.015f;
	m_z_scale = 0.015f;

	m_x_pos = -0.55f * m_dir + 0.02;
	m_y_pos = -0.01;
	m_z_pos = -0.1 * m_idx - 0.018;
}

//===========================================================================================

void CarSmallWheel_4::Move()
{
	m_x_pos += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_pos > 0.55)
		m_x_pos = -0.55f;
	else if (m_dir == MINUS && m_x_pos < -0.55)
		m_x_pos = 0.55f;
}

void CarSmallWheel_4::Update()
{
	Move();
}

void CarSmallWheel_4::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.f; // 0.5294f;
		m_color[i + 1] = 1.f; // 0.8078f;
		m_color[i + 2] = 1.f;
	}
}

void CarSmallWheel_4::DrawObject()
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

void CarSmallWheel_4::InitMatrix4()
{
	m_x_scale = 0.0075f;
	m_y_scale = 0.0075f;
	m_z_scale = 0.01501f;

	m_x_pos = -0.55f * m_dir + 0.02;
	m_y_pos = -0.01;
	m_z_pos = -0.1 * m_idx - 0.018;
}