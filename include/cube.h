#include "shape.h"
#include <vector>
#include <GL/glew.h>

class Cube : public Shape{
    public:
        Cube(Shader *shader_program);
        void draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection);
        void key_handler(int key);
        virtual ~Cube();
    
    private:
        GLuint VAO;
        GLuint buffers[2];
    };