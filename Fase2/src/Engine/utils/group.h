#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>

using namespace std;

class Translate {
    public:
        float x, y, z;
        Translate();
        Translate(float x, float y, float z);
};

class Rotate {
    public:
        float angle, axisX, axisY, axisZ;
        Rotate();
        Rotate(float angle, float axisX, float axisY, float axisZ);
};

class Group {
    private:
        Translate translate;
        Rotate rotate;
        vector<string> _3dFilesList;
        vector<Group> groups;
    public:
        Group();
        void setTranslate(float x, float y, float z);
        void setRotate(float angle, float axisX, float axisY, float axisZ);
        void add3dFile(string file);
        void addGroup(Group group);
};

#endif //GROUP_H
