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
/**#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
ça fait des erreurs sur mon pc
**/

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

    //si jamais on veut repasser au placement manuel
    /**Shape* cube2 = new TexturedCube(texture_shader, texture);
    glm::mat4 cube2_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.30f, 0.0f, 0.40f)) //A noté que le déplacement se fait en % de la taille de notre cube père
        * glm::scale(glm::mat4(1.0f), glm::vec3(0.01f, 1.0f, 0.2f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* cube2_node = new Node(cube2_mat);

    cube2_node->add(cube2);

    Shape* cube3 = new TexturedCube(texture_shader, texture);
    glm::mat4 cube3_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.205f, 0.0f, 0.30f)) //A noté que le déplacement se fait en % de la taille de notre cube père
        * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 1.0f, 0.01f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* cube3_node = new Node(cube3_mat);
    
    cube3_node->add(cube3);

    Shape* cube4 = new TexturedCube(texture_shader, texture);
    glm::mat4 cube4_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.110f, 0.0f, 0.20f)) // A noté que le déplacement se fait en % de la taille de notre cube père
        * glm::scale(glm::mat4(1.0f), glm::vec3(0.01f, 1.0f, 0.2f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Node* cube4_node = new Node(cube4_mat);
    
    cube4_node->add(cube4);
    cube1_node->add(cube2_node);
    cube1_node->add(cube3_node);
    cube1_node->add(cube4_node);
    **/

    //placement aléatoire

    //placement avec nombre d'élément prédéfini

    /**Shape* cube2 = new TexturedCube(texture_shader, texture);
    Shape* cube3 = new TexturedCube(texture_shader, texture);
    Shape* cube4 = new TexturedCube(texture_shader, texture);
    Shape* cube5 = new TexturedCube(texture_shader, texture);
    Shape* cube6 = new TexturedCube(texture_shader, texture);

    glm::mat4 taille_mur_couloir_vertical = glm::scale(glm::mat4(1.0f), glm::vec3(0.01f, 1.0f, 0.2f));
    glm::mat4 taille_mur_couloir_horzontal = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 1.0f, 0.01f));
    glm::mat4 rot_mur_couloir = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 cube2_mat = glm::mat4(1.0f);
    glm::mat4 cube3_mat = glm::mat4(1.0f);
    glm::mat4 cube4_mat = glm::mat4(1.0f);
    glm::mat4 cube5_mat = glm::mat4(1.0f);
    glm::mat4 cube6_mat = glm::mat4(1.0f);

    srand(time(NULL));

    glm::mat4 matrices[5] = {cube2_mat, cube3_mat, cube4_mat, cube5_mat, cube6_mat};

    for(int i=0; i<5; i++)
    {

        float x = 10;
        while(x>0.4)
        {
            x = ((double)rand()) / RAND_MAX;
        }
        int signe_x = rand()%2;
        if(signe_x == 1)
        {
            x = -x;
        }

        float z = 10;
        int signe_z = rand()%2;
        while(z>0.4)
        {
            z = ((double)rand()) / RAND_MAX;
        }

        if(signe_z==1)
        {
            z = -z;
        }

        int decision = rand()%2;
        if(decision == 0)
        {
            matrices[i] = matrices[i]
                        * glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, z))
                        * taille_mur_couloir_horzontal
                        * rot_mur_couloir;
        }
        else
        {
            matrices[i] = matrices[i]
                        * glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, z))
                        * taille_mur_couloir_vertical
                        * rot_mur_couloir;
        }

        
        
    }

    Node* cube2_node = new Node(matrices[0]);
    Node* cube3_node = new Node(matrices[1]);
    Node* cube4_node = new Node(matrices[2]);
    Node* cube5_node = new Node(matrices[3]);
    Node* cube6_node = new Node(matrices[4]);

    cube2_node->add(cube2);
    cube3_node->add(cube3);
    cube4_node->add(cube4);
    cube5_node->add(cube5);
    cube6_node->add(cube6);

    cube1_node->add(cube2_node);
    cube1_node->add(cube3_node);
    cube1_node->add(cube4_node);
    cube1_node->add(cube5_node);
    cube1_node->add(cube6_node);**/

    //placement d'un nombre aléatoire de murs

    glm::mat4 taille_mur_couloir_vertical = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 1.0f, 0.2f));
    glm::mat4 taille_mur_couloir_horzontal = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 1.0f, 0.02f));
    glm::mat4 rot_mur_couloir = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    int nb_elements = rand()%7;
    nb_elements += 4;
    for(int i=0; i<nb_elements;i++)
    {
        glm::mat4 cube_mat = glm::mat4(1.0f);
        float x = 10;
        while(x>0.4)
        {
            x = ((double)rand()) / RAND_MAX;
        }
        int signe_x = rand()%2;
        if(signe_x == 1)
        {
            x = -x;
        }

        float z = 10;
        int signe_z = rand()%2;
        while(z>0.4)
        {
            z = ((double)rand()) / RAND_MAX;
        }

        if(signe_z==1)
        {
            z = -z;
        }

        int decision = rand()%2;
        if(decision == 0)
        {
            cube_mat = cube_mat
                        * glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, z))
                        * taille_mur_couloir_horzontal
                        * rot_mur_couloir;
        }
        else
        {
            cube_mat = cube_mat
                        * glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, z))
                        * taille_mur_couloir_vertical
                        * rot_mur_couloir;
        }
        Shape* cube = new TexturedCube(texture_shader, texture);
        Node* cube_node = new Node(cube_mat);
        cube_node->add(cube);
        cube1_node->add(cube_node); 
    }
    
    viewer.scene_root->add(cube1_node);



    Shape* sphere1 = new TexturedSphere(texture_shader, texture);
    glm::mat4 sphere1_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -4.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* sphere1_node = new Node(sphere1_mat);

    sphere1_node->add(sphere1);

    //viewer.scene_root->add(sphere1_node);
    
    Shader *phong_shader = new Shader(shader_dir + "phong.vert", shader_dir + "phong.frag");

    Shader *color_shader = new Shader(shader_dir + "node.vert", shader_dir + "node.frag");

    Shape* sphere2 = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 sphere2_mat = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -4.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    Node* sphere2_node = new Node(sphere2_mat);

    Shape* cube = new Cube(color_shader);

    glm::mat4 cube_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.1f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* cube_node = new Node(cube_mat);

    sphere2_node->add(sphere2);
    cube_node->add(cube);

    //viewer.scene_root->add(sphere2_node);
    //viewer.scene_root->add(cube_node);

    viewer.run();
}