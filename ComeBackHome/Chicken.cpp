#include "usingInclude.h"
#include "extern.h"
#include "Basis.h"
#include "Chicken.h"
#include "Souce.h"
#include "Camera.h"
#include "Car.h"
#include "Tree.h"

//===========================================================================================

const float ending_velocity{ 0.1f };
// const float ending_velocity{ 0.002 };

// 간격
const float g_offset_x{ 0.07 };

//===========================================================================================

void ChickenBody::DrawObject()
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

void ChickenBody::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.f;
		m_color[i + 1] = 1.0f;
		m_color[i + 2] = 0.7;
	}
}

void ChickenBody::InitMatrix4()
{
	m_x_pos = 0.f;
	m_y_pos = 0.0f;
	m_z_pos = 0.f;

	m_x_scale = 0.01f;
	m_y_scale = 0.01f;
	m_z_scale = 0.01f;
}

void ChickenBody::InitMatrix4(bool player_id)
{
	// 0번 플레이어면
	if (!player_id) {
		m_x_pos = 0.f;
		m_y_pos = 0.0f;
		m_z_pos = 0.f;
	}
	else
	{
		m_x_pos = 0.f + g_offset_x;
		m_y_pos = 0.0f;
		m_z_pos = 0.f;
	}
}

void ChickenBody::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴
	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void ChickenBody::SetChickenFaceDir(unsigned char key)
{
	switch (key)
	{
	case 'w':
		face = North;
		face_degree = 180.f;
		break;

	case 's':
		face = South;
		face_degree = 0.f;
		break;

	case 'a':
		face = West;
		face_degree = -90.;
		break;

	case 'd':
		face = East;
		face_degree = 90.f;
		break;

	case STOP:
		face = STOP;
		break;
	}
}

void ChickenBody::Walk(float deltatime)
{
	
		switch (face)
		{
		case STOP:
			break;

		case South:
			m_z_pos += walk_velo * deltatime;
			break;

		case West:
			m_x_pos -= walk_velo * deltatime;
			break;

		case East:
			m_x_pos += walk_velo * deltatime;
			break;

		case North:
			m_z_pos -= walk_velo * deltatime;
			break;
		}
	

}

