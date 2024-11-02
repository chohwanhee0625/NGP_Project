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
	tagBody* body = dynamic_cast<tagBody*>(gVec[0]);
	body->setFaceDir(key);
	tagHead* head = dynamic_cast<tagHead*>(gVec[1]);
	head->setFaceDir(key);
	tagMouse* mouse = dynamic_cast<tagMouse*>(gVec[2]);
	mouse->setFaceDir(key);
	tagEyes* eyes = dynamic_cast<tagEyes*>(gVec[3]);
	eyes->setFaceDir(key);

	tagLeftArm* Larm = dynamic_cast<tagLeftArm*>(gVec[4]);
	Larm->setFaceDir(key);

	tagRightArm* Rarm = dynamic_cast<tagRightArm*>(gVec[5]);
	Rarm->setFaceDir(key);

	tagLeftLeg* Lleg = dynamic_cast<tagLeftLeg*>(gVec[6]);
	Lleg->setFaceDir(key);

	tagRightLeg* Rleg = dynamic_cast<tagRightLeg*>(gVec[7]);
	Rleg->setFaceDir(key);

	gCamera.setFaceDir(key);


}

void ChickenHandling()
{
	tagLeftArm* Larm = dynamic_cast<tagLeftArm*>(gVec[4]);
	Larm->handling();

	tagRightArm* Rarm = dynamic_cast<tagRightArm*>(gVec[5]);
	Rarm->handling();

	tagLeftLeg* Lleg = dynamic_cast<tagLeftLeg*>(gVec[6]);
	Lleg->handling();

	tagRightLeg* Rleg = dynamic_cast<tagRightLeg*>(gVec[7]);
	Rleg->handling();
}

void ChickenMove()
{
	tagBody* body = dynamic_cast<tagBody*>(gVec[0]);
	body->Walk();
	tagHead* head = dynamic_cast<tagHead*>(gVec[1]);
	head->Walk();
	tagMouse* mouse = dynamic_cast<tagMouse*>(gVec[2]);
	mouse->Walk();
	tagEyes* eyes = dynamic_cast<tagEyes*>(gVec[3]);
	eyes->Walk();

	tagLeftArm* Larm = dynamic_cast<tagLeftArm*>(gVec[4]);
	Larm->Walk();
	tagRightArm* Rarm = dynamic_cast<tagRightArm*>(gVec[5]);
	Rarm->Walk();
	tagLeftLeg* Lleg = dynamic_cast<tagLeftLeg*>(gVec[6]);
	Lleg->Walk();
	tagRightLeg* Rleg = dynamic_cast<tagRightLeg*>(gVec[7]);
	Rleg->Walk();

}

//===========================================================================================

void tagBody::DrawObject()
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

void tagBody::InitBuffer()
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

void tagBody::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.f;
		m_color[i + 1] = 1.0f;
		m_color[i + 2] = 0.7;
	}
}

void tagBody::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagBody::InitMatrix4()
{
	m_x_distance = 0.f;
	m_y_distance = 0.0f;
	m_z_distance = 0.f;

	m_x_scale = 0.01f;
	m_y_scale = 0.01f;
	m_z_scale = 0.01f;
}

void tagBody::WorldMatrix()
{
	initTotalworld();

	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_x_distance, m_y_distance, m_z_distance)); // 기본 이동 
	m_Total_world = glm::rotate(m_Total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴
	m_Total_world = glm::scale(m_Total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_Total_world));
}

void tagBody::setFaceDir(unsigned char key)
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

void tagBody::Walk()
{
	
		switch (face)
		{
		case STOP:
			break;

		case South:
			m_z_distance += walk_velo;
			break;

		case West:
			m_x_distance -= walk_velo;
			break;

		case East:
			m_x_distance += walk_velo;
			break;

		case North:
			m_z_distance -= walk_velo;
			break;
		}
	

}

void tagBody::update()
{
	if (m_z_distance > -(g_max_z) * 0.1 && !gIsReach) {
		Collision();
		Walk();
		update_yPos();
		
	}
	else
	{
		if(!gIsReach)
			PlaySound(L"BackSound.wav", NULL, SND_ASYNC);
		
		gIsReach = true;
		for (int i{}; i < 8; ++i) {
			gVec.at(i)->SetYdistance(gVec.at(i)->GetYdistance() + v);
			gVec.at(i)->SetZdistance(gVec.at(i)->getZdistance() + v);
			gVec.at(i)->setFaceDir('s');
		}

		if (m_y_distance >= 2.1)
		{
			glutLeaveMainLoop();
		}
	}
}

