#include "parser.h"

// Function to load a .3d file into a VBO
Model load3dFile(string _3dFile) {
    string line;
    string delim = ", ";
    ifstream file;
	vector<float> points;
	vector<float> normals;
	vector<float> textures;

	file.open(_3dFile.c_str(), ios::in);

	// Get number of points in file
	getline(file, line);
	int nr_points = atoi(line.c_str());

	// Check if there's normals in the file
	getline(file, line);
	bool b_normals;
	line == "true" ? b_normals = true : b_normals = false;

	// Check if there's textures in the file
	getline(file, line);
	bool b_textures;
	line == "true" ? b_textures = true : b_textures = false;

	// Read from file
	if (file.is_open()) {
		// Read points from file
		for (int j = 0; j < nr_points; j++) {
			getline(file, line);
    		
			string token;
    		istringstream tokenStream(line);

    		while (getline(tokenStream, token, ',')) {
				points.push_back(atof(token.c_str()));
			}
		}

		// Read normals from file
		if (b_normals) {
			for (int j = 0; j < nr_points; j++) {
				getline(file, line);
	
				string token;
    			istringstream tokenStream(line);

    			while (getline(tokenStream, token, ',')) {
					normals.push_back(atof(token.c_str()));
				}
			}
		}

		// Read textures from file
		if (b_textures) {
			for (int j = 0; j < nr_points; j++) {
				getline(file, line);
	
				string token;
    			istringstream tokenStream(line);

    			while (getline(tokenStream, token, ',')) {
					textures.push_back(atof(token.c_str()));
				}
			}
		}

		file.close();
	}
	else {
		std::cout << "Unable to open file: " << _3dFile.c_str() << "\n";
	}

	GLsizei vertice_count = (GLsizei) (points.size() / 3);

	GLuint p_vbo_ind;
	GLuint n_vbo_ind = 0;
	GLuint t_vbo_ind = 0;
	
	// Push points to VBO
	glGenBuffers(1, &p_vbo_ind);
	glBindBuffer(GL_ARRAY_BUFFER, p_vbo_ind);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(), GL_STATIC_DRAW);

	if (b_normals) {
		// Push normals to VBO
		glGenBuffers(1, &n_vbo_ind);
		glBindBuffer(GL_ARRAY_BUFFER, n_vbo_ind);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), normals.data(), GL_STATIC_DRAW);
	}

	if (b_textures) {
		// Push textures to VBO
		glGenBuffers(1, &t_vbo_ind);
		glBindBuffer(GL_ARRAY_BUFFER, t_vbo_ind);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * textures.size(), textures.data(), GL_STATIC_DRAW);
	}

	return Model(p_vbo_ind, n_vbo_ind, t_vbo_ind, vertice_count);
}

// Function to parse a float from an element attribute. If the attribute does not exist, returns the default value
float parseFloatFromElementAttribute(const XMLElement* element, string name, float default_value) {
	const XMLAttribute* attribute = element->FindAttribute(name.c_str());
	float value;
	attribute ? value = atof(attribute->Value()) : value = default_value;

	return value;
}

// Function to parse a translate element inside a group element
void parseXMLTranslateElement (XMLElement* translate_element, Group* new_group) {
	// Trying to get time attribute, so we know if it's a static or dynamic translation
	const XMLAttribute* time_attribute = translate_element->FindAttribute("time");

	// Test if we have a dynamic translation
	if (time_attribute) {
		float time = atof(time_attribute->Value());
		vector<Ponto> points = {};

		const XMLAttribute* closed_attribute = translate_element->FindAttribute("closed");
		string closed = closed_attribute->Value();

		// The points describe a closed line, so we need to duplicate some of them
		if (closed.compare("true") == 0) {
			vector<Ponto> temp_points;

			XMLElement* point_element = translate_element->FirstChildElement("point");

			while (point_element) {
				float x_value = atof(point_element->FindAttribute("X")->Value());
				float y_value = atof(point_element->FindAttribute("Y")->Value());
				float z_value = atof(point_element->FindAttribute("Z")->Value());

				temp_points.push_back( Ponto(x_value, y_value, z_value) );

				point_element = point_element->NextSiblingElement("point");
			}

			// Duplicate some points so we get a closed curve
			points.push_back(temp_points.back());
			for (int i = 0; i < temp_points.size(); i++)
				points.push_back(temp_points[i]);
			points.push_back(temp_points[0]);
			points.push_back(temp_points[1]);
		}

		// The points can describe a closed line, but none are duplicated and all are interpretated
		// as part of a Catmull-Rom cubic curve
		else {
			XMLElement* point_element = translate_element->FirstChildElement("point");

			while (point_element) {
				float x_value = atof(point_element->FindAttribute("X")->Value());
				float y_value = atof(point_element->FindAttribute("Y")->Value());
				float z_value = atof(point_element->FindAttribute("Z")->Value());

				points.push_back( Ponto(x_value, y_value, z_value) );

				point_element = point_element->NextSiblingElement("point");
			}
		}
		

		new_group->addDynamicTranslate(time, points);
	}

	// Static translation
	else {
		float x_trans = parseFloatFromElementAttribute(translate_element, "X", 0.0);
		float y_trans = parseFloatFromElementAttribute(translate_element, "Y", 0.0);
		float z_trans = parseFloatFromElementAttribute(translate_element, "Z", 0.0);

		new_group->addTranslate(x_trans, y_trans, z_trans);
	}
}

