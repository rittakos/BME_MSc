#include "Material.h"
#include <GL/glew.h>
#include <FreeImage.h>


Material::Material(void): 
		  surfaceColor(1,1,1)
		, colorTexName(0)		
		, normalTexName(0)
		, name("default")
		, glColorTexID(0)
		, glNormalTexID(0)
		,width(0)
		,height(0)
{
}


Material::~Material(void)
{
}

void Material::init()
{
	if(colorTexName)
	{
		FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(colorTexName, 0);
		if (formato == FIF_UNKNOWN) { /* go angry here */ }
		FIBITMAP* imagen = FreeImage_Load(formato, colorTexName);
		if (!imagen) { /* go very angry here */ }
		FIBITMAP* temp = FreeImage_ConvertTo32Bits(imagen);
		if (!imagen) { /* go mad here */ }
		width = FreeImage_GetWidth(imagen);
		height = FreeImage_GetHeight(imagen);

		char* pixels = (char*)FreeImage_GetBits(imagen);
		/*GLubyte* finalPixels = new GLubyte[4 * width*height];
		
		for (int j = 0; j<width*height; j++)
		{
			finalPixels[j * 4 + 0] = pixels[j * 4 + 2];
			finalPixels[j * 4 + 1] = pixels[j * 4 + 1];
			finalPixels[j * 4 + 2] = pixels[j * 4 + 0];
			finalPixels[j * 4 + 3] = pixels[j * 4 + 3];
		}*/

		glGenTextures(1, &glColorTexID);
		glBindTexture(GL_TEXTURE_2D, glColorTexID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, (GLvoid*)pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//delete finalPixels;
		FreeImage_Unload(imagen);

	}

	if (normalTexName)
	{
		FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(normalTexName, 0);
		if (formato == FIF_UNKNOWN) { /* go angry here */ }
		FIBITMAP* imagen = FreeImage_Load(formato, normalTexName);
		if (!imagen) { /* go very angry here */ }
		FIBITMAP* temp = FreeImage_ConvertTo32Bits(imagen);
		if (!imagen) { /* go mad here */ }
		width = FreeImage_GetWidth(imagen);
		height = FreeImage_GetHeight(imagen);

		char* pixels = (char*)FreeImage_GetBits(imagen);
		/*GLubyte* finalPixels = new GLubyte[4 * width*height];

		for (int j = 0; j<width*height; j++)
		{
		finalPixels[j * 4 + 0] = pixels[j * 4 + 2];
		finalPixels[j * 4 + 1] = pixels[j * 4 + 1];
		finalPixels[j * 4 + 2] = pixels[j * 4 + 0];
		finalPixels[j * 4 + 3] = pixels[j * 4 + 3];
		}*/

		glGenTextures(1, &glNormalTexID);
		glBindTexture(GL_TEXTURE_2D, glNormalTexID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, (GLvoid*)pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//delete finalPixels;
		FreeImage_Unload(imagen);

	}
}
