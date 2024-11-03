#include "usingInclude.h"
#include "extern.h"
#include "Basis.h"
#include "Chicken.h"
#include "소스.h"
#include "Camera.h"
#include "Car.h"
#include "Tree.h"

//===========================================================================================

const float v{ 0.002 };

void SetChickenFaceDir(unsigned char key)
{
	ChickenBody* body = dynamic_cast<ChickenBody*>(gVec[0]);
	body->SetChickenFaceDir(key);
	ChickenHead* head = dynamic_cast<ChickenHead*>(gVec[1]);
	head->SetChickenFaceDir(key);
	ChickenMouse* mouse = dynamic_cast<ChickenMouse*>(gVec[2]);
	mouse->SetChickenFaceDir(key);
	ChickenEyes* eyes = dynamic_cast<ChickenEyes*>(gVec[3]);
	eyes->SetChickenFaceDir(key);

	ChickenLeftArm* Larm = dynamic_cast<ChickenLeftArm*>(gVec[4]);
	Larm->SetChickenFaceDir(key);

	ChickenRightArm* Rarm = dynamic_cast<ChickenRightArm*>(gVec[5]);
	Rarm->SetChickenFaceDir(key);

	ChickenLeftLeg* Lleg = dynamic_cast<ChickenLeftLeg*>(gVec[6]);
	Lleg->SetChickenFaceDir(key);

	ChickenRightLeg* Rleg = dynamic_cast<ChickenRightLeg*>(gVec[7]);
	Rleg->SetChickenFaceDir(key);

	gCamera.SetCameraFaceDir(key);


}

void ChickenHandling()
{
	ChickenLeftArm* Larm = dynamic_cast<ChickenLeftArm*>(gVec[4]);
	Larm->handling();

	ChickenRightArm* Rarm = dynamic_cast<ChickenRightArm*>(gVec[5]);
	Rarm->handling();

	ChickenLeftLeg* Lleg = dynamic_cast<ChickenLeftLeg*>(gVec[6]);
	Lleg->handling();

	ChickenRightLeg* Rleg = dynamic_cast<ChickenRightLeg*>(gVec[7]);
	Rleg->handling();
}

void ChickenMove()
{
	ChickenBody* body = dynamic_cast<ChickenBody*>(gVec[0]);
	body->Walk();
	ChickenHead* head = dynamic_cast<ChickenHead*>(gVec[1]);
	head->Walk();
	ChickenMouse* mouse = dynamic_cast<ChickenMouse*>(gVec[2]);
	mouse->Walk();
	ChickenEyes* eyes = dynamic_cast<ChickenEyes*>(gVec[3]);
	eyes->Walk();

	ChickenLeftArm* Larm = dynamic_cast<ChickenLeftArm*>(gVec[4]);
	Larm->Walk();
	ChickenRightArm* Rarm = dynamic_cast<ChickenRightArm*>(gVec[5]);
	Rarm->Walk();
	ChickenLeftLeg* Lleg = dynamic_cast<ChickenLeftLeg*>(gVec[6]);
	Lleg->Walk();
	ChickenRightLeg* Rleg = dynamic_cast<ChickenRightLeg*>(gVec[7]);
	Rleg->Walk();

}

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

//void ChickenBody::InitBuffer()
//{
//	glGenVertexArrays(1, &this->m_vao);
//	glBindVertexArray(this->m_vao);
//
//	glGenBuffers(1, &this->m_pos_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_pos_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_vertex), this->m_vertex, GL_STATIC_DRAW);
//
//	int PosLocation = glGetAttribLocation(gShaderProgramID, "in_Position");
//	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(PosLocation);
//
//	int NormalLocation = glGetAttribLocation(gShaderProgramID, "in_Normal");
//	glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(NormalLocation);
//
//	glGenBuffers(1, &this->m_color_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_color_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_color), this->m_color, GL_STATIC_DRAW);
//
//	int ColorLocation = glGetAttribLocation(gShaderProgramID, "in_Color");
//	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
//}

