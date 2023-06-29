#pragma once

#ifndef _CATMULL_
#define _CATMULL_

#include <GL/glew.h>
#include <vector>

class Catmull {
private:
	GLuint vertexArray;

	static GLfloat vertices[18];
	GLuint vertexBuffer;

	static GLfloat texCoords[12];
	GLuint texCoordBuffer;

	std::vector<GLfloat> points;
	std::vector<GLfloat> controlPoints;
	int pointCount;

	void calcCatmullPoints();

public:
	Catmull();
	~Catmull();

	void addPoint(GLfloat x, GLfloat y);

	void init();
	void render();
	void render(int widtgh, int height);
};

#endif
