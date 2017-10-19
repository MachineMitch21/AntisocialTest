#version 330 core
out vec4 fragColor;

in vec3 FragPos;
in vec2 texCoord;

uniform sampler2D tex;
uniform sampler2D tex2;
uniform sampler2D tex3;

void main()
{
    fragColor = texture(tex, texCoord) * texture(tex2, texCoord) * texture(tex3, texCoord);
}
