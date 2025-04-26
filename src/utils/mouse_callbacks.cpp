#include "mouse_callbacks.h"
#include "GLFW/glfw3.h"

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    zoom -= (float)yoffset;

    if (zoom >= 1.0f)
        zoom -= yoffset;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 150.0f)
        zoom = 150.0f;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
    {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS)
        {
            firstMouse = true;
            return;
        }
    }

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.2f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    vertical   += xoffset;
    horizontal += yoffset;

    if(horizontal > 89.0f) horizontal = 89.0f;
    if(horizontal < -89.0f) horizontal = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(vertical)) * cos(glm::radians(horizontal));
    front.y = sin(glm::radians(horizontal));
    front.z = sin(glm::radians(vertical)) * cos(glm::radians(horizontal));
    cameraFront = glm::normalize(front);
}
