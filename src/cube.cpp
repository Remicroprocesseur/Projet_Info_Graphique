#include "cube.h"
#include <iostream>

Cube::Cube(Shader *shader_program) : Shape(shader_program) 
{
    GLfloat vertex_buffer_data[] = {
        // --- Back face ---
        -0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        0.0f,
        0.5f,
        -0.5f,
        -0.5f,
        1.0f,
        0.0f,
        0.5f,
        0.5f,
        -0.5f,
        1.0f,
        1.0f,
        0.5f,
        0.5f,
        -0.5f,
        1.0f,
        1.0f,
        -0.5f,
        0.5f,
        -0.5f,
        0.0f,
        1.0f,
        -0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        0.0f,

        // --- Front face ---
        -0.5f,
        -0.5f,
        0.5f,
        0.0f,
        0.0f,
        0.5f,
        -0.5f,
        0.5f,
        1.0f,
        0.0f,
        0.5f,
        0.5f,
        0.5f,
        1.0f,
        1.0f,
        0.5f,
        0.5f,
        0.5f,
        1.0f,
        1.0f,
        -0.5f,
        0.5f,
        0.5f,
        0.0f,
        1.0f,
        -0.5f,
        -0.5f,
        0.5f,
        0.0f,
        0.0f,

        // --- Left face ---
        -0.5f,
        0.5f,
        0.5f,
        1.0f,
        0.0f,
        -0.5f,
        0.5f,
        -0.5f,
        1.0f,
        1.0f,
        -0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        1.0f,
        -0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        1.0f,
        -0.5f,
        -0.5f,
        0.5f,
        0.0f,
        0.0f,
        -0.5f,
        0.5f,
        0.5f,
        1.0f,
        0.0f,

        // --- Right face ---
        0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        1.0f,
        0.5f,
        -0.5f,
        0.5f,
        0.0f,
        0.0f,
        0.5f,
        0.5f,
        0.5f,
        1.0f,
        0.0f,
        0.5f,
        0.5f,
        0.5f,
        1.0f,
        0.0f,
        0.5f,
        0.5f,
        -0.5f,
        1.0f,
        1.0f,
        0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        1.0f,

        // --- Bottom face ---
        -0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        1.0f,
        0.5f,
        -0.5f,
        -0.5f,
        1.0f,
        1.0f,
        0.5f,
        -0.5f,
        0.5f,
        1.0f,
        0.0f,
        0.5f,
        -0.5f,
        0.5f,
        1.0f,
        0.0f,
        -0.5f,
        -0.5f,
        0.5f,
        0.0f,
        0.0f,
        -0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        1.0f,

        // --- Top face ---
        -0.5f,
        0.5f,
        -0.5f,
        0.0f,
        1.0f,
        0.5f,
        0.5f,
        -0.5f,
        1.0f,
        1.0f,
        0.5f,
        0.5f,
        0.5f,
        1.0f,
        0.0f,
        0.5f,
        0.5f,
        0.5f,
        1.0f,
        0.0f,
        -0.5f,
        0.5f,
        0.5f,
        0.0f,
        0.0f,
        -0.5f,
        0.5f,
        -0.5f,
        0.0f,
        1.0f,
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(2, &buffers[0]);

    glEnableVertexAttribArray(0);
    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

    // Attribut position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    // Attribut UV (texture)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}

void Cube::draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{   
    glUseProgram(this->shader_program_);

    glBindVertexArray(VAO);
    
    Shape::draw(model, view, projection);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &buffers[0]);
}

void Cube::key_handler(int key) {
    return;
}