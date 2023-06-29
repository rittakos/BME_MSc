#ifndef _FRAMEBUFFER_
#define _FRAMEBUFFER_

#include <GL/glew.h>

class  Framebuffer
{
private:
  GLuint frameBufferHandle;
  GLuint* colorTextureHandles;
  GLuint planes;
  GLuint depthBufferHandle;
  GLuint width, height;
  bool isFloat;
  bool hasDepth;
  bool ownTexture;

  GLuint TEXTURE_INTERNAL_TYPE;
  GLuint TEXTURE_TYPE;
  GLuint TEXTURE_FILTERING;

public:
  Framebuffer(GLuint width, GLuint height, bool isFloat = true, bool hasDepth = false, GLuint planes = 1);
  Framebuffer(GLuint width, GLuint height, bool isFloat, unsigned int handle);
  ~Framebuffer();

  void resize(GLuint w, GLuint h);

  int getWidth(){ return width; }
  int getHeight(){ return height; }
  bool isFloatFormat(){return isFloat;}

  void setRenderTarget(int plane = -1);
  void disableRenderTarget();
  void clear(float r=0, float g=0, float b=0, float a=0, GLuint plane = 0);

  virtual void setData(unsigned char* data, int channels, GLuint plane = 0);
  virtual void setData(float* data, int channels, GLuint plane = 0);
  virtual GLuint getTextureHandle(GLuint plane = 0)
  {
	  return colorTextureHandles[plane];
  }

  virtual void getData_R8G8B8(unsigned char* data, GLuint plane = 0);
  virtual void getData_RGBA_32F(float* data, GLuint plane = 0);

  virtual void setBorderColor(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, GLuint plane = 0);
  virtual void setBorderColor(float r = 0, float g = 0, float b = 0, float a = 1, GLuint plane = 0);

};

#endif

