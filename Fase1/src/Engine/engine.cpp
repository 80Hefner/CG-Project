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
#include "../utils/tinyxml2.h"

using namespace tinyxml2;
using namespace std;

// Vector with all objects
vector<vector<Ponto>> objects;
// Object to draw (-1 draws all)
int current_object = -1;

// Presentation options
GLenum gl_mode = GL_LINE;
GLenum gl_face = GL_FRONT;

// Camera values
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


int load3dFiles(vector<string> _3dFilesList) {
    string line;
    string delim = ", ";
    ifstream file;

	for (int i = 0; i < _3dFilesList.size(); i++) {
		file.open(_3dFilesList[i].c_str(), ios::in);
		getline(file, line);
		int nr_points = atoi(line.c_str());
		vector<Ponto> points;

		if (file.is_open()) {
			for (int j = 0; j < nr_points; j++) {
				getline(file, line);
				Ponto p = Ponto(line);
				points.push_back(p);
			}
			file.close();
		}
		else {
			cout << "Unable to open file!\n";
			return 0;
		}

		objects.push_back(points);
	}

	return 1;
}

int loadXMLFile(string xmlFileString) {
	 XMLDocument doc;
	 vector<string> _3dFilesList;

	 // Trying to open XML File
	 XMLError load_result = doc.LoadFile(xmlFileString.c_str());
	 if (load_result != XML_SUCCESS)  {
		 cout << "Unable to load XML File!\n";
		 return 0;
	 }

	 // Trying to get scene element
	 XMLElement* root = doc.FirstChildElement("scene");
	 if (root == nullptr) {
		 cout << "XML File has wrong sintax! -> scene element\n";
		 return 0;
	 }

	 // Trying to get first model element (folder path)
	 XMLElement* element = root->FirstChildElement("model");
	 if (element == nullptr) {
		 cout << "XML File has wrong sintax! -> first model element\n";
		 return 0;
	 }
	 string folder = element->Attribute("folder");

	 // Reading .3d files
	 while (element = element->NextSiblingElement()) {
		 string file = element->Attribute("file");

		 _3dFilesList.push_back(folder + file);
	 }

	 // init 3d models
	 return (load3dFiles(_3dFilesList));
}

int main(int argc, char **argv) {

    if (argc > 1) {
		// load XML file
        string xmlFileString = argv[1];
    	xmlFileString = "../../filesXML/" + xmlFileString;
		if (loadXMLFile(xmlFileString) == 0) {
			cout << "Error reading XML File!\n";
			return 0;
		}

		// init GLUT and the window
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
		glutInitWindowPosition(0,0);
		glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
		glutCreateWindow("FASE 1");

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
    }
	else {
		cout << "Invalid input!\n";
	}

	return 1;
}
