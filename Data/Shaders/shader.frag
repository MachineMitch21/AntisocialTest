#version 330 core
out vec4 fragColor;

in vec3 FragPos;
in vec3 normal;
in vec2 texCoord;

uniform sampler2D tex;
uniform sampler2D tex2;
uniform sampler2D tex3;

uniform bool usingUnit1;
uniform bool usingUnit2;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 viewPos;

uniform float specularStrength;

uniform vec3 objectColor;

vec3 getDiffuseContribution();
vec3 getSpecularContribution();

void main()
{
    vec3 ambient = .25f * vec3(.25f);

    vec3 diffuse = getDiffuseContribution();
    vec3 specular = getSpecularContribution();

    float distance = length(lightPos - FragPos);
    float attenuation = 1.0f / (1.0f + 0.07f * distance + 0.0075f * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = (ambient + diffuse + specular) * objectColor;

    fragColor = texture(tex, texCoord) * (usingUnit1 ? texture(tex2, texCoord) : vec4(1.0f)) * (usingUnit2 ? texture(tex3, texCoord) : vec4(1.0f)) * vec4(result, 1.0f);
}

vec3 getDiffuseContribution()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    return diffuse;
}

vec3 getSpecularContribution()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 256);
    vec3 specular = (specularStrength * spec) * lightColor;

    return specular;
}
