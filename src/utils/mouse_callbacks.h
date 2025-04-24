#ifndef MOUSECALLBACKS
#define MOUSECALLBACKS


#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

extern float zoom;
extern bool firstMouse;
extern float lastX;
extern float lastY;
extern float vertical;
extern float horizontal;
extern glm::vec3 cameraFront;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

#endif // !MOUSECALLBACKS
