/*
 -------------------------------------
 File:    crowd.cpp
 Project: SimpleView3
 file description
 -------------------------------------
 Author:  Brandon Parker
 ID:      191593730
 Email:   park3730@mylaurier.ca
 Version  2021-11-29
 -------------------------------------
 */

#include "crowd.hpp"
#include <stdio.h>

crowd::crowd() {
	cube1 = new Cube();
	cube1->setParentMC(&mc);
	cube2 = new Cube();
	cube2->setParentMC(&mc);
	cube3 = new Cube();
	cube3->setParentMC(&mc);
	cube4 = new Cube();
	cube4->setParentMC(&mc);

	cube1->cubetype = CROWD;
	cube2->cubetype = CROWD;
	cube3->cubetype = CROWD;
	cube4->cubetype = CROWD;

	cube1->texture = true;
	cube2->texture = true;
	cube3->texture = true;
	cube4->texture = true;

	cube1->vertex[0][0] = -8;
	cube1->vertex[0][1] = -20;
	cube1->vertex[0][2] = -1;
	cube1->vertex[1][0] = -8;
	cube1->vertex[1][1] = 20;
	cube1->vertex[1][2] = -1;
	cube1->vertex[2][0] = 5;
	cube1->vertex[2][1] = 20;
	cube1->vertex[2][2] = -1;
	cube1->vertex[3][0] = 5;
	cube1->vertex[3][1] = -20;
	cube1->vertex[3][2] = -1;
	cube1->vertex[4][0] = -8;
	cube1->vertex[4][1] = -20;
	cube1->vertex[4][2] = 0;
	cube1->vertex[5][0] = -8;
	cube1->vertex[5][1] = 20;
	cube1->vertex[5][2] = 0;
	cube1->vertex[6][0] = 5;
	cube1->vertex[6][1] = 20;
	cube1->vertex[6][2] = 0;
	cube1->vertex[7][0] = 5;
	cube1->vertex[7][1] = -20;
	cube1->vertex[7][2] = 0;

	cube2->vertex[0][0] = -8;
	cube2->vertex[0][1] = -20;
	cube2->vertex[0][2] = -1;
	cube2->vertex[1][0] = -8;
	cube2->vertex[1][1] = 20;
	cube2->vertex[1][2] = -1;
	cube2->vertex[2][0] = 5;
	cube2->vertex[2][1] = 20;
	cube2->vertex[2][2] = -1;
	cube2->vertex[3][0] = 5;
	cube2->vertex[3][1] = -20;
	cube2->vertex[3][2] = -1;
	cube2->vertex[4][0] = -8;
	cube2->vertex[4][1] = -20;
	cube2->vertex[4][2] = 0;
	cube2->vertex[5][0] = -8;
	cube2->vertex[5][1] = 20;
	cube2->vertex[5][2] = 0;
	cube2->vertex[6][0] = 5;
	cube2->vertex[6][1] = 20;
	cube2->vertex[6][2] = 0;
	cube2->vertex[7][0] = 5;
	cube2->vertex[7][1] = -20;
	cube2->vertex[7][2] = 0;

	cube3->vertex[0][0] = -8;
	cube3->vertex[0][1] = -10;
	cube3->vertex[0][2] = -1;
	cube3->vertex[1][0] = -8;
	cube3->vertex[1][1] = 10;
	cube3->vertex[1][2] = -1;
	cube3->vertex[2][0] = 5;
	cube3->vertex[2][1] = 10;
	cube3->vertex[2][2] = -1;
	cube3->vertex[3][0] = 5;
	cube3->vertex[3][1] = -10;
	cube3->vertex[3][2] = -1;
	cube3->vertex[4][0] = -8;
	cube3->vertex[4][1] = -10;
	cube3->vertex[4][2] = 0;
	cube3->vertex[5][0] = -8;
	cube3->vertex[5][1] = 10;
	cube3->vertex[5][2] = 0;
	cube3->vertex[6][0] = 5;
	cube3->vertex[6][1] = 10;
	cube3->vertex[6][2] = 0;
	cube3->vertex[7][0] = 5;
	cube3->vertex[7][1] = -10;
	cube3->vertex[7][2] = 0;

	cube4->vertex[0][0] = -8;
	cube4->vertex[0][1] = -10;
	cube4->vertex[0][2] = -1;
	cube4->vertex[1][0] = -8;
	cube4->vertex[1][1] = 10;
	cube4->vertex[1][2] = -1;
	cube4->vertex[2][0] = 5;
	cube4->vertex[2][1] = 10;
	cube4->vertex[2][2] = -1;
	cube4->vertex[3][0] = 5;
	cube4->vertex[3][1] = -10;
	cube4->vertex[3][2] = -1;
	cube4->vertex[4][0] = -8;
	cube4->vertex[4][1] = -10;
	cube4->vertex[4][2] = 0;
	cube4->vertex[5][0] = -8;
	cube4->vertex[5][1] = 10;
	cube4->vertex[5][2] = 0;
	cube4->vertex[6][0] = 5;
	cube4->vertex[6][1] = 10;
	cube4->vertex[6][2] = 0;
	cube4->vertex[7][0] = 5;
	cube4->vertex[7][1] = -10;
	cube4->vertex[7][2] = 0;

	cube1->rotate(90, YAXIS); //right wall
	cube1->translate(-10, 0, 5);

	cube2->rotate(90, YAXIS); //left wall
	cube2->rotate(180, XAXIS);
	cube2->translate(10, 0, 5);

	cube3->rotate(90, YAXIS);
	cube3->rotate(90, XAXIS);
	cube3->translate(0, 20, 5);

	cube4->rotate(90, YAXIS);
	cube4->rotate(-90, XAXIS);
	cube4->translate(0, -20, 5);

}

crowd::~crowd() {
	delete cube1;
	delete cube2;
	delete cube3;
	delete cube4;
}

void crowd::draw() {

//	pix[6].setTexture(1);
//	pix[1].setTexture(6);

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

	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	cube3->draw();
	glPopMatrix();

	glPushMatrix();
	this->ctmMultiply();
	glScalef(s, s, s);
	cube4->draw();
	glPopMatrix();

//	pix[1].setTexture(1);
//	pix[6].setTexture(6);
}
