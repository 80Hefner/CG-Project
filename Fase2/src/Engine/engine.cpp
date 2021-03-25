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
#include "utils/fpsCamera.h"
#include "utils/staticCamera.h"

#define _3DFILESFOLDER "../../files3D/"
#define XMLFILESFOLDER "../../filesXML/"
#define FPS_CAMERA_CFG_FILE "../../cfg/fpsCamera.cfg"
#define STATIC_CAMERA_CFG_FILE "../../cfg/staticCamera.cfg"

using namespace tinyxml2;
using namespace std;
// TODO: criar xml sistema solar
// TODO: poder andar com a camara a vontade

// * Global variables * //

// Vector with all objects
vector<Group> groups_vector = {};

// Presentation options
GLenum gl_mode = GL_LINE;
GLenum gl_face = GL_FRONT_AND_BACK;

// Camera values
fpsCamera* fps_camera;
staticCamera* static_camera;
int camera_mode = 0; // 0 -> static   1 -> fps
int draw_axis = 0;

// * Functions declarations * //

void changeSize(int w, int h);
void renderScene(void);
void reactRegularKeys(unsigned char key, int x, int y);
void processMouseMotion(int xx, int yy);
void processMouseButtons(int button, int state, int xx, int yy);
void drawAxis(void);
void drawObject(vector<Ponto> points);
void drawGroup(Group g);
vector<Ponto> load3dFile(string _3dFile);
int loadXMLFile(string xmlFileString);
Group parseXMLGroupElement (XMLElement* main_element);
void engineHelpMenu();


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
	if (camera_mode == 1) {
    	gluLookAt(fps_camera->getEyeX(), fps_camera->getEyeY(), fps_camera->getEyeZ(),
		      	fps_camera->getCenterX(), fps_camera->getCenterY(), fps_camera->getCenterZ(),
			  	0.0f,1.0f,0.0f);
	}
	else if (camera_mode == 0) {
		gluLookAt(static_camera->getEyeX(), static_camera->getEyeY(), static_camera->getEyeZ(),
		      	0.0f, 0.0f, 0.0f,
			  	0.0f,1.0f,0.0f);
	}
	glPolygonMode(gl_face, gl_mode);

    // put drawing instructions here
	// Draw axis
	if (draw_axis) drawAxis();

	// Draw groups
    for (Group g : groups_vector) {
		drawGroup(g);
	}

	// End of frame
	glutSwapBuffers();
}


// * Mouse and Keyboard Functions * //

// Function to react to events from regular keys
void reactRegularKeys(unsigned char key, int xx, int yy) {
	switch (key) {
        case 'a':
			camera_mode ? fps_camera->reactRegularKey(key) : static_camera->reactRegularKey(key);
			break;
        case 'd':
			camera_mode ? fps_camera->reactRegularKey(key) : static_camera->reactRegularKey(key);
			break;
		case 'w':
			camera_mode ? fps_camera->reactRegularKey(key) : static_camera->reactRegularKey(key);
			break;
		case 's':
			camera_mode ? fps_camera->reactRegularKey(key) : static_camera->reactRegularKey(key);
			break;
		case 'q':
			camera_mode ? fps_camera->reactRegularKey(key) : static_camera->reactRegularKey(key);
			break;
		case 'e':
			camera_mode ? fps_camera->reactRegularKey(key) : static_camera->reactRegularKey(key);
			break;

		case 't':
			if (gl_mode == GL_FILL) gl_mode = GL_LINE;
			else if (gl_mode == GL_LINE) gl_mode = GL_POINT;
			else if (gl_mode == GL_POINT) gl_mode = GL_FILL;

			glPolygonMode(gl_face,gl_mode);
			break;
		case '1':
			camera_mode = 0;
			break;
		case '2':
			camera_mode = 1;
			break;
		case 'l':
			camera_mode ? fps_camera->loadCamera(FPS_CAMERA_CFG_FILE) : static_camera->loadCamera(STATIC_CAMERA_CFG_FILE);
			break;
		case 'p':
			camera_mode ? fps_camera->saveCamera(FPS_CAMERA_CFG_FILE) : static_camera->saveCamera(STATIC_CAMERA_CFG_FILE);
			break;
		case 27:
			exit(0);
			break;
	}

	glutPostRedisplay();
}