void tagBody::Collision()
{
	if (!m_coll) return;

	if (m_x_distance > 0.5)
	{
		m_x_distance = 0.5;
		gCamera.setFaceDir(STOP);
		for (int j{}; j < 8; ++j)
		{
			gVec.at(j)->setFaceDir(STOP);
			gVec.at(j)->SetXdistance(0.5);
		}
	}
	else if (m_x_distance < -0.5)
	{
		m_x_distance = -0.5;
		gCamera.setFaceDir(STOP);
		for (int j{}; j < 8; ++j)
		{
			gVec.at(j)->setFaceDir(STOP);
			gVec.at(j)->SetXdistance(-0.5);
		}
	}

	if (m_z_distance > 0.01)
	{
		m_z_distance = 0.01;
		gCamera.setFaceDir(STOP);
		for (int j{}; j < 8; ++j)
		{
			gVec.at(j)->setFaceDir(STOP);
			gVec.at(j)->SetZdistance(0.01);
		}
	}

	float Chickenpivot[6]{
	  getXmax(), getXmin(), getYmax(),getYmin(),getZmax(), getZmin()
	};

	int size = static_cast<int>(gVec.size());
	
	for (int i = 0; i < size; ++i) {
		if (dynamic_cast<tagCar*>(gVec[i]) != nullptr) {
			float colPivot[6]{
				gVec[i]->getXmax(), gVec[i]->getXmin(), gVec[i]->getYmax(),
				gVec[i]->getYmin(), gVec[i]->getZmax(), gVec[i]->getZmin()
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
					gCamera.initCamera();
				}
			}		
		}

		if (dynamic_cast<tagWood*>(gVec[i]) != nullptr) {
			float colPivot[6]{
				gVec[i]->getXmax(), gVec[i]->getXmin(), gVec[i]->getYmax(),
				gVec[i]->getYmin(), gVec[i]->getZmax(), gVec[i]->getZmin()
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
					if (South == gVec.at(j)->Get_dir())
					{
						float z{ gVec.at(j)->getZdistance() };
						z -= 0.0025;
						gVec.at(j)->SetZdistance(z);
					}

					else if (West == gVec.at(j)->Get_dir())
					{
						float x{ gVec.at(j)->getXdistance() };
						x += 0.0025;
						gVec.at(j)->SetXdistance(x);
					}

					else if (East == gVec.at(j)->Get_dir())
					{
						float x{ gVec.at(j)->getXdistance() };
						x -= 0.0025;
						gVec.at(j)->SetXdistance(x);
					}

					else if (North == gVec.at(j)->Get_dir())
					{
						float z{ gVec.at(j)->getZdistance() };
						z += 0.0025;
						gVec.at(j)->SetZdistance(z);
					}

					gCamera.setFaceDir(STOP);
					gVec.at(j)->setFaceDir(STOP);
				}
			}


		}

	}
}

void tagBody::update_yvelo()
{
	if (m_y_distance > 0.0) {
		m_fyvelo -= m_fgravity;
	}
	else
	{
		m_y_distance = 0;
		Set_yvelo_zero();
	}

}

void tagBody::Set_yvelo_zero()
{
	m_fyvelo = 0.0;
}

void tagBody::update_yPos()
{
	update_yvelo();
	m_y_distance += m_fyvelo;

}

void tagBody::jump()
{
	if (GetYdistance() <= 0) {
		PlaySound(L"jump_2.wav", NULL, SND_ASYNC);
		m_y_distance += 0.01;
		m_fyvelo = 0.005;
	}
}

void tagBody::initModelLocation()
{
	face = STOP;
	walk_velo = 0.002f;
	face_degree = 0.f;
}

//===========================================================================================

void tagHead::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagHead::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.0f;
		m_color[i + 1] = 1.0f;
		m_color[i + 2] = 1.0f;
	}
}

void tagHead::InitBuffer()
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

void tagHead::DrawObject()
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

void tagHead::InitMatrix4()
{
	m_x_scale = 0.01f;
	m_y_scale = 0.01f;
	m_z_scale = 0.01f;

	m_x_distance = 0.f;
	m_y_distance = 0.01;
	m_z_distance = 0.f;
}

void tagHead::WorldMatrix()
{
	initTotalworld();

	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_x_distance, m_y_distance, m_z_distance)); // 기본 이동 
	m_Total_world = glm::rotate(m_Total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴
	m_Total_world = glm::scale(m_Total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_Total_world));
}

