#ifndef CUBE
#define CUBE

#include <glm/glm.hpp>
#include <vector>
#include "Object.h"

class Cube : public Object{
public:

    Cube(const char* vertexPath, const char* fragmentPath, float size, glm::vec3 pos, glm::vec3 color)
        : Object(vertexPath, fragmentPath, size, pos, color) {}

    Cube(const char* vertexPath, const char* fragmentPath, float size, glm::vec3 pos)
        : Object(vertexPath, fragmentPath, size, pos) {}

    Cube(const char* vertexPath, const char* fragmentPath, glm::vec3 pos)
        : Object(vertexPath, fragmentPath, pos) {}

private:
    void gen_vertex_n_indices(float size, std::vector<float>& vertices, std::vector<unsigned int>& indices) override {
        float h = size / 2.0f;

        float verts[] = {
            -h, -h, -h,  h, -h, -h,  h,  h, -h, -h,  h, -h,
            -h, -h,  h,  h, -h,  h,  h,  h,  h, -h,  h,  h
        };

        vertices.assign(verts, verts + 24);

        unsigned int inds[] = {
            0, 1, 2, 2, 3, 0,
            1, 5, 6, 6, 2, 1,
            5, 4, 7, 7, 6, 5,
            4, 0, 3, 3, 7, 4,
            3, 2, 6, 6, 7, 3,
            4, 5, 1, 1, 0, 4
        };

        indices.assign(inds, inds + 36);
    }
};

#endif // !CUBE