void ChickenBody::Update(float deltatime)
{
	float goal_line = g_max_z * 0.1; // 15.f 

	// z를 + 단위로 재려고 -1 곱함
	float player_z_pos = MINUS * gVec.at(0)->GetZpos();  
	float enemy_z_pos  = MINUS * gEnemyVec.at(0)->GetZpos();
	static bool winner;

	// 적이나 플레이어가 도착했을 시
	if (((goal_line <= player_z_pos) || (goal_line <= enemy_z_pos)) || gIsReach == true) {

		// 첫 도착 시점 
		if (false == gIsReach) {
			PlaySound(L"BackSound.wav", NULL, SND_ASYNC);
			gIsReach = true;

			// if 플레이어가 이기는 경우 else 적이 이기는 경우
			if (enemy_z_pos < player_z_pos) winner = PLAYER; else winner = ENEMY; 
		}

		switch (winner)
		{
		case PLAYER:
			for (int i = 0; i < 8; ++i) {
				gVec.at(i)->SetYpos(gVec.at(i)->GetYpos() + ending_velocity * deltatime);
				gVec.at(i)->SetZpos(gVec.at(i)->GetZpos() + ending_velocity * deltatime);
				gVec.at(i)->SetChickenFaceDir('s');

				//gGameManager.m_playerData[(int)ID::ENERMY];
				gEnemyVec.at(i)->SetXpos(gVec.at(i)->GetXpos());
				gEnemyVec.at(i)->SetYpos(gVec.at(i)->GetYpos());
				gEnemyVec.at(i)->SetZpos(gVec.at(i)->GetZpos());
				gEnemyVec.at(i)->SetEnemyFace(South);
			}
			break;

		case ENEMY:
			for (int i = 0; i < 8; ++i) {
				gEnemyVec.at(i)->SetYpos(gEnemyVec.at(i)->GetYpos() + ending_velocity * deltatime);
				gEnemyVec.at(i)->SetZpos(gEnemyVec.at(i)->GetZpos() + ending_velocity * deltatime);
				gEnemyVec.at(i)->SetEnemyFace(South); 

				//gGameManager.m_playerData[(int)ID::ENERMY];
				gVec.at(i)->SetXpos(gEnemyVec.at(i)->GetXpos());
				gVec.at(i)->SetYpos(gEnemyVec.at(i)->GetYpos());
				gVec.at(i)->SetZpos(gEnemyVec.at(i)->GetZpos());
				gEnemyVec.at(i)->SetChickenFaceDir('s');
			}
			break;
		}

		if (m_y_pos >= 2.1)
		{
			// 빠져나가기
			glutLeaveMainLoop();
		}
	}
	// 아무도 도착 못 했을 시 -> 게임중
	else if( gIsReach == false )
	{
		Collision();
		Walk(deltatime);
		UpdateChickenYpos(deltatime);
	}

#if 0
	float goal_line = -g_max_z * 0.1; // -15.f 

	if (m_z_pos > goal_line && !gIsReach) {
		Collision();
		Walk(deltatime);
		UpdateChickenYpos(deltatime);
		
	}
	else
	{
		if(!gIsReach)
			PlaySound(L"BackSound.wav", NULL, SND_ASYNC);
		
		// 도착하면 y,z 위치 증가 -> y_pos가 2.1이 넘어갈 때까지
		gIsReach = true;
		for (int i{}; i < 8; ++i) {
			gVec.at(i)->SetYpos(gVec.at(i)->GetYpos() + ending_velocity);
			gVec.at(i)->SetZpos(gVec.at(i)->GetZpos() + ending_velocity);
			gVec.at(i)->SetChickenFaceDir('s');

			//gGameManager.m_playerData[(int)ID::ENERMY];
			gEnemyVec.at(i)->SetXpos(gVec.at(i)->GetXpos());
			gEnemyVec.at(i)->SetYpos(gVec.at(i)->GetYpos());
			gEnemyVec.at(i)->SetZpos(gVec.at(i)->GetZpos());
			gEnemyVec.at(i)->SetEnemyFace(South);
		}

		if (m_y_pos >= 2.1)
		{
			glutLeaveMainLoop();
		}
	}
#endif
}

