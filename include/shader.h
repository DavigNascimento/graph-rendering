#ifndef SHADER_H
#define SHADER_H

#include <cstdio>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int ID;

    Shader();

    Shader(const char* vertexPath, const char* fragmentPath) {
        std::string vertexCode, fragmentCode;

        std::ifstream vShaderFile(vertexPath);
        std::ifstream fShaderFile(fragmentPath);

        if (!vShaderFile.is_open()) {
            std::cerr << "Failed to open vertex shader file: " << vertexPath << std::endl;
            vertexCode = "#version 330 core\nlayout(location=0) in vec3 aPos;\n"
                "uniform mat4 model;\n"
                "uniform mat4 view;\n"
                "uniform mat4 projection;\n"
                "void main() {\n"
                "gl_Position = projection * view * model * vec4(aPos, 1.0); }";
        } else {
            std::stringstream vShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            vertexCode = vShaderStream.str();
        }

        if (!fShaderFile.is_open()) {
            std::cerr << "Failed to open fragment shader file: " << fragmentPath << std::endl;
            fragmentCode = "#version 330 core\nout vec4 FragColor;\n"
                "void main() { FragColor = vec4(1.0, 0.0, 0.0, 1.0); }"; // fallback: red
        } else {
            std::stringstream fShaderStream;
            fShaderStream << fShaderFile.rdbuf();
            fragmentCode = fShaderStream.str();
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "VERTEX SHADER COMPILATION FAILED:\n" << infoLog << std::endl;
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "FRAGMENT SHADER COMPILATION FAILED:\n" << infoLog << std::endl;
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "SHADER PROGRAM LINKING FAILED:\n" << infoLog << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use() {
        glUseProgram(ID);
    }

    void setMat4(const std::string& name, const glm::mat4& mat) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }

    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
};

#endif
