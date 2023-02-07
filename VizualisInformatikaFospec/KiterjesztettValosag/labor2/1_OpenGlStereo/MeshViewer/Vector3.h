#pragma once
#include <math.h>

class Vector3
{
public:
	Vector3(float x = 0, float y = 0, float z = 0);

	Vector3 operator *(float v){return Vector3(v*x,v*y,v*z);}
	Vector3 operator /(float v){return Vector3(v/x,v/y,v/z);}
	Vector3 operator +(Vector3 v){return Vector3(v.x+x,v.y+y,v.z+z);}
	Vector3 operator -(Vector3 v){return Vector3(v.x-x,v.y-y,v.z-z);}

	float length(){return sqrt(x*x + y*y + z*z);}
	void normalize(){float l = length(); x /= l;y /= l;z /= l;}

	Vector3 cross(Vector3 v){return Vector3(y * v.z - z * v.y,
											z * v.x - x * v.z,
											x * v.y - y * v.x);}

	float x;
	float y;
	float z;
	
};

