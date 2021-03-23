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
#include "utils/group.h"

#define _3DFILESFOLDER "../../files3D/"
#define XMLFILESFOLDER "../../filesXML/"

using namespace tinyxml2;
using namespace std;
// TODO: criar xml sistema solar
// TODO: poder andar com a camara a vontade

// * Global variables * //

// Vector with all objects
vector<Group> groups_vector;

// Presentation options
GLenum gl_mode = GL_LINE;
GLenum gl_face = GL_FRONT_AND_BACK;

// Camera values
GLdouble alpha_angle = M_PI / 4;
GLdouble alpha_angle_inc = M_PI / 64;
GLdouble beta_angle = M_PI / 6;
GLdouble beta_angle_inc = M_PI / 64;
GLdouble gamma_value = 100.0;
GLdouble gamma_value_inc = 1;


// * Functions declarations * //

void changeSize(int w, int h);
void renderScene(void);
void engineHelpMenu();
void drawAxis(void);
void drawObject(vector<Ponto> points);
void drawGroup(Group g);
void reactRegularKeys(unsigned char key, int x, int y);
vector<Ponto> load3dFile(string _3dFile);
int loadXMLFile(string xmlFileString);
Group parseXMLGroupElement (XMLElement* main_element);


// * Glut Functions * //

// Reshape function
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

// Display function
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
	// Draw axis
	drawAxis();

	// Draw groups
    for (Group g : groups_vector) {
		drawGroup(g);
	}

	// End of frame
	glutSwapBuffers();
}

// Function to react to events from regular keys
void reactRegularKeys(unsigned char key, int x, int y) {
	switch (key) {
        case 'a': alpha_angle -= alpha_angle_inc; break;
		case 'd': alpha_angle += alpha_angle_inc; break;
		case 'w':
			beta_angle += beta_angle_inc;
			if (beta_angle > 1.5) beta_angle = 1.5;
			break;
		case 's':
			beta_angle -= beta_angle_inc;
			if (beta_angle < -1.5) beta_angle = -1.5;
			break;
		case 'e': gamma_value -= gamma_value_inc; break;
		case 'q': gamma_value += gamma_value_inc; break;
		case 't':
			if (gl_mode == GL_FILL) gl_mode = GL_LINE;
			else if (gl_mode == GL_LINE) gl_mode = GL_POINT;
			else if (gl_mode == GL_POINT) gl_mode = GL_FILL;

			glPolygonMode(gl_face,gl_mode);
			break;
		case 27:
			exit(0);
			break;
	}
	glutPostRedisplay();
}


// * Draw Functions * //

// Function to draw xyz axis
void drawAxis(void) {
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glEnd();
}

// Function to draw a single object, given its points
void drawObject(vector<Ponto> points) {
	for (int j = 0; j < points.size(); j+=3) {
		glBegin(GL_TRIANGLES);
		glVertex3f(points[j].getX(),points[j].getY(),points[j].getZ());
		glVertex3f(points[j+1].getX(),points[j+1].getY(),points[j+1].getZ());
		glVertex3f(points[j+2].getX(),points[j+2].getY(),points[j+2].getZ());
		glEnd();
	}
}

// Function to draw a single group
void drawGroup(Group g) {
	
	// Set the model view matrix as current, just for safety
	glMatrixMode(GL_MODELVIEW);

	// Push matrix on beggining
	glPushMatrix();

	// Trying to get translations from group
	vector<Translate> ts = g.getTranslates();
	for (Translate t : ts) {
		glTranslatef(t.getX(), t.getY(), t.getZ());
	}

	// Trying to get rotations from group
	vector<Rotate> rs = g.getRotates();
	for (Rotate r : rs) {
		glRotatef(r.getAngle(), r.getAxisX(), r.getAxisY(), r.getAxisZ());
	}

	// Trying to get scales from group
	vector<Scale> scs = g.getScales();
	for (Scale sc : scs) {
		glScalef(sc.getX(), sc.getY(), sc.getZ());
	}

	// Trying to get scales from group
	Color cl = g.getColor();
	glColor3f(cl.getR(), cl.getG(), cl.getB());

	// Drawing objects in this group
	vector<vector<Ponto>> objects = g.getObjects();
	for (vector<Ponto> object : objects) {
		drawObject(object);
	}

	// Drawing groups in this group
	vector<Group> groups = g.getGroups();
	for (Group group : groups) {
		drawGroup(group);
	}

	// Popping matrix after drawing all objects in this group
	glPopMatrix();
}



