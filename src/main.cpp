#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "glm/fwd.hpp"
#include "objects/Floor.h"
#include "objects/Objects.h"
#include "utils/mouse_callbacks.h"
#include "utils/process_input.h"
#include "objects/Cube.h"

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

float zoom = 80.0f;

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

    Objects ObjHandler;

    Floor* floor = new Floor("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl", 50.0f, glm::vec3(cameraPos.x, 0.0f, cameraPos.z), glm::vec3(0.2f, 0.4f, 0.1f));
    ObjHandler.add(floor);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInputStandard(window, deltaTime);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);




        ObjHandler.updatePos(0, cameraPos);
        ObjHandler.displayAll(projection, view);


        static double lastPressTime = 0.0;
        double currentTime = glfwGetTime();
        if(currentTime - lastPressTime >= 0.08)
        {
            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            {
                glfwSetWindowShouldClose(window, true);
            }
            if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
            {
                Cube* obj = new Cube("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl", 1.0f, cameraPos);
                obj->initialize();
                ObjHandler.add(obj);
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
            lastPressTime = currentTime;
        }


        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    glViewport(0, 0, width, height);
}

