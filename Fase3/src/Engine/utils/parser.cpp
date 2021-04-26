#include "parser.h"

// Function to load a .3d file into a VBO
Model load3dFile(string _3dFile) {
    string line;
    string delim = ", ";
    ifstream file;
	vector<float> points;

	file.open(_3dFile.c_str(), ios::in);
	getline(file, line);
	int nr_points = atoi(line.c_str());

	if (file.is_open()) {
		for (int j = 0; j < nr_points; j++) {
			getline(file, line);
    		
			string token;
    		istringstream tokenStream(line);

    		while (getline(tokenStream, token, ',')) {
				points.push_back(atof(token.c_str()));
			}
		}
		file.close();
	}
	else {
		std::cout << "Unable to open file: " << _3dFile.c_str() << "\n";
	}

	GLuint vertice_count = (GLuint) (points.size() / 3);
	GLuint vbo_ind;

	glGenBuffers(1, &vbo_ind);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_ind);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), points.data(), GL_STATIC_DRAW);

	return Model(vbo_ind, vertice_count);
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

		new_group->addTranslate(x_trans, y_trans, z_trans);
	}
}

// Function to parse a rotate element inside a group element
void parseXMLRotateElement (XMLElement* rotate_element, Group* new_group) {
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
		const XMLAttribute* angle_attribute = rotate_element->FindAttribute("angle");
		float angle_rot;
		angle_attribute ? angle_rot = atof(angle_attribute->Value()) : angle_rot = 0;

		new_group->addRotate(angle_rot, axisX_rot, axisY_rot, axisZ_rot);
	}
}

// Function to parse a scale element inside a group element
void parseXMLScaleElement (XMLElement* scale_element, Group* new_group) {
	// Get x attribute
	const XMLAttribute* x_attribute = scale_element->FindAttribute("X");
	float x_scale;
	x_attribute ? x_scale = atof(x_attribute->Value()) : x_scale = 1;

	// Get y attribute
	const XMLAttribute* y_attribute = scale_element->FindAttribute("Y");
	float y_scale;
	y_attribute ? y_scale = atof(y_attribute->Value()) : y_scale = 1;

	// Get z attribute
	const XMLAttribute* z_attribute = scale_element->FindAttribute("Z");
	float z_scale;
	z_attribute ? z_scale = atof(z_attribute->Value()) : z_scale = 1;

	new_group->addScale(x_scale, y_scale, z_scale);
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
			}

			new_group.addModel(model);

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


// Function to parse a xml file
int loadXMLFile(string xmlFileString, vector<Group>* groups_vector) {
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

	// Trying to get all group elements
	XMLElement* group_element = root->FirstChildElement("group");
	while (group_element) {
		Group g = parseXMLGroupElement(group_element);
		groups_vector->push_back(g);

		group_element = group_element->NextSiblingElement("group");
	}

	return 1;
}
