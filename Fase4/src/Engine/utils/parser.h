#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "model.h"
#include "group.h"
#include "../../lib/tinyxml2.h"

#define _3DFILESFOLDER "../../files3D/"

using namespace tinyxml2;
using namespace std;

int loadXMLFile(string xmlFileString, vector<Group>* groups_vector);

#endif //PARSER_H