void tagHead::setFaceDir(unsigned char key)
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

void tagHead::Walk()
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_distance += walk_velo;
		break;

	case West:
		m_x_distance -= walk_velo;
		break;

	case East:
		m_x_distance += walk_velo;
		break;

	case North:
		m_z_distance -= walk_velo;
		break;
	}
}

void tagHead::update()
{
	if (!gIsReach) {
		update_yPos();
		Walk();
	}
}

void tagHead::update_yPos()
{
	m_y_distance = gVec.at(0)->GetYdistance() + 0.01;
}

void tagHead::initModelLocation()
{
	face = STOP;
	walk_velo = 0.002f;
	face_degree = 0.f;
}

//===========================================================================================

void tagMouse::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagMouse::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.99607843137f;
		m_color[i + 1] = 0.43921568627f;
		m_color[i + 2] = 0.29803921568f;
	}
}

void tagMouse::InitBuffer()
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

void tagMouse::DrawObject()
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

void tagMouse::InitMatrix4()
{
	m_x_scale = 0.01f / 4;
	m_y_scale = 0.01f / 3;
	m_z_scale = 0.0125f;

	m_x_distance = 0.0f;
	m_y_distance = 0.01f;
	m_z_distance = 0.0f;
}

void tagMouse::WorldMatrix()
{
	initTotalworld();

	m_Total_world = glm::rotate(m_Total_world, glm::radians(m_x_degree), glm::vec3(1.0f, 0.0f, 0.0f)); // x축 회전 기본
	m_Total_world = glm::rotate(m_Total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 회전 기본
	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_x_distance, m_y_distance, m_z_distance)); // 기본 이동 

	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // 기본 이동 
	m_Total_world = glm::rotate(m_Total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴

	m_Total_world = glm::scale(m_Total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_Total_world));
}

void tagMouse::setFaceDir(unsigned char key)
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

void tagMouse::Walk()
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_distance += walk_velo;
		break;

	case West:
		m_x_distance -= walk_velo;
		break;

	case East:
		m_x_distance += walk_velo;
		break;

	case North:
		m_z_distance -= walk_velo;
		break;
	}
}

void tagMouse::update()
{
	if (!gIsReach) {
		update_yPos();
		Walk();
	}
	
}

void tagMouse::update_yPos()
{
	m_y_distance = gVec.at(0)->GetYdistance() + 0.01;
}

void tagMouse::initModelLocation()
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

void tagEyes::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagEyes::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.;
		m_color[i + 1] = 0.;
		m_color[i + 2] = 0.;
	}
}

void tagEyes::InitBuffer()
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

void tagEyes::DrawObject()
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

void tagEyes::InitMatrix4()
{
	m_x_scale = 0.011f;
	m_y_scale = 0.01f / 5;
	m_z_scale = 0.01f / 5;

	m_x_distance = 0.f;
	m_y_distance = 0.0105;
	m_z_distance = 0.f;
}

void tagEyes::WorldMatrix()
{
	initTotalworld();

	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_x_distance, m_y_distance, m_z_distance)); // 기본 이동 
	m_Total_world = glm::rotate(m_Total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴
	m_Total_world = glm::scale(m_Total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_Total_world));
}

void tagEyes::setFaceDir(unsigned char key)
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

void tagEyes::Walk()
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_distance += walk_velo;
		break;

	case West:
		m_x_distance -= walk_velo;
		break;

	case East:
		m_x_distance += walk_velo;
		break;

	case North:
		m_z_distance -= walk_velo;
		break;
	}
}

void tagEyes::update()
{
	if (!gIsReach) {
		update_yPos();
		Walk();
	}
}

void tagEyes::update_yPos()
{
	m_y_distance = gVec.at(0)->GetYdistance() + 0.0105;
}

void tagEyes::initModelLocation()
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

void tagLeftArm::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagLeftArm::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.9f;
		m_color[i + 1] = 0.9f;
		m_color[i + 2] = 0.9f;
	}
}

void tagLeftArm::InitBuffer()
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

void tagLeftArm::DrawObject()
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

void tagLeftArm::InitMatrix4()
{
	m_x_distance = 0.0;
	m_y_distance = -0.0005f;
	m_z_distance = 0.f;

	m_x_scale = 0.00125f;
	m_y_scale = 0.005f;
	m_z_scale = 0.005f;
}

void tagLeftArm::handling()
{
	if (sign == PLUS && hand_degree >= hand_max_degree) {
		sign = MINUS;
	}
	if (sign == MINUS && hand_degree <= 0) {
		sign = PLUS;
	}

	hand_degree += hand_velo * sign;
}

