/*
 -------------------------------------
 File:    car.cpp
 Project: SimpleView3
 file description
 -------------------------------------
 Author:  Brandon Parker
 ID:      191593730
 Email:   park3730@mylaurier.ca
 Version  2021-11-29
 -------------------------------------
 */

#include "car.hpp"
#include <stdio.h>

car::car() {

	cube1 = new Cube();
	cube1->setParentMC(&mc);
	cube2 = new Cube();
	cube2->setParentMC(&mc);
	cube2->translate(0.3, 0, 0.5);

	cube1->cubetype = CAR;
	cube2->cubetype = CAR;

	cube1->texture = false;
	cube2->texture = false;

	cube1->vertex[0][0] = -3;
	cube1->vertex[0][1] = -1;
	cube1->vertex[0][2] = -1;
	cube1->vertex[1][0] = -3;
	cube1->vertex[1][1] = 1;
	cube1->vertex[1][2] = -1;
	cube1->vertex[2][0] = 2.5;
	cube1->vertex[2][1] = 1;
	cube1->vertex[2][2] = -1;
	cube1->vertex[3][0] = 2.5;
	cube1->vertex[3][1] = -1;
	cube1->vertex[3][2] = -1;
	cube1->vertex[4][0] = -2.8;
	cube1->vertex[4][1] = -1;
	cube1->vertex[4][2] = 0;
	cube1->vertex[5][0] = -2.8;
	cube1->vertex[5][1] = 1;
	cube1->vertex[5][2] = 0;
	cube1->vertex[6][0] = 2.5;
	cube1->vertex[6][1] = 1;
	cube1->vertex[6][2] = 0;
	cube1->vertex[7][0] = 2.5;
	cube1->vertex[7][1] = -1;
	cube1->vertex[7][2] = 0;

	cube2->vertex[0][0] = -1.5;
	cube2->vertex[0][1] = -0.9;
	cube2->vertex[0][2] = -1;
	cube2->vertex[1][0] = -1.5;
	cube2->vertex[1][1] = 0.9;
	cube2->vertex[1][2] = -0.9;
	cube2->vertex[2][0] = 1.5;
	cube2->vertex[2][1] = 0.9;
	cube2->vertex[2][2] = -1;
	cube2->vertex[3][0] = 1.5;
	cube2->vertex[3][1] = -0.9;
	cube2->vertex[3][2] = -1;
	cube2->vertex[4][0] = -0.7;
	cube2->vertex[4][1] = -0.9;
	cube2->vertex[4][2] = 0;
	cube2->vertex[5][0] = -0.7;
	cube2->vertex[5][1] = 0.9;
	cube2->vertex[5][2] = 0;
	cube2->vertex[6][0] = 0.7;
	cube2->vertex[6][1] = 0.9;
	cube2->vertex[6][2] = 0;
	cube2->vertex[7][0] = 0.7;
	cube2->vertex[7][1] = -0.9;
	cube2->vertex[7][2] = 0;

	cube1->faceColor[0][0] = 0.04, cube1->faceColor[0][1] = 0.04;
	cube1->faceColor[0][2] = 0.5; //bottom
	cube1->faceColor[1][0] = 0.04, cube1->faceColor[1][1] = 0.04;
	cube1->faceColor[1][2] = 0.7; //top
	cube1->faceColor[2][0] = 0.04, cube1->faceColor[2][1] = 0.04;
	cube1->faceColor[2][2] = 0.5; // front
	cube1->faceColor[3][0] = 0.04, cube1->faceColor[3][1] = 0.04;
	cube1->faceColor[3][2] = 0.3;
	cube1->faceColor[4][0] = 0.04, cube1->faceColor[4][1] = 0.04;
	cube1->faceColor[4][2] = 0.5; //back
	cube1->faceColor[5][0] = 0.04, cube1->faceColor[5][1] = 0.04;
	cube1->faceColor[5][2] = 0.3;

	cube2->faceColor[0][0] = 0.04, cube2->faceColor[0][1] = 0.04;
	cube2->faceColor[0][2] = 0.5;
	cube2->faceColor[1][0] = 0.04, cube2->faceColor[1][1] = 0.04;
	cube2->faceColor[1][2] = 0.5;
	cube2->faceColor[2][0] = 0.5, cube2->faceColor[2][1] = 0.5;
	cube2->faceColor[2][2] = 0.5;
	cube2->faceColor[3][0] = 0.5, cube2->faceColor[3][1] = 0.5;
	cube2->faceColor[3][2] = 0.5;
	cube2->faceColor[4][0] = 0.5, cube2->faceColor[4][1] = 0.5;
	cube2->faceColor[4][2] = 0.5;
	cube2->faceColor[5][0] = 0.5, cube2->faceColor[5][1] = 0.5;
	cube2->faceColor[5][2] = 0.5;

}

car::~car() {
	delete cube1;
	delete cube2;
}

void car::draw() {
	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	cube1->draw();
	glPopMatrix();

	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	cube2->draw();
	glPopMatrix();
}

