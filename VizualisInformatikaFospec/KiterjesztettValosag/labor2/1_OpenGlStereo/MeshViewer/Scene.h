#pragma once
#include "Mesh.h"
#include <glm/glm.hpp>
#include "Material.h"
#include "Shader.h"

class Scene
{
public:
	Scene(void);
	~Scene(void);

	void addMesh(Mesh* mesh);
	void addMaterial(Material* material);
	void clearScene();
	void renderScene(Shader* shader);
	
	void initGL();

	Material& getDefaultMaterial(){return mDefaultMaterial;}
	std::vector<Material*> mMaterials;	
protected:
	std::vector<Mesh*> mMeshes;		
	
	Material mDefaultMaterial;
	GLuint mDefaultColorTextureId;
	GLuint mDefaultNormalTextureId;
	
};