// Function to process mouse motion
void processMouseMotion(int xx, int yy) {
	if (camera_mode) {
		fps_camera->processMouseMotion(xx, yy);
		glutPostRedisplay();
	}
}

// Function to process mouse buttons
void processMouseButtons(int button, int state, int xx, int yy) {
	if (camera_mode) {
		fps_camera->processMouseButtons(button, state, xx, yy);
		glutPostRedisplay();
	}
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

	// Trying to get transformations from group
	vector<Transformation*> ts = g.getTransformations();
	for (Transformation* t : ts) {
		Translate* t_t = dynamic_cast<Translate*>(t);
		if (t_t) {
			glTranslatef(t_t->getX(), t_t->getY(), t_t->getZ());
			continue;
		}

		Rotate* t_r = dynamic_cast<Rotate*>(t);
		if (t_r) {
			glRotatef(t_r->getAngle(), t_r->getAxisX(), t_r->getAxisY(), t_r->getAxisZ());
			continue;
		}

		Scale* t_s = dynamic_cast<Scale*>(t);
		if (t_s) {
			glScalef(t_s->getX(), t_s->getY(), t_s->getZ());
			continue;
		}
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
		Group g = parseXMLGroupElement(group_element);
		groups_vector.push_back(g);

		group_element = group_element->NextSiblingElement("group");
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
		Group g = parseXMLGroupElement(group_element);
		new_group.addGroup(g);

		group_element = group_element->NextSiblingElement("group");
	}

	return new_group;
}


// * Print Functions * //

// Function to print help menu
void engineHelpMenu() {
	cout << "┌─────────────────────────ENGINE HELP─────────────────────────┐" << endl;
	cout << "│    Usage: ./engine [XML FILE]                               │" << endl;
	cout << "│    Displays all primitives loaded from XML FILE             │" << endl;
	cout << "│                                                             │" << endl;
	cout << "│    FPS camera options                                       │" << endl;
	cout << "│    › Use w,a,s,d to navigate in space                       │" << endl;
	cout << "│    › Click and drag left mouse to turn camera horizontally  │" << endl;
	cout << "│    › Click and drag right mouse to turn camera vertically   │" << endl;
	cout << "│    › Use q and e to move camera up and down                 │" << endl;
	cout << "│                                                             │" << endl;
	cout << "│    Static camera options                                    │" << endl;
	cout << "│    › a : Moves camera to the left                           │" << endl;
	cout << "│    › d : Moves camera to the right                          │" << endl;
	cout << "│    › w : Moves camera up                                    │" << endl;
	cout << "│    › s : Moves camera down                                  │" << endl;
	cout << "│    › e : Zoom in                                            │" << endl;
	cout << "│    › q : Zoom out                                           │" << endl;
	cout << "│                                                             │" << endl;
	cout << "│    Scene options                                            │" << endl;
	cout << "│    › l : Load saved camera settings                         │" << endl;
	cout << "│    › p : Save camera settings                               │" << endl;
	cout << "│    › t : Cycle between drawing modes                        │" << endl;
	cout << "│    › 1 : Sets camera to static mode                         │" << endl;
	cout << "│    › 2 : Sets camera to fps mode                            │" << endl;
	cout << "│                                                             │" << endl;
	cout << "│    Press ESC at any time to exit program                    │" << endl;
	cout << "└─────────────────────────────────────────────────────────────┘" << endl;
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

		// put here the registration of the keyboard and mouse callbacks
		glutKeyboardFunc(reactRegularKeys);
		glutMouseFunc(processMouseButtons);
		glutMotionFunc(processMouseMotion);

		//  OpenGL settings
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		// init fps camera
		fps_camera = new fpsCamera(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), FPS_CAMERA_CFG_FILE);
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_HEIGHT)/2);

		// init static camera
		static_camera = new staticCamera(STATIC_CAMERA_CFG_FILE);

		// enter GLUT's main cycle
		glutMainLoop();
    }
	else {
		cout << "Invalid input!\n";
	}

	return 1;
}
