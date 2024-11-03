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
	Dir pre_face;

	GLfloat  move_velo;
	GLfloat  face_degree;

	GLfloat m_far_x;
	GLfloat m_far_y;
	GLfloat m_far_z;

	glm::mat4 total_view;
	glm::mat4 total_projection;

	glm::vec3 camera_pos;
	glm::vec3 camera_direction;
	glm::vec3 camera_up;

	Sign sign;

public:
	Camera()
		:
		face{ North },
		move_velo{ 0.002f },
		face_degree{ 0.f },
		m_far_x{ 0.0 },
		m_far_y{ 0.0 },
		m_far_z{ 0.02 }
	{
		InitCamera();
	}

	void InitCamera()
	{
		camera_move_x = 0;
		camera_move_y = 0;
		camera_move_z = 0;
		camera_at_x = 0;
		camera_at_y = 0;
		camera_at_z = 0;
		sign = PLUS;
	}
	void Move();

	void PerspectiveProjection();
	
	// 3인칭, 1인칭
	void SetViewTransform_ThirdPersonViewport();
	void SetViewTransform_FirstPersonViewport();
	
	// 치킨 고정, 경계액자 
	void SetViewTransform_ChickenViewport();
	void SetViewTransform_BorderViewport();

	void SetCameraFaceDir(unsigned char key);
};