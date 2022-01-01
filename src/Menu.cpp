/*
 *  Author: Brandon Parker
 *  Version: 2021-11-18
 */

// --------- for playing sound ---------
#include <windows.h>
#include <mmsystem.h>
// --------- for playing sound ---------

#include "Menu.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "glsl/Angel.h"
#include "pixmap/RGBpixmap.h"

#include "Cube.hpp"
extern GLint csType;
extern Shape *selectObj;
extern GLint transType, xbegin;
extern World myWorld;
extern Camera myCamera;
extern Light myLight;

extern CullMode cullMode;
extern RenderMode renderMode;

extern GLint displayOption;

extern GLfloat carSpeed;
extern GLfloat carAngle;
extern GLfloat moving;
extern GLfloat yTranslation;
extern GLfloat xTranslation;
extern float yValue;
extern float xValue;
bool crashed = false;

GLfloat zRocketTranslation = 0.00001;

GLfloat opeingMovementRotation = 0.05;

void menu() {

	GLint MCTrans_Menu = glutCreateMenu(MCSTransMenu);
	glutAddMenuEntry("Rotate x", 1);
	glutAddMenuEntry("Rotate y", 2);
	glutAddMenuEntry("Rotate z", 3);
	glutAddMenuEntry("Scale", 4);

	GLint music_menu = glutCreateMenu(musicMenu);
	glutAddMenuEntry("Dance", 1);
	glutAddMenuEntry("Rumble", 2);
	glutAddMenuEntry("None", 3);

	GLint WCTrans_Menu = glutCreateMenu(WCSTransMenu);
	glutAddMenuEntry("Rotate x", 1);
	glutAddMenuEntry("Rotate y", 2);
	glutAddMenuEntry("Rotate z", 3);
	glutAddMenuEntry("Translate x", 4);
	glutAddMenuEntry("Translate y", 5);
	glutAddMenuEntry("Translate z", 6);

	GLint VCTrans_Menu = glutCreateMenu(VCSTransMenu);
	glutAddMenuEntry("Rotate x", 1);
	glutAddMenuEntry("Rotate y", 2);
	glutAddMenuEntry("Rotate z", 3);
	glutAddMenuEntry("Translate x", 4);
	glutAddMenuEntry("Translate y", 5);
	glutAddMenuEntry("Translate z", 6);
	glutAddMenuEntry("Clipping Near", 7);
	glutAddMenuEntry("Clipping Far", 8);

	GLint cam_pos_Menu = glutCreateMenu(camPossMenu);
	glutAddMenuEntry("Sky", 1);
	glutAddMenuEntry("Car", 2);
	glutAddMenuEntry("Top Down", 3);
	glutAddMenuEntry("Middle", 4);

	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Start", 1);
	glutAddMenuEntry("Reset", 2);
	glutAddMenuEntry("Rocket", 3);
	glutAddSubMenu("Music", music_menu);
//	glutAddSubMenu("MCS Transformations", MCTrans_Menu);
//	glutAddSubMenu("WCS Transformations", WCTrans_Menu);
//	glutAddSubMenu("VCS Transformations", VCTrans_Menu);
//	glutAddSubMenu("Camera Position", cam_pos_Menu);
	glutAddMenuEntry("Quit", 4);

	glutIdleFunc(openingMovement);

	musicMenu(1);
}

void openingMovement() {

	myCamera.rotate(0.0, 0.0, 1.0, opeingMovementRotation);
//	opeingMovementRotation += 0.005;
	glutPostRedisplay();
}

GLfloat yRefAdjustment = 0.0;

