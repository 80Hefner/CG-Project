#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>


float cx = 0;
float cy = 0;
float cz = 0;

float rx = 0;
float ry = 0;
float rz = 0;

float tallness = 0;

GLenum modo = GL_FILL;

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


void desenhaEixo(void) {
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


void desenhaPiramide(void) {
	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);

	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);


	glColor3f(0.5f, 1.0f, 0.5f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);

	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glEnd();
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	desenhaEixo();
	

// put the geometric transformations here
	
	// Trnaslação
	glTranslatef(cx, cy, cz);

	//Rotação (apesar de rx e rz ficar constante, com a implementação só alteramos ry)
	glRotatef(rx, 1, 0, 0);
	glRotatef(ry, 0, 1, 0);
	glRotatef(rz, 0, 0, 1);

	//Escala
	glScalef(1.0,1.0+tallness,1.0);


// put drawing instructions here
	desenhaPiramide();

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events

	//Reage a eventos de special keys (setas, Home, etc.)
void reageEvento(int key_code, int x, int y) {
	switch (key_code) {
		case GLUT_KEY_LEFT:
			cz+=0.1f;
			break;
		case GLUT_KEY_UP:
			cx-=0.1f;
			break;
		case GLUT_KEY_RIGHT:
			cz-=0.1f;
			break;
		case GLUT_KEY_DOWN:
			cx+=0.1f;
			break;
	}
	glutPostRedisplay();
}

	//Reage a eventos de regular keys (letras, numeros, etc.)
void reageEventoChar(unsigned char key, int x, int y) {
	switch (key) {
		case 'q':
			ry += 5.0f;
			break;
		case 'e':
			ry -= 5.0f;
			break;
		case 'w':
			tallness += 0.1f;
			break;
		case 's':
			if (tallness >= -0.5f) tallness -= 0.1f;
			break;
		case 't':
			if (modo == GL_FILL) modo = GL_LINE;
			else if (modo == GL_LINE) modo = GL_POINT;
			else if (modo == GL_POINT) modo = GL_FILL;

			glPolygonMode(GL_FRONT,modo);
			break;
		case 27:
			exit(0);
			break;
	}
	glutPostRedisplay();
}






int main(int argc, char **argv) {

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
	glutSpecialFunc(reageEvento);
	glutKeyboardFunc(reageEventoChar);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