void ChickenBody::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.f;
		m_color[i + 1] = 1.0f;
		m_color[i + 2] = 0.7;
	}
}

//void ChickenBody::InitVertex(const GLfloat rec_array[36 * 6])
//{
//	for (int i = 0; i < 36 * 6; ++i) {
//		this->m_vertex[i] = rec_array[i];
//	}
//}

void ChickenBody::InitMatrix4()
{
	m_x_pos = 0.f;
	m_y_pos = 0.0f;
	m_z_pos = 0.f;

	m_x_scale = 0.01f;
	m_y_scale = 0.01f;
	m_z_scale = 0.01f;
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

void ChickenBody::Walk()
{
	
		switch (face)
		{
		case STOP:
			break;

		case South:
			m_z_pos += walk_velo;
			break;

		case West:
			m_x_pos -= walk_velo;
			break;

		case East:
			m_x_pos += walk_velo;
			break;

		case North:
			m_z_pos -= walk_velo;
			break;
		}
	

}

void ChickenBody::Update()
{
	if (m_z_pos > -(g_max_z) * 0.1 && !gIsReach) {
		Collision();
		Walk();
		UpdateChickenYpos();
		
	}
	else
	{
		if(!gIsReach)
			PlaySound(L"BackSound.wav", NULL, SND_ASYNC);
		
		// 도착하면 y,z 위치 증가 -> y_pos가 2.1이 넘어갈 때까지
		gIsReach = true;
		for (int i{}; i < 8; ++i) {
			gVec.at(i)->SetYpos(gVec.at(i)->GetYpos() + v);
			gVec.at(i)->SetZpos(gVec.at(i)->GetZpos() + v);
			gVec.at(i)->SetChickenFaceDir('s');
		}

		if (m_y_pos >= 2.1)
		{
			glutLeaveMainLoop();
		}
	}
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
				cout << "충돌 성공!" << i << endl;
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

void ChickenBody::update_yvelo()
{
	if (m_y_pos > 0.0) {
		m_fyvelo -= m_fgravity;
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

void ChickenBody::UpdateChickenYpos()
{
	update_yvelo();
	m_y_pos += m_fyvelo;

}

void ChickenBody::ChickenJump()
{
	if (GetYpos() <= 0) {
		PlaySound(L"jump_2.wav", NULL, SND_ASYNC);
		m_y_pos += 0.01;
		m_fyvelo = 0.005;
	}
}

void ChickenBody::initModelLocation()
{
	face = STOP;
	walk_velo = 0.002f;
	face_degree = 0.f;
}

//===========================================================================================

//void ChickenHead::InitVertex(const GLfloat rec_array[36 * 6])
//{
//	for (int i = 0; i < 36 * 6; ++i) {
//		this->m_vertex[i] = rec_array[i];
//	}
//}

void ChickenHead::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.0f;
		m_color[i + 1] = 1.0f;
		m_color[i + 2] = 1.0f;
	}
}

//void ChickenHead::InitBuffer()
//{
//	glGenVertexArrays(1, &this->m_vao);
//	glBindVertexArray(this->m_vao);
//
//	glGenBuffers(1, &this->m_pos_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_pos_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_vertex), this->m_vertex, GL_STATIC_DRAW);
//
//	int PosLocation = glGetAttribLocation(gShaderProgramID, "in_Position");
//	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(PosLocation);
//
//	int NormalLocation = glGetAttribLocation(gShaderProgramID, "in_Normal");
//	glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(NormalLocation);
//
//	glGenBuffers(1, &this->m_color_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_color_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_color), this->m_color, GL_STATIC_DRAW);
//
//	int ColorLocation = glGetAttribLocation(gShaderProgramID, "in_Color");
//	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
//}

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
	m_x_scale = 0.01f;
	m_y_scale = 0.01f;
	m_z_scale = 0.01f;

	m_x_pos = 0.f;
	m_y_pos = 0.01;
	m_z_pos = 0.f;
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

void ChickenHead::Walk()
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_pos += walk_velo;
		break;

	case West:
		m_x_pos -= walk_velo;
		break;

	case East:
		m_x_pos += walk_velo;
		break;

	case North:
		m_z_pos -= walk_velo;
		break;
	}
}

