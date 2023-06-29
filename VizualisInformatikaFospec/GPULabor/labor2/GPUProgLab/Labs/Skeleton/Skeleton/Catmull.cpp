#include "Catmull.hpp"

/*
 *
 * Copyright © 2010-2016 Balázs Tóth <tbalazs@iit.bme.hu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "quad.hpp"
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

void Catmull::calcCatmullPoints()
{
	int xxx = (controlPoints.size() / 3) - 2;
	points.clear();
	for (int idx = 1; idx < xxx; ++idx)
	{
		for (float t = 0.0f; t <= 1.0001f; t += 0.1f)
		{
			glm::vec4 r0((float)controlPoints[(idx - 1) * 3], (float)controlPoints[(idx - 1) * 3 + 1], (float)controlPoints[(idx - 1) * 3 + 2], 1.0f);
			glm::vec4 r1((float)controlPoints[(idx) * 3], (float)controlPoints[(idx) * 3 + 1], (float)controlPoints[(idx) * 3 + 2], 1.0f);
			glm::vec4 r2((float)controlPoints[(idx + 1) * 3], (float)controlPoints[(idx + 1) * 3 + 1], (float)controlPoints[(idx + 1) * 3 + 2], 1.0f);
			glm::vec4 r3((float)controlPoints[(idx + 2) * 3], (float)controlPoints[(idx + 2) * 3 + 1], (float)controlPoints[(idx + 2) * 3 + 2], 1.0f);
		
			glm::vec4 ts = glm::vec4( t * t * t, t * t, t, 1 );

			float s = 0.5;

			glm::mat4 S
			(
				-s, 2*s, -s, 0,
				2-s, s-3, 0, 1,
				s-2, 3-2*s, s, 0,
				s, -s, 0, 0
			);

			glm::vec4 weights = ts * S;
			glm::vec4 p = weights.x * r0 + weights.y * r1 + weights.z * r2 + weights.w * r3;

			points.push_back(p.x);
			points.push_back(p.y);
			points.push_back(p.z);
		}
	}
}

Catmull::Catmull()
{
	
}

Catmull::~Catmull()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteVertexArrays(1, &texCoordBuffer);
}

void Catmull::addPoint(GLfloat x, GLfloat y)
{
	controlPoints.push_back(x);
	controlPoints.push_back(y);
	controlPoints.push_back(0.0f);

	calcCatmullPoints();

	init();
}

void Catmull::init()
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	GLfloat* vertices = new GLfloat[points.size()];

	for (int idx = 0; idx < points.size(); ++idx)
		vertices[idx] = points[idx];


	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * points.size(), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	delete[] vertices;

	glBindVertexArray(0);
}

void Catmull::render() {
	glBindVertexArray(vertexArray);
	glDrawArrays(GL_LINE_STRIP, 0, points.size() / 3);
	glBindVertexArray(0);
}

void Catmull::render(int width, int height)
{
	int vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	glViewport(0, 0, width, height);
	glBindVertexArray(vertexArray);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	glViewport(vp[0], vp[1], vp[2], vp[3]);
}

