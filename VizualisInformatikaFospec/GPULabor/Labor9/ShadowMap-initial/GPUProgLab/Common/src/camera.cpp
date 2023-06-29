#include "camera.hpp"
#include <iostream>

Camera::Camera()
{
	position = { 0.0f, 0.0f, 3.0f };
	yaw = -90.0f;
	pitch = 0.0f;

	fov = 1.5f;
	aspect = 1.0f;
	nearPlane = 0.1f;
	farPlane = 10000.0f;

	ahead = { 0.0f, 0.0f, -1.0f };
	right = { 1.0f, 0.0f, 0.0f };
	up = { 0.0f, 1.0f, 0.0f };

	speed = 10.5f;

	mouseDelta = { 0.0f, 0.0f };

	viewProjMatrix = glm::mat4(1.0f);
}

void Camera::update() {
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::lookAt(position, position + ahead, up);
	glm::mat4 proj = glm::perspective(fov, aspect, nearPlane, farPlane);

	viewProjMatrix = proj * view * model;
}

void Camera::move(GLfloat dt, std::set<char> keysPressed) {
	if (keysPressed.find('w') != keysPressed.end()) {
		position += ahead * (speed * dt);
	}
	
	if (keysPressed.find('s') != keysPressed.end()) {
		position -= ahead * (speed * dt);
	}

	if (keysPressed.find('d') != keysPressed.end()) {
		position += right * (speed * dt);
	}

	if (keysPressed.find('a') != keysPressed.end()) {
		position -= right * (speed * dt);
	}

	if (keysPressed.find('e') != keysPressed.end()) {
		position += up * (speed * dt);
	}

	if (keysPressed.find('q') != keysPressed.end()) {
		position -= up * (speed * dt);
	}

	update();
}

void Camera::mouseMoveStart(glm::vec2 coords) {
	mouseDelta = coords;
}

void Camera::mouseMove(glm::vec2 xy) {
	yaw += (mouseDelta[0] - xy.x) * 0.3f;
	pitch += (mouseDelta[1] - xy.y) * 0.3f;
	
	if (pitch > 90.0f)
		pitch = 90.0f;
	if (pitch < -90.0f)
		pitch = -90.0f;

	ahead = glm::normalize(glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
									 sin(glm::radians(pitch)),
									 sin(glm::radians(yaw)) * cos(glm::radians(pitch))));

	right = glm::normalize(glm::cross(ahead, glm::vec3(0.0, 1.0, 0.0)));

	update();

	mouseDelta = { xy.x, xy.y };
}

glm::mat4 Camera::getViewProjMatrix() const {
	return viewProjMatrix;
}

glm::vec3 Camera::getPosition() const {
	return position;
}

