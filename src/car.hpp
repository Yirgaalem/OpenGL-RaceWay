/*
 -------------------------------------
 File:    car.hpp
 Project: SimpleView3
 file description
 -------------------------------------
 Author:  Brandon Parker
 ID:      191593730
 Email:   park3730@mylaurier.ca
 Version  2021-11-29
 -------------------------------------
 */
#ifndef SRC_CAR_HPP_
#define SRC_CAR_HPP_

#include <GL/glut.h>

#include "Cube.hpp"

class car: public Shape {
protected:
	Cube *cube1;
	Cube *cube2;

public:
	~car();
	car();
	void draw();

};

#endif /* SRC_CAR_HPP_ */
