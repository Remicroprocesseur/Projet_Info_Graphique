#ifndef VIEWER_H
#define VIEWER_H

#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "node.h"

class Viewer
{
public:
    Viewer(int width = 640, int height = 480);

    void run();
    void on_key(int key);
    void on_mouse(double xpos, double ypos);

    Node *scene_root;

private:
    GLFWwindow *win;
    static void key_callback_static(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void mouse_callback_static(GLFWwindow *window, double xpos, double ypos);
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    bool firstMouse = true;
    float lastX, lastY;
    float yaw = -90.0f; // angle de rotation autour de l'axe x
    float pitch = 0.0f; // angle de rotation autour de l'axe y
};

#endif // VIEWER_H