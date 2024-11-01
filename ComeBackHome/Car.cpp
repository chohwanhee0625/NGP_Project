#include "usingInclude.h"
#include "Basis.h"
#include "Car.h"
#include "extern.h"

void tagCar::Move()
{
	m_x_distance += m_velocity * m_dir;
	if (m_dir == PLUS  && m_x_distance > 0.55 )
		m_x_distance = -0.55f;
	else if (m_dir == MINUS && m_x_distance < -0.55)
		m_x_distance = 0.55f;
}

void tagCar::update()
{
	Move();
}

void tagCar::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagCar::initColor(const GLfloat color_array[36 * 3])
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

void tagCar::InitBuffer()
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

void tagCar::DrawObject()
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

void tagCar::initMatrix4()
{
	m_x_scale = 0.07f;
	m_y_scale = 0.025f;
	m_z_scale = 0.05;

	m_x_distance = -0.55f * m_dir;
	m_y_distance = 0.005;
	m_z_distance = -0.1 * m_idx; //(0.1f + (0.1 * (float)m_idx)); //* m_idx;
//	m_z_distance = -0.5f * m_idx;

	m_velocity = m_velocity + (m_idx * 0.000015 * gCarspeed(gRandomEngine));
}

void tagCar::make_car()
{
	tagCarMiddle* middle = new tagCarMiddle(m_vertex, m_color, m_dir, m_idx, m_velocity);
	gVec.push_back(middle);

	tagCarWindow* winodw = new tagCarWindow(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(winodw);

	// 왼쪽 앞
	tagCarWheel_1* wheel_1 = new tagCarWheel_1(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_1);
	tagCarWheel_1_small* wheel_1_small = new tagCarWheel_1_small(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_1_small);

	// 왼쪽 뒤 
	tagCarWheel_2* wheel_2 = new tagCarWheel_2(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_2);
	tagCarWheel_2_small* wheel_2_small = new tagCarWheel_2_small(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_2_small);

	// 오른쪽 앞
	tagCarWheel_3* wheel_3 = new tagCarWheel_3(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_3);
	tagCarWheel_3_small* wheel_3_small = new tagCarWheel_3_small(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_3_small);

	// 오른쪽 뒤
	tagCarWheel_4* wheel_4 = new tagCarWheel_4(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_4);
	tagCarWheel_4_small* wheel_4_small = new tagCarWheel_4_small(m_vertex, m_dir, m_idx, m_velocity);
	gVec.push_back(wheel_4_small);
}

// --------------------------------------------------------------------------

void tagCarMiddle::Move()
{
	m_x_distance += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_distance > 0.55)
		m_x_distance = -0.55f;
	else if (m_dir == MINUS && m_x_distance < -0.55)
		m_x_distance = 0.55f;
}

void tagCarMiddle::update()
{
	Move();
}

void tagCarMiddle::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagCarMiddle::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3; ++i) {
		m_color[i] = color_array[i];
	}
}

void tagCarMiddle::InitBuffer()
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

void tagCarMiddle::DrawObject()
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

void tagCarMiddle::initMatrix4()
{
	m_x_scale = 0.04f;
	m_y_scale = 0.03f;
	m_z_scale = 0.05;

	m_x_distance = -0.55f * m_dir;
	m_y_distance = 0.005 + 0.5 * m_y_scale;
	m_z_distance = -0.1 * m_idx; //(0.1f + (0.1 * (float)m_idx)); //* m_idx;
	//	m_z_distance = -0.5f * m_idx;
}

// --------------------------------------------------------------------------

void tagCarWindow::Move()
{
	m_x_distance += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_distance > 0.55)
		m_x_distance = -0.55f;
	else if (m_dir == MINUS && m_x_distance < -0.55)
		m_x_distance = 0.55f;
}

void tagCarWindow::update()
{
	Move();
}

void tagCarWindow::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagCarWindow::initColor()
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.6294f; // 0.5294f;
		m_color[i + 1] = 0.9078f; // 0.8078f;
		m_color[i + 2] = 0.9216;
	}
}

void tagCarWindow::InitBuffer()
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

void tagCarWindow::DrawObject()
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