// Function to parse a rotate element inside a group element
void parseXMLRotateElement (XMLElement* rotate_element, Group* new_group) {

	float axisX_rot = parseFloatFromElementAttribute(rotate_element, "axisX", 0.0);
	float axisY_rot = parseFloatFromElementAttribute(rotate_element, "axisY", 0.0);
	float axisZ_rot = parseFloatFromElementAttribute(rotate_element, "axisZ", 0.0);

	// Trying to get time attribute, so we know if it's a static or dynamic rotation
	const XMLAttribute* time_attribute = rotate_element->FindAttribute("time");

	// Test if we have a dynamic rotation
	if (time_attribute) {
		float time = atof(time_attribute->Value());

		new_group->addDynamicRotate(time, axisX_rot, axisY_rot, axisZ_rot);
	}

	// Static rotation
	else {
		// Get angle attribute
		float angle_rot = parseFloatFromElementAttribute(rotate_element, "angle", 0.0);

		new_group->addRotate(angle_rot, axisX_rot, axisY_rot, axisZ_rot);
	}
}

// Function to parse a scale element inside a group element
void parseXMLScaleElement (XMLElement* scale_element, Group* new_group) {
	
	float x_scale = parseFloatFromElementAttribute(scale_element, "X", 1.0);
	float y_scale = parseFloatFromElementAttribute(scale_element, "Y", 1.0);
	float z_scale = parseFloatFromElementAttribute(scale_element, "Z", 1.0);

	new_group->addScale(x_scale, y_scale, z_scale);
}

// Function to parse ambient attributes in a light or model element
GLfloat* parseAmbientAttributes(XMLElement* element, GLfloat default_value) {
	const XMLAttribute* aux_attribute;
	GLfloat* ambient = new GLfloat[4];
	
	ambient[0] = parseFloatFromElementAttribute(element, "ambiR", default_value);
	ambient[1] = parseFloatFromElementAttribute(element, "ambiG", default_value);
	ambient[2] = parseFloatFromElementAttribute(element, "ambiB", default_value);
	ambient[3] = parseFloatFromElementAttribute(element, "ambiA", 1.0);

	return ambient;
}

// Function to parse diffuse attributes in a light or model element
GLfloat* parseDiffuseAttributes(XMLElement* element, GLfloat default_value) {
	const XMLAttribute* aux_attribute;
	GLfloat* diffuse = new GLfloat[4];
	
	diffuse[0] = parseFloatFromElementAttribute(element, "diffR", default_value);
	diffuse[1] = parseFloatFromElementAttribute(element, "diffG", default_value);
	diffuse[2] = parseFloatFromElementAttribute(element, "diffB", default_value);
	diffuse[3] = parseFloatFromElementAttribute(element, "diffA", 1.0);

	return diffuse;
}

// Function to parse specular attributes in a light or model element
GLfloat* parseSpecularAttributes(XMLElement* element, GLfloat default_value) {
	const XMLAttribute* aux_attribute;
	GLfloat* specular = new GLfloat[4];
	
	specular[0] = parseFloatFromElementAttribute(element, "specR", default_value);
	specular[1] = parseFloatFromElementAttribute(element, "specG", default_value);
	specular[2] = parseFloatFromElementAttribute(element, "specB", default_value);
	specular[3] = parseFloatFromElementAttribute(element, "specA", 1.0);

	return specular;
}

// Function to parse emissive attributes in a model element
GLfloat* parseEmissiveAttributes(XMLElement* element, GLfloat default_value) {
	const XMLAttribute* aux_attribute;
	GLfloat* emissive = new GLfloat[4];
	
	emissive[0] = parseFloatFromElementAttribute(element, "emisR", default_value);
	emissive[1] = parseFloatFromElementAttribute(element, "emisG", default_value);
	emissive[2] = parseFloatFromElementAttribute(element, "emisB", default_value);
	emissive[3] = parseFloatFromElementAttribute(element, "emisA", 1.0);

	return emissive;
}

