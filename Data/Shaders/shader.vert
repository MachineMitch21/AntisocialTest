#version 330 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 TexCoord;

out vec3 FragPos;
out vec4 FragColor;
out vec2 texCoord;

uniform float time;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = Pos;
    FragColor = vec4(Color, 1.0f);
    texCoord = TexCoord;
    gl_Position = vec4(FragPos, 1.0f) * model * view * projection;
}