void ChickenBody::Collision()
{
	// m_coll이 false면 충돌검사 X [ 무적모드 ]
	//			 true면 충돌검사 O [ 생존모드 ]
	if (!m_coll) return;

	if (m_x_pos > 0.5)
	{
		m_x_pos = 0.5;
		gCamera.SetCameraFaceDir(STOP);
		for (int j{}; j < 8; ++j)
		{
			gVec.at(j)->SetChickenFaceDir(STOP);
			gVec.at(j)->SetXpos(0.5);
		}
	}
	else if (m_x_pos < -0.5)
	{
		m_x_pos = -0.5;
		gCamera.SetCameraFaceDir(STOP);
		for (int j{}; j < 8; ++j)
		{
			gVec.at(j)->SetChickenFaceDir(STOP);
			gVec.at(j)->SetXpos(-0.5);
		}
	}

	if (m_z_pos > 0.01)
	{
		m_z_pos = 0.01;
		gCamera.SetCameraFaceDir(STOP);
		for (int j{}; j < 8; ++j)
		{
			gVec.at(j)->SetChickenFaceDir(STOP);
			gVec.at(j)->SetZpos(0.01);
		}
	}

	float Chickenpivot[6]{
	  GetXmaxBoundary(), GetXminBoundary(), GetYmaxBoundary(),GetYminBoundary(),GetZmaxBoundary(), GetZminBoundary()
	};

	int size = static_cast<int>(gVec.size());
	
	for (int i = 0; i < size; ++i) {
		if (dynamic_cast<Car*>(gVec[i]) != nullptr) {
			float colPivot[6]{
				gVec[i]->GetXmaxBoundary(), gVec[i]->GetXminBoundary(), gVec[i]->GetYmaxBoundary(),
				gVec[i]->GetYminBoundary(), gVec[i]->GetZmaxBoundary(), gVec[i]->GetZminBoundary()
			};

			// 충돌 판정 (AABB 충돌 검사)
			bool collisionX = Chickenpivot[0] >= colPivot[1] && Chickenpivot[1] <= colPivot[0];
			bool collisionY = Chickenpivot[2] >= colPivot[3] && Chickenpivot[3] <= colPivot[2];
			bool collisionZ = Chickenpivot[4] >= colPivot[5] && Chickenpivot[5] <= colPivot[4];

			
			// 모든 축에서의 충돌이 있는지 확인하여 최종 충돌 판정
			if (collisionX && collisionY && collisionZ) {
				
				PlaySound(L"dead_sound2.wav", NULL, SND_ASYNC);
				
				for (int j{}; j < 8; ++j)
				{
					gVec.at(j)->InitMatrix4();
					gCamera.InitCamera();
				}
			}		
		}

		if (dynamic_cast<Wood*>(gVec[i]) != nullptr) {
			float colPivot[6]{
				gVec[i]->GetXmaxBoundary(), gVec[i]->GetXminBoundary(), gVec[i]->GetYmaxBoundary(),
				gVec[i]->GetYminBoundary(), gVec[i]->GetZmaxBoundary(), gVec[i]->GetZminBoundary()
			};

			// 충돌 판정 (AABB 충돌 검사)
			bool collisionX = Chickenpivot[0] >= colPivot[1] && Chickenpivot[1] <= colPivot[0];
			bool collisionY = Chickenpivot[2] >= colPivot[3] && Chickenpivot[3] <= colPivot[2];
			bool collisionZ = Chickenpivot[4] >= colPivot[5] && Chickenpivot[5] <= colPivot[4];


			// 모든 축에서의 충돌이 있는지 확인하여 최종 충돌 판정
			if (collisionX && collisionY && collisionZ) {
				for (int j{}; j < 8; ++j)
				{
					if (South == gVec.at(j)->GetChickenDir())
					{
						float z{ gVec.at(j)->GetZpos() };
						z -= 0.0025;
						gVec.at(j)->SetZpos(z);
					}

					else if (West == gVec.at(j)->GetChickenDir())
					{
						float x{ gVec.at(j)->GetXpos() };
						x += 0.0025;
						gVec.at(j)->SetXpos(x);
					}

					else if (East == gVec.at(j)->GetChickenDir())
					{
						float x{ gVec.at(j)->GetXpos() };
						x -= 0.0025;
						gVec.at(j)->SetXpos(x);
					}

					else if (North == gVec.at(j)->GetChickenDir())
					{
						float z{ gVec.at(j)->GetZpos() };
						z += 0.0025;
						gVec.at(j)->SetZpos(z);
					}

					gCamera.SetCameraFaceDir(STOP);
					gVec.at(j)->SetChickenFaceDir(STOP);
				}
			}
		}
	}
}

void ChickenBody::update_yvelo(float deltatime)
{
	if (m_y_pos > 0.0) {
		m_fyvelo -= m_fgravity * deltatime;
	}
	else
	{
		m_y_pos = 0;
		Set_yvelo_zero();
	}

}

void ChickenBody::Set_yvelo_zero()
{
	m_fyvelo = 0.0;
}

void ChickenBody::UpdateChickenYpos(float deltatime)
{
	update_yvelo(deltatime);
	m_y_pos += m_fyvelo * deltatime;

}

void ChickenBody::ChickenJump()
{
	if (GetYpos() <= 0) {
		PlaySound(L"jump_2.wav", NULL, SND_ASYNC);
		m_y_pos += 0.01;
		m_fyvelo = 0.2;
	}
}

void ChickenBody::initModelLocation()
{
	face = STOP;
	face_degree = 0.f;
}

//===========================================================================================

void ChickenHead::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.0f;
		m_color[i + 1] = 1.0f;
		m_color[i + 2] = 1.0f;
	}
}

void ChickenHead::DrawObject()
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

