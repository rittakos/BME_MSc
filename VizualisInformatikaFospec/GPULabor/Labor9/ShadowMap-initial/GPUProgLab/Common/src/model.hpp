#pragma once
#ifndef _MODEL_
#define _MODEL_

#include <GL/glew.h>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

#include "mesh.hpp"
#include "texture.hpp"

class Model {
private:
	glm::vec3 position;
	GLfloat roll;
	GLfloat yaw;
	GLfloat pitch;
	glm::vec3 scale;

	glm::mat4 modelMatrix;
public:
	std::vector<Mesh> meshes;
	Texture2D image;

	Model();
	~Model();

	void init(const std::string& path, const std::string& textureFileName);
	void processNode(aiNode* node, const aiScene* scene);
	void render();
	void setPosition(glm::vec3 newPosition);
	void setRoll(GLfloat newRoll);
	void setYaw(GLfloat newYaw);
	void setPitch(GLfloat newPitch);
	void setScale(glm::vec3 newScale);

	glm::mat4 getModelMatrix();
};

#endif
