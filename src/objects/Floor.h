#ifndef FLOOR
#define FLOOR

#include "Object.h"

class Floor: public Object{
public:

    Floor(const char* vertexPath, const char* fragmentPath, float size, glm::vec3 pos, glm::vec3 color)
        : Object(vertexPath, fragmentPath, size, pos, color) {}

    Floor(const char* vertexPath, const char* fragmentPath, float size, glm::vec3 pos)
        : Object(vertexPath, fragmentPath, size, pos) {}

    Floor(const char* vertexPath, const char* fragmentPath, glm::vec3 pos)
        : Object(vertexPath, fragmentPath, pos) {}

private:
    void gen_vertex_n_indices(float size, std::vector<float>& vertices, std::vector<unsigned int>& indices) override
    {
        float half = size / 2.0f;

        float verts[] = {
            -half, -1.0f, -half,
             half, -1.0f, -half,
             half, -1.0f,  half,
            -half, -1.0f,  half
        };

        vertices.assign(verts, verts + 12);

        unsigned int inds[] = {
            0, 1, 2,
            2, 3, 0
        };

        indices.assign(inds, inds + 6);
    }

};

#endif // !DEBUG