void ChickenHead::InitMatrix4()
{
	m_x_pos = 0.f;
	m_y_pos = 0.01;
	m_z_pos = 0.f;

	m_x_scale = 0.01f;
	m_y_scale = 0.01f;
	m_z_scale = 0.01f;
}

void ChickenHead::InitMatrix4(bool player_id)
{
	if (!player_id) {

		m_x_pos = 0.f;
		m_y_pos = 0.01;
		m_z_pos = 0.f;
	}
	else
	{
		m_x_pos = 0.f + g_offset_x;
		m_y_pos = 0.01;
		m_z_pos = 0.f;
	}
}

void ChickenHead::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴
	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void ChickenHead::SetChickenFaceDir(unsigned char key)
{
	switch (key)
	{
	case 'w':
		face = North;
		face_degree = 180.f;
		break;

	case 's':
		face = South;
		face_degree = 0.f;
		break;

	case 'a':
		face = West;
		face_degree = -90.;
		break;

	case 'd':
		face = East;
		face_degree = 90.f;
		break;

	case STOP:
		face = STOP;
		break;
	}
}

void ChickenHead::Walk(float deltatime)
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_pos += walk_velo * deltatime;
		break;

	case West:
		m_x_pos -= walk_velo * deltatime;
		break;

	case East:
		m_x_pos += walk_velo * deltatime;
		break;

	case North:
		m_z_pos -= walk_velo * deltatime;
		break;
	}
}

void ChickenHead::Update(float deltatime)
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk(deltatime);
	}
}

void ChickenHead::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() + 0.01;
}

void ChickenHead::initModelLocation()
{
	face = STOP;
	face_degree = 0.f;
}

//===========================================================================================

void ChickenMouse::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.99607843137f;
		m_color[i + 1] = 0.43921568627f;
		m_color[i + 2] = 0.29803921568f;
	}
}

void ChickenMouse::DrawObject()
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

void ChickenMouse::InitMatrix4()
{
	m_x_pos = 0.0f;
	m_y_pos = 0.01f;
	m_z_pos = 0.0f;

	m_x_scale = 0.01f / 4;
	m_y_scale = 0.01f / 3;
	m_z_scale = 0.0125f;
}

void ChickenMouse::InitMatrix4(bool player_id)
{
	m_x_pos = 0.0f;
	m_y_pos = 0.01f;
	m_z_pos = 0.0f;
	if (player_id) m_x_pos += g_offset_x;
}

void ChickenMouse::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::rotate(m_total_world, glm::radians(m_x_degree), glm::vec3(1.0f, 0.0f, 0.0f)); // x축 회전 기본
	m_total_world = glm::rotate(m_total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 회전 기본
	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 

	m_total_world = glm::translate(m_total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴

	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void ChickenMouse::SetChickenFaceDir(unsigned char key)
{
	switch (key)
	{
	case 'w':
		face = North;
		face_degree = 180.f;
		m_far_x = 0.f;
		m_far_y = 0.f;
		m_far_z = -m_far_value;
		break;

	case 's':
		face = South;
		face_degree = 0.f;
		m_far_x = 0.f;
		m_far_y = 0.f;
		m_far_z = m_far_value;
		break;

	case 'a':
		face = West;
		face_degree = -90.;
		m_far_x = -m_far_value;
		m_far_y = 0.f;
		m_far_z = 0.f;
		break;

	case 'd':
		face = East;
		face_degree = 90.f;
		m_far_x = m_far_value;
		m_far_y = 0.f;
		m_far_z = 0.f;
		break;

	case STOP:
		face = STOP;
		break;
	}
}

void ChickenMouse::Walk(float deltatime)
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_pos += walk_velo * deltatime;
		break;

	case West:
		m_x_pos -= walk_velo * deltatime;
		break;

	case East:
		m_x_pos += walk_velo * deltatime;
		break;

	case North:
		m_z_pos -= walk_velo * deltatime;
		break;
	}
}

void ChickenMouse::Update(float deltatime)
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk(deltatime);
	}
	
}

void ChickenMouse::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() + 0.01;
}