void ChickenHead::Update()
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk();
	}
}

void ChickenHead::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() + 0.01;
}

void ChickenHead::initModelLocation()
{
	face = STOP;
	walk_velo = 0.002f;
	face_degree = 0.f;
}

//===========================================================================================

//void ChickenMouse::InitVertex(const GLfloat rec_array[36 * 6])
//{
//	for (int i = 0; i < 36 * 6; ++i) {
//		this->m_vertex[i] = rec_array[i];
//	}
//}

void ChickenMouse::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.99607843137f;
		m_color[i + 1] = 0.43921568627f;
		m_color[i + 2] = 0.29803921568f;
	}
}

//void ChickenMouse::InitBuffer()
//{
//	glGenVertexArrays(1, &this->m_vao);
//	glBindVertexArray(this->m_vao);
//
//	glGenBuffers(1, &this->m_pos_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_pos_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_vertex), this->m_vertex, GL_STATIC_DRAW);
//
//	int PosLocation = glGetAttribLocation(gShaderProgramID, "in_Position");
//	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(PosLocation);
//
//	int NormalLocation = glGetAttribLocation(gShaderProgramID, "in_Normal");
//	glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(NormalLocation);
//
//	glGenBuffers(1, &this->m_color_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_color_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_color), this->m_color, GL_STATIC_DRAW);
//
//	int ColorLocation = glGetAttribLocation(gShaderProgramID, "in_Color");
//	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//}

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
	m_x_scale = 0.01f / 4;
	m_y_scale = 0.01f / 3;
	m_z_scale = 0.0125f;

	m_x_pos = 0.0f;
	m_y_pos = 0.01f;
	m_z_pos = 0.0f;
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

void ChickenMouse::Walk()
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_pos += walk_velo;
		break;

	case West:
		m_x_pos -= walk_velo;
		break;

	case East:
		m_x_pos += walk_velo;
		break;

	case North:
		m_z_pos -= walk_velo;
		break;
	}
}

void ChickenMouse::Update()
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk();
	}
	
}

void ChickenMouse::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() + 0.01;
}

void ChickenMouse::initModelLocation()
{
	face = STOP;
	walk_velo = 0.002f;
	face_degree = 180.f;
	m_far_value = 0.002;

	m_far_x = 0.0;
	m_far_y = 0.0;
	m_far_z = -m_far_value;
}

//===========================================================================================

//void ChickenEyes::InitVertex(const GLfloat rec_array[36 * 6])
//{
//	for (int i = 0; i < 36 * 6; ++i) {
//		this->m_vertex[i] = rec_array[i];
//	}
//}

void ChickenEyes::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.;
		m_color[i + 1] = 0.;
		m_color[i + 2] = 0.;
	}
}

//void ChickenEyes::InitBuffer()
//{
//	glGenVertexArrays(1, &this->m_vao);
//	glBindVertexArray(this->m_vao);
//
//	glGenBuffers(1, &this->m_pos_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_pos_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_vertex), this->m_vertex, GL_STATIC_DRAW);
//
//	int PosLocation = glGetAttribLocation(gShaderProgramID, "in_Position");
//	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(PosLocation);
//
//	int NormalLocation = glGetAttribLocation(gShaderProgramID, "in_Normal");
//	glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(NormalLocation);
//
//	glGenBuffers(1, &this->m_color_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_color_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_color), this->m_color, GL_STATIC_DRAW);
//
//	int ColorLocation = glGetAttribLocation(gShaderProgramID, "in_Color");
//	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//}

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
	m_x_scale = 0.011f;
	m_y_scale = 0.01f / 5;
	m_z_scale = 0.01f / 5;

	m_x_pos = 0.f;
	m_y_pos = 0.0105;
	m_z_pos = 0.f;
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

