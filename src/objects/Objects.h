#ifndef OBJECTS
#define OBJECTS

#include "Object.h"
#include <vector>

class Objects {
public:
    std::vector<Object*> objects;

    Objects() = default;

    ~Objects() {
        for (auto obj : objects) {
            delete obj;
        }
        objects.clear();
    }

    void add(Object* obj, float size) {
        obj->initialize(size);
        objects.push_back(obj);
    }

    void add(Object* obj) {
        obj->initialize();
        objects.push_back(obj);
    }

    void initializeAll() {
        for (auto obj : objects) {
            obj->initialize();  // calls each object's initialize()
        }
    }

    void displayAll(const glm::mat4& projection, const glm::mat4& view) {
        for (auto obj : objects) {
            obj->display(projection, view);
        }
    }

    void updatePos(int idx, glm::vec3 newPos)
    {
        Object* sel = objects[idx];
        sel->position = newPos;
    }

};

#endif // !OBJECTST