void ChickenMouse::initModelLocation()
{
	face = STOP;

	face_degree = 180.f;
	m_far_value = 0.002;

	m_far_x = 0.0;
	m_far_y = 0.0;
	m_far_z = -m_far_value;
}

//===========================================================================================

void ChickenEyes::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.;
		m_color[i + 1] = 0.;
		m_color[i + 2] = 0.;
	}
}

void ChickenEyes::DrawObject()
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

void ChickenEyes::InitMatrix4()
{
	m_x_pos = 0.f;
	m_y_pos = 0.0105;
	m_z_pos = 0.f;

	m_x_scale = 0.011f;
	m_y_scale = 0.01f / 5;
	m_z_scale = 0.01f / 5;
}

void ChickenEyes::InitMatrix4(bool player_id)
{
	m_x_pos = 0.f;
	m_y_pos = 0.0105;
	m_z_pos = 0.f;
	if (player_id) m_x_pos += g_offset_x;
}

void ChickenEyes::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴
	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void ChickenEyes::SetChickenFaceDir(unsigned char key)
{
	switch (key)
	{
	case 'w':
		face = North;
		face_degree = 180.f;
		m_far_x = 0.f;
		m_far_y = 0.f;
		m_far_z = -m_far_value;
		break;

	case 's':
		face = South;
		face_degree = 0.f;
		m_far_x = 0.f;
		m_far_y = 0.f;
		m_far_z = m_far_value;
		break;

	case 'a':
		face = West;
		face_degree = -90.;
		m_far_x = -m_far_value;
		m_far_y = 0.f;
		m_far_z = 0.f;
		break;

	case 'd':
		face = East;
		face_degree = 90.f;
		m_far_x = m_far_value;
		m_far_y = 0.f;
		m_far_z = 0.f;
		break;

	case STOP:
		face = STOP;
		break;
	}
}

void ChickenEyes::Walk(float deltatime)
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_pos += walk_velo * deltatime;
		break;

	case West:
		m_x_pos -= walk_velo * deltatime;
		break;

	case East:
		m_x_pos += walk_velo * deltatime;
		break;

	case North:
		m_z_pos -= walk_velo * deltatime;
		break;
	}
}

void ChickenEyes::Update(float deltatime)
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk(deltatime);
	}
}

void ChickenEyes::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() + 0.0105;
}

void ChickenEyes::initModelLocation()
{
	face = STOP;

	face_degree = 0.f;
	m_far_value = 0.0;

	m_far_x = 0.0;
	m_far_y = 0.0;
	m_far_z = m_far_value;
}

//===========================================================================================

void ChickenLeftArm::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.9f;
		m_color[i + 1] = 0.9f;
		m_color[i + 2] = 0.9f;
	}
}

void ChickenLeftArm::DrawObject()
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

void ChickenLeftArm::InitMatrix4()
{
	m_x_pos = 0.0;
	m_y_pos = -0.0005f;
	m_z_pos = 0.f;

	m_x_scale = 0.00125f;
	m_y_scale = 0.005f;
	m_z_scale = 0.005f;
}

void ChickenLeftArm::InitMatrix4(bool player_id)
{
	m_x_pos = 0.0;
	m_y_pos = -0.0005f;
	m_z_pos = 0.f;

	if (player_id) m_x_pos += g_offset_x;
}

void ChickenLeftArm::handling()
{
	if (sign == PLUS && hand_degree >= hand_max_degree) {
		sign = MINUS;
	}
	if (sign == MINUS && hand_degree <= 0) {
		sign = PLUS;
	}

	hand_degree += hand_velo * sign;
}