// * Parsing Functions * //

// Function to load a .3d file into a vector of points
vector<Ponto> load3dFile(string _3dFile) {
    string line;
    string delim = ", ";
    ifstream file;
	vector<Ponto> points = {};

	file.open(_3dFile.c_str(), ios::in);
	getline(file, line);
	int nr_points = atoi(line.c_str());
		

	if (file.is_open()) {
		for (int j = 0; j < nr_points; j++) {
			getline(file, line);
			Ponto p = Ponto(line);
			points.push_back(p);
		}
		file.close();
	}
	else {
		cout << "Unable to open file: " << _3dFile.c_str() << "\n";
	}

	return points;
}

// Function to parse a xml file
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

	// Trying to get all group elements
	XMLElement* group_element = root->FirstChildElement("group");
	while (group_element) {
		groups_vector.push_back(parseXMLGroupElement(group_element));

		group_element = root->NextSiblingElement("group");
	}

	return 1;
}

// Function to parse a group element in a xml file
Group parseXMLGroupElement (XMLElement* main_element) {
	Group new_group = Group();

	// Trying to get translate element
	XMLElement* translate_element = main_element->FirstChildElement("translate");
	while (translate_element) {
		// Get x attribute
		const XMLAttribute* x_attribute = translate_element->FindAttribute("X");
		float x_trans;
		x_attribute ? x_trans = atof(x_attribute->Value()) : x_trans = 0;

		// Get y attribute
		const XMLAttribute* y_attribute = translate_element->FindAttribute("Y");
		float y_trans;
		y_attribute ? y_trans = atof(y_attribute->Value()) : y_trans = 0;

		// Get z attribute
		const XMLAttribute* z_attribute = translate_element->FindAttribute("Z");
		float z_trans;
		z_attribute ? z_trans = atof(z_attribute->Value()) : z_trans = 0;

		new_group.addTranslate(x_trans, y_trans, z_trans);

		translate_element = translate_element->NextSiblingElement("translate");
	}

	// Trying to get rotate element
	XMLElement* rotate_element = main_element->FirstChildElement("rotate");
	while (rotate_element) {
		// Get angle attribute
		const XMLAttribute* angle_attribute = rotate_element->FindAttribute("angle");
		float angle_rot;
		angle_attribute ? angle_rot = atof(angle_attribute->Value()) : angle_rot = 0;

		// Get axisX attribute
		const XMLAttribute* axisX_attribute = rotate_element->FindAttribute("axisX");
		float axisX_rot;
		axisX_attribute ? axisX_rot = atof(axisX_attribute->Value()) : axisX_rot = 0;

		// Get axisY attribute
		const XMLAttribute* axisY_attribute = rotate_element->FindAttribute("axisY");
		float axisY_rot;
		axisY_attribute ? axisY_rot = atof(axisY_attribute->Value()) : axisY_rot = 0;

		// Get axisZ attribute
		const XMLAttribute* axisZ_attribute = rotate_element->FindAttribute("axisZ");
		float axisZ_rot;
		axisZ_attribute ? axisZ_rot = atof(axisZ_attribute->Value()) : axisZ_rot = 0;

		new_group.addRotate(angle_rot, axisX_rot, axisY_rot, axisZ_rot);

		rotate_element = rotate_element->NextSiblingElement("rotate");
	}

	// Trying to get scale element
	XMLElement* scale_element = main_element->FirstChildElement("scale");
	while (scale_element) {
		// Get x attribute
		const XMLAttribute* x_attribute = scale_element->FindAttribute("X");
		float x_scale;
		x_attribute ? x_scale = atof(x_attribute->Value()) : x_scale = 0;

		// Get y attribute
		const XMLAttribute* y_attribute = scale_element->FindAttribute("Y");
		float y_scale;
		y_attribute ? y_scale = atof(y_attribute->Value()) : y_scale = 0;

		// Get z attribute
		const XMLAttribute* z_attribute = scale_element->FindAttribute("Z");
		float z_scale;
		z_attribute ? z_scale = atof(z_attribute->Value()) : z_scale = 0;

		new_group.addScale(x_scale, y_scale, z_scale);

		scale_element = scale_element->NextSiblingElement("scale");
	}

	// Trying to get color element. If not found, sets color to white
	XMLElement* color_element = main_element->FirstChildElement("color");
	if (color_element) {
		// Get r attribute
		const XMLAttribute* r_attribute = color_element->FindAttribute("R");
		float r_color;
		r_attribute ? r_color = atof(r_attribute->Value()) : r_color = 0;

		// Get g attribute
		const XMLAttribute* g_attribute = color_element->FindAttribute("G");
		float g_color;
		g_attribute ? g_color = atof(g_attribute->Value()) : g_color = 0;

		// Get b attribute
		const XMLAttribute* b_attribute = color_element->FindAttribute("B");
		float b_color;
		b_attribute ? b_color = atof(b_attribute->Value()) : b_color = 0;

		new_group.setColor(r_color, g_color, b_color);
	}
	else {
		new_group.setColor(1.0f,1.0f,1.0f);
	}

	// Trying to get models element
	XMLElement* models_element = main_element->FirstChildElement("models");
	if (models_element) {
		// Get all model elements
		XMLElement* model_element = models_element->FirstChildElement("model");
		while (model_element) {
			// Parse model file attribute
			const XMLAttribute* file_attribute = model_element->FindAttribute("file");
			if (file_attribute) {
				string file = file_attribute->Value();
				vector<Ponto> file_object = load3dFile(_3DFILESFOLDER + file);
				new_group.addObject(file_object);
			}
			model_element = model_element->NextSiblingElement("models");
		}
	}

	// Trying to get group elements
	XMLElement* group_element = main_element->FirstChildElement("group");
	while (group_element) {
		new_group.addGroup(parseXMLGroupElement(group_element));

		group_element = group_element->NextSiblingElement("group");
	}

	return new_group;
}

