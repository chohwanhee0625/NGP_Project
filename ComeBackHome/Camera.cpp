#include "usingInclude.h"
#include "Basis.h"
#include "Camera.h"
#include "extern.h"

//===========================================================================================

void Camera::PerspectiveProjection()
{
	Total_projection = glm::perspective(glm::radians(45.0f), 1.f, 0.1f, 50.f);
	Total_projection = glm::translate(Total_projection, glm::vec3(0.0f, 0.0f, 0.f));
	unsigned int projectionLocation = glGetUniformLocation(gShaderProgramID, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(Total_projection));
}

void Camera::setViewTransform_firstVeiwPort()
{
	Total_view = glm::mat4{ 1.0f };
	
	if (gToggle[(int)Toggle::NearFar] == Far)
		cameraPos = glm::vec3{ 0.1f + camera_move_x , 0.5f + camera_move_y, 0.5f + camera_move_z };
	else if (gToggle[(int)Toggle::NearFar] == Near)
		cameraPos = glm::vec3{ 0.0f + camera_move_x , camera_move_y + 0.05f, 0.2f + camera_move_z }; // y-0.05f
	
	cameraDirection = glm::vec3{ 0.0f + camera_move_x, 0.0f + camera_move_y, 0.0f + camera_move_z };
	
	cameraUp = glm::vec3{ 0.f, 1.f, 0.f };
	Total_view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	unsigned int viewLocation = glGetUniformLocation(gShaderProgramID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(Total_view));
}

void Camera::setViewTransform_firstVeiwPort_One()
{
	Total_view = glm::mat4{ 1.0f };
	
	if (North == face) {
		cameraPos = glm::vec3{ camera_move_x , camera_move_y+0.015, camera_move_z };
		cameraDirection = glm::vec3{camera_move_x, camera_move_y, -5.f + camera_move_z };
	}
	else if (South == face) {
		cameraPos = glm::vec3{ camera_move_x , camera_move_y + 0.015, camera_move_z };
		cameraDirection = glm::vec3{ camera_move_x, camera_move_y, +5.f + camera_move_z };
	}
	else if (East == face) {
		cameraPos = glm::vec3{ camera_move_x , camera_move_y + 0.015, camera_move_z };
		cameraDirection = glm::vec3{ 5.f+camera_move_x, camera_move_y,  + camera_move_z };
	}
	else if (West == face) {
		cameraPos = glm::vec3{ camera_move_x , camera_move_y + 0.015, camera_move_z };
		cameraDirection = glm::vec3{ camera_move_x - 5.f, camera_move_y, + camera_move_z };
	}
	else
	{
		if (North == Past_face) {
			cameraPos = glm::vec3{ camera_move_x , camera_move_y + 0.01, camera_move_z };
			cameraDirection = glm::vec3{ camera_move_x, camera_move_y, -5.f + camera_move_z };
		}
		else if (South == Past_face) {
			cameraPos = glm::vec3{ camera_move_x , camera_move_y + 0.01, camera_move_z };
			cameraDirection = glm::vec3{ camera_move_x, camera_move_y, +5.f + camera_move_z };
		}
		else if (East == Past_face) {
			cameraPos = glm::vec3{ camera_move_x , camera_move_y + 0.01, camera_move_z };
			cameraDirection = glm::vec3{ 5.f + camera_move_x, camera_move_y,  +camera_move_z };
		}
		else if (West == Past_face) {
			cameraPos = glm::vec3{ camera_move_x , camera_move_y + 0.01, camera_move_z };
			cameraDirection = glm::vec3{ camera_move_x - 5.f, camera_move_y, +camera_move_z };
		}
	}

	cameraUp = glm::vec3{ 0.f, 1.f, 0.f };
	Total_view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	unsigned int viewLocation = glGetUniformLocation(gShaderProgramID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(Total_view));
}

void Camera::setViewTransform_secondVeiwPort()
{
	Total_view = glm::mat4{ 1.0f };

	//   cameraPos = glm::vec3{ 0.1f + camera_move_x , 0.08f, -0.2f + camera_move_z };
 //   cameraPos = glm::vec3{ 0.05f + camera_move_x ,camera_move_y +  0.08f, -0.07f + camera_move_z };
	cameraPos = glm::vec3{ 0.05f + camera_move_x ,camera_move_y + 0.1f, -0.07f + camera_move_z };

	cameraDirection = glm::vec3{ 0.0f + camera_move_x, camera_move_y + 0.0f, 0.0f + camera_move_z };
	cameraUp = glm::vec3{ 0.f, 1.f, 0.f };
	Total_view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	unsigned int viewLocation = glGetUniformLocation(gShaderProgramID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(Total_view));
}

void Camera::setViewTransform_thirdVeiwPort()
{
	Total_view = glm::mat4{ 1.0f };

	cameraPos = glm::vec3{ 0.0f, camera_move_y + 0.5f, 30.0f };

	cameraDirection = glm::vec3{ 0.0f, camera_move_y + 0.0f, 30.0f };
	cameraUp = glm::vec3{ 0.f, 0.f, -1.f };
	Total_view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	unsigned int viewLocation = glGetUniformLocation(gShaderProgramID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(Total_view));
}

void Camera::setFaceDir(unsigned char key)
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
			Past_face = face;
		}
		face = STOP;
		break;
	}
}

void Camera::Move()
{
		camera_move_z = gVec.at(0)->getZdistance();
		camera_move_x = gVec.at(0)->getXdistance();
		camera_move_y = gVec.at(0)->GetYdistance();
	
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


