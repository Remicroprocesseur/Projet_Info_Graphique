#include "viewer.h"

#include <iostream>
#include <glm/glm.hpp>
#include "glm/ext.hpp"
#include <glm/gtc/matrix_transform.hpp>

Viewer::Viewer(int width, int height)
{
    if (!glfwInit()) // initialize window system glfw
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        glfwTerminate();
    }

    // version hints: create GL window with >= OpenGL 3.3 and core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    win = glfwCreateWindow(width, height, "Viewer", NULL, NULL);

    if (win == NULL)
    {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
    }

    // make win's OpenGL context current; no OpenGL calls can happen before
    glfwMakeContextCurrent(win);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
    }

    // initialize the last mouse positions (the center of the screen)
    lastX = width / 2;
    lastY = height / 2;

    // Set user pointer for GLFW window to this Viewer instance
    glfwSetWindowUserPointer(win, this);

    // tell GLFW that it should hide the cursor and capture it
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // register event handlers
    glfwSetKeyCallback(win, key_callback_static);
    glfwSetCursorPosCallback(win, mouse_callback_static);

    // useful message to check OpenGL renderer characteristics
    std::cout << glGetString(GL_VERSION) << ", GLSL "
              << glGetString(GL_SHADING_LANGUAGE_VERSION) << ", Renderer "
              << glGetString(GL_RENDERER) << std::endl;

    // initialize GL by setting viewport and default render characteristics
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

    /* tell GL to only draw onto a pixel if the shape is closer to the viewer
    than anything already drawn at that pixel */
    glEnable(GL_DEPTH_TEST); /* enable depth-testing */
    /* with LESS depth-testing interprets a smaller depth value as meaning "closer" */
    glDepthFunc(GL_LESS);

    // initialize our scene_root
    scene_root = new Node();
}