void ChickenLeftArm::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::rotate(m_total_world, glm::radians(m_x_degree), glm::vec3(1.0f, 0.0f, 0.0f)); // x축 회전 기본
	m_total_world = glm::rotate(m_total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 회전 기본 
	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 

	m_total_world = glm::translate(m_total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴

	m_total_world = glm::translate(m_total_world, glm::vec3(0, 0.125 * 0.025, 0)); // 기본 이동
	m_total_world = glm::rotate(m_total_world, glm::radians(hand_degree), glm::vec3(0.0f, 0.0f, 1.0f));
	m_total_world = glm::translate(m_total_world, glm::vec3(0, -0.125 * 0.025, 0)); // 기본 이동

	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void ChickenLeftArm::SetChickenFaceDir(unsigned char key)
{
	switch (key)
	{
	case 'w':
		face = North;
		face_degree = 180.f;
		m_far_x = -m_far_value;
		m_far_y = 0.f;
		m_far_z = 0.f;
		break;

	case 's':
		face = South;
		face_degree = 0.f;
		m_far_x = m_far_value;
		m_far_y = 0.f;
		m_far_z = 0.f;
		break;

	case 'a':
		face = West;
		face_degree = -90.;
		m_far_x = 0.f;
		m_far_y = 0.f;
		m_far_z = m_far_value;
		break;

	case 'd':
		face = East;
		face_degree = 90.f;
		m_far_x = 0.f;
		m_far_y = 0.f;
		m_far_z = -m_far_value;
		break;

	case STOP:
		face = STOP;
		break;
	}
}

void ChickenLeftArm::Walk(float deltatime)
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_pos += walk_velo * deltatime;
		break;

	case West:
		m_x_pos -= walk_velo * deltatime;
		break;

	case East:
		m_x_pos += walk_velo * deltatime;
		break;

	case North:
		m_z_pos -= walk_velo* deltatime;
		break;
	}
}

void ChickenLeftArm::Update(float deltatime)
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk(deltatime);
		
	}
	else
	{
		handling();
		handling();
		handling();
		handling();
	}

	handling();
}

void ChickenLeftArm::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() - 0.0005;
}

void ChickenLeftArm::initModelLocation()
{
	sign = MINUS;
	hand_degree = 0.f;
	hand_velo = 0.8f;
	hand_max_degree = 45.f;

	face = STOP;

	face_degree = 180.f;
	m_far_value = 0.005;

	m_far_x = -m_far_value;
	m_far_y = 0.0;
	m_far_z = 0.0;
}

//===========================================================================================

void ChickenRightArm::handling()
{
	if (sign == PLUS && hand_degree >= hand_max_degree) {
		sign = MINUS;
	}
	if (sign == MINUS && hand_degree <= 0) {
		sign = PLUS;
	}

	hand_degree += hand_velo * sign;
}

void ChickenRightArm::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.9f;
		m_color[i + 1] = 0.9f;
		m_color[i + 2] = 0.9f;
	}
}

void ChickenRightArm::DrawObject()
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

void ChickenRightArm::InitMatrix4()
{
	m_x_pos = 0.0;
	m_y_pos = 0.0005f;
	m_z_pos = 0.f;

	m_x_scale = 0.00125f;
	m_y_scale = 0.005f;
	m_z_scale = 0.005f;
}

void ChickenRightArm::InitMatrix4(bool player_id)
{
	m_x_pos = 0.0;
	m_y_pos = 0.0005f;
	m_z_pos = 0.f;

	if (player_id) m_x_pos += g_offset_x;
}

void ChickenRightArm::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 

	m_total_world = glm::translate(m_total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴

	m_total_world = glm::translate(m_total_world, glm::vec3(0, 0.125 * 0.025, 0)); // 기본 이동
	m_total_world = glm::rotate(m_total_world, glm::radians(-hand_degree), glm::vec3(0.0f, 0.0f, 1.0f));
	m_total_world = glm::translate(m_total_world, glm::vec3(0, -0.125 * 0.025, 0)); // 기본 이동

	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void ChickenRightArm::SetChickenFaceDir(unsigned char key)
{
	switch (key)
	{
	case 'w':
		face = North;
		face_degree = 180.f;
		m_far_x = m_far_value;
		m_far_y = 0.f;
		m_far_z = 0.f;
		break;

	case 's':
		face = South;
		face_degree = 0.f;
		m_far_x = -m_far_value;
		m_far_y = 0.f;
		m_far_z = 0.f;
		break;

	case 'a':
		face = West;
		face_degree = -90.;
		m_far_x = 0.f;
		m_far_y = 0.f;
		m_far_z = -m_far_value;
		break;

	case 'd':
		face = East;
		face_degree = 90.f;
		m_far_x = 0.f;
		m_far_y = 0.f;
		m_far_z = m_far_value;
		break;

	case STOP:
		face = STOP;
		break;
	}
}

void ChickenRightArm::Walk(float deltatime)
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_pos += walk_velo * deltatime;
		break;

	case West:
		m_x_pos -= walk_velo * deltatime;
		break;

	case East:
		m_x_pos += walk_velo * deltatime;
		break;

	case North:
		m_z_pos -= walk_velo * deltatime;
		break;
	}
}