void ChickenEyes::Walk()
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_pos += walk_velo;
		break;

	case West:
		m_x_pos -= walk_velo;
		break;

	case East:
		m_x_pos += walk_velo;
		break;

	case North:
		m_z_pos -= walk_velo;
		break;
	}
}

void ChickenEyes::Update()
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk();
	}
}

void ChickenEyes::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() + 0.0105;
}

void ChickenEyes::initModelLocation()
{
	face = STOP;
	walk_velo = 0.002f;
	face_degree = 0.f;
	m_far_value = 0.0;

	m_far_x = 0.0;
	m_far_y = 0.0;
	m_far_z = m_far_value;
}

//===========================================================================================

//void ChickenLeftArm::InitVertex(const GLfloat rec_array[36 * 6])
//{
//	for (int i = 0; i < 36 * 6; ++i) {
//		this->m_vertex[i] = rec_array[i];
//	}
//}

void ChickenLeftArm::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.9f;
		m_color[i + 1] = 0.9f;
		m_color[i + 2] = 0.9f;
	}
}

//void ChickenLeftArm::InitBuffer()
//{
//	glGenVertexArrays(1, &this->m_vao);
//	glBindVertexArray(this->m_vao);
//
//	glGenBuffers(1, &this->m_pos_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_pos_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_vertex), this->m_vertex, GL_STATIC_DRAW);
//
//	int PosLocation = glGetAttribLocation(gShaderProgramID, "in_Position");
//	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(PosLocation);
//
//	int NormalLocation = glGetAttribLocation(gShaderProgramID, "in_Normal");
//	glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(NormalLocation);
//
//	glGenBuffers(1, &this->m_color_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_color_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_color), this->m_color, GL_STATIC_DRAW);
//
//	int ColorLocation = glGetAttribLocation(gShaderProgramID, "in_Color");
//	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
//}

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

void ChickenLeftArm::Walk()
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_pos += walk_velo;
		break;

	case West:
		m_x_pos -= walk_velo;
		break;

	case East:
		m_x_pos += walk_velo;
		break;

	case North:
		m_z_pos -= walk_velo;
		break;
	}
}

void ChickenLeftArm::Update()
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk();
		
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
	walk_velo = 0.002f;
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

//void ChickenRightArm::InitVertex(const GLfloat rec_array[36 * 6])
//{
//	for (int i = 0; i < 36 * 6; ++i) {
//		this->m_vertex[i] = rec_array[i];
//	}
//}

void ChickenRightArm::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.9f;
		m_color[i + 1] = 0.9f;
		m_color[i + 2] = 0.9f;
	}
}

//void ChickenRightArm::InitBuffer()
//{
//	glGenVertexArrays(1, &this->m_vao);
//	glBindVertexArray(this->m_vao);
//
//	glGenBuffers(1, &this->m_pos_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_pos_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_vertex), this->m_vertex, GL_STATIC_DRAW);
//
//	int PosLocation = glGetAttribLocation(gShaderProgramID, "in_Position");
//	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(PosLocation);
//
//	int NormalLocation = glGetAttribLocation(gShaderProgramID, "in_Normal");
//	glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(NormalLocation);
//
//	glGenBuffers(1, &this->m_color_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_color_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_color), this->m_color, GL_STATIC_DRAW);
//
//	int ColorLocation = glGetAttribLocation(gShaderProgramID, "in_Color");
//	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//}

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

void ChickenRightArm::Walk()
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_pos += walk_velo;
		break;

	case West:
		m_x_pos -= walk_velo;
		break;

	case East:
		m_x_pos += walk_velo;
		break;

	case North:
		m_z_pos -= walk_velo;
		break;
	}
}

void ChickenRightArm::Update()
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk();
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
	walk_velo = 0.002f;
	face_degree = 180.f;
	m_far_value = 0.005;

	m_far_x = m_far_value;
	m_far_y = 0.0;
	m_far_z = 0.0;
}

//===========================================================================================

