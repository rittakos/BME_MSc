#include "Scene.h"
#include "hdrloader.h"


Scene::Scene(void)
{
}


Scene::~Scene(void)
{
	clearScene();
}

void Scene::initGL()
{
	unsigned char whitePixel[] = {255,255,255};
	glGenTextures(1, &mDefaultColorTextureId);
	glBindTexture(GL_TEXTURE_2D, mDefaultColorTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, whitePixel);
	unsigned char nullBumpPixel[] = { 127,127,127 };
	glGenTextures(1, &mDefaultNormalTextureId);
	glBindTexture(GL_TEXTURE_2D, mDefaultNormalTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, nullBumpPixel);
}

void Scene::addMesh(Mesh* mesh)
{
	mMeshes.push_back(mesh);
}

void Scene::addMaterial(Material* material)
{
	mMaterials.push_back(material);
}

void Scene::clearScene()
{
	for(int i = 0; i < mMeshes.size(); ++i)
	{
		//delete mMeshes[i];
	}

	mMeshes.clear();
	mMaterials.clear();
}



void Scene::renderScene(Shader* shader)
{	
	for(int i = 0; i < mMeshes.size(); ++i)
	{
		Material* mat = &mDefaultMaterial;
		int matIdx = mMeshes[i]->getMaterialIndex();
		if(matIdx>=0)
			mat = mMaterials[matIdx];
		 
		shader->bindUniformFloat3("surfaceColor", &mat->surfaceColor.x);
		
		if(mat->colorTexName != 0)
			shader->bindUniformTexture("color_texture", mat->glColorTexID);
		else
			shader->bindUniformTexture("color_texture", mDefaultColorTextureId);
				
		if(mat->normalTexName != 0)
			shader->bindUniformTexture("normal_texture", mat->glNormalTexID);
		else
			shader->bindUniformTexture("normal_texture", mDefaultNormalTextureId);
					
		mMeshes[i]->render();		
	}
}
