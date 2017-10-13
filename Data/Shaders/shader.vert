#version 330 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;

out vec3 FragPos;
out vec4 FragColor;

void main()
{
    FragPos = Pos;
    FragColor = vec4(Color, 1.0f);
    gl_Position = vec4(FragPos, 1.0f);
}
