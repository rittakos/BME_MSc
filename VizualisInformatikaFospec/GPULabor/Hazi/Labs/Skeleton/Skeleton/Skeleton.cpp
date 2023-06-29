#include <GL\glew.h>
#include <GL\freeglut.h>

#include <cstdio>

#include "shader.hpp"
#include "texture.hpp"
#include "quad.hpp"


#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <algorithm>
#include <vector>

const unsigned int windowWidth = 600;
const unsigned int windowHeight = 600;

Quad quad;
Shader shader;

float	zoom = 1.0f;
float	centerX = -0.0f;
float	centerY = -0.0f;



void onInitialization()
{
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("Cannot initialize GLEW\n");
		exit(-1);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	quad.init();
	shader.loadShader(GL_VERTEX_SHADER, "..\\shaders\\shader.vert");
	shader.loadShader(GL_FRAGMENT_SHADER, "..\\shaders\\shader.frag");
	shader.compile();
}

void onDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.enable();
	shader.setUniform1f("zoom", zoom);
	shader.setUniform2f("center", centerX, centerY);
	quad.render();
	shader.disable();

	glutSwapBuffers();
}

void onKeyboard(unsigned char key, int pX, int pY) {
	switch (key)
	{
	case 27:
		glutExit();
		break;
	case 'w':
		centerY = centerY + 0.01f * zoom;
		break;
	case 's':
		centerY = centerY - 0.01f * zoom;
		break;
	case 'a':
		centerX = centerX - 0.01f * zoom;
		break;
	case 'd':
		centerX = centerX + 0.01f * zoom;
		break;
	}

	if (centerY > 1.0f)
		centerY = 1.0f;
	if (centerY < -1.0f)
		centerY = -1.0f;
	if (centerX < -1.0f)
		centerX = -1.0f;
	if (centerX > 1.0f)
		centerX = 1.0f;

	shader.setUniform2f("center", centerX, centerY);
	onDisplay();
}


void onMouseWheel(int wheel, int dir, int pX, int pY) {
	if (dir > 0)
		zoom *= 1.04f;
	else if (dir < 0)
		zoom *= 0.96f;

	shader.setUniform1f("zoom", zoom);
	onDisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glewExperimental = true;
	glewInit();

	printf("GL Vendor    : %s\n", glGetString(GL_VENDOR));
	printf("GL Renderer  : %s\n", glGetString(GL_RENDERER));
	printf("GL Version (string)  : %s\n", glGetString(GL_VERSION));
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	printf("GL Version (integer) : %d.%d\n", major, minor);
	printf("GLSL Version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	onInitialization();
	glutDisplayFunc(onDisplay);
	glutKeyboardFunc(onKeyboard);
	glutMouseWheelFunc(onMouseWheel);
	glutMainLoop();

	return 0;
}
