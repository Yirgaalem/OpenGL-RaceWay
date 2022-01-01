/*
 -------------------------------------
 File:    track.hpp
 Project: SimpleView3
 file description
 -------------------------------------
 Author:  Brandon Parker
 ID:      191593730
 Email:   park3730@mylaurier.ca
 Version  2021-11-29
 -------------------------------------
 */
#ifndef SRC_TRACK_HPP_
#define SRC_TRACK_HPP_

#include <GL/glut.h>

#include "Cube.hpp"

class track: public Shape {
protected:
	Cube *cube1;

public:
	~track();
	track();
	void draw();
};

#endif /* SRC_TRACK_HPP_ */