void tagCarWindow::initMatrix4()
{
	m_x_scale = 0.03f;
	m_y_scale = 0.017f;
	m_z_scale = 0.05001;

	m_x_distance = -0.55f * m_dir;
	m_y_distance = 0.013 + 0.5 * m_y_scale;
	m_z_distance = -0.1 * m_idx; //(0.1f + (0.1 * (float)m_idx)); //* m_idx;
	//	m_z_distance = -0.5f * m_idx;
}

// --------------------------------------------------------------------------

void tagCarWheel_1::Move()
{
	m_x_distance += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_distance > 0.55)
		m_x_distance = -0.55f;
	else if (m_dir == MINUS && m_x_distance < -0.55)
		m_x_distance = 0.55f;
}

void tagCarWheel_1::update()
{
	Move();
}

void tagCarWheel_1::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagCarWheel_1::initColor()
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.f; // 0.5294f;
		m_color[i + 1] = 0.f; // 0.8078f;
		m_color[i + 2] = 0.f;
	}
}

void tagCarWheel_1::InitBuffer()
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

void tagCarWheel_1::DrawObject()
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

void tagCarWheel_1::initMatrix4()
{
	m_x_scale = 0.015f;
	m_y_scale = 0.015f;
	m_z_scale = 0.015f;

	m_x_distance = -0.55f * m_dir - 0.02;
	m_y_distance = -0.01;
	m_z_distance = -0.1 * m_idx + 0.018; 
}

// --------------------------------------------------------------------------

void tagCarWheel_1_small::Move()
{
	m_x_distance += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_distance > 0.55)
		m_x_distance = -0.55f;
	else if (m_dir == MINUS && m_x_distance < -0.55)
		m_x_distance = 0.55f;
}

void tagCarWheel_1_small::update()
{
	Move();
}

void tagCarWheel_1_small::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagCarWheel_1_small::initColor()
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.f; // 0.5294f;
		m_color[i + 1] = 1.f; // 0.8078f;
		m_color[i + 2] = 1.f;
	}
}

void tagCarWheel_1_small::InitBuffer()
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

void tagCarWheel_1_small::DrawObject()
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

void tagCarWheel_1_small::initMatrix4()
{
	m_x_scale = 0.0075f;
	m_y_scale = 0.0075f;
	m_z_scale = 0.01501f;

	m_x_distance = -0.55f * m_dir - 0.02;
	m_y_distance = -0.01;
	m_z_distance = -0.1 * m_idx + 0.018;
}

// --------------------------------------------------------------------------

void tagCarWheel_2::Move()
{
	m_x_distance += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_distance > 0.55)
		m_x_distance = -0.55f;
	else if (m_dir == MINUS && m_x_distance < -0.55)
		m_x_distance = 0.55f;
}

void tagCarWheel_2::update()
{
	Move();
}

void tagCarWheel_2::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagCarWheel_2::initColor()
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.f; // 0.5294f;
		m_color[i + 1] = 0.f; // 0.8078f;
		m_color[i + 2] = 0.f;
	}
}

void tagCarWheel_2::InitBuffer()
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

void tagCarWheel_2::DrawObject()
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

void tagCarWheel_2::initMatrix4()
{
	m_x_scale = 0.015f;
	m_y_scale = 0.015f;
	m_z_scale = 0.015f;

	m_x_distance = -0.55f * m_dir - 0.02;
	m_y_distance = -0.01;
	m_z_distance = -0.1 * m_idx - 0.018;
}

// --------------------------------------------------------------------------

void tagCarWheel_2_small::Move()
{
	m_x_distance += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_distance > 0.55)
		m_x_distance = -0.55f;
	else if (m_dir == MINUS && m_x_distance < -0.55)
		m_x_distance = 0.55f;
}

void tagCarWheel_2_small::update()
{
	Move();
}

void tagCarWheel_2_small::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagCarWheel_2_small::initColor()
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.f; // 0.5294f;
		m_color[i + 1] = 1.f; // 0.8078f;
		m_color[i + 2] = 1.f;
	}
}

void tagCarWheel_2_small::InitBuffer()
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

void tagCarWheel_2_small::DrawObject()
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

void tagCarWheel_2_small::initMatrix4()
{
	m_x_scale = 0.0075f;
	m_y_scale = 0.0075f;
	m_z_scale = 0.01501f;

	m_x_distance = -0.55f * m_dir - 0.02;
	m_y_distance = -0.01;
	m_z_distance = -0.1 * m_idx - 0.018;
}


