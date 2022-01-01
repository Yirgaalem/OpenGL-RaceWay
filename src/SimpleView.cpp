/*
 *  Author: Brandon Parker
 *  Version: 2021-11-18
 */

#include <GL/glew.h>
#include "pixmap/RGBpixmap.h"

#include "GL/glaux.h"
#include "glsl/Angel.h"

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Menu.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"

#include "Cube.hpp"

GLint winWidth = 800, winHeight = 800;
GLint isInMove = 0, xbegin = 0, csType = 1, /* coordinate system type: 1 for MCS, 2 for WCS, 3 for VCS */
transType = 4; /* depends on csType  */

CullMode cullMode = GLCULLDEPTHBUFFER; /* culling option */

RenderMode renderMode = TEXTURE;
;
/* shade option  */

World myWorld;
Camera myCamera;
Light myLight;
Shape *selectObj = NULL;  // pointer to select object
GLint displayOption = 0; /* 0: world, 1: solar system, 2: control points, 3: curve, 4: rotation surface.  */

RGBpixmap pix[7]; /* pixmaps for 6 textures */
GLuint ProgramObject; /* GLSL program object */

float carSpeed = 0;
float carAngle = 0;
float moving = 0;

GLfloat yTranslation = 0;
GLfloat xTranslation = 0;
float yValue = 0;
float xValue = 0;

void init(void) {

	displayOption = 0;
	renderMode = TEXTURE;
	glUseProgram(0);  // disable GLSL shader
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	myLight.on = false;

	glClearColor(0.0, 0.0, 0.0, 1.0);
	selectObj = myWorld.searchById(1);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	/* load six texture bitmap */
	pix[0].makeCheckerboard();
	pix[0].setTexture(0);

	pix[1].readBMPFile("track1.bmp");
	pix[1].setTexture(1);

	pix[6].readBMPFile("ppl_in_stands2.bmp");
	pix[6].setTexture(6);

}

void drawWCSAxes() {
	glBegin(GL_LINES);
	//x-axis red
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-2, 0, 0);
	glVertex3f(4, 0, 0);
	//y-axis green
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, -2, 0);
	glVertex3f(0, 4, 0);
	//z-axis blue
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, -2);
	glVertex3f(0, 0, 4);
	glEnd();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (displayOption) {
	case 0:
		myCamera.setProjectionMatrix();
//		drawWCSAxes();
		myWorld.draw();
//		myLight.draw();
		break;
	case 1:
		myCamera.setProjectionMatrix();

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:
		//myRBM.RotateCurve();
		myCamera.setProjectionMatrix();
		drawWCSAxes();
		glColor3f(0.0, 1.0, 1.0);

		myLight.draw();
		break;
	}
	glFlush();
	glutSwapBuffers();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

void mouseActionFcn(int button, int state, int xMouse, int yMouse) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		isInMove = 1;
		xbegin = xMouse;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		isInMove = 0;
	}
}

void mouseMotionFcn(GLint xMouse, GLint yMouse) {
	if (isInMove) {
		if (csType == 1) {
			MCSTransform(xMouse);
		} else if (csType == 2) {
			WCSTransform(xMouse);
		} else if (csType == 3) {
			VCSTransform(xMouse);
		} else if (csType == 4) {
			lightTransform(xMouse);
		}
		glutPostRedisplay();
	}
}

void moveCarCalculations() {
	if (moving != 0) {
		if (carAngle == 0) {
			xTranslation = 0;
			yTranslation = -(carSpeed) * 0.0001 * moving;
		} else {
			if (carAngle < 90) { // 0 - 90

				xTranslation = ((carAngle - carSpeed * (carAngle / 90))
						* 0.00005) * moving;

				yTranslation = -(carSpeed - carAngle * (carSpeed / 90)) * 0.0001
						* moving;

			} else if (carAngle < 180) { // 90 - 180

				xTranslation = ((90 - (carAngle - 90))
						- carSpeed * ((90 - (carAngle - 90)) / 90)) * 0.00005
						* moving;

				yTranslation = -(carSpeed - carAngle * (carSpeed / 90)) * 0.0001
						* moving;

			} else if (carAngle < 270) { // 180 - 270

				xTranslation = ((90 - (carAngle - 90))
						- carSpeed * ((90 - (carAngle - 90)) / 90)) * 0.00005
						* moving;

				yTranslation = -(carSpeed
						- (180 - (carAngle - 180)) * (carSpeed / 90)) * 0.0001
						* moving;
			} else if (carAngle < 360) { // 270 - 360

				xTranslation = -((90 - (carAngle - 270))
						- carSpeed * ((90 - (carAngle - 270)) / 90)) * 0.00005
						* moving;

				yTranslation = -(carSpeed
						- (180 - (carAngle - 180)) * (carSpeed / 89)) * 0.0001
						* moving;
			}

		}
	} else {
		xTranslation = 0;
		yTranslation = 0;
	}

}

void SpecialInput(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
		if (carSpeed < 90) {
			carSpeed += 1;
		}
		break;

	case GLUT_KEY_DOWN:

		if (carSpeed > 0) {
			carSpeed -= 1;
		}
		break;

	case GLUT_KEY_LEFT:

		selectObj->rotate(1, ZAXIS);
		carAngle += 1;

		break;

	case GLUT_KEY_RIGHT:

		selectObj->rotate(-1, ZAXIS);
		carAngle -= 1;
		break;

	case GLUT_KEY_SHIFT_L:
		carSpeed = 0;
		break;

	case GLUT_KEY_SHIFT_R:
		carSpeed = 0;
		break;
	}

	if (carSpeed != 0) {
		moving = 1;
	} else {
		moving = 0;
	}

	if (carAngle >= 360) {
		carAngle = 0;
	}

	moveCarCalculations();

	glutPostRedisplay();
}

int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("SimpleView Raceway - Brandon | Jonah | Nahor ");

	glewInit(); // this is for GSLS

	menu();
	init();

	glutSpecialFunc(SpecialInput);

	glutDisplayFunc(display);
	glutMotionFunc(mouseMotionFcn);
	glutMouseFunc(mouseActionFcn);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 0;
}
