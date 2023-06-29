#pragma once
#ifndef _CAMERA_
#define _CAMERA_

#include <GL/glew.h>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <set>
#include <string>

class Camera {
private:
	glm::vec3 position;

	GLfloat yaw;
	GLfloat pitch;
	GLfloat fov;
	GLfloat aspect;
	GLfloat nearPlane;
	GLfloat farPlane;

	glm::vec3 ahead;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat speed;

	glm::mat4 viewProjMatrix;

	glm::vec2 mouseDelta;

public:
	Camera();

	void update();
	void move(GLfloat dt, std::set<char> keysPressed);
	void mouseMoveStart(glm::vec2 coords);
	void mouseMove(glm::vec2 xy);
	glm::mat4 getViewProjMatrix() const;
	glm::vec3 getPosition() const;
};

#endif