//void ChickenLeftLeg::InitVertex(const GLfloat rec_array[36 * 6])
//{
//	for (int i = 0; i < 36 * 6; ++i) {
//		this->m_vertex[i] = rec_array[i];
//	}
//}

void ChickenLeftLeg::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.0f;
		m_color[i + 1] = 0.47843137254f;
		m_color[i + 2] = 0.34509803921f;
	}
}

//void ChickenLeftLeg::InitBuffer()
//{
//	glGenVertexArrays(1, &this->m_vao);
//	glBindVertexArray(this->m_vao);
//
//	glGenBuffers(1, &this->m_pos_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_pos_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_vertex), this->m_vertex, GL_STATIC_DRAW);
//
//	int PosLocation = glGetAttribLocation(gShaderProgramID, "in_Position");
//	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(PosLocation);
//
//	int NormalLocation = glGetAttribLocation(gShaderProgramID, "in_Normal");
//	glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(NormalLocation);
//
//	glGenBuffers(1, &this->m_color_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_color_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_color), this->m_color, GL_STATIC_DRAW);
//
//	int ColorLocation = glGetAttribLocation(gShaderProgramID, "in_Color");
//	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
//}

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
	m_x_scale = 0.00125f;
	m_y_scale = 0.0125f;
	m_z_scale = 0.00125f;

	m_x_pos = 0.f;
	m_y_pos = -0.005f;
	m_z_pos = 0.f;
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

void ChickenLeftLeg::Walk()
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_pos += walk_velo;
		break;

	case West:
		m_x_pos -= walk_velo;
		break;

	case East:
		m_x_pos += walk_velo;
		break;

	case North:
		m_z_pos -= walk_velo;
		break;
	}
}

void ChickenLeftLeg::Update()
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk();
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
	walk_velo = 0.002f;
	face_degree = 180.f;
	m_far_value = 0.0025;

	m_far_x = -m_far_value;
	m_far_y = 0.0;
	m_far_z = 0.0;
}

//===========================================================================================

//void ChickenRightLeg::InitVertex(const GLfloat rec_array[36 * 6])
//{
//	for (int i = 0; i < 36 * 6; ++i) {
//		this->m_vertex[i] = rec_array[i];
//	}
//}

void ChickenRightLeg::InitColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.0f;
		m_color[i + 1] = 0.47843137254f;
		m_color[i + 2] = 0.34509803921f;
	}
}

//void ChickenRightLeg::InitBuffer()
//{
//	glGenVertexArrays(1, &this->m_vao);
//	glBindVertexArray(this->m_vao);
//
//	glGenBuffers(1, &this->m_pos_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_pos_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_vertex), this->m_vertex, GL_STATIC_DRAW);
//
//	int PosLocation = glGetAttribLocation(gShaderProgramID, "in_Position");
//	glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(PosLocation);
//
//	int NormalLocation = glGetAttribLocation(gShaderProgramID, "in_Normal");
//	glVertexAttribPointer(NormalLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(NormalLocation);
//
//	glGenBuffers(1, &this->m_color_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, this->m_color_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(this->m_color), this->m_color, GL_STATIC_DRAW);
//
//	int ColorLocation = glGetAttribLocation(gShaderProgramID, "in_Color");
//	glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
//}

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
	m_x_scale = 0.00125f;
	m_y_scale = 0.0125f;
	m_z_scale = 0.00125f;

	m_x_pos = 0.f;
	m_y_pos = -0.005f;
	m_z_pos = 0.f;
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

void ChickenRightLeg::Walk()
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_pos += walk_velo;
		break;

	case West:
		m_x_pos -= walk_velo;
		break;

	case East:
		m_x_pos += walk_velo;
		break;

	case North:
		m_z_pos -= walk_velo;
		break;
	}
}

void ChickenRightLeg::Update()
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk();

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
	walk_velo = 0.002f;
	face_degree = 180.f;
	m_far_value = 0.0025;

	m_far_x = m_far_value;
	m_far_y = 0.0;
	m_far_z = 0.0;
}