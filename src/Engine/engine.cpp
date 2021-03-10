#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "../utils/ponto.h"

using namespace std;


vector<vector<Ponto>> objects;

GLenum gl_mode = GL_LINE;
GLenum gl_face = GL_FRONT;
GLdouble alpha_angle = M_PI / 4;
GLdouble beta_angle = M_PI / 6;
GLdouble gamma_value = 10.0;
int current_object = -1;


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void drawAxis(void) {
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);
	glEnd();
}

void drawObject(vector<Ponto> points) {
	for (int j = 0; j < points.size(); j+=3) {
		glBegin(GL_TRIANGLES);
		glVertex3f(points[j].getX(),points[j].getY(),points[j].getZ());
		glVertex3f(points[j+1].getX(),points[j+1].getY(),points[j+1].getZ());
		glVertex3f(points[j+2].getX(),points[j+2].getY(),points[j+2].getZ());
		glEnd();
	}
}

void drawObjects() {
    glColor3f(1,1,1);

	if (current_object == -1) {
		for (int i = 0; i < objects.size(); i++) {
			vector<Ponto> points = objects[i];
			drawObject(points);
		}
	}
	else {
		vector<Ponto> points = objects[current_object];
		drawObject(points);
	}

}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
    gluLookAt(sin(alpha_angle)*cos(beta_angle)*gamma_value, sin(beta_angle)*gamma_value, cos(alpha_angle)*cos(beta_angle)*gamma_value,
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
	glPolygonMode(gl_face, gl_mode);


    // put drawing instructions here
	drawAxis();
    drawObjects();

	// End of frame
	glutSwapBuffers();
}

//Reage a eventos de regular keys (letras, numeros, etc.)
void reageEventoChar(unsigned char key, int x, int y) {
	switch (key) {
        case 'a': alpha_angle -= M_PI / 32; break;
		case 'd': alpha_angle += M_PI / 32; break;
		case 'w':
			beta_angle += M_PI / 32;
			if (beta_angle > 1.5) beta_angle = 1.5;
			break;
		case 's':
			beta_angle -= M_PI / 32;
			if (beta_angle < -1.5) beta_angle = -1.5;
			break;
		case 'e': gamma_value -= 0.5; break;
		case 'q': gamma_value += 0.5; break;
		case 't':
			if (gl_mode == GL_FILL) gl_mode = GL_LINE;
			else if (gl_mode == GL_LINE) gl_mode = GL_POINT;
			else if (gl_mode == GL_POINT) gl_mode = GL_FILL;

			glPolygonMode(gl_face,gl_mode);
			break;
		case 27:
			exit(0);
			break;
		default:
			if (key >= '0' && key <= '9') {
				int keyN = key - '0';
				if (keyN <= objects.size()) current_object = keyN - 1;
			}
			break;
	}
	glutPostRedisplay();
}


void load3dFiles(vector<string> _3dFilesList) {
    string line;
    string delim = ", ";
    ifstream file;

	for (int i = 0; i < _3dFilesList.size(); i++) {
		file.open(_3dFilesList[i], ios::in);
		vector<Ponto> points;

		if (file.is_open()) {
			while ( getline (file,line) ) {
				Ponto p = Ponto(line);
				points.push_back(p);
			}
			file.close();
		}

		objects.push_back(points);
	}

}

int main(int argc, char **argv) {

    if (argc > 1) {
        //string xmlFileString = argv[1];
        //xmlFileString = "../../filesXML/" + xmlFileString; // TODO: ler do xml

        vector<string> _3dFilesList;
		_3dFilesList.push_back("../../files3D/cone.3d");
		_3dFilesList.push_back("../../files3D/box.3d");
		_3dFilesList.push_back("../../files3D/plane.3d");

        // init 3d models
        load3dFiles(_3dFilesList);

    }


// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");

// Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

// put here the registration of the keyboard callbacks
	glutKeyboardFunc(reageEventoChar);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
