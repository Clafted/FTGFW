#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 fragmentPos;

struct Material {
    sampler2D diffuseMap0;
    sampler2D specularMap0;
    float shininess;
};

uniform Material u_Material;

void main()
{
    vec4 result = texture(u_Material.diffuseMap0, texCoord);
    if (result.a == 0.0) discard;
	FragColor = result;
};