#version 330 core
out vec4 fragColor;

in vec3 FragPos;
in vec2 texCoord;

uniform sampler2D tex;
uniform sampler2D tex2;
uniform sampler2D tex3;

uniform bool usingUnit1;
uniform bool usingUnit2;

void main()
{
    fragColor = texture(tex, texCoord) * (usingUnit1 ? texture(tex2, texCoord) : vec4(1.0f)) * (usingUnit2 ? texture(tex3, texCoord) : vec4(1.0f));
}
