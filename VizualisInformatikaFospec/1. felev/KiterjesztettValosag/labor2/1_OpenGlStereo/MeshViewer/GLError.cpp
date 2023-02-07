#include "GL/glew.h"
#include "GLError.h"


struct token_string
{
   GLuint Token;
   const char* String;
};

static const struct token_string Errors[]=
{
   /* GL */
   {GL_NO_ERROR, "no error"},
   {GL_INVALID_ENUM, "invalid enumerant"},
   {GL_INVALID_VALUE, "invalid value"},
   {GL_INVALID_OPERATION, "invalid operation"},
   {GL_OUT_OF_MEMORY, "out of memory"} ,
   {GL_INVALID_FRAMEBUFFER_OPERATION, "invalid framebuffer operation" }
};

void checkGLError(const char* message)
{
	GLuint error = glGetError();
	
	if(error != GL_NO_ERROR)
        std::cerr << "GLError occured!! " << gluErrorString(error) << " " << message << std::endl;
}
