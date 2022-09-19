#pragma once
#define _USE_MATH_DEFINES 
#define DEG2RAD(n)	n*(M_PI/180)
#include<math.h>
#include <stdio.h>
#include <glm/glm/glm.hpp>
#include "camera.h"

float cam_dist = 2.f;

void MoveAndOrientCamera(SCamera& in, glm::vec3 target, float distance, float xoffset, float yoffset)
{
	in.Yaw -= xoffset * in.MovementSpeed;
	in.Pitch -= yoffset * in.MovementSpeed;
	if (in.Pitch > 89.0f) in.Pitch = 89.0f;
	if (in.Pitch < -89.0f) in.Pitch = -89.0f;

	float yaw, pitch;
	yaw = DEG2RAD(in.Yaw);
	pitch = DEG2RAD(in.Pitch);
	in.Position.x = glm::cos(yaw) * glm::cos(pitch) * cam_dist;
	in.Position.y = glm::sin(pitch) * cam_dist;
	in.Position.z = glm::sin(yaw) * glm::cos(pitch)* cam_dist;
	//glm::vec3(glm::cos(yaw)*glm::sin1(pitch), glm::sin(pitch), glm::sin(yaw)*glm::cos(pitch));
	in.Front = glm::normalize(target - in.Position);
	in.Right = glm::normalize(glm::cross(in.Front, in.WorldUp));
	in.Up = glm::normalize(glm::cross(in.Right, in.Front));

}