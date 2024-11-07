#include "usingInclude.h"
#include "extern.h"
#include "Basis.h"
#include "Road.h"
#include "Car.h"

//===========================================================================================

void Road::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3; i += 3) {
		m_color[i + 0] = 0.2824f;
		m_color[i + 1] = 0.3059f;
		m_color[i + 2] = 0.3608f;
	}
}

void Road::DrawObject()
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

void Road::InitMatrix4()
{
	m_x_scale = 2.5f;
	m_y_scale = 1.f;
	m_z_scale = 0.1;

	m_x_pos = 0.f;
	m_y_pos = -0.52;
	m_z_pos = -(m_index * m_z_scale);
}

void Road::Update(float deltatime)
{
}

void Road::InitCarSpawnDir()
{
	// 0 : LEFT  -> +1 -> 왼쪽에서 태어나서 오른쪽으로 이동
	// 1 : RIGHT -> -1 -> 오른쪽에서 태어나서 왼쪽으로 이동
	GLboolean bLeftOrRight{ (bool)gBoolUniform(gRandomEngine) };

	if (bLeftOrRight == LEFT)
		m_car_spawn_dir = PLUS;
	else if (bLeftOrRight == RIGHT)
		m_car_spawn_dir = MINUS;
}

void Road::CreateCar()
{
	Car* car = new Car(m_vertex, m_color, m_car_spawn_dir, m_index);
	gVec.push_back(car);
}

void Road::CreateLane()
{
	RoadLane* pLine{};
	for (int i = -2; i < 8; ++i) {
		pLine = new RoadLane{ m_vertex, m_color, i ,m_index };
		gVec.push_back(pLine);
	}
}

//===========================================================================================

void RoadLane::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3; i += 3) {
		m_color[i + 0] = 0.5235f;
		m_color[i + 1] = 0.5510f;
		m_color[i + 2] = 0.6569f;
	}
}

void RoadLane::DrawObject()
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

void RoadLane::InitMatrix4()
{
	m_x_scale = 0.07f;
	m_y_scale = 0.01f;
	m_z_scale = 0.0115f;

	m_x_pos = -0.46 + 0.15 * m_x_idx; // m_idx 범위 (0~6), 0.15는 선 간격
	m_y_pos = -0.02458; // 고정 상수 
	m_z_pos = -(m_z_idx * 0.1 + 0.05); // +0.05는 도로 반쪽 길이만큼 더한거 -> 안하면 도로가 선 위로 주행함 
}
