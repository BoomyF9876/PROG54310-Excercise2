#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "StandardIncludes.h"

class Camera
{
public:
	Camera(
		Resolution _resolution,
		glm::vec3 _eye = {1, 0, 0}, glm::vec3 _center = { 0, 0, 0 }, glm::vec3 _up = { 0, 1, 0 },
		float _fov = 45.0f, float _near = 0.1f, float _far = 1000.0f
	);
	~Camera() = default;

	void LookAt(const glm::vec3& _position, const glm::vec3& _lookAt, const glm::vec3& _up);
	void SetProjection(Resolution _resolution);

	glm::mat4 GetProjection() { return projection; }
	glm::mat4 GetView() { return view; }
	glm::vec3 GetPosition() { return position; }
private:
	float fov, near_plane, far_plane;
	glm::vec3 eye, center, up;
	glm::mat4 projection;
	glm::mat4 view = {};
	glm::vec3 position = {};
};

#endif

