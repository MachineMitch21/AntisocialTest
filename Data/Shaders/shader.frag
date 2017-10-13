#version 330 core
out vec4 fragColor;

in vec3 FragPos;
in vec4 FragColor;

void main()
{
    fragColor = FragColor;
}
