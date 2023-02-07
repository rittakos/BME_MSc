#include "framebuffer.h"
#include "GLError.h"

bool useHalf = true;

Framebuffer::Framebuffer(GLuint width, GLuint height, bool isFloat, bool hasDepth, GLuint planes) {
	this->isFloat = isFloat;
	this->hasDepth = hasDepth;
	this->planes = planes;
	colorTextureHandles = new GLuint[planes];
    ownTexture = true;

    if(isFloat)
	{
        if(useHalf)
			TEXTURE_INTERNAL_TYPE = GL_RGBA16F;
		else
			TEXTURE_INTERNAL_TYPE = GL_RGBA32F;
		TEXTURE_TYPE = GL_FLOAT; //leave the conversion to OpenGL if needed
		TEXTURE_FILTERING = GL_LINEAR;
	}
	else
	{
		TEXTURE_INTERNAL_TYPE = GL_RGBA;
		TEXTURE_TYPE = GL_UNSIGNED_BYTE;
		TEXTURE_FILTERING = GL_LINEAR;
	}

	this->width = width;
	this->height = height;

	glGetError();
	glGenFramebuffers(1, &frameBufferHandle); 
	checkGLError("framebuffer framebuffer gen");
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle); 
    checkGLError("framebuffer framebuffer bind");
	for(int i = 0; i < planes; ++i)
	{
		glGenTextures(1, &colorTextureHandles[i]); 
		checkGLError("framebuffer texture gen");
		glBindTexture(GL_TEXTURE_2D, colorTextureHandles[i]); 
		checkGLError("framebuffer texture bind");
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TEXTURE_FILTERING); 
		checkGLError("framebuffer texture minfilter");
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TEXTURE_FILTERING); 
		checkGLError("framebuffer texture magfilter");
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		checkGLError("framebuffer texture wrap s");
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		checkGLError("framebuffer texture wrap t");
		glTexImage2D(GL_TEXTURE_2D, 0, TEXTURE_INTERNAL_TYPE, width, height, 0,
				GL_RGBA, TEXTURE_TYPE, 0);
		checkGLError("framebuffer teximage2d");
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+i, GL_TEXTURE_2D,
			colorTextureHandles[i], 0); 
		checkGLError("framebuffer framebuffertexture2d");
	}

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE){
        std::cerr << "Framebuffer: Incomplete framebuffer" << std::endl;
	}

	if (hasDepth) {
		glGenTextures(1, &depthBufferHandle);
		glBindTexture(GL_TEXTURE_2D, depthBufferHandle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depthBufferHandle, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	checkGLError("framebuffer framebuffer bind 0");	
}

Framebuffer::Framebuffer(GLuint width, GLuint height, bool isFloat, unsigned int handle)
{
    this->isFloat = isFloat;
	this->hasDepth = false;
	this->planes = 1;
	colorTextureHandles = new GLuint[planes];
    ownTexture = false;

    glBindTexture(GL_TEXTURE_2D, handle);
    int w, h;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);

    this->width = width;
    this->height = height;

    glGetError();
    glGenFramebuffers(1, &frameBufferHandle);
    checkGLError("framebuffer framebuffer gen");
    colorTextureHandles[0] = handle;
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);
    checkGLError("framebuffer framebuffer bind");
    glBindTexture(GL_TEXTURE_2D, colorTextureHandles[0]);
    checkGLError("framebuffer texture bind");
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    checkGLError("framebuffer texture minfilter");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    checkGLError("framebuffer texture magfilter");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    checkGLError("framebuffer texture wrap s");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    checkGLError("framebuffer texture wrap t");
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
            colorTextureHandles[0], 0);
    checkGLError("framebuffer framebuffertexture2d");

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE){
        std::cerr << "Framebuffer: Incomplete framebuffer" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    checkGLError("framebuffer framebuffer bind 0");
}

Framebuffer::~Framebuffer() {
glGetError();
	glDeleteFramebuffers(1, &frameBufferHandle);
    checkGLError("framebuffer framebuffer delete");
    if(ownTexture)
    {
        glDeleteTextures(1, &colorTextureHandles[0]);
        checkGLError("framebuffer texture delete");
    }

}

void Framebuffer::resize(GLuint w, GLuint h)
{
    width = w;
    height = h;

    //glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);
    for(int i = 0; i < planes; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, colorTextureHandles[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, TEXTURE_INTERNAL_TYPE, width, height, 0, GL_RGBA, TEXTURE_TYPE, 0);
       // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+i, GL_TEXTURE_2D, colorTextureHandles[i], 0);
    }

    if (hasDepth) {
        glBindTexture(GL_TEXTURE_2D, depthBufferHandle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
       // glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depthBufferHandle, 0);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Framebuffer::setRenderTarget(int plane)
{
	glGetError();
		
	if(plane == -1)//bind all rendertargets
	{
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);
		GLuint* buffers = new GLuint[planes];
		for(int i = 0; i < planes; ++i)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+i, GL_TEXTURE_2D, colorTextureHandles[i], 0);			
			buffers[i] = GL_COLOR_ATTACHMENT0+i; 
		}
		glDrawBuffers(planes, buffers);
		delete buffers;
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle); 
        checkGLError("framebuffer setrendertarget glBindFramebuffer");
		
		for(int i = 0; i < planes; ++i)
		{
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+i, GL_TEXTURE_2D, 0, 0);
            checkGLError("framebuffer setrendertarget glFramebufferTexture2D 0");
		}
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTextureHandles[plane], 0);
        checkGLError("framebuffer setrendertarget glFramebufferTexture2D");
		GLuint buffer = GL_COLOR_ATTACHMENT0;
		glDrawBuffers(1, &buffer);
        checkGLError("framebuffer setrendertarget glDrawBuffers");
	}
	glViewport(0, 0, width, height);
	checkGLError("framebuffer setrendertarget");
}

