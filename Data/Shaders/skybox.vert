#version 330 core
layout (location = 0) in vec3 Pos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec3 texCoord;

uniform float time;

void main()
{
    texCoord = Pos;
    gl_Position = (vec4(Pos, 1.0f) * model * view * projection);
}
