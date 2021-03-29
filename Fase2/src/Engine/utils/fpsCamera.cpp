#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES // always before the include
#include <string>
#include <math.h>
#include <iostream>
#include <fstream>

#include "fpsCamera.h"

using namespace std;

fpsCamera::fpsCamera(int width, int height, string cfg_file_str) {
	// loads camera settings from cfg file
	loadCamera(cfg_file_str);

	// sets mouse starting point
	startX = width / 2;
	startY = height / 2;

	// disables mouse tracking
	tracking[0] = 0;
	tracking[1] = 0;
}

GLdouble fpsCamera::getCenterX() {
	return eyeX + sin(alpha) * sin(beta);
}

GLdouble fpsCamera::getCenterY() {
	return eyeY + cos(beta);
}

GLdouble fpsCamera::getCenterZ() {
	return eyeZ + cos(alpha) * sin(beta);
}


void fpsCamera::reactRegularKey(unsigned char c) {
    switch (c) {
        case 'a':
			eyeX -= sin(alpha - M_PI/2) * speed;
        	eyeZ -= cos(alpha - M_PI/2) * speed;
			break;
        case 'd':
			eyeX -= sin(alpha + M_PI/2) * speed;
        	eyeZ -= cos(alpha + M_PI/2) * speed;
			break;
		case 'w':
			eyeX += sin(alpha) * speed;
			eyeZ += cos(alpha) * speed;
			break;
		case 's':
			eyeX -= sin(alpha) * speed;
			eyeZ -= cos(alpha) * speed;
			break;
		case 'q':
			eyeY += 0.3 * speed;
			break;
		case 'e':
			eyeY -= 0.3 * speed;
			break;
    }

}

void fpsCamera::processMouseMotion(int xx, int yy) {
	if (tracking[0] == 1) {
		int deltaX = xx - startX;
		startX = xx;

		alpha -= deltaX * sensitivity;
	}
	
	if (tracking[1] == 1) {
		int deltaY = yy - startY;
		startY = yy;

		beta += deltaY * sensitivity;

		if (beta < M_PI/32) beta = M_PI/32;
    	else if (beta > M_PI - M_PI/32) beta = M_PI - M_PI/32;
	}
}

void fpsCamera::processMouseButtons(int button, int state, int xx, int yy) {
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			startX = xx;
			tracking[0] = 1;
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			startY = yy;
			tracking[1] = 1;
		}
	}
	else if (state == GLUT_UP) {
		if (button == GLUT_LEFT_BUTTON)
			tracking[0] = 0;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking[1] = 0;
	}
}


void fpsCamera::loadCamera(string file_str) {
	string line;
	ifstream file;
	
	file.open(file_str.c_str(), ios::in);

	if (file.is_open()) {

		while (getline(file, line)) {
			size_t pos = line.find(":");
			string token = line.substr(0, pos);
			string value = line.substr(pos+1, line.size());

			if (token == "alpha")
				this->alpha = atof(value.c_str());
			else if (token == "beta")
				this->beta = atof(value.c_str());
			else if (token == "eyeX")
				this->eyeX = atof(value.c_str());
			else if (token == "eyeY")
				this->eyeY = atof(value.c_str());
			else if (token == "eyeZ")
				this->eyeZ = atof(value.c_str());
			else if (token == "sensitivity")
				this->sensitivity = atof(value.c_str());
			else if (token == "speed")
				this->speed = atof(value.c_str());
		}

		file.close();
	}
	else {
		cout << "Unable to open file: " << file_str.c_str() << "\n";
	}
}

void fpsCamera::saveCamera(string file_str) {
	ofstream file;
	
	file.open(file_str.c_str(), ios::out | ios::trunc);

	if (file.is_open()) {

		file << "alpha:" << this->alpha << "\n";
		file << "beta:" << this->beta << "\n";
		file << "eyeX:" << this->eyeX << "\n";
		file << "eyeY:" << this->eyeY << "\n";
		file << "eyeZ:" << this->eyeZ << "\n";
		file << "sensitivity:" << this->sensitivity << "\n";
		file << "speed:" << this->speed << "\n";

		file.close();
	}
	else {
		cout << "Unable to open file: " << file_str.c_str() << "\n";
	}
}
