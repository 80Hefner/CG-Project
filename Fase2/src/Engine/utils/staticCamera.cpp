#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <math.h>
#include <iostream>
#include <fstream>

#include "staticCamera.h"

using namespace std;

staticCamera::staticCamera(string cfg_file_str) {
    loadCamera(cfg_file_str);
}

GLdouble staticCamera::getEyeX() {
    return sin(alpha) * cos(beta) * gamma;
}

GLdouble staticCamera::getEyeY() {
    return sin(beta) * gamma;
}

GLdouble staticCamera::getEyeZ() {
    return cos(alpha) * cos(beta) * gamma;
}


void staticCamera::reactRegularKey(unsigned char c) {
    switch (c) {
        case 'a': alpha -= alpha_inc; break;
        case 'd': alpha += alpha_inc; break;
		case 'w':
			beta += beta_inc;
			if (beta > 1.5) beta = 1.5;
			break;
		case 's':
			beta -= beta_inc;
			if (beta < -1.5) beta = -1.5;
			break;
		case 'q': gamma += gamma_inc; break;
		case 'e': gamma -= gamma_inc; break;
    }
}

void staticCamera::loadCamera(string file_str) {
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
			else if (token == "alpha_inc")
				this->alpha_inc = atof(value.c_str());
			else if (token == "beta")
				this->beta = atof(value.c_str());
			else if (token == "beta_inc")
				this->beta_inc = atof(value.c_str());
			else if (token == "gamma")
				this->gamma = atof(value.c_str());
			else if (token == "gamma_inc")
				this->gamma_inc = atof(value.c_str());
		}

		file.close();
	}
	else {
		cout << "Unable to open file: " << file_str.c_str() << "\n";
	}
}

void staticCamera::saveCamera(string file_str) {
	ofstream file;
	
	file.open(file_str.c_str(), ios::out | ios::trunc);

	if (file.is_open()) {

		file << "alpha:" << this->alpha << "\n";
		file << "alpha_inc:" << this->alpha_inc << "\n";
		file << "beta:" << this->beta << "\n";
		file << "beta_inc:" << this->beta_inc << "\n";
		file << "gamma:" << this->gamma << "\n";
		file << "gamma_inc:" << this->gamma_inc << "\n";
		
        file.close();
	}
	else {
		cout << "Unable to open file: " << file_str.c_str() << "\n";
	}
}