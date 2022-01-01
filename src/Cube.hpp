/*
 *  Author: Brandon Parker
 *  Version: 2021-11-18
 */
#ifndef CCUBE_H
#define CCUBE_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"

#include "Camera.hpp"
#include "Light.hpp"

enum cubeType {
	NORMAL = 0, CAR, TRACK, CROWD
};

enum axisType {
	XAXIS = 1, YAXIS, ZAXIS
};

class Cube: public Shape {

protected:
//	GLfloat vertex[8][3];
	GLint face[6][4];
	GLfloat faceNormal[6][3];

	GLfloat vertexColor[8][3];
	GLfloat vertexNormal[8][3];
	GLfloat r, g, b;

public:

	GLfloat vertex[8][3];
	GLfloat faceColor[6][3];
	bool texture;
	cubeType cubetype;

	Cube();
	void draw();
	void drawFace(int);

	bool isFrontface(int faceindex, Camera camera);
	GLfloat getFaceShade(int faceindex, Light light);
	GLfloat getVertexShade(int vertexindex, Light light);

};

#endif
