#include "StdInc.h"

CRectangle::CRectangle(Vertex2D* position, uint width, uint heigth, ColorRGBA* color) {
	vPosition = position;
	uiWidth = width;
	uiHeigth = heigth;
	cColor = color;
};

CRectangle::~CRectangle() {
};

void CRectangle::Draw() {
	glBegin(GL_QUADS);
	glColor4ub(cColor->r, cColor->g, cColor->b, cColor->a);
	glVertex2i(vPosition->x, vPosition->y);
	glVertex2i(vPosition->x + uiWidth, vPosition->y);
	glVertex2i(vPosition->x + uiWidth, vPosition->y + uiHeigth);
	glVertex2i(vPosition->x, vPosition->y + uiHeigth);
	glEnd();
};