void tagLeftArm::WorldMatrix()
{
	initTotalworld();

	m_Total_world = glm::rotate(m_Total_world, glm::radians(m_x_degree), glm::vec3(1.0f, 0.0f, 0.0f)); // x축 회전 기본
	m_Total_world = glm::rotate(m_Total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 회전 기본 
	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_x_distance, m_y_distance, m_z_distance)); // 기본 이동 

	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // 기본 이동 
	m_Total_world = glm::rotate(m_Total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴

	m_Total_world = glm::translate(m_Total_world, glm::vec3(0, 0.125 * 0.025, 0)); // 기본 이동
	m_Total_world = glm::rotate(m_Total_world, glm::radians(hand_degree), glm::vec3(0.0f, 0.0f, 1.0f));
	m_Total_world = glm::translate(m_Total_world, glm::vec3(0, -0.125 * 0.025, 0)); // 기본 이동

	m_Total_world = glm::scale(m_Total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_Total_world));
}

void tagLeftArm::setFaceDir(unsigned char key)
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

void tagLeftArm::Walk()
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_distance += walk_velo;
		break;

	case West:
		m_x_distance -= walk_velo;
		break;

	case East:
		m_x_distance += walk_velo;
		break;

	case North:
		m_z_distance -= walk_velo;
		break;
	}
}

void tagLeftArm::update()
{
	if (!gIsReach) {
		update_yPos();
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

void tagLeftArm::update_yPos()
{
	m_y_distance = gVec.at(0)->GetYdistance() - 0.0005;
}

void tagLeftArm::initModelLocation()
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

void tagRightArm::handling()
{
	if (sign == PLUS && hand_degree >= hand_max_degree) {
		sign = MINUS;
	}
	if (sign == MINUS && hand_degree <= 0) {
		sign = PLUS;
	}

	hand_degree += hand_velo * sign;
}

void tagRightArm::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagRightArm::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 0.9f;
		m_color[i + 1] = 0.9f;
		m_color[i + 2] = 0.9f;
	}
}

void tagRightArm::InitBuffer()
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

void tagRightArm::DrawObject()
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

void tagRightArm::InitMatrix4()
{
	m_x_distance = 0.0;
	m_y_distance = 0.0005f;
	m_z_distance = 0.f;

	m_x_scale = 0.00125f;
	m_y_scale = 0.005f;
	m_z_scale = 0.005f;
}

void tagRightArm::WorldMatrix()
{
	initTotalworld();

	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_x_distance, m_y_distance, m_z_distance)); // 기본 이동 

	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // 기본 이동 
	m_Total_world = glm::rotate(m_Total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴

	m_Total_world = glm::translate(m_Total_world, glm::vec3(0, 0.125 * 0.025, 0)); // 기본 이동
	m_Total_world = glm::rotate(m_Total_world, glm::radians(-hand_degree), glm::vec3(0.0f, 0.0f, 1.0f));
	m_Total_world = glm::translate(m_Total_world, glm::vec3(0, -0.125 * 0.025, 0)); // 기본 이동

	m_Total_world = glm::scale(m_Total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_Total_world));
}

void tagRightArm::setFaceDir(unsigned char key)
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

void tagRightArm::Walk()
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_distance += walk_velo;
		break;

	case West:
		m_x_distance -= walk_velo;
		break;

	case East:
		m_x_distance += walk_velo;
		break;

	case North:
		m_z_distance -= walk_velo;
		break;
	}
}

void tagRightArm::update()
{
	if (!gIsReach) {
		update_yPos();
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

void tagRightArm::update_yPos()
{
	m_y_distance = gVec.at(0)->GetYdistance() - 0.0005;
}

void tagRightArm::initModelLocation()
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

void tagLeftLeg::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagLeftLeg::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.0f;
		m_color[i + 1] = 0.47843137254f;
		m_color[i + 2] = 0.34509803921f;
	}
}

void tagLeftLeg::InitBuffer()
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

void tagLeftLeg::DrawObject()
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

void tagLeftLeg::InitMatrix4()
{
	m_x_scale = 0.00125f;
	m_y_scale = 0.0125f;
	m_z_scale = 0.00125f;

	m_x_distance = 0.f;
	m_y_distance = -0.005f;
	m_z_distance = 0.f;
}

