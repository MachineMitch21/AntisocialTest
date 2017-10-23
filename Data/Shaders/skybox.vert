#version 330 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 UV;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec3 texCoord3D;
out vec2 texCoord2D;

uniform float time;

void main()
{
    texCoord3D = normalize(Pos);
    texCoord2D = UV;
    vec4 pos = vec4(Pos, 1.0f) * model * view * projection;
    gl_Position = pos.xyww;
}
