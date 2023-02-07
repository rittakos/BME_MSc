#pragma once

#include <GL/glew.h>
#include "Vector3.h"
#include <vector>

class Mesh
{
public:
	Mesh(void);
	~Mesh(void);

	void setData(float* vertices, unsigned short* indices, unsigned int numVertices, unsigned int numTriangles, float* normals = 0, float* texcoords = 0);
	void render();
	void renderWithSorting(Vector3 cameraPos);

	int getMaterialIndex(){return materialIndex;}
	void setMaterialIndex(int idx){materialIndex = idx;}

	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<Vector3> tangents;
	std::vector<float> texcoords;
	std::vector<unsigned short> indices;

protected:

	void clear();

	GLuint vertexBuffer;
	GLuint normalBuffer;
	GLuint texcoordBuffer;
	GLuint tangentBuffer;
	GLuint indexBuffer;

	int materialIndex;
};

