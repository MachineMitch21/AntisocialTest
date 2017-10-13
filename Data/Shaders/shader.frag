#version 330 core
out vec4 fragColor;

in vec3 FragPos;
in vec4 FragColor;
in vec2 texCoord;

uniform sampler2D tex;
uniform sampler2D tex2;

void main()
{
    fragColor = mix(texture(tex, texCoord), texture(tex2, texCoord), 0.4) * FragColor;
}
