#pragma once
class Camera
{
private:
	float camera_move_x;
	float camera_move_y;
	float camera_move_z;
	float camera_at_x;
	float camera_at_y;
	float camera_at_z;

	Dir face;
	Dir Past_face;
	GLfloat  walk_velo;
	GLfloat  face_degree;

	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;

	glm::mat4 Total_view;
	glm::mat4 Total_projection;

	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;

	Sign m_sign;

public:
	Camera()
		:
		face{ North },
		walk_velo{ 0.002f },
		face_degree{ 0.f },
		m_far_x{ 0.0 },
		m_far_y{ 0.0 },
		m_far_z{ 0.02 }
	{
		initCamera();

	}

	void initCamera()
	{
		camera_move_x = 0;
		camera_move_y = 0;
		camera_move_z = 0;
		camera_at_x = 0;
		camera_at_y = 0;
		camera_at_z = 0;
		m_sign = PLUS;
	}
	void Move();

	void PerspectiveProjection();
	void setViewTransform_firstVeiwPort();
	void setViewTransform_secondVeiwPort();
	void setViewTransform_thirdVeiwPort();
	void setViewTransform_firstVeiwPort_One();

	void setFaceDir(unsigned char key);
};