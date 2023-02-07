#include "AssimpSceneImporter.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Material.h"


void AssimpSceneImporter::loadMeshToScene(char* filename, Scene* scene)
{
	const aiScene* ai_scene;
	ai_scene = aiImportFile(filename, aiProcessPreset_TargetRealtime_MaxQuality);
	if (ai_scene) {

		for(int i = 0; i < ai_scene->mNumMeshes; ++i)
		{
			aiMesh* ai_mesh = ai_scene->mMeshes[i];
			Mesh *mesh = new Mesh();
			unsigned short* indices = 0;
			float* vpos = 0;
			float* vnormal = 0;
			float* vtex = 0;

			indices = new unsigned short[ai_mesh->mNumFaces * 3];
			for (unsigned int f = 0; f < ai_mesh->mNumFaces; f++) {
				for (unsigned int i = 0; i < 3; i++) {
					indices[f*3+i] = (GLushort)ai_mesh->mFaces[f].mIndices[i];
				}
			}
			vpos = &(ai_mesh->mVertices[0][0]);
			if( ai_mesh->mNormals)
				vnormal = &ai_mesh->mNormals[0][0];
			if( ai_mesh->mTextureCoords[0])
			{
				vtex = new float[ai_mesh->mNumVertices * 2];
				for(int v = 0; v < ai_mesh->mNumVertices; ++v)
				{
				
					vtex[v*2] = ai_mesh->mTextureCoords[0][v][0];
					vtex[v*2+1] = ai_mesh->mTextureCoords[0][v][1];
				}				
			}

			mesh->setData(vpos, indices, ai_mesh->mNumVertices, ai_mesh->mNumFaces, vnormal, vtex);
			mesh->setMaterialIndex(ai_mesh->mMaterialIndex);

			if( ai_mesh->mTextureCoords[0])
				delete vtex;
			scene->addMesh(mesh);
		}

		for(int i = 0; i < ai_scene->mNumMaterials; ++i)
		{
			Material* material = new Material();
			aiMaterial* ai_mat = ai_scene->mMaterials[i];
			unsigned int matnp = ai_mat->mNumProperties;
			aiReturn ret;

			aiString matName;
			ret = ai_mat->Get(AI_MATKEY_NAME, matName);
			if(ret == AI_SUCCESS)
			{
				material->name = new char[strlen(matName.C_Str())+1];
				strcpy(material->name,matName.C_Str());
			}
			
			aiColor3D color;
			ret = ai_mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
			if(ret == AI_SUCCESS)
				material->surfaceColor = Vector3(color.r,color.g,color.b);
			
			aiMaterialProperty** mps = ai_mat->mProperties;
			//unsigned int mtc = mat->GetTextureCount();
			
			char* pathName = new char[strlen(filename)+1];
			strcpy(pathName, filename);
			char* end = strrchr(pathName,'/');
			if(end != 0)
			{
				end++;
				*end = '\0';
			}
			else
				pathName = 0;
			
			aiString texturePath;
			if(ai_mat->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath, NULL, NULL, NULL, NULL, NULL)  == AI_SUCCESS)
			{
				
				if(pathName != 0)
				{
					material->colorTexName = new char[strlen(pathName) + strlen(texturePath.C_Str())+1];
					strcpy(material->colorTexName,pathName);
					strcat(material->colorTexName,texturePath.C_Str());
				}
				else
				{
					material->colorTexName = new char[strlen(texturePath.C_Str())+1];
					strcpy(material->colorTexName,texturePath.C_Str());
				}

				material->surfaceColor = Vector3(1,1,1);
			}	

			if(ai_mat->GetTexture(aiTextureType_AMBIENT, 0, &texturePath, NULL, NULL, NULL, NULL, NULL)  == AI_SUCCESS)
			{
				if(pathName != 0)
				{
					material->normalTexName = new char[strlen(pathName) + strlen(texturePath.C_Str())+1];
					strcpy(material->normalTexName,pathName);
					strcat(material->normalTexName,texturePath.C_Str());
				}
				else
				{
					material->normalTexName = new char[strlen(texturePath.C_Str())+1];
					strcpy(material->normalTexName,texturePath.C_Str());
				}
			}
						
			material->init();
			scene->addMaterial(material);
		}


		aiReleaseImport(ai_scene);
	}
	else
	{
		printf("Failed to load scene file: %s, error:\n %s\n", filename, aiGetErrorString());
	}
}
