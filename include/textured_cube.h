#ifndef TEXTURED_CUBE_H
#define TEXTURED_CUBE_H

#include "cube.h"
#include "texture.h"

class TexturedCube : public Cube {
public:
    TexturedCube(Shader *shader_program, Texture *texture);

    virtual void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) override;

private:
    GLuint loc_diffuse_map;
    Texture *texture;
};

#endif // TEXTURED_CUBE_H
