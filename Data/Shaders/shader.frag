#version 330 core
out vec4 fragColor;

in vec3 FragPos;
in vec2 texCoord;

uniform sampler2D tex;
uniform sampler2D tex2;

void main()
{
    fragColor = texture(tex, texCoord);
}