void Framebuffer::disableRenderTarget() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::setData(unsigned char* data, int channels, GLuint plane) {
    glGetError();
	glBindTexture(GL_TEXTURE_2D, colorTextureHandles[plane]);
	checkGLError("framebuffer setData bindtexture");

	if(channels == 1){

		unsigned char* tempdata = 0;
		if(data != 0)
		{
			tempdata = new unsigned char[width * height * 4];
			for (int i = 0; i < width * height; ++i) {
				unsigned char v = data[i];
				tempdata[i * 4] = v;
				tempdata[i * 4 + 1] = v;
				tempdata[i * 4 + 2] = v;
				tempdata[i * 4 + 3] = 0;
			}
		}
        glTexImage2D(GL_TEXTURE_2D, 0, TEXTURE_INTERNAL_TYPE, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempdata);
        if(tempdata)
            delete[] tempdata;
// this should work in desktop openGL, but for some resolutions (eg. 338x226) it ruined the image
//		glTexImage2D(GL_TEXTURE_2D, 0, TEXTURE_INTERNAL_TYPE, width, height, 0,
//				GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
	}
	else if(channels == 2){
        glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,width, height,GL_RG, GL_UNSIGNED_BYTE, data);        
	}
	else if(channels == 3){
        glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,width, height,GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else if(channels == 4){
        glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,width, height,GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	
	checkGLError("framebuffer setData uchar");
}

void Framebuffer::setData(float* data, int channels, GLuint plane) {
	if(!isFloat)
	{//convert to unsigned char array and call the uchar version (this is not the fastest solution ... but this situation is not common)
		unsigned char* ucharData = new unsigned char[width * height * channels];
		for(unsigned int i = 0; i < width * height * channels; ++i)
		{
			ucharData[i] = data[i] * 255.0;
		}
		setData(ucharData, channels);
		delete ucharData;
		return;
	}
glGetError();
	glBindTexture(GL_TEXTURE_2D, colorTextureHandles[plane]);
	checkGLError("framebuffer setData bindtexture");
	if (channels == 1) {
		float* tempdata = 0;
		if(data != 0)
		{
			tempdata = new float[width * height * 4];
			for (int i = 0; i < width * height; ++i) {
				float v = data[i];
				tempdata[i * 4] = v;
				tempdata[i * 4 + 1] = v;
				tempdata[i * 4 + 2] = v;
				tempdata[i * 4 + 3] = 0;
			}
		}
        glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,width, height, GL_RGBA, GL_FLOAT, tempdata);
		delete tempdata;
	}
	else if (channels == 2)
    {
        glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,width, height, GL_RG, GL_FLOAT, data);        
	}
	else if (channels == 3)
	{
        glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,width, height, GL_RGB, GL_FLOAT, data);        
	}
	else if (channels == 4)
	{
        glTexSubImage2D(GL_TEXTURE_2D, 0,0,0,width, height, GL_RGBA, GL_FLOAT, data);
    }
	
	checkGLError("framebuffer setData float");
}

void Framebuffer::getData_R8G8B8(unsigned char* data, GLuint plane)
{
    setRenderTarget(plane);
    glReadPixels(0,0,width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    disableRenderTarget();
}

void Framebuffer::getData_RGBA_32F(float* data, GLuint plane)
{
    setRenderTarget(plane);
    checkGLError("framebuffer getData_RGBA_32F readpixel start");
    glReadPixels(0,0,width, height, GL_RGBA, GL_FLOAT, data);
    checkGLError("framebuffer getData_RGBA_32F readpixel end");
    disableRenderTarget();
}

void Framebuffer::clear(float r, float g, float b, float a, GLuint plane){
	setRenderTarget(plane);
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	disableRenderTarget();
}

void Framebuffer::setBorderColor(float r, float g, float b, float a, GLuint plane)
{
    glBindTexture(GL_TEXTURE_2D, colorTextureHandles[plane]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    checkGLError("framebuffer texture wrap s");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    checkGLError("framebuffer texture wrap t");

    float color[] = { r, g, b, a};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
}

void Framebuffer::setBorderColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a, GLuint plane)
{
    setBorderColor((float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f, plane);
}


