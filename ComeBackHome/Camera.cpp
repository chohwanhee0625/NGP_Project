#include "usingInclude.h"
#include "Basis.h"
#include "Camera.h"
#include "extern.h"

//===========================================================================================

void Camera::PerspectiveProjection()
{
	total_projection = glm::perspective(glm::radians(45.0f), 1.f, 0.1f, 50.f);
	total_projection = glm::translate(total_projection, glm::vec3(0.0f, 0.0f, 0.f));
	unsigned int projectionLocation = glGetUniformLocation(gShaderProgramID, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(total_projection));
}

void Camera::SetViewTransform_ThirdPersonViewport()
{
	total_view = glm::mat4{ 1.0f };
	
	if (gToggle[(int)Toggle::NearFar] == Far) {
		// 먼 3인칭
		camera_pos = glm::vec3{ 0.1f + camera_move_x , 0.5f + camera_move_y, 0.5f + camera_move_z };
	}
	else if (gToggle[(int)Toggle::NearFar] == Near) {
		// 가까운 3인칭
		camera_pos = glm::vec3{ 0.0f + camera_move_x , camera_move_y + 0.05f, 0.2f + camera_move_z }; // y-0.05f
	}
	
	camera_direction = glm::vec3{ 0.0f + camera_move_x, 0.0f + camera_move_y, 0.0f + camera_move_z };
	
	camera_up = glm::vec3{ 0.f, 1.f, 0.f };
	total_view = glm::lookAt(camera_pos, camera_direction, camera_up);

	unsigned int viewLocation = glGetUniformLocation(gShaderProgramID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(total_view));
}

void Camera::SetViewTransform_FirstPersonViewport()
{
	// 1인칭 

	total_view = glm::mat4{ 1.0f };
	
	if (North == face) {
		camera_pos = glm::vec3{ camera_move_x , camera_move_y+0.015, camera_move_z };
		camera_direction = glm::vec3{camera_move_x, camera_move_y, -5.f + camera_move_z };
	}
	else if (South == face) {
		camera_pos = glm::vec3{ camera_move_x , camera_move_y + 0.015, camera_move_z };
		camera_direction = glm::vec3{ camera_move_x, camera_move_y, +5.f + camera_move_z };
	}
	else if (East == face) {
		camera_pos = glm::vec3{ camera_move_x , camera_move_y + 0.015, camera_move_z };
		camera_direction = glm::vec3{ 5.f+camera_move_x, camera_move_y,  + camera_move_z };
	}
	else if (West == face) {
		camera_pos = glm::vec3{ camera_move_x , camera_move_y + 0.015, camera_move_z };
		camera_direction = glm::vec3{ camera_move_x - 5.f, camera_move_y, + camera_move_z };
	}
	else
	{
		if (North == pre_face) {
			camera_pos = glm::vec3{ camera_move_x , camera_move_y + 0.01, camera_move_z };
			camera_direction = glm::vec3{ camera_move_x, camera_move_y, -5.f + camera_move_z };
		}
		else if (South == pre_face) {
			camera_pos = glm::vec3{ camera_move_x , camera_move_y + 0.01, camera_move_z };
			camera_direction = glm::vec3{ camera_move_x, camera_move_y, +5.f + camera_move_z };
		}
		else if (East == pre_face) {
			camera_pos = glm::vec3{ camera_move_x , camera_move_y + 0.01, camera_move_z };
			camera_direction = glm::vec3{ 5.f + camera_move_x, camera_move_y,  +camera_move_z };
		}
		else if (West == pre_face) {
			camera_pos = glm::vec3{ camera_move_x , camera_move_y + 0.01, camera_move_z };
			camera_direction = glm::vec3{ camera_move_x - 5.f, camera_move_y, +camera_move_z };
		}
	}

	camera_up = glm::vec3{ 0.f, 1.f, 0.f };
	total_view = glm::lookAt(camera_pos, camera_direction, camera_up);

	unsigned int viewLocation = glGetUniformLocation(gShaderProgramID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(total_view));
}

void Camera::SetViewTransform_ChickenViewport()
{
	// 치킨 고정 카메라

	total_view = glm::mat4{ 1.0f };

	//   cameraPos = glm::vec3{ 0.1f + camera_move_x , 0.08f, -0.2f + camera_move_z };
 //   cameraPos = glm::vec3{ 0.05f + camera_move_x ,camera_move_y +  0.08f, -0.07f + camera_move_z };
	camera_pos = glm::vec3{ 0.05f + camera_move_x ,camera_move_y + 0.1f, -0.07f + camera_move_z };

	camera_direction = glm::vec3{ 0.0f + camera_move_x, camera_move_y + 0.0f, 0.0f + camera_move_z };
	camera_up = glm::vec3{ 0.f, 1.f, 0.f };
	total_view = glm::lookAt(camera_pos, camera_direction, camera_up);

	unsigned int viewLocation = glGetUniformLocation(gShaderProgramID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(total_view));
}

void Camera::SetViewTransform_BorderViewport()
{
	// 경계 액자 카메라

	total_view = glm::mat4{ 1.0f };

	camera_pos = glm::vec3{ 0.0f, camera_move_y + 0.5f, 30.0f };

	camera_direction = glm::vec3{ 0.0f, camera_move_y + 0.0f, 30.0f };
	camera_up = glm::vec3{ 0.f, 0.f, -1.f };
	total_view = glm::lookAt(camera_pos, camera_direction, camera_up);

	unsigned int viewLocation = glGetUniformLocation(gShaderProgramID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(total_view));
}

void Camera::SetCameraFaceDir(unsigned char key)
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
		if (STOP != face) {
			pre_face = face;
		}
		face = STOP;
		break;
	}
}

void Camera::Move()
{
		camera_move_x = gVec.at(0)->GetXpos();
		camera_move_y = gVec.at(0)->GetYpos();
		camera_move_z = gVec.at(0)->GetZpos();
	
		/*switch (face)
	{
	case STOP:
		break;

	case South:
		camera_move_z += walk_velo;
		break;

	case West:
		camera_move_x -= walk_velo;
		break;

	case East:
		camera_move_x += walk_velo;
		break;

	case North:
		camera_move_z -= walk_velo;
		break;
	}*/
}


