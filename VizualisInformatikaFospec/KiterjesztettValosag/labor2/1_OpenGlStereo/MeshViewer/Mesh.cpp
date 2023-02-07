#include "Mesh.h"


Mesh::Mesh(void) : vertexBuffer(0), indexBuffer(0), normalBuffer(0), texcoordBuffer(0), materialIndex(-1)
{
}


Mesh::~Mesh(void)
{
	clear();
}

void Mesh::setData(float* vertices, unsigned short* indices, unsigned int numVertices, unsigned int numTriangles, float* normals, float* uvs)
{
	clear();
	this->vertices.reserve(numVertices);
	for(int i = 0; i < numVertices; ++i)
	{
		this->vertices.push_back(Vector3(vertices[i*3], vertices[i*3 + 1], vertices[i*3 + 2]));
	}
	this->normals.reserve(numVertices);
	
	for(int i = 0; i < numVertices; ++i)
	{
		if(normals)
			this->normals.push_back(Vector3(normals[i*3], normals[i*3 + 1], normals[i*3 + 2]));
		else
			this->normals.push_back(Vector3(0,0,0));
		this->tangents.push_back(Vector3(0,0,0));
	}

	this->texcoords.reserve(numVertices * 2);
	for(int i = 0; i < numVertices; ++i)
	{
		if(uvs)
		{
			this->texcoords.push_back(uvs[2*i]);
			this->texcoords.push_back(uvs[2*i + 1]);
		}
		else
		{
			this->texcoords.push_back(0);
			this->texcoords.push_back(0);
		}
	}

	bool calculateTangents = true;
	this->indices.reserve(numTriangles * 3);
	for(int i = 0; i < numTriangles; ++i)
	{
		unsigned short idx1 = indices[i*3];
		unsigned short idx2 = indices[i*3 + 1];
		unsigned short idx3 = indices[i*3 + 2];
		this->indices.push_back(idx1);
		this->indices.push_back(idx2);
		this->indices.push_back(idx3);

		if(!normals || calculateTangents)
		{
			//calculate smooth normals
			Vector3 e1 = this->vertices[idx2] - this->vertices[idx1];
			Vector3 e2 = this->vertices[idx3] - this->vertices[idx1];
			
			if(calculateTangents)
			{
				float v2_v1 = this->texcoords[idx2*2+1] - this->texcoords[idx1*2+1];
				float v3_v1 = this->texcoords[idx3*2+1] - this->texcoords[idx1*2+1];
				float u2_u1 = this->texcoords[idx2*2] - this->texcoords[idx1*2];
				float u3_u1 = this->texcoords[idx3*2] - this->texcoords[idx1*2];
				if(v2_v1*v3_v1*u2_u1*u3_u1 != 0)
				{
					Vector3 T = (e2 * v2_v1 - e1 * v3_v1) * (1.0 / (u3_u1 * v2_v1 - u2_u1 * v3_v1));
					T.normalize();

					this->tangents[idx1] = this->tangents[idx1] + T;
					this->tangents[idx2] = this->tangents[idx2] + T;
					this->tangents[idx3] = this->tangents[idx3] + T;
				}
			}

			if(!normals)
			{
				e1.normalize();
				e2.normalize();
			
				Vector3 N = e1.cross(e2);
				N.normalize();		
		
				this->normals[idx1] = this->normals[idx1] + N;
				this->normals[idx2] = this->normals[idx2] + N;
				this->normals[idx3] = this->normals[idx3] + N;
			}
		}
	}
	
	if(!normals || calculateTangents)
	{
		for(int i = 0; i < numVertices; ++i)
		{
			if(!normals)
				this->normals[i].normalize();
			if(calculateTangents)
				this->tangents[i].normalize();
		}
	}

	glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 3, &this->vertices[0], GL_STATIC_DRAW); 

	glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 3, &this->normals[0], GL_STATIC_DRAW); 

	glGenBuffers(1, &texcoordBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, texcoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 2, &this->texcoords[0], GL_STATIC_DRAW);

	glGenBuffers(1, &tangentBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 3, &this->tangents[0], GL_STATIC_DRAW);

	glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * numTriangles * 3, &this->indices[0], GL_STATIC_DRAW); 
}

struct IndexDistance
{
	unsigned int index;
	float distance;
};

void Mesh::renderWithSorting(Vector3 cameraPos)
{

}

void Mesh::render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); 
	glVertexAttribPointer(0,3, GL_FLOAT, false, sizeof(float) * 3, 0);

	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer); 
	glVertexAttribPointer(1,3,GL_FLOAT, false, sizeof(float) * 3, 0);

	glBindBuffer(GL_ARRAY_BUFFER, texcoordBuffer); 
	glVertexAttribPointer(2,2,GL_FLOAT, false, sizeof(float) * 2, 0);

	glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer); 
	glVertexAttribPointer(3,3,GL_FLOAT, false, sizeof(float) * 3, 0);
   
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void Mesh::clear()
{
	if(vertexBuffer != 0)
	{
		glDeleteBuffers(1, &vertexBuffer);
	}
	if(indexBuffer != 0)
	{
		glDeleteBuffers(1, &indexBuffer);
	}
	if(normalBuffer != 0)
	{
		glDeleteBuffers(1, &normalBuffer);
	}
	if(texcoordBuffer != 0)
	{
		glDeleteBuffers(1, &texcoordBuffer);
	}
	vertices.clear();
	indices.clear();
	normals.clear();
	texcoords.clear();
}


