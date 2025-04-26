#ifndef OBJECT
#define OBJECT

#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>
#include "../include/shader.h"
#include "glm/ext/matrix_transform.hpp"

class Object{
public:
    Shader* shader;
    float size;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    glm::vec3 position;
    glm::vec3 color;
    unsigned VBO, VAO, EBO;

    Object(const char* vertexPath, const char* fragmentPath, float size, glm::vec3 pos, glm::vec3 color)
        : position(pos), color(color), size(size)
    {
        shader = new Shader(vertexPath, fragmentPath);
    }

    Object(const char* vertexPath, const char* fragmentPath, float size, glm::vec3 pos)
        : position(pos), size(size)
    {
        shader = new Shader(vertexPath, fragmentPath);
        this->color = glm::vec3(0.9f, 0.2f, 0.8f);
    }

    Object(const char* vertexPath, const char* fragmentPath, glm::vec3 pos)
        : position(pos)
    {
        shader = new Shader(vertexPath, fragmentPath);
        this->color = glm::vec3(0.9f, 0.2f, 0.8f);
    }

    void display(const glm::mat4& projection, const glm::mat4& view){
        shader->use();

        shader->setMat4("projection", projection);
        shader->setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        shader->setMat4("model", model);

        // Draw filled
        glEnable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        shader->setVec3("color", color);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // Draw triangle lines 
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_DEPTH_TEST);
        shader->setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    void initialize(float size)
    {
        gen_vertex_n_indices(size, vertices, indices);
        setupMesh();
    }

    void initialize()
    {
        gen_vertex_n_indices(size, vertices, indices);
        setupMesh();
    }

    ~Object(){
        delete shader;
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

private:

    void setupMesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    virtual void gen_vertex_n_indices(float size, std::vector<float>& vertices, std::vector<unsigned int>& indices) = 0;
};

#endif // !OBJECT