void Viewer::run()
{
    //human parts
    Node* human = this->scene_root->getchildren()[1];

    //human state
    float human_rot = 0.0f;
    float current_x = 0.0f;
    float current_z = 0.0f;
    int trajectory_number = 1;
    bool trajectory_return = false;

    float speed = 0.001;

    // Main render loop for this OpenGL window
    while (!glfwWindowShouldClose(win))
    {

        // clear draw buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*character's movement*/

        glm::mat4 model_human = glm::mat4(1.0f);

        //trajectory definition

        //trajectory 1
        if(trajectory_number == 1)
        {
            if(!trajectory_return)
            {
                if(current_z<=12.0f)
                {
                    model_human = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.001f));
                    human->movement(model_human);
                    current_z+=speed;
                }
                else
                {
                    if(current_x>=-13.0f)
                    {
                        
                        if(human_rot>-90.0f) //On fait rotater le personnage de 90° sur la droite si cela n'a pas déjà été fait
                        {
                            glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                            glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                            model_human = back1
                                * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                                * transl_origin1;
                            human_rot = human_rot - 90.0f;
                        }
                        
                        model_human = glm::translate(glm::mat4(1.0f), glm::vec3(-0.001f, 0.0f, 0.0f)) * model_human;
                        human->movement(model_human);
                        current_x-=speed;
                    }
                    else
                    {
                        trajectory_return = true;
                    }
                }
            }
            else
            {
                if(current_x<0.0f)
                {
                    //rajouter une rotation de 180° au bonhomme                 
                    if(human_rot<90.0f)
                    {
                        glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                        glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                        model_human = back1
                            * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                            * transl_origin1;
                        human_rot += 180.0f;
                    }

                    model_human = glm::translate(glm::mat4(1.0f), glm::vec3(0.001f, 0.0f, 0.0f)) * model_human;
                    human->movement(model_human);
                    current_x+=speed;
                }
                else
                {
                    if(current_z>0.0f)
                    {
                        //Rajouter une rotation de 90° au bonhomme 
                        if(human_rot<180.0f)
                        {
                            glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                            glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                            model_human = back1
                                * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                                * transl_origin1;
                            human_rot += 90.0f;
                        }

                        model_human = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.001f))* model_human;
                        human->movement(model_human);
                        current_z-=speed;
                    }
                    else
                    {
                        trajectory_number = 2;
                        trajectory_return = false;
                    }
                }

            }
        }
        //trajectory 2
        if(trajectory_number == 2)
        {
            if(!trajectory_return)
            {
                if(current_z>-2)
                {
                    model_human = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.001f));
                    human->movement(model_human);
                    current_z-=speed;
                }
                else
                {
                    if(current_x>-12)
                    {
                        if(human_rot<270)
                        {
                            glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                            glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                            model_human = back1
                                * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                                * transl_origin1;
                            human_rot += 90.0f;
                        }

                        model_human = glm::translate(glm::mat4(1.0f), glm::vec3(-0.001f, 0.0f, 0.0f))* model_human;
                        human->movement(model_human);
                        current_x-=speed;
                    }
                    else
                    {
                        if(current_z>-12)
                        {
                            if(human_rot>180)
                            {
                                glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                                glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                                model_human = back1
                                    * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                                    * transl_origin1;
                                human_rot -= 90.0f;
                            }
                            model_human = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.001f))* model_human;
                            human->movement(model_human);
                            current_z-=speed;
                            
                        }
                        else
                        {
                            trajectory_number = 3;
                        }
                    }
                }
            }
            else
            {
                if(current_z<-2)
                {
                    if(human_rot<0)
                    {
                        glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                        glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                        model_human = back1
                            * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                            * transl_origin1;
                        human_rot += 90.0f;
                    }
                    model_human = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.001f))* model_human;
                    human->movement(model_human);
                    current_z+=speed;
                }
                else
                {
                    if(current_x<0)
                    {
                        if(human_rot<90)
                        {
                            glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                            glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                            model_human = back1
                                * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                                * transl_origin1;
                            human_rot += 90.0f;
                        }
                        model_human = glm::translate(glm::mat4(1.0f), glm::vec3(0.001f, 0.0f, 0.0f))* model_human;
                        human->movement(model_human);
                        current_x+=speed;
                    }
                    else
                    {
                        if(current_z<0)
                        {
                            if(human_rot>0)
                            {
                                glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                                glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                                model_human = back1
                                    * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                                    * transl_origin1;
                                human_rot -= 90.0f;
                            }
                            model_human = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.001f))* model_human;
                            human->movement(model_human);
                            current_z+=speed;
                        }
                        else
                        {
                            trajectory_return = false;
                            trajectory_number = 4;
                        }
                    }
                }

            }
        }
        //trajectory 3
        if(trajectory_number == 3)
        {
            if(!trajectory_return)
            {
                if(current_x<0)
                {
                    if(human_rot>90)
                    {
                        glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                        glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                        model_human = back1
                            * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                            * transl_origin1;
                        human_rot -= 90.0f;
                    }

                    model_human = glm::translate(glm::mat4(1.0f), glm::vec3(0.001f, 0.0f, 0.0f))* model_human;
                    human->movement(model_human);
                    current_x+=speed;
                }
                else
                {
                    trajectory_return = true;
                }
            }
            else
            {
                if(current_x>-12)
                {
                    if(human_rot>-90)
                    {
                        glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                        glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                        model_human = back1
                            * glm::rotate(glm::mat4(1.0f), glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                            * transl_origin1;
                        human_rot -= 180.0f;
                    }
                    model_human = glm::translate(glm::mat4(1.0f), glm::vec3(-0.001f, 0.0f, 0.0f))* model_human;
                    human->movement(model_human);
                    current_x-=speed;
                }
                else
                {
                    trajectory_number = 2;
                }
            }
        }

        //tractory 4
        if(trajectory_number == 4)
        {
            if(!trajectory_return)
            {
                if(current_z>-6)
                {
                    if(human_rot<180)
                    {
                        glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                        glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                        model_human = back1
                            * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                            * transl_origin1;
                        human_rot += 180.0f;
                    }
                    model_human = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.001f))* model_human;
                    human->movement(model_human);
                    current_z-=speed;
                }
                else
                {
                    if(current_x<9)
                    {
                        if(human_rot>90)
                        {
                            glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                            glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                            model_human = back1
                                * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                                * transl_origin1;
                            human_rot -= 90.0f;
                        }
                        model_human = glm::translate(glm::mat4(1.0f), glm::vec3(0.001f, 0.0f, 0.0f))* model_human;
                        human->movement(model_human);
                        current_x+=speed;
                    }
                    else
                    {
                        trajectory_number = 5;
                    }
                }
            }
            else
            {
                if(current_x>0)
                {
                    if(human_rot<-90)
                    {
                        glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                        glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                        model_human = back1
                            * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                            * transl_origin1;
                        human_rot += 90.0f;
                    }
                    model_human = glm::translate(glm::mat4(1.0f), glm::vec3(-0.001f, 0.0f, 0.0f))* model_human;
                    human->movement(model_human);
                    current_x-=speed;
                }
                else
                {
                    if(current_z<0)
                    {
                        if(human_rot<0)
                        {
                            glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                            glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                            model_human = back1
                                * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                                * transl_origin1;
                            human_rot += 90.0f;
                        }
                        model_human = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.001f))* model_human;
                        human->movement(model_human);
                        current_z+=speed;
                    }
                    else
                    {
                        trajectory_return = false;
                        trajectory_number = 1;
                    }
                }
            }
        }

        //trajectory 5
        if(trajectory_number == 5)
        {
            if(!trajectory_return)
            {
                if(current_z<3)
                {
                    if(human_rot>0)
                    {
                        glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                        glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                        model_human = back1
                            * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                            * transl_origin1;
                        human_rot -= 90.0f;
                    }
                    model_human = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.001f))* model_human;
                    human->movement(model_human);
                    current_z+=speed;
                }
                else
                {
                    trajectory_return = true;
                }
            }
            else
            {
                if(current_z>-6)
                {
                    if(human_rot>-180)
                    {
                        glm::mat4 transl_origin1 = glm::translate(glm::mat4(1.0f), glm::vec3(-current_x, 0.0f + 1.0f, -current_z + 4.0f));
                        glm::mat4 back1 = glm::translate(glm::mat4(1.0f), glm::vec3(current_x, 0.0f -1.0f, current_z - 4.0f));
                        model_human = back1
                            * glm::rotate(glm::mat4(1.0f), glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f))
                            * transl_origin1;
                        human_rot -= 180.0f;
                    }
                    model_human = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.001f))* model_human;
                    human->movement(model_human);
                    current_z-=speed;
                }
                else
                {
                    trajectory_number = 4;
                }
            }
            
        }

        /*camera*/
        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

        scene_root->draw(model, view, projection);

        // Poll for and process events
        glfwPollEvents();

        // flush render commands, and swap draw buffers
        glfwSwapBuffers(win);
    }

    /* close GL context and any other GLFW resources */
    glfwTerminate();
}

void Viewer::key_callback_static(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Viewer *viewer = static_cast<Viewer *>(glfwGetWindowUserPointer(window));
    viewer->on_key(key);
}

void Viewer::on_key(int key)
{
    // 'Q' or 'Escape' quits
    if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)
    {
        glfwSetWindowShouldClose(win, GLFW_TRUE);
    }
    const float cameraSpeed = 0.1f; // adjust accordingly
    if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Viewer::mouse_callback_static(GLFWwindow *window, double xpos, double ypos)
{
    Viewer *viewer = static_cast<Viewer *>(glfwGetWindowUserPointer(window));
    viewer->on_mouse(xpos, ypos);
}

void Viewer::on_mouse(double xpos, double ypos)
{
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

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}