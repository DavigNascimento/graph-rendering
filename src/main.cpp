#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "../include/shader.h" // A utility to load vertex/fragment shaders
#include "utils/mouse_callbacks.h"
#include "utils/process_input.h"

unsigned int SCR_WIDTH = 1200;
unsigned int SCR_HEIGHT = 900;

// Camera
glm::vec3 cameraPos   = glm::vec3(1.0f, 1.5f, 4.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float vertical   = -90.0f;
float horizontal = 0.0f;
bool firstMouse = true;

float deltaTime = 0.1f; // time between current frame and last frame
float lastFrame = 0.0f;

float zoom = 60.0f;

bool cursor = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D Cube with Camera", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader shader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        4, 7, 3, 3, 0, 4,
        1, 5, 6, 6, 2, 1,
        3, 2, 6, 6, 7, 3,
        4, 5, 1, 1, 0, 4
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInputStandard(window, deltaTime);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 projection = glm::perspective(glm::radians(zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        // Create model matrix (identity for now)
        glm::mat4 model = glm::mat4(1.0f);
        shader.setMat4("model", model);

        // Draw the solid cube (filled)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        shader.setVec3("color", glm::vec3(0.9f, 0.2f, 0.8f));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // Draw cube triangle lines
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_DEPTH_TEST);
        shader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        





        // Reset to default state (filled rendering)

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        {
            if(cursor) 
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                cursor = false;
            }
            else
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                cursor = true;
            }
        }



        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport(0, 0, width, height);
}

