#include "usingInclude.h"
#include "extern.h"
#include "Basis.h"
#include "Chicken.h"
#include "�ҽ�.h"
#include "Camera.h"
#include "Car.h"
#include "Tree.h"

//===========================================================================================

const float v{ 0.002 };

void SetChickenFaceDir(unsigned char key)
{
	tagBody* body = dynamic_cast<tagBody*>(gVec[0]);
	body->SetChickenFaceDir(key);
	tagHead* head = dynamic_cast<tagHead*>(gVec[1]);
	head->SetChickenFaceDir(key);
	tagMouse* mouse = dynamic_cast<tagMouse*>(gVec[2]);
	mouse->SetChickenFaceDir(key);
	tagEyes* eyes = dynamic_cast<tagEyes*>(gVec[3]);
	eyes->SetChickenFaceDir(key);

	tagLeftArm* Larm = dynamic_cast<tagLeftArm*>(gVec[4]);
	Larm->SetChickenFaceDir(key);

	tagRightArm* Rarm = dynamic_cast<tagRightArm*>(gVec[5]);
	Rarm->SetChickenFaceDir(key);

	tagLeftLeg* Lleg = dynamic_cast<tagLeftLeg*>(gVec[6]);
	Lleg->SetChickenFaceDir(key);

	tagRightLeg* Rleg = dynamic_cast<tagRightLeg*>(gVec[7]);
	Rleg->SetChickenFaceDir(key);

	gCamera.SetCameraFaceDir(key);


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

	glEnableVertexAttribArray(PosLocation); // Enable �ʼ�! ����ϰڴ� �ǹ�
	glEnableVertexAttribArray(ColorLocation);
	glEnableVertexAttribArray(NormalLocation);

	glBindVertexArray(this->m_vao);

	WorldMatrix();

	glDrawArrays(GL_TRIANGLES, 0, 36); // 1 �ո�

	glDisableVertexAttribArray(PosLocation); // Disable �ʼ�!
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
	m_x_pos = 0.f;
	m_y_pos = 0.0f;
	m_z_pos = 0.f;

	m_x_scale = 0.01f;
	m_y_scale = 0.01f;
	m_z_scale = 0.01f;
}

void tagBody::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // �⺻ �̵� 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y�� ��
	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // �⺻ ����

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void tagBody::SetChickenFaceDir(unsigned char key)
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

void tagBody::Update()
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
		
		// �����ϸ� y,z ��ġ ���� -> y_pos�� 2.1�� �Ѿ ������
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

