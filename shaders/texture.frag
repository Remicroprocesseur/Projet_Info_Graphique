#version 330 core

in vec2 TexCoord;  // Reçu du vertex shader

uniform sampler2D diffuse_map;

out vec4 FragColor;

void main()
{
    FragColor = texture(diffuse_map, TexCoord);
}
