/*
 *  Author: Brandon Parker
 *  Version: 2021-11-18
 */
#ifndef MENU_HPP_
#define MENU_HPP_

#include "glsl/Angel.h"
#include <GL/glut.h>

// SimpleView1
void menu();
void mainMenu(GLint option);
void musicMenu(GLint option);
void ObjSubMenu(GLint objectOption);
void MCSTransMenu(GLint transOption);
void WCSTransMenu(GLint transOption);
void VCSTransMenu(GLint transOption);
void reset();
void MCSTransform(GLint);
void WCSTransform(GLint);
void VCSTransform(GLint);

void openingMovement();
void carMovement();
void carRocket();
void sound1();
void sound2();
void playCrashSound();

// SimpleView2
void cullMenu(GLint option);
void lightMenu(GLint option);
void lightTransform(GLint);
void shadeMenu(GLint option);
void animateMenu(GLint option);

// SimpleView3
void curveSurfaceMenu(GLint option);
void move();

void camPossMenu(GLint transOption);

#endif