void tagBody::Collision()
{
	// m_coll�� false�� �浹�˻� X [ ������� ]
	//			 true�� �浹�˻� O [ ������� ]
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
		if (dynamic_cast<tagCar*>(gVec[i]) != nullptr) {
			float colPivot[6]{
				gVec[i]->GetXmaxBoundary(), gVec[i]->GetXminBoundary(), gVec[i]->GetYmaxBoundary(),
				gVec[i]->GetYminBoundary(), gVec[i]->GetZmaxBoundary(), gVec[i]->GetZminBoundary()
			};

			// �浹 ���� (AABB �浹 �˻�)
			bool collisionX = Chickenpivot[0] >= colPivot[1] && Chickenpivot[1] <= colPivot[0];
			bool collisionY = Chickenpivot[2] >= colPivot[3] && Chickenpivot[3] <= colPivot[2];
			bool collisionZ = Chickenpivot[4] >= colPivot[5] && Chickenpivot[5] <= colPivot[4];

			
			// ��� �࿡���� �浹�� �ִ��� Ȯ���Ͽ� ���� �浹 ����
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
				gVec[i]->GetXmaxBoundary(), gVec[i]->GetXminBoundary(), gVec[i]->GetYmaxBoundary(),
				gVec[i]->GetYminBoundary(), gVec[i]->GetZmaxBoundary(), gVec[i]->GetZminBoundary()
			};

			// �浹 ���� (AABB �浹 �˻�)
			bool collisionX = Chickenpivot[0] >= colPivot[1] && Chickenpivot[1] <= colPivot[0];
			bool collisionY = Chickenpivot[2] >= colPivot[3] && Chickenpivot[3] <= colPivot[2];
			bool collisionZ = Chickenpivot[4] >= colPivot[5] && Chickenpivot[5] <= colPivot[4];


			// ��� �࿡���� �浹�� �ִ��� Ȯ���Ͽ� ���� �浹 ����
			if (collisionX && collisionY && collisionZ) {
				cout << "�浹 ����!" << i << endl;
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

void tagBody::update_yvelo()
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

void tagBody::Set_yvelo_zero()
{
	m_fyvelo = 0.0;
}

void tagBody::UpdateChickenYpos()
{
	update_yvelo();
	m_y_pos += m_fyvelo;

}

void tagBody::ChickenJump()
{
	if (GetYpos() <= 0) {
		PlaySound(L"jump_2.wav", NULL, SND_ASYNC);
		m_y_pos += 0.01;
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

	glEnableVertexAttribArray(PosLocation); // Enable �ʼ�! ����ϰڴ� �ǹ�
	glEnableVertexAttribArray(ColorLocation);
	glEnableVertexAttribArray(NormalLocation);

	glBindVertexArray(this->m_vao);

	WorldMatrix();

	glDrawArrays(GL_TRIANGLES, 0, 36); // 1 �ո�

	glDisableVertexAttribArray(PosLocation); // Disable �ʼ�!
	glDisableVertexAttribArray(ColorLocation);
	glDisableVertexAttribArray(NormalLocation);

}

void tagHead::InitMatrix4()
{
	m_x_scale = 0.01f;
	m_y_scale = 0.01f;
	m_z_scale = 0.01f;

	m_x_pos = 0.f;
	m_y_pos = 0.01;
	m_z_pos = 0.f;
}

void tagHead::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // �⺻ �̵� 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y�� ��
	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // �⺻ ����

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void tagHead::SetChickenFaceDir(unsigned char key)
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

void tagHead::Update()
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk();
	}
}

void tagHead::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() + 0.01;
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

	glEnableVertexAttribArray(PosLocation); // Enable �ʼ�! ����ϰڴ� �ǹ�
	glEnableVertexAttribArray(ColorLocation);
	glEnableVertexAttribArray(NormalLocation);

	glBindVertexArray(this->m_vao);

	WorldMatrix();

	glDrawArrays(GL_TRIANGLES, 0, 36); // 1 �ո�

	glDisableVertexAttribArray(PosLocation); // Disable �ʼ�!
	glDisableVertexAttribArray(ColorLocation);
	glDisableVertexAttribArray(NormalLocation);

}

void tagMouse::InitMatrix4()
{
	m_x_scale = 0.01f / 4;
	m_y_scale = 0.01f / 3;
	m_z_scale = 0.0125f;

	m_x_pos = 0.0f;
	m_y_pos = 0.01f;
	m_z_pos = 0.0f;
}

void tagMouse::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::rotate(m_total_world, glm::radians(m_x_degree), glm::vec3(1.0f, 0.0f, 0.0f)); // x�� ȸ�� �⺻
	m_total_world = glm::rotate(m_total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y�� ȸ�� �⺻
	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // �⺻ �̵� 

	m_total_world = glm::translate(m_total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // �⺻ �̵� 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y�� ��

	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // �⺻ ����

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void tagMouse::SetChickenFaceDir(unsigned char key)
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

void tagMouse::Update()
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk();
	}
	
}

void tagMouse::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() + 0.01;
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

	glEnableVertexAttribArray(PosLocation); // Enable �ʼ�! ����ϰڴ� �ǹ�
	glEnableVertexAttribArray(ColorLocation);
	glEnableVertexAttribArray(NormalLocation);

	glBindVertexArray(this->m_vao);

	WorldMatrix();

	glDrawArrays(GL_TRIANGLES, 0, 36); // 1 �ո�

	glDisableVertexAttribArray(PosLocation); // Disable �ʼ�!
	glDisableVertexAttribArray(ColorLocation);
	glDisableVertexAttribArray(NormalLocation);

}

