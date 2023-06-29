// Skeleton.cpp : Defines the entry point for the console application.
//

#include <GL\glew.h>
#include <GL\freeglut.h>

#include <cstdio>
#include <minmax.h>

#include "shader.hpp"

const unsigned int windowWidth = 600;
const unsigned int windowHeight = 600;

Shader feedBackShader, shader;

struct xyzw
{
	float x, y, z, w;
};

struct Particle
{
	xyzw position;
	xyzw velocity;
	xyzw life;
};

GLuint positionBuffer[2];
GLuint vao[2];

unsigned int currentVB;
unsigned int currentTFB;

const unsigned int particlesNum = 1;

void onInitialization()
{
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("Cannot initialize GLEW\n");
		exit(-1);
	}

	glClearColor(0.4f, 0.6f, 0.8f, 1.0f);

	// Feedback pass
	feedBackShader.loadShader(GL_VERTEX_SHADER, "..\\shaders\\passthrough.vert");
	feedBackShader.loadShader(GL_GEOMETRY_SHADER, "..\\shaders\\duplicate.geom");
	feedBackShader.compile();
	feedBackShader.enable();

	// Render pass
	shader.loadShader(GL_VERTEX_SHADER, "..\\shaders\\passthrough.vert");
	shader.loadShader(GL_FRAGMENT_SHADER, "..\\shaders\\simple.frag");
	shader.compile();

	// Create VAOs
	glGenVertexArrays(2, vao);
	glGenBuffers(2, positionBuffer);

	for (int i = 0; i < 2; i++) {

		glBindVertexArray(vao[i]);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, particlesNum * sizeof(Particle)*10000, NULL, GL_DYNAMIC_DRAW);
		Particle* particle = (Particle*)glMapBufferRange(GL_ARRAY_BUFFER, 0, particlesNum * sizeof(Particle)*10000, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
		for (unsigned int i = 0; i < particlesNum; ++i)
		{
			particle[i].position.x = -0.0f; //2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f;
			particle[i].position.y = 0.0f;//2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f;
			particle[i].position.z = -0.0f;//2.0f * ((float)rand() / (float)RAND_MAX) - 1.0f;
			particle[i].position.w = 1.0f;

			particle[i].velocity.x = 0.0;
			particle[i].velocity.y = 0.0;
			particle[i].velocity.z = 0.0;
			particle[i].velocity.w = 0.0;

			particle[i].life.x = 1.0;
			particle[i].life.y = 0.0;
			particle[i].life.z = 0.0;
			particle[i].life.w = 0.0;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer[i]);
		glVertexAttribPointer((GLuint)0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer[i]);
		glVertexAttribPointer((GLuint)1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)16);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer[i]);
		glVertexAttribPointer((GLuint)2, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)32);
	}
	glBindVertexArray(0);

	glPointSize(4.0f);

}

void onDisplay()
{
	static int currentSize = 1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(feedBackShader.getProgramID());

	// Feedback pass
	GLuint query;
	glGenQueries(1, &query);

	feedBackShader.enable();
	glEnable(GL_RASTERIZER_DISCARD);
	glBindVertexArray(vao[currentVB]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, positionBuffer[currentTFB]);
	glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, query);
	glBeginTransformFeedback(GL_POINTS);
	glDrawArrays(GL_POINTS, 0, currentSize);
	glEndTransformFeedback();
	glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
	GLuint primitives;
	glGetQueryObjectuiv(query, GL_QUERY_RESULT, &primitives);

	currentSize = primitives > 0 ? primitives : 1;

	std::vector<Particle> feedback;
	feedback.resize(currentSize);
	glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, feedback.size()*sizeof(Particle), feedback.data());

	glDisable(GL_RASTERIZER_DISCARD);
	glFlush();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render pass
	glUseProgram(shader.getProgramID());
	glBindVertexArray(vao[currentTFB]);
	glDrawArrays(GL_POINTS, 0, currentSize);

	glutSwapBuffers();

	currentVB = currentTFB;
	currentTFB = (currentTFB + 1) & 0x1;
}

void onKeyboard(unsigned char key, int pX, int pY) {
	switch (key)
	{
	case 27:
		glutExit();
		break;
	}
}

void onIdle()
{
	glutPostRedisplay();
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
	glutIdleFunc(onIdle);
	glutMainLoop();

	glDeleteBuffers(2, positionBuffer);
	glDeleteVertexArrays(2, vao);

	return 0;
}

