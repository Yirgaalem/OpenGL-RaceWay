/*
 -------------------------------------
 File:    crowd.hpp
 Project: SimpleView3
 file description
 -------------------------------------
 Author:  Brandon Parker
 ID:      191593730
 Email:   park3730@mylaurier.ca
 Version  2021-11-29
 -------------------------------------
 */
#ifndef SRC_CROWD_HPP_
#define SRC_CROWD_HPP_

#include <GL/glut.h>

#include "Cube.hpp"

class crowd: public Shape {
protected:
	Cube *cube1;
	Cube *cube2;
	Cube *cube3;
	Cube *cube4;

public:
	~crowd();
	crowd();
	void draw();
};

#endif /* SRC_CROWD_HPP_ */
