#version 330 core
out vec4 fragColor;

in vec3 texCoord3D;
in vec2 texCoord2D;

uniform samplerCube cubeTex;
uniform sampler2D cubeTex2D;
uniform bool usingCubeMap;

void main()
{
    vec4 result;

    if (usingCubeMap)
    {
        result = texture(cubeTex, texCoord3D);
    }
    else
    {
        result = texture(cubeTex2D, texCoord2D);
    }
    
    fragColor = result;
}
