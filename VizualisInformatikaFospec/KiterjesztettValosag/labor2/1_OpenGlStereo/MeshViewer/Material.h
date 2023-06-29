#pragma once

#include "Vector3.h"

class Material
{
public:
	Material(void);
	~Material(void);

	void init();

	Vector3 surfaceColor;

	char* name;
	char* colorTexName;
	char* normalTexName;		
	
	unsigned int glColorTexID;
	unsigned int glNormalTexID;

	unsigned int width;
	unsigned int height;
};

