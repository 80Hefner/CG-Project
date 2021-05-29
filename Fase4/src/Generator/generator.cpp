#include <vector>
#include <map>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../utils/ponto.h"
#include "primitives.h"
#include "../lib/Matrix.tpp"

#define _3DFILESFOLDER "../../files3D/"
#define PATCHFILESFOLDER "../../filesPATCH/"

using namespace std;


void writePointsToFile(vector<Ponto> points, vector<Ponto>* normals, string fileString) {
    ofstream file;

    // Write number of points to file
    file.open(fileString, ios::out | ios::trunc);
    file << points.size() << "\n";

    // Write true or false indicating if there's normals associated with the points
    normals ? file << "true\n" : file << "false\n";

    for(Ponto p : points) {
        float px = p.getX();
        float py = p.getY();
        float pz = p.getZ();

        string line = to_string(px) + ", " + to_string(py) + ", " + to_string(pz) + "\n";
        file << line;
    }

    if (normals) {
        for(Ponto n : *normals) {
            float nx = n.getX();
            float ny = n.getY();
            float nz = n.getZ();

            string line = to_string(nx) + ", " + to_string(ny) + ", " + to_string(nz) + "\n";
            file << line;
        }
    }

    file.close();
}

void generatorHelpMenu() {
	cout << "┌───────────────────────────────────────GENERATOR HELP───────────────────────────────────────┐" << endl;
	cout << "│   Usage: ./generator [SHAPE]... [OUTPUT FILE]                                              │" << endl;
	cout << "│   Generates a .3d file, ready to be readen by the engine                                   │" << endl;
	cout << "│                                                                                            │" << endl;
	cout << "│   SHAPE                                                                                    │" << endl;
	cout << "│      plane [SIZE]                                                                          │" << endl;
	cout << "│          Creates a square in the XZ plane, centred in the origin, with given size.         │" << endl;
    cout << "│                                                                                            │" << endl;
    cout << "│      box [X_DIM] [Y_DIM] [Z_DIM] <optional>[DIVISIONS]                                     │" << endl;
	cout << "│          Creates a box with given dimensions, optionally divided in given divisions.       │" << endl;
	cout << "│                                                                                            │" << endl;
    cout << "│      sphere [RADIUS] [SLICES] [STACKS]                                                     │" << endl;
    cout << "│          Creates a sphere with given radius, divided in given slices and stacks.           │" << endl;
    cout << "│                                                                                            │" << endl;
    cout << "│      cone [RADIUS] [HEIGHT] [SLICES] [STACKS]                                              │" << endl;
    cout << "│          Creates a cone with given radius and height, divided in given slices and stacks.  │" << endl;
    cout << "│                                                                                            │" << endl;
    cout << "│      torus [INNER_RADIUS] [OUTER_RADIUS] [SLICES] [STACKS]                                 │" << endl;
    cout << "│          Creates a torus with given radiuses, divided in given slices and stacks.          │" << endl;
	cout << "└────────────────────────────────────────────────────────────────────────────────────────────┘" << endl;
}


