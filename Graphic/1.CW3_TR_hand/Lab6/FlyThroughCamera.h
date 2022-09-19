#pragma once

#include <glm/glm/glm.hpp>
#include "camera.h"
#include <iostream>

void MoveCamera(SCamera& in, SCamera::Camera_Movement direction)
{
	

	
	switch (direction)
	{
	case  SCamera::Camera_Movement::FORWARD:
		in.Position += in.Front * in.MovementSpeed;
		break;
	case  SCamera::Camera_Movement::BACKWARD:
		in.Position -= in.Front * in.MovementSpeed;
		break;
	case  SCamera::Camera_Movement::RIGHT:
		in.Position += in.Right * in.MovementSpeed;
		break;
	case  SCamera::Camera_Movement::LEFT:
		in.Position -= in.Right * in.MovementSpeed;
		break;
	default:
		break;
	}
	std::cout << "KEYBOARD: "<< in.Position.x <<" " << in.Position.y << " " << in.Position.z<< std::endl;
}


void OrientCamera(SCamera& in, float xoffset, float yoffset)
{
	in.Yaw -= xoffset * in.MouseSensitivity;
	in.Pitch -= yoffset * in.MouseSensitivity;

	glm::vec3 focus_pos;
	float yaw, pitch;
	yaw = glm::radians(in.Yaw);
	pitch = glm::radians(in.Pitch);
	focus_pos.x = glm::cos(yaw) * glm::cos(pitch) ;
	focus_pos.y = glm::sin(pitch);
	focus_pos.z = glm::sin(yaw) * glm::cos(pitch) ;

	in.Front = glm::normalize(focus_pos);
	in.Right = glm::normalize(glm::cross(in.Front, in.WorldUp));
	in.Up = glm::normalize(glm::cross(in.Right, in.Front));

	std::cout <<"Mouse: " << in.Front.x << " " << in.Front.y << " " << in.Front.z << std::endl;
}