void carMovement() {

	if (!crashed) {
		if (yValue < -16.9759 || xValue < -1.0930 || xValue > 17.33
				|| yValue > 21.1312) {
			crashed = true;
			playCrashSound();
		} else {
			xValue += xTranslation;
			yValue += yTranslation;
			selectObj->translate(xTranslation, yTranslation, 0);
			if (carAngle >= 90 && carAngle <= 180) {
				yRefAdjustment = ((float) carAngle - 90) * (7.0 / 90.0);
			} else if (carAngle >= 180 && carAngle <= 270) {
				yRefAdjustment = 7 - (((float) carAngle - 180) * (7.0 / 90));
			} else {
				yRefAdjustment = 0.0;
			}
			myCamera.setRef(xValue - 7, yValue - 7 + yRefAdjustment, 2);
		}
	}
	glutPostRedisplay();

}

void playCrashSound() {

	PlaySound((LPCSTR) "Car_Explosion.wav", NULL,
	SND_FILENAME | SND_ASYNC);

}

void carRocket() {
	selectObj->translate(0, 0, zRocketTranslation);
	selectObj->rotate(-0.5, ZAXIS);
	myCamera.setRef(myCamera.ref.x, myCamera.ref.y,
			myCamera.ref.z + zRocketTranslation);
	zRocketTranslation += 0.00001;
	glutPostRedisplay();
}