void bezierTo3DFile(string patchFile, int tess_level, vector<Ponto>* ps, vector<Ponto>* ns) {
    string line;
    ifstream file;

    map<int, vector<int>> patches;
    vector<Ponto> control_points;
    int nr_patches, nr_control_points;

    // Parsing of patch file
	file.open(patchFile.c_str(), ios::in);
    if (file.is_open()) {
        // Patches parsing
        getline(file, line);
        nr_patches = atoi(line.c_str());

        for (int i = 0; i < nr_patches; i++) {
            getline(file, line);
            vector<int> patch;

            string token;
            istringstream tokenStream(line);

    		while (getline(tokenStream, token, ',')) {
				int index = atoi(token.c_str());
                patch.push_back(index);
			}

            patches[i] = patch;
        }


        // Control points parsing
        getline(file, line);
        nr_control_points = atoi(line.c_str());

        for (int i = 0; i < nr_control_points; i++) {
            getline(file, line);
            Ponto point = Ponto(line);

            control_points.push_back(point);
        }

        file.close();
    }
	else {
		std::cout << "Unable to open file: " << patchFile.c_str() << "\n";
	}


    // Calculate Bezier Surfaces
    vector<Ponto> result_points;
    vector<Ponto> result_normals;

    // Processing of each patch
    for (int i_p = 0; i_p < nr_patches; i_p++) {
        vector<int> patch = patches[i_p];
        vector<Ponto> cps;          // patch control points
        vector<Ponto> grid_points;  // points obtained from control points

        // Get control points for this patch
        for (int i_pp = 0; i_pp < patch.size(); i_pp++) {
            cps.push_back(control_points[patch[i_pp]]);
        }

        // Initialize matrices to calculate bezier surface points
        Matrix<float> m = {{-1.0f,  3.0f, -3.0f,  1.0f},
                           { 3.0f, -6.0f,  3.0f,  0.0f},
                           {-3.0f,  3.0f,  0.0f,  0.0f},
                           { 1.0f,  0.0f,  0.0f,  0.0f}};

        Matrix<float> m_px = {{cps[0].getX(), cps[1].getX(), cps[2].getX(), cps[3].getX()},
                              {cps[4].getX(), cps[5].getX(), cps[6].getX(), cps[7].getX()},
                              {cps[8].getX(), cps[9].getX(), cps[10].getX(), cps[11].getX()},
                              {cps[12].getX(), cps[13].getX(), cps[14].getX(), cps[15].getX()}};

        Matrix<float> m_py = {{cps[0].getY(), cps[1].getY(), cps[2].getY(), cps[3].getY()},
                              {cps[4].getY(), cps[5].getY(), cps[6].getY(), cps[7].getY()},
                              {cps[8].getY(), cps[9].getY(), cps[10].getY(), cps[11].getY()},
                              {cps[12].getY(), cps[13].getY(), cps[14].getY(), cps[15].getY()}};

        Matrix<float> m_pz = {{cps[0].getZ(), cps[1].getZ(), cps[2].getZ(), cps[3].getZ()},
                              {cps[4].getZ(), cps[5].getZ(), cps[6].getZ(), cps[7].getZ()},
                              {cps[8].getZ(), cps[9].getZ(), cps[10].getZ(), cps[11].getZ()},
                              {cps[12].getZ(), cps[13].getZ(), cps[14].getZ(), cps[15].getZ()}};

        Matrix<float> m_x = m * m_px * m;
        Matrix<float> m_y = m * m_py * m ;
        Matrix<float> m_z = m * m_pz * m;
        

        // Give values to u and v to calculate grid points
        float inc = 1.0 / tess_level;
        for (float v = 0.0; v <= 1.0; v += inc) {
            for (float u = 0.0; u <= 1.0; u += inc) {
                Matrix<float> m_u = {{u*u*u, u*u, u, 1.0f}};

                Matrix<float> m_v = {{v*v*v},
                                     {v*v},
                                     {v},
                                     {1.0f}};
                
                float x_value = (m_u * m_x * m_v)[0][0];
                float y_value = (m_u * m_y * m_v)[0][0];
                float z_value = (m_u * m_z * m_v)[0][0];

                grid_points.push_back(Ponto(x_value, y_value, z_value));
            }
        }


        // Write triangles correspondent to the grid
        for (int v_ind = 0; v_ind < tess_level; v_ind++) {
            for (int u_ind = 0; u_ind < tess_level; u_ind++) {
                int points_per_line = tess_level + 1;
                Ponto p0 = grid_points[u_ind   + v_ind     * points_per_line];
                Ponto p1 = grid_points[u_ind+1 + v_ind     * points_per_line];
                Ponto p2 = grid_points[u_ind   + (v_ind+1) * points_per_line];
                Ponto p3 = grid_points[u_ind+1 + (v_ind+1) * points_per_line];

                result_points.push_back(p0); result_points.push_back(p2); result_points.push_back(p1);
                result_points.push_back(p1); result_points.push_back(p2); result_points.push_back(p3);

                result_normals.push_back(calculate_normal(p0, p2, p1));
                result_normals.push_back(calculate_normal(p2, p1, p0));
                result_normals.push_back(calculate_normal(p1, p0, p2));

                result_normals.push_back(calculate_normal(p1, p2, p3));
                result_normals.push_back(calculate_normal(p2, p3, p1));
                result_normals.push_back(calculate_normal(p3, p1, p2));
            }
        }

    }

    *ps = result_points;
    *ns = result_normals;
}

int main(int argc, char** argv) {

    vector<Ponto> points;
    vector<Ponto> normals;
    string fileString;

    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        generatorHelpMenu();
    }
    else if (argc == 4 && strcmp(argv[1], "plane") == 0) {
        float size = atof(argv[2]);
        points = plane(size);

        fileString = argv[3];
        fileString = _3DFILESFOLDER + fileString;

        writePointsToFile(points, nullptr, fileString);
    }
    else if (argc >= 6 && strcmp(argv[1], "box") == 0) {
        int i = 2;
        float dimX = atof(argv[i++]); // i=2
        float dimY = atof(argv[i++]); // i=3
        float dimZ = atof(argv[i++]); // i=4
        int divisions = 1;
        if (argc == 7) divisions = atoi(argv[i++]); // i=5
        points = box(dimX, dimY, dimZ, divisions);

        fileString = argv[i]; // i=5 or 6
        fileString = _3DFILESFOLDER + fileString;

        writePointsToFile(points, nullptr, fileString);
    }
    else if (argc == 7 && strcmp(argv[1], "cone") == 0) {
        float radius = atof(argv[2]);
        float height = atof(argv[3]);
        int slices = atoi(argv[4]);
        int stacks = atoi(argv[5]);

        points = cone(radius, height, slices, stacks);

        fileString = argv[6];
        fileString = _3DFILESFOLDER + fileString;

        writePointsToFile(points, nullptr, fileString);
    }
    else if (argc == 6 && strcmp(argv[1], "sphere") == 0) {
        float radius = atof(argv[2]);
        int slices = atoi(argv[3]);
        int stacks = atoi(argv[4]);

        sphere(radius, slices, stacks, &points, &normals);

        fileString = argv[5];
        fileString = _3DFILESFOLDER + fileString;

        writePointsToFile(points, &normals, fileString);
    }
    else if (argc == 7 && strcmp(argv[1], "torus") == 0) {
        float innerRadius = atof(argv[2]);
        float outerRadius = atof(argv[3]);
        int slices = atoi(argv[5]);
        int stacks = atoi(argv[4]);

        torus(innerRadius, outerRadius, slices, stacks, &points, &normals);

        fileString = argv[6];
        fileString = _3DFILESFOLDER + fileString;

        writePointsToFile(points, &normals, fileString);
    }
    else if (argc == 5 && strcmp(argv[1], "--bezier") == 0) {
        string patchFileString = argv[2];
        int tess_level = atoi(argv[3]);
        string _3dFileString = argv[4];
        
        patchFileString = PATCHFILESFOLDER + patchFileString;
        bezierTo3DFile(patchFileString, tess_level, &points, &normals);
        
        _3dFileString = _3DFILESFOLDER + _3dFileString;
        writePointsToFile(points, &normals, _3dFileString);
    }

}
