#version 330 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

out vec3 FragPos;
out vec2 texCoord;
out vec3 normal;

uniform float time;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float verticeOffset = 0.0f;

void main()
{
    mat4 model_view = model * view;
    FragPos = Pos;
    FragPos += Normal * 0.0f;
    normal = Normal * mat3(model_view);
    texCoord = TexCoord;
    gl_Position = vec4(FragPos, 1.0f) * model_view * projection;
}
