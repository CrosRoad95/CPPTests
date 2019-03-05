#include "StdInc.h"

CTriangle::CTriangle(Vertex2DUVColor* vertex1, Vertex2DUVColor* vertex2, Vertex2DUVColor* vertex3, SString textureName) {
	vertex[0] = vertex1;
	vertex[1] = vertex2;
	vertex[2] = vertex3;
};

CTriangle::~CTriangle() {
};

CTriangle::DoPulse() {
};

void CTriangle::Draw() {
	/*
	glBegin(GL_TRIANGLES);
	if (texture)
	{
		texture->Select();
	}
	for (int i = 0; i < 3; i++)
	{
		if (vertex[i]->color)
		{
			glColor4ub(vertex[i]->color->r, vertex[i]->color->g, vertex[i]->color->b, vertex[i]->color->a);
		}
		glTexCoord2f(vertex[i]->u, vertex[i]->v);
		glVertex2f(vertex[i]->x, vertex[i]->y);
	}
	glEnd();*/
};