void tagLeftLeg::WorldMatrix()
{
	initTotalworld();

	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_x_distance, m_y_distance, m_z_distance)); // 기본 이동

	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // 기본 이동 
	m_Total_world = glm::rotate(m_Total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴

	m_Total_world = glm::translate(m_Total_world, glm::vec3(0, 0.125 * 0.025, 0)); // 기본 이동
	m_Total_world = glm::rotate(m_Total_world, glm::radians(hand_degree), glm::vec3(1.0f, 0.0f, 0.0f));
	m_Total_world = glm::translate(m_Total_world, glm::vec3(0, -0.125 * 0.025, 0)); // 기본 이동

	m_Total_world = glm::scale(m_Total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_Total_world));
}

void tagLeftLeg::handling()
{

	if (sign == PLUS && hand_degree >= hand_max_degree) {
		sign = MINUS;
	}
	if (sign == MINUS && hand_degree <= -hand_max_degree) {
		sign = PLUS;
	}


	hand_degree += hand_velo * sign;
}

void tagLeftLeg::setFaceDir(unsigned char key)
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

void tagLeftLeg::Walk()
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_distance += walk_velo;
		break;

	case West:
		m_x_distance -= walk_velo;
		break;

	case East:
		m_x_distance += walk_velo;
		break;

	case North:
		m_z_distance -= walk_velo;
		break;
	}
}

void tagLeftLeg::update()
{
	if (!gIsReach) {
		update_yPos();
		Walk();
	}
	handling();
}

void tagLeftLeg::update_yPos()
{
	m_y_distance = gVec.at(0)->GetYdistance() - 0.005;
}

void tagLeftLeg::initModelLocation()
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

void tagRightLeg::initVertex(const GLfloat rec_array[36 * 6])
{
	for (int i = 0; i < 36 * 6; ++i) {
		this->m_vertex[i] = rec_array[i];
	}
}

void tagRightLeg::initColor(const GLfloat color_array[36 * 3])
{
	for (int i = 0; i < 36 * 3 - 2; i += 3) {
		m_color[i] = 1.0f;
		m_color[i + 1] = 0.47843137254f;
		m_color[i + 2] = 0.34509803921f;
	}
}

void tagRightLeg::InitBuffer()
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

void tagRightLeg::DrawObject()
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

void tagRightLeg::InitMatrix4()
{
	m_x_scale = 0.00125f;
	m_y_scale = 0.0125f;
	m_z_scale = 0.00125f;

	m_x_distance = 0.f;
	m_y_distance = -0.005f;
	m_z_distance = 0.f;
}

void tagRightLeg::handling()
{
	if (sign == PLUS && hand_degree >= hand_max_degree) {
		sign = MINUS;
	}
	if (sign == MINUS && hand_degree <= -hand_max_degree) {
		sign = PLUS;
	}


	hand_degree += hand_velo * sign;
}

void tagRightLeg::WorldMatrix()
{
	initTotalworld();

	m_Total_world = glm::rotate(m_Total_world, glm::radians(m_x_degree), glm::vec3(1.0f, 0.0f, 0.0f)); // x축 회전 기
	m_Total_world = glm::rotate(m_Total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 회전 기본 
	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_x_distance, m_y_distance, m_z_distance)); // 기본 이동 

	m_Total_world = glm::translate(m_Total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // 기본 이동 
	m_Total_world = glm::rotate(m_Total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y축 얼굴

	m_Total_world = glm::translate(m_Total_world, glm::vec3(0, 0.125 * 0.025, 0)); // 기본 이동
	m_Total_world = glm::rotate(m_Total_world, glm::radians(hand_degree), glm::vec3(1.0f, 0.0f, 0.0f));
	m_Total_world = glm::translate(m_Total_world, glm::vec3(0, -0.125 * 0.025, 0)); // 기본 이동

	m_Total_world = glm::scale(m_Total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // 기본 신축

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_Total_world));
}

void tagRightLeg::setFaceDir(unsigned char key)
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

void tagRightLeg::Walk()
{
	switch (face)
	{
	case STOP:
		break;

	case South:
		m_z_distance += walk_velo;
		break;

	case West:
		m_x_distance -= walk_velo;
		break;

	case East:
		m_x_distance += walk_velo;
		break;

	case North:
		m_z_distance -= walk_velo;
		break;
	}
}

void tagRightLeg::update()
{
	if (!gIsReach) {
		update_yPos();
		Walk();

	}
	handling();
}

void tagRightLeg::update_yPos()
{
	m_y_distance = gVec.at(0)->GetYdistance() - 0.005;
}

void tagRightLeg::initModelLocation()
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