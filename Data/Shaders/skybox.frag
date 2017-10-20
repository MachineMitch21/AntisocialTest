#version 330 core

in vec3 texCoord;
uniform samplerCube cubeTex;
out vec4 fragColor;

void main()
{
    fragColor = texture(cubeTex, texCoord);
}
