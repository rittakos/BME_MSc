#pragma once
#include "Scene.h"
class AssimpSceneImporter
{
public:
	static void loadMeshToScene(char* filename, Scene* scene);
};