void ChickenRightArm::Update(float deltatime)
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk(deltatime);
	}
	else
	{
		handling();
		handling();
		handling();
		handling();
	}
	handling();
}

void ChickenRightArm::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() - 0.0005;
}

void ChickenRightArm::initModelLocation()
{
	sign = PLUS;
	hand_degree = 0.f;
	hand_velo = 0.8f;
	hand_max_degree = 45.f;

	face = STOP;

	face_degree = 180.f;
	m_far_value = 0.005;

	m_far_x = m_far_value;
	m_far_y = 0.0;
	m_far_z = 0.0;
}

//===========================================================================================

void ChickenLeftLeg::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.0f;
		m_color[i + 1] = 0.47843137254f;
		m_color[i + 2] = 0.34509803921f;
	}
}

void ChickenLeftLeg::DrawObject()
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

void ChickenLeftLeg::InitMatrix4()
{
	m_x_pos = 0.f;
	m_y_pos = -0.005f;
	m_z_pos = 0.f;

	m_x_scale = 0.00125f;
	m_y_scale = 0.0125f;
	m_z_scale = 0.00125f;
}

void ChickenLeftLeg::InitMatrix4(bool player_id)
{
	m_x_pos = 0.f;
	m_y_pos = -0.005f;
	m_z_pos = 0.f;

	if (player_id) m_x_pos += g_offset_x;
}

void ChickenLeftLeg::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동

	m_total_world = glm::translate(m_total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴

	m_total_world = glm::translate(m_total_world, glm::vec3(0, 0.125 * 0.025, 0)); // 기본 이동
	m_total_world = glm::rotate(m_total_world, glm::radians(hand_degree), glm::vec3(1.0f, 0.0f, 0.0f));
	m_total_world = glm::translate(m_total_world, glm::vec3(0, -0.125 * 0.025, 0)); // 기본 이동

	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void ChickenLeftLeg::handling()
{

	if (sign == PLUS && hand_degree >= hand_max_degree) {
		sign = MINUS;
	}
	if (sign == MINUS && hand_degree <= -hand_max_degree) {
		sign = PLUS;
	}


	hand_degree += hand_velo * sign;
}

void ChickenLeftLeg::SetChickenFaceDir(unsigned char key)
{
	switch (key)
	{
	case 'w':
		face = North;
		face_degree = 180.f;
		m_far_x = -m_far_value;
		m_far_y = 0.f;
		m_far_z = 0.f;
		break;

	case 's':
		face = South;
		face_degree = 0.f;
		m_far_x = m_far_value;
		m_far_y = 0.f;
		m_far_z = 0.f;
		break;

	case 'a':
		face = West;
		face_degree = -90.;
		m_far_x = 0.f;
		m_far_y = 0.f;
		m_far_z = m_far_value;
		break;

	case 'd':
		face = East;
		face_degree = 90.f;
		m_far_x = 0.f;
		m_far_y = 0.f;
		m_far_z = -m_far_value;
		break;

	case STOP:
		face = STOP;
		break;
	}
}

void ChickenLeftLeg::Walk(float deltatime)
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_pos += walk_velo * deltatime;
		break;

	case West:
		m_x_pos -= walk_velo * deltatime;
		break;

	case East:
		m_x_pos += walk_velo * deltatime;
		break;

	case North:
		m_z_pos -= walk_velo * deltatime;
		break;
	}
}