void mainMenu(GLint option) {
	switch (option) {
	case 1:
		reset();
		glutIdleFunc(carMovement);

		break;
	case 2:
		reset();
		glutIdleFunc(carMovement);
		break;

	case 3:
		zRocketTranslation = 0.0;
		glutIdleFunc(carRocket);
		break;

	case 4:
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void ObjSubMenu(GLint option) {
	if (option == 4) {
		displayOption = 4;
	} else {
		selectObj = myWorld.searchById(option);
		displayOption = 0;
	}
	Matrix mp = selectObj->getMC();
	myCamera.setRef(mp.mat[0][3], mp.mat[1][3], mp.mat[1][3]);
	glutPostRedisplay();
}

void sound1() {
	PlaySound((LPCSTR) "bensound-rumble.wav", NULL,
	SND_FILENAME | SND_ASYNC);
}

void sound2() {
	PlaySound((LPCSTR) "bensound-dance.wav", NULL,
	SND_FILENAME | SND_ASYNC);
}

void musicMenu(GLint option) {
	switch (option) {
	case 1:
		sound1();

		break;
	case 2:
		sound2();
		break;
	case 3:
		PlaySound(NULL, NULL, NULL);
		break;
	}
}

void MCSTransMenu(GLint transOption) {
	csType = 1;
	transType = transOption;
	glutPostRedisplay();
}

void WCSTransMenu(GLint transOption) {
	csType = 2;
	transType = transOption;
	glutPostRedisplay();
}

void camPossMenu(GLint transOption) {
	if (transOption == 1) { // sky
		myCamera.setCameraSky();
	} else if (transOption == 2) {  // car

		myCamera.setCameraCar();
	} else if (transOption == 3) {  // top

		myCamera.setCameraTop();
	} else if (transOption == 4) {  // middle

		myCamera.setCameraMiddle();
	}

	glutPostRedisplay();
}

void VCSTransMenu(GLint transOption) {
	csType = 3;
	transType = transOption;
	glutPostRedisplay();
}

void MCSTransform(GLint x) {
	GLfloat x0, y0, z0, rx, ry, rz, theta;
	theta = (xbegin - x > 0) ? 1 : -1;

	x0 = selectObj->getMC().mat[0][3];
	y0 = selectObj->getMC().mat[1][3];
	z0 = selectObj->getMC().mat[2][3];

	if (transType == 1) { //model rotate x
		rx = selectObj->getMC().mat[0][0];
		ry = selectObj->getMC().mat[1][0];
		rz = selectObj->getMC().mat[2][0];
		selectObj->rotate(x0, y0, z0, rx, ry, rz, theta * 0.5);
	} else if (transType == 2) { //model rotate y
		rx = selectObj->getMC().mat[0][1];
		ry = selectObj->getMC().mat[1][1];
		rz = selectObj->getMC().mat[2][1];
		selectObj->rotate(x0, y0, z0, rx, ry, rz, theta * 0.5);
	} else if (transType == 3) {  //model rotate z
		rx = selectObj->getMC().mat[0][2];
		ry = selectObj->getMC().mat[1][2];
		rz = selectObj->getMC().mat[2][2];
		selectObj->rotate(x0, y0, z0, rx, ry, rz, theta * 0.5);
	}
//	else if (transType == 4) { //model scale
//		selectObj->scaleChange(theta * 0.02);
//	}
}

void WCSTransform(GLint x) {
	GLfloat theta = (xbegin - x > 0) ? 1 : -1;
	if (transType == 1) {
		selectObj->rotateOrigin(0, 0, 0, 1, 0, 0, theta * 0.5);
	} else if (transType == 2) {
		selectObj->rotateOrigin(0, 0, 0, 0, 1, 0, theta * 0.5);
	} else if (transType == 3) {
		selectObj->rotateOrigin(0, 0, 0, 0, 0, 1, theta * 0.5);
	} else if (transType == 4) {
		selectObj->translate(theta * 0.02, 0, 0);
	} else if (transType == 5) { //WC translate y
		selectObj->translate(0, theta * 0.02, 0);
	} else if (transType == 6) { //WC translate z
		selectObj->translate(0, 0, theta * 0.02);
	}
}

void VCSTransform(GLint x) {
	GLfloat theta = (xbegin - x > 0) ? 1 : -1;
	if (transType == 1) {  //eye rotate x
		myCamera.rotate(1.0, 0.0, 0.0, theta * 0.5);
	} else if (transType == 2) { // eye rotate y
		myCamera.rotate(0.0, 1.0, 0.0, theta * 0.5);
	} else if (transType == 3) { //eye rotate z
		myCamera.rotate(0.0, 0.0, 1.0, theta * 0.5);
	} else if (transType == 4) { //eye translate x
		myCamera.translate(theta * 0.02, 0.0, 0.0);
	} else if (transType == 5) {   // eye translate y
		myCamera.translate(0.0, theta * 0.02, 0.0);
	} else if (transType == 6) { // eye translate z
		myCamera.translate(0.0, 0.0, theta * 0.02);
	} else if (transType == 7) {  // change dnear
		myCamera.dnear += theta * .1;
	} else if (transType == 8) {  // change dfar
		myCamera.dfar += theta * .1;
	}
}

void cullMenu(GLint option) {
	switch (option) {
	case 1:
		cullMode = NONE;
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		break;
	case 2:
		cullMode = BACKFACE;
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		break;
	case 3:
		cullMode = GLCULL;
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		break;
	case 4:
		cullMode = GLCULLDEPTHBUFFER;
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		break;
	case 5:
		cullMode = GLCULLDEPTHBUFFER;
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		break;
	}
	glutPostRedisplay();
}

void lightMenu(GLint option) {
	csType = 4;
	transType = option;
	switch (option) {
	case 8:
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
		myLight.on = true;
		break;
	case 9:

		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_DEPTH_TEST);
		myLight.on = false;
		break;

	case 10:
//isShading = 0;
//		glLightModelf( GL_LIGHT_MODEL_TWO_SIDE, 0);
//		GLfloat material_Ka[] = { 1.0f, 0.5f, 0.5f, 0.0f };
//		GLfloat material_Kd[] = { 1.0f, 0.4f, 0.0f, 0.0f };
//		GLfloat material_Ks[] = { 1.0f, 0.5f, 0.5f, 0.0f };
//		GLfloat material_Ke[] = { 1.0f, 0.5f, 0.5f, 0.0f };
//		GLfloat material_Se = 20.0f;
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
//		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);

//		GLfloat material_Kd[] = { 1.0f * myLight.I, 0.4f * myLight.I, 0.0f
//				* myLight.I, 0.0f };
//		glMaterialfv(GL_FRONT, GL_DIFFUSE, material_Kd);

//		GLfloat material_Ke[] = { 0.5 * myLight.I, 0.1 * myLight.I, 0.1
//				* myLight.I, 0.0f };
//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
//		glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
//
//		GLfloat pos[] = { myLight.getMC().mat[0][3], myLight.getMC().mat[1][3],
//				myLight.getMC().mat[2][3], 1.0 };
//		GLfloat Ka[] = { 1.0, 1.0, 1.0, 1.0 };
//		GLfloat Kd[] =
//				{ 1.0 * myLight.I, 1.0 * myLight.I, 1.0 * myLight.I, 1.0 };
//		GLfloat Ks[] = { 1.0, 1.0, 1.0, 1.0 };
//		glLightfv(GL_LIGHT0, GL_POSITION, pos);
//		//glLightfv(GL_LIGHT0, GL_AMBIENT, Ka);
//		glLightfv(GL_LIGHT0, GL_DIFFUSE, Kd);
//		glLightfv(GL_LIGHT0, GL_SPECULAR, Ks);

		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_LIGHT0);
		break;
	}

	glutPostRedisplay();
}

