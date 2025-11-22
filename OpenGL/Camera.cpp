#include "Camera.h"

Camera::Camera(
	Resolution _resolution,
	glm::vec3 _eye, glm::vec3 _center, glm::vec3 _up,
	float _fov, float _near, float _far
):
	fov(_fov), near_plane(_near), far_plane(_far), eye(_eye), center(_center), up(_up)
{
	projection = glm::perspective(
		glm::radians(fov),
		(float)_resolution.width / (float)_resolution.height,
		near_plane,
		far_plane
	);

	view = glm::lookAt(eye,center,up);
}

void Camera::SetProjection(Resolution _resolution) {
	projection = glm::perspective(glm::radians(fov),
		(float)_resolution.width / (float)_resolution.height,
		near_plane,
		far_plane);
}

void Camera::LookAt(const glm::vec3& _position, const glm::vec3& _lookAt, const glm::vec3& _up)
{
	position = _position;
	view = glm::lookAt(_position, _lookAt, _up);
}
