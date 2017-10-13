#version 330 core
layout (location = 0) in vec3 Pos;

out vec3 FragPos;
out vec4 FragColor;

void main()
{
    FragPos = Pos;
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    gl_Position = vec4(Pos, 1.0f);
}
