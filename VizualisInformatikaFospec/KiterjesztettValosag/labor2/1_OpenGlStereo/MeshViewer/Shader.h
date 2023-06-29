
#pragma once

#include <GL\glew.h>

#include <string>
using namespace std;

//--------------------------------------------------------------------------------
// Shader
// A wrapper class for OpenGL shader program objects. They should be
// created and accessed from the main OpenGL user thread only.
//--------------------------------------------------------------------------------
class Shader {
public:
	class Values {
		friend class Shader;
	private:
		const GLchar** values;
		GLsizei size;

	public:
		Values();
		Values(const GLchar** values, GLsizei size);
	};
protected:
	GLuint shaderProgram;
	GLuint nextTextureUnit;

	void shaderFromFile(string path, GLenum shaderType, GLuint& handle);
	string getShaderInfoLog(GLuint& object);
	string getProgramInfoLog(GLuint& object);

	// Disabling special constructors
	Shader(Shader const&);
	void operator=(Shader const&);

public:
	Shader(string vertexShaderPath, string fragmentShaderPath, Values input,
		string geometryShaderPath = string(), Values feedback = Values());
	~Shader();

	GLuint getProgram();
	void resetTextureUnit();
	void enable();
	void disable();

	void bindUniformInt(const char* name, int i);

	void bindUniformFloat(const char* name, float f);
	void bindUniformFloat2(const char* name, float *f);
	void bindUniformFloat3(const char* name, float *f);
	void bindUniformFloat4(const char* name, float *f);

	void bindUniformMat3(const char* name, float* m);
	void bindUniformMat4(const char* name, float* m, GLsizei count = 1);

	void bindUniformTexture(const char* name, GLuint textureHandle);
};