void ChickenLeftLeg::Update(float deltatime)
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk(deltatime);
	}
	handling();
}

void ChickenLeftLeg::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() - 0.005;
}

void ChickenLeftLeg::initModelLocation()
{
	sign = PLUS;
	hand_degree = 0.f;
	hand_velo = 0.8f;
	hand_max_degree = 20.f;

	face = STOP;

	face_degree = 180.f;
	m_far_value = 0.0025;

	m_far_x = -m_far_value;
	m_far_y = 0.0;
	m_far_z = 0.0;
}

//===========================================================================================

void ChickenRightLeg::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.0f;
		m_color[i + 1] = 0.47843137254f;
		m_color[i + 2] = 0.34509803921f;
	}
}

void ChickenRightLeg::DrawObject()
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

void ChickenRightLeg::InitMatrix4()
{
	m_x_pos = 0.f;
	m_y_pos = -0.005f;
	m_z_pos = 0.f;

	m_x_scale = 0.00125f;
	m_y_scale = 0.0125f;
	m_z_scale = 0.00125f;
}

void ChickenRightLeg::InitMatrix4(bool player_id)
{
	m_x_pos = 0.f;
	m_y_pos = -0.005f;
	m_z_pos = 0.f;

	if (player_id) m_x_pos += g_offset_x;
}

void ChickenRightLeg::handling()
{
	if (sign == PLUS && hand_degree >= hand_max_degree) {
		sign = MINUS;
	}
	if (sign == MINUS && hand_degree <= -hand_max_degree) {
		sign = PLUS;
	}


	hand_degree += hand_velo * sign;
}

void ChickenRightLeg::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::rotate(m_total_world, glm::radians(m_x_degree), glm::vec3(1.0f, 0.0f, 0.0f)); // x축 회전 기
	m_total_world = glm::rotate(m_total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 회전 기본 
	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // 기본 이동 

	m_total_world = glm::translate(m_total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // 기본 이동 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴

	m_total_world = glm::translate(m_total_world, glm::vec3(0, 0.125 * 0.025, 0)); // 기본 이동
	m_total_world = glm::rotate(m_total_world, glm::radians(hand_degree), glm::vec3(1.0f, 0.0f, 0.0f));
	m_total_world = glm::translate(m_total_world, glm::vec3(0, -0.125 * 0.025, 0)); // 기본 이동

	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void ChickenRightLeg::SetChickenFaceDir(unsigned char key)
{
	switch (key)
	{
	case 'w':
		face = North;
		face_degree = 180.f;
		m_far_x = m_far_value;
		m_far_y = 0.f;
		m_far_z = 0.f;
		break;

	case 's':
		face = South;
		face_degree = 0.f;
		m_far_x = -m_far_value;
		m_far_y = 0.f;
		m_far_z = 0.f;
		break;

	case 'a':
		face = West;
		face_degree = -90.;
		m_far_x = 0.f;
		m_far_y = 0.f;
		m_far_z = -m_far_value;
		break;

	case 'd':
		face = East;
		face_degree = 90.f;
		m_far_x = 0.f;
		m_far_y = 0.f;
		m_far_z = m_far_value;
		break;

	case STOP:
		face = STOP;
		break;
	}
}

void ChickenRightLeg::Walk(float deltatime)
{

	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_pos += walk_velo * deltatime;
		break;

	case West:
		m_x_pos -= walk_velo * deltatime;
		break;

	case East:
		m_x_pos += walk_velo * deltatime;
		break;

	case North:
		m_z_pos -= walk_velo * deltatime;
		break;
	}
}

void ChickenRightLeg::Update(float deltatime)
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk(deltatime);

	}
	handling();
}

void ChickenRightLeg::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() - 0.005;
}

void ChickenRightLeg::initModelLocation()
{
	sign = MINUS;
	hand_degree = 0.f;
	hand_velo = 0.8f;
	hand_max_degree = 20.f;

	face = STOP;

	face_degree = 180.f;
	m_far_value = 0.0025;

	m_far_x = m_far_value;
	m_far_y = 0.0;
	m_far_z = 0.0;
}