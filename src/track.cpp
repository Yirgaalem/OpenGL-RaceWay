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

#include "track.hpp"
#include <stdio.h>

track::track() {
	cube1 = new Cube();
	cube1->setParentMC(&mc);
	cube1->cubetype = TRACK;

	cube1->vertex[0][0] = -10;
	cube1->vertex[0][1] = -20;
	cube1->vertex[0][2] = -1;
	cube1->vertex[1][0] = -10;
	cube1->vertex[1][1] = 20;
	cube1->vertex[1][2] = -1;
	cube1->vertex[2][0] = 10;
	cube1->vertex[2][1] = 20;
	cube1->vertex[2][2] = -1;
	cube1->vertex[3][0] = 10;
	cube1->vertex[3][1] = -20;
	cube1->vertex[3][2] = -1;
	cube1->vertex[4][0] = -10;
	cube1->vertex[4][1] = -20;
	cube1->vertex[4][2] = 0;
	cube1->vertex[5][0] = -10;
	cube1->vertex[5][1] = 20;
	cube1->vertex[5][2] = 0;
	cube1->vertex[6][0] = 10;
	cube1->vertex[6][1] = 20;
	cube1->vertex[6][2] = 0;
	cube1->vertex[7][0] = 10;
	cube1->vertex[7][1] = -20;
	cube1->vertex[7][2] = 0;

	cube1->texture = true;

}

track::~track() {
	delete cube1;
}

void track::draw() {
	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	cube1->draw();
	glPopMatrix();

}
