// Skeleton.cpp : Defines the entry point for the console application.
//

#include <GL\glew.h>
#include <GL\freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdio>
#include <chrono>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader.hpp"
#include "camera.hpp"
#include "model.hpp"
#include "quad.hpp"

const unsigned int windowWidth = 600;
const unsigned int windowHeight = 600;

Shader shader, depthShader, debugShader;
Camera camera;

Model giraffe;
Model ground;

std::vector<Model*> models;

Quad debugQuad;

std::chrono::system_clock::time_point startTime;
std::chrono::system_clock::time_point systemTime;

std::set<char> keysPressed;

unsigned int depthFBO;
unsigned int depthTexture;

void onInitialization()
{
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("Cannot initialize GLEW\n");
		exit(-1);
	}

	glClearColor(1.0f, 1.0f, 1.f, 1.0f);
	shader.loadShader(GL_VERTEX_SHADER, "..\\shaders\\passthrough.vert");
	shader.loadShader(GL_FRAGMENT_SHADER, "..\\shaders\\simple.frag");
	shader.compile();

	depthShader.loadShader(GL_VERTEX_SHADER, "..\\shaders\\depth.vert");
	depthShader.loadShader(GL_FRAGMENT_SHADER, "..\\shaders\\depth.frag");
	depthShader.compile();

	debugShader.loadShader(GL_VERTEX_SHADER, "..\\shaders\\debug.vert");
	debugShader.loadShader(GL_FRAGMENT_SHADER, "..\\shaders\\debug.frag");
	debugShader.compile();

	giraffe.init("..\\..\\..\\Common\\images\\giraffe.obj", "..\\..\\..\\Common\\images\\giraffe.jpg");
	ground.init("..\\..\\..\\Common\\images\\ground.obj", "..\\..\\..\\Common\\images\\ground.png");

	ground.setScale(glm::vec3(10.0f, 10.0f, 10.0f));
	ground.setPosition(glm::vec3(0.0f, -0.0855f, 0.0f));

	glGenFramebuffers(1, &depthFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);

	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 600, 600, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	debugQuad.init();
}

void renderScene(Shader& shader) {
	shader.setUniformMat4("viewProjMatrix", camera.getViewProjMatrix());
	glm::vec3 cameraPosition = camera.getPosition();
	shader.setUniform3f("cameraPosition", cameraPosition.x, cameraPosition.y, cameraPosition.z);

	shader.setUniformMat4("modelMatrix", giraffe.getModelMatrix());
	shader.setUniformMat4("modelMatrixInverse", glm::inverse(giraffe.getModelMatrix()));
	shader.setUniformTexture("modelTexture", giraffe.image.getTextureHandle(), 0);
	giraffe.render();

	shader.setUniformMat4("modelMatrix", ground.getModelMatrix());
	shader.setUniformMat4("modelMatrixInverse", glm::inverse(ground.getModelMatrix()));
	shader.setUniformTexture("modelTexture", ground.image.getTextureHandle(), 0);
	ground.render();
}

glm::mat4 getLightViewProj() {
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 8.0f);
	glm::vec3 lightPos = glm::vec3(-1.33927190, 0.866008162, 1.77144039);
	glm::mat4 lightView = glm::lookAt(lightPos, lightPos + glm::vec3(0.468118578, -0.522498608, -0.712643147), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightViewProj = lightProjection * lightView;
	return lightViewProj;
}

void onDisplay()
{
	glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 600, 600);
	glEnable(GL_DEPTH_TEST);
	depthShader.enable();
	depthShader.setUniformMat4("lightViewProj", getLightViewProj());
	renderScene(depthShader);
	depthShader.disable();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 600, 600);
	shader.enable();
	shader.setUniformMat4("lightViewProjMatrix", getLightViewProj());
	shader.setUniformTexture("depthTexture", depthTexture, 1);
	renderScene(shader);
	shader.disable();

	glViewport(0, 400, 200, 200);
	debugShader.enable();
	debugShader.setUniformTexture("depthTexture", depthTexture, 0);
	debugQuad.render();
	debugShader.disable();

	glutSwapBuffers();
}

void onKeyboardDown(unsigned char key, int pX, int pY) {
	keysPressed.insert(key);

	switch (key)
	{
	case 27:
		glutExit();
		break;
	}
}

void onKeyboardUp(unsigned char key, int x, int y) {
	keysPressed.clear();
}

void onMouseDown(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		camera.mouseMoveStart(glm::vec2((float)x, (float)y));
	}
}

void onMouseMove(int x, int y) {
	camera.mouseMove(glm::vec2((float)x, (float)y));
}

void onIdle() {
	auto currentTime = std::chrono::system_clock::now();
	std::chrono::duration<double> timeStep = currentTime - systemTime;
	systemTime = currentTime;

	float dt = timeStep.count();
	camera.move(dt, keysPressed);

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
	startTime = std::chrono::system_clock::now();
	systemTime = startTime;

	glutDisplayFunc(onDisplay);
	glutKeyboardFunc(onKeyboardDown);
	glutKeyboardUpFunc(onKeyboardUp);
	glutMouseFunc(onMouseDown);
	glutMotionFunc(onMouseMove);
	glutIdleFunc(onIdle);
	glutMainLoop();

    return 0;
}

