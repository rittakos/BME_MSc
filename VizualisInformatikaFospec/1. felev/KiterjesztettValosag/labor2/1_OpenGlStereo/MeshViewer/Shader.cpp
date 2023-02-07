
#include "Shader.h"
#include <string>
#include <sstream>
#include <fstream>

Shader::Values::Values() : size(0), values(0)
{ }

Shader::Values::Values(const GLchar** values, GLsizei size)
	: values(values), size(size)
{ }

void Shader::shaderFromFile(string path, GLenum shaderType, GLuint& handle) {
	const char* shaderSource[1];
	int shaderSourceLength[1];
	int errorFlag = -1;

	ifstream file(path, ios::binary);
	if (!file.is_open()) {
		printf("Error: can't open file: %s\n", path);
	}
	stringstream sstr;
	sstr << file.rdbuf();
	string buff = sstr.str();
	shaderSource[0] = buff.c_str();
	shaderSourceLength[0] = (int)buff.length();

	handle = glCreateShader(shaderType);
	glShaderSource(handle, 1, shaderSource, shaderSourceLength);
	glCompileShader(handle);

	glGetShaderiv(handle, GL_COMPILE_STATUS, &errorFlag);
	if (!errorFlag) {
		printf("Error: failed to compile shader: %s \n %s\n", path.c_str(), getShaderInfoLog(handle).c_str());
	}
}

Shader::Shader(string vertexShaderPath, string fragmentShaderPath, Values input,
	string geometryShaderPath, Values feedback)
	: nextTextureUnit(0)
{
	GLuint vertexProgram, fragmentProgram, geometryProgram = 0;

	shaderFromFile(vertexShaderPath, GL_VERTEX_SHADER, vertexProgram);
	shaderFromFile(fragmentShaderPath, GL_FRAGMENT_SHADER, fragmentProgram);
	if (!geometryShaderPath.empty()) {
		shaderFromFile(geometryShaderPath, GL_GEOMETRY_SHADER, geometryProgram);
	}
	// Linking shaders
	int errorFlag = -1;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexProgram);
	glAttachShader(shaderProgram, fragmentProgram);
	if (geometryProgram != 0) {
		glAttachShader(shaderProgram, geometryProgram);
	}
	for (int i = 0; i < input.size; i++) {
		glBindAttribLocation(shaderProgram, i, input.values[i]);
	}
	if (feedback.size != 0) {
		glTransformFeedbackVaryings(shaderProgram, feedback.size, feedback.values, GL_SEPARATE_ATTRIBS);
	}
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &errorFlag);
	if (!errorFlag) {
		printf("Error: can't link shader:\n %s\n", getProgramInfoLog(shaderProgram).c_str());
	}
	// Can be freed after linking
	glDeleteShader(vertexProgram);
	glDeleteShader(fragmentProgram);
	if (geometryProgram != 0) {
		glDeleteShader(geometryProgram);
	}
}

Shader::~Shader() {
	glDeleteProgram(shaderProgram);
}

string Shader::getShaderInfoLog(GLuint& object) {
	int logLength = 0;
	glGetShaderiv(object, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		int charsWritten = 0;
		char* tmpLog = new char[logLength];
		glGetShaderInfoLog(object, logLength, &charsWritten, tmpLog);
		string log = tmpLog;
		delete[] tmpLog;
		return log;
	}
	return string();
}

string Shader::getProgramInfoLog(GLuint& object) {
	int logLength = 0;
	glGetProgramiv(object, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) {
		int charsWritten = 0;
		char *tmpLog = new char[logLength];
		glGetProgramInfoLog(object, logLength, &charsWritten, tmpLog);
		string log = tmpLog;
		delete[] tmpLog;
		return log;
	}
	return string();
}

GLuint Shader::getProgram() {
	return shaderProgram;
}

void Shader::resetTextureUnit() {
	nextTextureUnit = 0;
}

void Shader::enable() {
	resetTextureUnit();
	glUseProgram(shaderProgram);
}

void Shader::disable() {
	glUseProgram(NULL);
}

void Shader::bindUniformInt(const char* name, int i) {
	GLuint vectorLocation = glGetUniformLocation(shaderProgram, name);
	glUniform1i(vectorLocation, i);
}

void Shader::bindUniformFloat(const char* name, float f) {
	GLuint location = glGetUniformLocation(shaderProgram, name);
	glUniform1f(location, f);
}

void Shader::bindUniformFloat2(const char* name, float *f) {
	GLuint location = glGetUniformLocation(shaderProgram, name);
	glUniform2fv(location, 1, f);
}

void Shader::bindUniformFloat3(const char* name, float *f) {
	GLuint location = glGetUniformLocation(shaderProgram, name);
	glUniform3fv(location, 1, f);
}

void Shader::bindUniformFloat4(const char* name, float *f) {
	GLuint location = glGetUniformLocation(shaderProgram, name);
	glUniform4fv(location, 1, f);
}

void Shader::bindUniformMat3(const char* name, float* m) {
	GLuint location = glGetUniformLocation(shaderProgram, name);
	glUniformMatrix3fv(location, 1, false, m);
}

void Shader::bindUniformMat4(const char* name, float* m, GLsizei count) {
	GLuint location = glGetUniformLocation(shaderProgram, name);
	glUniformMatrix4fv(location, count, false, m);
}

void Shader::bindUniformTexture(const char* name, GLuint textureHandle) {
	GLuint location = glGetUniformLocation(shaderProgram, name);
	glActiveTexture(GL_TEXTURE0 + nextTextureUnit);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glUniform1i(location, nextTextureUnit);
	nextTextureUnit++;
}
