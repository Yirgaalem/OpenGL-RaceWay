/*
 *  Author: Brandon Parker
 *  Version: 2021-11-18
 */

#include "World.hpp"
#include "Cube.hpp"

#include "car.hpp"
#include "track.hpp"
#include "crowd.hpp"

using namespace std;

World::World() {
	Shape *obj = NULL;

	/* add Cube into the world object list */
	obj = new car();
	obj->setId(1);
	obj->scaleChange(-.7);
	obj->translate(-8, -2, .4);
	obj->rotate(90, ZAXIS);
	objlist.push_back(obj);

	obj = new track();
	obj->setId(2);
	objlist.push_back(obj);

	obj = new crowd();
	obj->setId(3);
	objlist.push_back(obj);

}

World::~World() {
	Shape *obj;
	while (!objlist.empty()) {
		obj = objlist.front();
		objlist.pop_front();
		free(obj);
	}
}

void lineSegment(float x1, float y1, float z1, float x2, float y2, float z2) {
	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}

void World::draw() {
//	glColor3f(1.0, 0.0, 0.0);
//	lineSegment(-2, 0, 0, 4, 0, 0); /* x-axis in red */
// 	glColor3f(0.0, 1.0, 0.0);
//	lineSegment(0, -2, 0, 0, 4, 0); /* y-axis in green */
//	glColor3f(0.0, 0.0, 1.0);
//	lineSegment(0, 0, -2, 0, 0, 4); /* z-axis in blue */

	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it != objlist.end(); ++it) {
		(*it)->draw();
	}
}

void World::reset() {
	Shape *obj = NULL;

	obj = this->searchById(1);
	obj->reset();
	obj->setScale(0.3);
	obj->translate(-8, -2, .4);
	obj->rotate(90, ZAXIS);

	obj = this->searchById(2);
	obj->reset();
//
//	obj = this->searchById(3);
//	obj->reset();
//	obj->setScale(0.5);

//	std::list<Shape*>::iterator it;
//	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
//	  (*it)->reset();
//  }
}

Shape* World::searchById(GLint i) {
	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it != objlist.end(); ++it) {
		if ((*it)->getId() == i)
			return *it;
	}
	return NULL;
}