// Function to parse a group element in a xml file
Group parseXMLGroupElement (XMLElement* main_element) {
	Group new_group = Group();

	XMLElement* generic_element = main_element->FirstChildElement();

	while(generic_element) {
		const char* name = generic_element->Name();

		if (strcmp(name, "translate") == 0) {
			parseXMLTranslateElement(generic_element, &new_group);
		}
		else if (strcmp(name, "rotate") == 0) {
			parseXMLRotateElement(generic_element, &new_group);
		}
		else if (strcmp(name, "scale") == 0) {
			parseXMLScaleElement(generic_element, &new_group);
		}

		generic_element = generic_element->NextSiblingElement();
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
			Model model;

			// Parse model file attribute
			const XMLAttribute* file_attribute = model_element->FindAttribute("file");
			if (file_attribute) {
				string file = file_attribute->Value();
				model = load3dFile(_3DFILESFOLDER + file);

				// Get diffuse attributes
				GLfloat* diffuse = parseDiffuseAttributes(model_element, 0.8);
				model.setDiffuse(diffuse);

				// Get specular attributes
				GLfloat* specular = parseSpecularAttributes(model_element, 0.0);
				model.setSpecular(specular);

				// Get emissive attributes
				GLfloat* emissive = parseEmissiveAttributes(model_element, 0.0);
				model.setEmissive(emissive);

				// Get ambient attributes
				GLfloat* ambient = parseAmbientAttributes(model_element, 0.2);
				model.setAmbient(ambient);

				// Get texture attribute
				const XMLAttribute* texture_attribute = model_element->FindAttribute("texture");
				string texture_file;
				texture_attribute ? texture_file = texture_attribute->Value() : texture_file = "";
				
				model.loadTexture(texture_file);
				
				new_group.addModel(model);
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

// Function to parse a group element in a xml file
Light* parseXMLLightElement (XMLElement* light_element, int light_ind) {
	Light* new_light = nullptr;

	// Get light type: POINT, DIRECTIONAL or SPOT
	const XMLAttribute* type_attribute = light_element->FindAttribute("type");
	const char* light_type = type_attribute->Value();

	// Get ambient attributes
	GLfloat* ambient = parseAmbientAttributes(light_element, 0.0);

	// Get diffuse attributes
	GLfloat* diffuse = parseDiffuseAttributes(light_element, 1.0);

	// Get specular attributes
	GLfloat* specular = parseSpecularAttributes(light_element, 1.0);

	if (strcmp(light_type, "POINT") == 0) {
		float posX = parseFloatFromElementAttribute(light_element, "posX", 0.0);
		float posY = parseFloatFromElementAttribute(light_element, "posY", 0.0);
		float posZ = parseFloatFromElementAttribute(light_element, "posZ", 0.0);

		new_light = new LightPoint(light_ind, new Ponto(posX, posY, posZ), ambient, diffuse, specular);
	}
	else if (strcmp(light_type, "DIRECTIONAL") == 0) {
		float dirX = parseFloatFromElementAttribute(light_element, "dirX", 0.0);
		float dirY = parseFloatFromElementAttribute(light_element, "dirY", 0.0);
		float dirZ = parseFloatFromElementAttribute(light_element, "dirZ", 1.0);

		new_light = new LightDirectional(light_ind, new Ponto(dirX, dirY, dirZ), ambient, diffuse, specular);
	}
	else if (strcmp(light_type, "SPOT") == 0) {
		float posX = parseFloatFromElementAttribute(light_element, "posX", 0.0);
		float posY = parseFloatFromElementAttribute(light_element, "posY", 0.0);
		float posZ = parseFloatFromElementAttribute(light_element, "posZ", 0.0);

		float dirX = parseFloatFromElementAttribute(light_element, "dirX", 0.0);
		float dirY = parseFloatFromElementAttribute(light_element, "dirY", 0.0);
		float dirZ = parseFloatFromElementAttribute(light_element, "dirZ", -1.0);

		float cutoff = parseFloatFromElementAttribute(light_element, "cutoff", 180.0);

		new_light = new LightSpot(light_ind, new Ponto(posX, posY, posZ), new Ponto(dirX, dirY, dirZ), cutoff, ambient, diffuse, specular);
	}

	return new_light;
}

// Function to parse a xml file
int loadXMLFile(string xmlFileString, vector<Group>* groups_vector, vector<Light*>* lights_vector) {
	XMLDocument doc;
	vector<string> _3dFilesList;

	// Trying to open XML File
	XMLError load_result = doc.LoadFile(xmlFileString.c_str());
	if (load_result != XML_SUCCESS)  {
		std::cout << "Unable to load XML File!\n";
		return 0;
	}

	// Trying to get scene element
	XMLElement* root = doc.FirstChildElement("scene");
	if (root == nullptr) {
		std::cout << "XML File has wrong sintax! -> scene element\n";
		return 0;
	}

	// Trying to get lights element
	XMLElement* lights_element = root->FirstChildElement("lights");
	if (lights_element) {
		int light_ind = 0;
		
		XMLElement* light_element = lights_element->FirstChildElement("light");
		while (light_element) {
			Light* l = parseXMLLightElement(light_element, light_ind);
			lights_vector->push_back(l);

			light_element = light_element->NextSiblingElement("light");
			light_ind++;
		}

		Group g = parseXMLGroupElement(lights_element);
		groups_vector->push_back(g);
	}

	// Trying to get all group elements
	XMLElement* group_element = root->FirstChildElement("group");
	while (group_element) {
		Group g = parseXMLGroupElement(group_element);
		groups_vector->push_back(g);

		group_element = group_element->NextSiblingElement("group");
	}

	return 1;
}