// Function to print help menu
void engineHelpMenu() {
	cout << "┌───────────────────────ENGINE HELP───────────────────────┐" << endl;
	cout << "│   Usage: ./engine [XML FILE]                            │" << endl;
	cout << "│   Displays all primitives loaded from XML FILE          │" << endl;
	cout << "│                                                         │" << endl;
	cout << "│   Camera options                                        │" << endl;
	cout << "│      a : Moves camera to the left                       │" << endl;
	cout << "│      d : Moves camera to the right                      │" << endl;
	cout << "│      w : Moves camera up                                │" << endl;
	cout << "│      s : Moves camera down                              │" << endl;
	cout << "│      e : Zoom in                                        │" << endl;
	cout << "│      q : Zoom out                                       │" << endl;
	cout << "│                                                         │" << endl;
	cout << "│   Scene options                                         │" << endl;
	cout << "│      t   : Cycle between drawing modes                  │" << endl;
	cout << "│      c   : Cycle between white and random colors        │" << endl;
	cout << "│      1-9 : Draw a single object                         │" << endl;
	cout << "│      0   : Draw all objects                             │" << endl;
	cout << "│                                                         │" << endl;
	cout << "│   Press ESC at any time to exit program                 │" << endl;
	cout << "└─────────────────────────────────────────────────────────┘" << endl;
}


// * MAIN * //

int main(int argc, char **argv) {

	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
		engineHelpMenu();
	}
    else if (argc == 2) {
		// load XML file
        string xmlFileString = argv[1];
    	xmlFileString = XMLFILESFOLDER + xmlFileString;
		if (loadXMLFile(xmlFileString) == 0) {
			cout << "Error reading XML File!\n";
			return 0;
		}

		// init GLUT and the window
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
		glutInitWindowPosition(0,0);
		glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
		glutCreateWindow("CG - FASE 2");

		// Required callback registry
		glutDisplayFunc(renderScene);
		glutReshapeFunc(changeSize);

		// put here the registration of the keyboard callbacks
		glutKeyboardFunc(reactRegularKeys);

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