void lightTransform(GLint x) {
	GLfloat theta = (xbegin - x > 0) ? 1 : -1;
	if (transType == 1) {   // rotate x
		myLight.rotate(0, 0, 0, 1.0, 0.0, 0.0, theta * 0.5);
	} else if (transType == 2) { // rotate y
		myLight.rotate(0, 0, 0, 0.0, 1.0, 0.0, theta * 0.5);
	} else if (transType == 3) { // rotate z
		myLight.rotate(0, 0, 0, 0.0, 0.0, 1.0, theta * 0.5);
	} else if (transType == 4) { // translate x
		myLight.translate(theta * 0.1, 0.0, 0.0);
	} else if (transType == 5) {   // eye translate y
		myLight.translate(0.0, theta * 0.1, 0.0);
	} else if (transType == 6) { // eye translate z
		myLight.translate(0.0, 0.0, theta * 0.1);
	} else if (transType == 7) {  // change intensity
		myLight.I += theta * 0.01;
	}

//	GLfloat Kd[] = { 1.0 * myLight.I, 1.0 * myLight.I, 1.0 * myLight.I, 1.0 };
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, Kd);
//
//	GLfloat material_Ke[] = { 0.5 * myLight.I, 0.5 * myLight.I, 0.5 * myLight.I,
//			0.0f };
//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);

//	glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);

	GLfloat pos[] = { myLight.getMC().mat[0][3], myLight.getMC().mat[1][3],
			myLight.getMC().mat[2][3], 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	glutPostRedisplay();
}

void move(void) {
	selectObj->rotate(selectObj->getMC().mat[0][3],
			selectObj->getMC().mat[1][3], selectObj->getMC().mat[2][3], 0, 0, 1,
			0.1);
	glutPostRedisplay();
}

void animateMenu(GLint option) {
	switch (option) {
	case 1:
//displayOption = 0;
		glutIdleFunc(move);
		break;
	case 2:
		myLight.on = false;
		displayOption = 0;
		glDisable(GL_LIGHTING);

		break;
	case 3:
		myLight.on = false;
		displayOption = 1;
//glDisable(GL_LIGHTING);

		break;
	case 4:
		glutIdleFunc(NULL);
		break;
	}
	glutPostRedisplay();
}

void reset() {
	displayOption = 0;
	renderMode = TEXTURE;
	myWorld.reset();
	myLight.reset();
	myCamera.reset();
	carSpeed = 0;
	carAngle = 0;
	moving = 0;
	xTranslation = 0;
	yTranslation = 0;
	xValue = 0;
	yValue = 0;
	crashed = false;

	glUseProgram(0);  // disable GLSL shader
	glutIdleFunc(NULL);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}
