
/***********************************************************************************
	Created:	17:9:2002
	FileName: 	hdrloader.h
	Author:		Igor Kravtchenko
	
	Info:		Load HDR image and convert to a set of float32 RGB triplet.
************************************************************************************/

class HDRLoaderResult {
public:
	int width, height;
	// each pixel takes 3 float32, each component can be of any value...
	float *cols;
	unsigned char *rgba;

	HDRLoaderResult(){cols = 0; rgba = 0; width = 0; height = 0;}
};

class HDRLoader {
public:
	static bool load(const char *fileName, HDRLoaderResult &res, bool convert_to_float = false);
};

