#version 330 core
layout (location = 0) in vec2 Pos;

out vec2 FragPos;

uniform mat4 projection;

void main()
{
    FragPos = Pos;
    gl_Position = vec4(Pos, 0.0f, 1.0f) * projection;
}
