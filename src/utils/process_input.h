#ifndef PROCESSINPUT
#define PROCESSINPUT

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;
extern glm::vec3 cameraPos;

void processInput(GLFWwindow* window, float deltaTime);


#endif // !PROCESSINPUT