void tagEyes::InitMatrix4()
{
	m_x_scale = 0.011f;
	m_y_scale = 0.01f / 5;
	m_z_scale = 0.01f / 5;

	m_x_pos = 0.f;
	m_y_pos = 0.0105;
	m_z_pos = 0.f;
}

void tagEyes::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // �⺻ �̵� 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y�� ��
	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // �⺻ ����

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void tagEyes::SetChickenFaceDir(unsigned char key)
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

void tagEyes::Update()
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk();
	}
}

void tagEyes::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() + 0.0105;
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

	glEnableVertexAttribArray(PosLocation); // Enable �ʼ�! ����ϰڴ� �ǹ�
	glEnableVertexAttribArray(ColorLocation);
	glEnableVertexAttribArray(NormalLocation);

	glBindVertexArray(this->m_vao);

	WorldMatrix();

	glDrawArrays(GL_TRIANGLES, 0, 36); // 1 �ո�

	glDisableVertexAttribArray(PosLocation); // Disable �ʼ�!
	glDisableVertexAttribArray(ColorLocation);
	glDisableVertexAttribArray(NormalLocation);

}

void tagLeftArm::InitMatrix4()
{
	m_x_pos = 0.0;
	m_y_pos = -0.0005f;
	m_z_pos = 0.f;

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
	InitTotalworld();

	m_total_world = glm::rotate(m_total_world, glm::radians(m_x_degree), glm::vec3(1.0f, 0.0f, 0.0f)); // x�� ȸ�� �⺻
	m_total_world = glm::rotate(m_total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y�� ȸ�� �⺻ 
	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // �⺻ �̵� 

	m_total_world = glm::translate(m_total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // �⺻ �̵� 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y�� ��

	m_total_world = glm::translate(m_total_world, glm::vec3(0, 0.125 * 0.025, 0)); // �⺻ �̵�
	m_total_world = glm::rotate(m_total_world, glm::radians(hand_degree), glm::vec3(0.0f, 0.0f, 1.0f));
	m_total_world = glm::translate(m_total_world, glm::vec3(0, -0.125 * 0.025, 0)); // �⺻ �̵�

	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // �⺻ ����

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void tagLeftArm::SetChickenFaceDir(unsigned char key)
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

void tagLeftArm::Update()
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

void tagLeftArm::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() - 0.0005;
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

	glEnableVertexAttribArray(PosLocation); // Enable �ʼ�! ����ϰڴ� �ǹ�
	glEnableVertexAttribArray(ColorLocation);
	glEnableVertexAttribArray(NormalLocation);

	glBindVertexArray(this->m_vao);

	WorldMatrix();

	glDrawArrays(GL_TRIANGLES, 0, 36); // 1 �ո�

	glDisableVertexAttribArray(PosLocation); // Disable �ʼ�!
	glDisableVertexAttribArray(ColorLocation);
	glDisableVertexAttribArray(NormalLocation);

}

void tagRightArm::InitMatrix4()
{
	m_x_pos = 0.0;
	m_y_pos = 0.0005f;
	m_z_pos = 0.f;

	m_x_scale = 0.00125f;
	m_y_scale = 0.005f;
	m_z_scale = 0.005f;
}

void tagRightArm::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // �⺻ �̵� 

	m_total_world = glm::translate(m_total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // �⺻ �̵� 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y�� ��

	m_total_world = glm::translate(m_total_world, glm::vec3(0, 0.125 * 0.025, 0)); // �⺻ �̵�
	m_total_world = glm::rotate(m_total_world, glm::radians(-hand_degree), glm::vec3(0.0f, 0.0f, 1.0f));
	m_total_world = glm::translate(m_total_world, glm::vec3(0, -0.125 * 0.025, 0)); // �⺻ �̵�

	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // �⺻ ����

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void tagRightArm::SetChickenFaceDir(unsigned char key)
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

void tagRightArm::Update()
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

void tagRightArm::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() - 0.0005;
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

	glEnableVertexAttribArray(PosLocation); // Enable �ʼ�! ����ϰڴ� �ǹ�
	glEnableVertexAttribArray(ColorLocation);
	glEnableVertexAttribArray(NormalLocation);

	glBindVertexArray(this->m_vao);

	WorldMatrix();

	glDrawArrays(GL_TRIANGLES, 0, 36); // 1 �ո�

	glDisableVertexAttribArray(PosLocation); // Disable �ʼ�!
	glDisableVertexAttribArray(ColorLocation);
	glDisableVertexAttribArray(NormalLocation);

}

void tagLeftLeg::InitMatrix4()
{
	m_x_scale = 0.00125f;
	m_y_scale = 0.0125f;
	m_z_scale = 0.00125f;

	m_x_pos = 0.f;
	m_y_pos = -0.005f;
	m_z_pos = 0.f;
}

void tagLeftLeg::WorldMatrix()
{
	InitTotalworld();

	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // �⺻ �̵�

	m_total_world = glm::translate(m_total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // �⺻ �̵� 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y�� ��

	m_total_world = glm::translate(m_total_world, glm::vec3(0, 0.125 * 0.025, 0)); // �⺻ �̵�
	m_total_world = glm::rotate(m_total_world, glm::radians(hand_degree), glm::vec3(1.0f, 0.0f, 0.0f));
	m_total_world = glm::translate(m_total_world, glm::vec3(0, -0.125 * 0.025, 0)); // �⺻ �̵�

	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // �⺻ ����

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
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

void tagLeftLeg::SetChickenFaceDir(unsigned char key)
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

void tagLeftLeg::Update()
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk();
	}
	handling();
}

void tagLeftLeg::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() - 0.005;
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

	glEnableVertexAttribArray(PosLocation); // Enable �ʼ�! ����ϰڴ� �ǹ�
	glEnableVertexAttribArray(ColorLocation);
	glEnableVertexAttribArray(NormalLocation);

	glBindVertexArray(this->m_vao);

	WorldMatrix();

	glDrawArrays(GL_TRIANGLES, 0, 36); // 1 �ո�

	glDisableVertexAttribArray(PosLocation); // Disable �ʼ�!
	glDisableVertexAttribArray(ColorLocation);
	glDisableVertexAttribArray(NormalLocation);
}

void tagRightLeg::InitMatrix4()
{
	m_x_scale = 0.00125f;
	m_y_scale = 0.0125f;
	m_z_scale = 0.00125f;

	m_x_pos = 0.f;
	m_y_pos = -0.005f;
	m_z_pos = 0.f;
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
	InitTotalworld();

	m_total_world = glm::rotate(m_total_world, glm::radians(m_x_degree), glm::vec3(1.0f, 0.0f, 0.0f)); // x�� ȸ�� ��
	m_total_world = glm::rotate(m_total_world, glm::radians(m_y_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y�� ȸ�� �⺻ 
	m_total_world = glm::translate(m_total_world, glm::vec3(m_x_pos, m_y_pos, m_z_pos)); // �⺻ �̵� 

	m_total_world = glm::translate(m_total_world, glm::vec3(m_far_x, m_far_y, m_far_z)); // �⺻ �̵� 
	m_total_world = glm::rotate(m_total_world, glm::radians(face_degree), glm::vec3(0.0f, 1.0f, 0.0f)); // y�� ��

	m_total_world = glm::translate(m_total_world, glm::vec3(0, 0.125 * 0.025, 0)); // �⺻ �̵�
	m_total_world = glm::rotate(m_total_world, glm::radians(hand_degree), glm::vec3(1.0f, 0.0f, 0.0f));
	m_total_world = glm::translate(m_total_world, glm::vec3(0, -0.125 * 0.025, 0)); // �⺻ �̵�

	m_total_world = glm::scale(m_total_world, glm::vec3(m_x_scale, m_y_scale, m_z_scale)); // �⺻ ����

	unsigned int modelLocation = glGetUniformLocation(gShaderProgramID, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(this->m_total_world));
}

void tagRightLeg::SetChickenFaceDir(unsigned char key)
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

void tagRightLeg::Update()
{
	if (!gIsReach) {
		UpdateChickenYpos();
		Walk();

	}
	handling();
}

void tagRightLeg::UpdateChickenYpos()
{
	m_y_pos = gVec.at(0)->GetYpos() - 0.005;
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