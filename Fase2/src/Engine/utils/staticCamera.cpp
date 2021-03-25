#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <math.h>

#include "staticCamera.h"

using namespace std;

staticCamera::staticCamera() {
    alpha = -M_PI / 3;
    alpha_inc = M_PI / 64;
    beta = M_PI / 12;
    beta_inc = M_PI / 64;
    gamma = 10.0;
    gamma_inc = 1;
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