// --------------------------------------------------------------------------

void tagCarWheel_3::Move()
{
	m_x_distance += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_distance > 0.55)
		m_x_distance = -0.55f;
	else if (m_dir == MINUS && m_x_distance < -0.55)
		m_x_distance = 0.55f;
}

void tagCarWheel_3::update()
{
	Move();
}

void tagCarWheel_3::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagCarWheel_3::initColor()
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.f; // 0.5294f;
		m_color[i + 1] = 0.f; // 0.8078f;
		m_color[i + 2] = 0.f;
	}
}

void tagCarWheel_3::InitBuffer()
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

void tagCarWheel_3::DrawObject()
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

void tagCarWheel_3::initMatrix4()
{
	m_x_scale = 0.015f;
	m_y_scale = 0.015f;
	m_z_scale = 0.015f;

	m_x_distance = -0.55f * m_dir + 0.02;
	m_y_distance = -0.01;
	m_z_distance = -0.1 * m_idx + 0.018;
}

// --------------------------------------------------------------------------

void tagCarWheel_3_small::Move()
{
	m_x_distance += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_distance > 0.55)
		m_x_distance = -0.55f;
	else if (m_dir == MINUS && m_x_distance < -0.55)
		m_x_distance = 0.55f;
}

void tagCarWheel_3_small::update()
{
	Move();
}

void tagCarWheel_3_small::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagCarWheel_3_small::initColor()
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.f; // 0.5294f;
		m_color[i + 1] = 1.f; // 0.8078f;
		m_color[i + 2] = 1.f;
	}
}

void tagCarWheel_3_small::InitBuffer()
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

void tagCarWheel_3_small::DrawObject()
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

void tagCarWheel_3_small::initMatrix4()
{
	m_x_scale = 0.0075f;
	m_y_scale = 0.0075f;
	m_z_scale = 0.01501f;

	m_x_distance = -0.55f * m_dir + 0.02;
	m_y_distance = -0.01;
	m_z_distance = -0.1 * m_idx + 0.018;
}


// --------------------------------------------------------------------------

void tagCarWheel_4::Move()
{
	m_x_distance += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_distance > 0.55)
		m_x_distance = -0.55f;
	else if (m_dir == MINUS && m_x_distance < -0.55)
		m_x_distance = 0.55f;
}

void tagCarWheel_4::update()
{
	Move();
}

void tagCarWheel_4::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagCarWheel_4::initColor()
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.f; // 0.5294f;
		m_color[i + 1] = 0.f; // 0.8078f;
		m_color[i + 2] = 0.f;
	}
}

void tagCarWheel_4::InitBuffer()
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

void tagCarWheel_4::DrawObject()
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

void tagCarWheel_4::initMatrix4()
{
	m_x_scale = 0.015f;
	m_y_scale = 0.015f;
	m_z_scale = 0.015f;

	m_x_distance = -0.55f * m_dir + 0.02;
	m_y_distance = -0.01;
	m_z_distance = -0.1 * m_idx - 0.018;
}

// --------------------------------------------------------------------------

void tagCarWheel_4_small::Move()
{
	m_x_distance += m_velocity * m_dir;
	if (m_dir == PLUS && m_x_distance > 0.55)
		m_x_distance = -0.55f;
	else if (m_dir == MINUS && m_x_distance < -0.55)
		m_x_distance = 0.55f;
}

void tagCarWheel_4_small::update()
{
	Move();
}

void tagCarWheel_4_small::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagCarWheel_4_small::initColor()
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.f; // 0.5294f;
		m_color[i + 1] = 1.f; // 0.8078f;
		m_color[i + 2] = 1.f;
	}
}

void tagCarWheel_4_small::InitBuffer()
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

void tagCarWheel_4_small::DrawObject()
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

void tagCarWheel_4_small::initMatrix4()
{
	m_x_scale = 0.0075f;
	m_y_scale = 0.0075f;
	m_z_scale = 0.01501f;

	m_x_distance = -0.55f * m_dir + 0.02;
	m_y_distance = -0.01;
	m_z_distance = -0.1 * m_idx - 0.018;
}