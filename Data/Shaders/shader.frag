#version 330 core

in vec3 FragPos;
in vec4 FragColor;
in vec2 texCoord;

void main()
{
    gl_FragColor = FragColor;
}
