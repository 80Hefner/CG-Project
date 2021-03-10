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


vector<Ponto> objects;

GLenum gl_mode = GL_LINE;
GLdouble alpha_angle = M_PI / 4;
GLdouble beta_angle = M_PI / 6;
GLdouble gamma_value = 10.0;


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

void drawObjects() { //TODO: desenhar todos objetos e rever funçao
    glColor3f(1,1,1);
    for(int i = 0;i<objects.size();i+=3){
        glBegin(GL_TRIANGLES);
        glVertex3f(objects[i].getX(),objects[i].getY(),objects[i].getZ());
        glVertex3f(objects[i+1].getX(),objects[i+1].getY(),objects[i+1].getZ());
        glVertex3f(objects[i+2].getX(),objects[i+2].getY(),objects[i+2].getZ());
        glEnd();
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
	glPolygonMode(GL_FRONT_AND_BACK, gl_mode);


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

			glPolygonMode(GL_FRONT_AND_BACK,gl_mode);
			break;
		case 27:
			exit(0);
			break;
	}
	glutPostRedisplay();
}


void load3dFiles(string pointsFileString) {
    string line;
    string delim = ", ";
    ifstream file;
    file.open(pointsFileString, ios::in);

    if (file.is_open()) {
        while ( getline (file,line) ) {
            Ponto p = Ponto(line);
            objects.push_back(p);
        }

        file.close();
    }
}

int main(int argc, char **argv) {

    if (argc > 1) {
        string xmlFileString = argv[1];
        xmlFileString = "../../filesXML/" + xmlFileString; // TODO: ler do xml

        string pointsFileString = "../../files3D/cone.3d";
        // init 3d models
        load3dFiles(pointsFileString);

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
