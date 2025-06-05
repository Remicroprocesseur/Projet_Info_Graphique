#include "viewer.h"
#include "textured_sphere.h"
#include "lighting_sphere.h"
#include "texture.h"
#include "node.h"
#include "shader.h"
#include "textured_cube.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include "cylinder.h"
#include "triangle.h"
#include "lighting_cylinder.h"

#ifndef SHADER_DIR
#error "SHADER_DIR not defined"
#endif

#ifndef TEXTURE_DIR
#error "TEXTURE_DIR not defined"
#endif

int main()
{
    // create window, add shaders & scene objects, then run rendering loop
    Viewer viewer;

    // get shader directory
    std::string shader_dir = SHADER_DIR;

    // get texture directory
    std::string texture_dir = TEXTURE_DIR;

    Shader* texture_shader = new Shader(shader_dir + "texture.vert", shader_dir + "texture.frag");

    Texture *texture = new Texture(texture_dir + "Wood.jpg");

    Shape* cube1 = new TexturedCube(texture_shader, texture);
    glm::mat4 cube1_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -4.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(30.0f, 8.0f, 30.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* cube1_node = new Node(cube1_mat);

    cube1_node->add(cube1);

    //placement manuel des murs sur dans le premier cube
    glm::mat4 verical_wall_SR = glm::scale(glm::mat4(1.0f), glm::vec3(0.01f, 1.0f, 0.2f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 horizontal_wall_SR =  glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 1.0f, 0.01f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    Shape* wall1 = new TexturedCube(texture_shader, texture);
    glm::mat4 wall1_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.30f, 0.0f, 0.40f)) //A noté que le déplacement se fait en % de la taille totale de notre cube père (ici la taille est 30)
        * verical_wall_SR;
    Node* wall1_node = new Node(wall1_mat);

    wall1_node->add(wall1);

    Shape* wall2 = new TexturedCube(texture_shader, texture);
    glm::mat4 wall2_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.205f, 0.0f, 0.295f)) //A noté que le déplacement se fait en % de la taille de notre cube père
        * horizontal_wall_SR;
    Node* wall2_node = new Node(wall2_mat);
    
    wall2_node->add(wall2);

    Shape* wall3 = new TexturedCube(texture_shader, texture);
    glm::mat4 wall3_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.1f, 0.0f, 0.10f)) // A noté que le déplacement se fait en % de la taille de notre cube père
        *glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 2.0f)) //On double la longueur du mur, à voir si ça fait bizarre
        * verical_wall_SR;
    Node* wall3_node = new Node(wall3_mat);

    wall3_node->add(wall3);

    Shape* wall4 = new TexturedCube(texture_shader, texture);
    glm::mat4 wall4_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.1f, 0.0f, -0.40f)) // A noté que le déplacement se fait en % de la taille de notre cube père
        * verical_wall_SR;
    Node* wall4_node = new Node(wall4_mat);
    
    wall4_node->add(wall4);

    Shape* wall5 = new TexturedCube(texture_shader, texture);
    glm::mat4 wall5_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.095f, 0.0f, -0.295f)) // A noté que le déplacement se fait en % de la taille de notre cube père
        *glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 1.0f)) //On double la longueur du mur, à voir si ça fait bizarre
        * horizontal_wall_SR;
    Node* wall5_node = new Node(wall5_mat);
    
    wall5_node->add(wall5);

    Shape* wall6 = new TexturedCube(texture_shader, texture);
    glm::mat4 wall6_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.4f, 0.0f, 0.295f)) // A noté que le déplacement se fait en % de la taille de notre cube père
        * horizontal_wall_SR;
    Node* wall6_node = new Node(wall6_mat);
    
    wall6_node->add(wall6);

    Shape* wall7 = new TexturedCube(texture_shader, texture);
    glm::mat4 wall7_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.295f, 0.0f, 0.2f)) // A noté que le déplacement se fait en % de la taille de notre cube père
        * verical_wall_SR;
    Node* wall7_node = new Node(wall7_mat);
    
    wall7_node->add(wall7);

    cube1_node->add(wall1_node);
    cube1_node->add(wall2_node);
    cube1_node->add(wall3_node);
    cube1_node->add(wall4_node);
    cube1_node->add(wall5_node);
    cube1_node->add(wall6_node);
    cube1_node->add(wall7_node);
    
    viewer.scene_root->add(cube1_node);
    
    Shader *phong_shader = new Shader(shader_dir + "phong.vert", shader_dir + "phong.frag");

    Shader *color_shader = new Shader(shader_dir + "node.vert", shader_dir + "node.frag");

    //création du bonhomme à animer
    glm::mat4 human_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, -4.0f)) 
        * glm::scale(glm::mat4(1.0f), glm::vec3(0.9f, 0.9f, 0.9f)) 
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node *human = new Node(human_mat);
    // human -> add(new Cylinder(color_shader,2.0f,0.5f,100));

    Shape *head = new LightingCylinder(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 head_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)) 
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.5f)) 
        * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node *head_node = new Node(head_mat);

    head_node->add(head);

    Shape *body = new LightingCylinder(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 body_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 0.0f)) 
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.35f, 2.0f, 0.5f)) 
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node *body_node = new Node(body_mat);

    body_node->add(body);

    Shape *rightEye = new LightingCylinder(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 rightEye_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, 0.05f, 0.15f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.4f, 1.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node *rightEye_node = new Node(rightEye_mat);

    rightEye_node->add(rightEye);

    Shape *leftEye = new LightingCylinder(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 leftEye_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25f, 0.05f, 0.15f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.4f, 1.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node *leftEye_node = new Node(leftEye_mat);

    leftEye_node->add(leftEye);

    Shape *rightEar = new Triangle(color_shader);

    glm::mat4 rightEar_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.35f, 0.45f, 0.4f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.35f, 1.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(80.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    Node *rightEar_node = new Node(rightEar_mat);

    rightEar_node->add(rightEar);

    Shape *leftEar = new Triangle(color_shader);

    glm::mat4 leftEar_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-0.35f, 0.45f, 0.4f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.35f, 1.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(-80.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    Node *leftEar_node = new Node(leftEar_mat);

    leftEar_node->add(leftEar);

    Shape *rightuArm = new LightingCylinder(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 rightuArm_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.12f, 0.6f)) 
        * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.7f, 0.25f)) 
        * glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(1.0f, -0.1f, 0.0f));

    Node *rightuArm_node = new Node(rightuArm_mat);

    rightuArm_node->add(rightuArm);

    Shape *leftuArm = new LightingCylinder(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 leftuArm_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.12f, -0.6f)) 
        * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.7f, 0.25f)) 
        * glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(-1.0f, -0.1f, 0.0f));

    Node *leftuArm_node = new Node(leftuArm_mat);

    leftuArm_node->add(leftuArm);

    body_node->add(head_node);
    head_node->add(rightEye_node);
    head_node->add(leftEye_node);
    head_node->add(rightEar_node);
    head_node->add(leftEar_node);
    body_node->add(rightuArm_node);
    body_node->add(leftuArm_node);
    human->add(body_node);

    viewer.scene_root->add(human);

    viewer.run();
}