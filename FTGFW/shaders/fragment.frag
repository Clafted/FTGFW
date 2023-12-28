#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragmentPos;

struct Light {
    vec3 pos;
    vec3 lightColor;
    float intensity;
};

struct Material {
    sampler2D u_currentTexture;
    sampler2D u_specularMap;
    float shininess;
};

uniform Material material;
uniform Light light = Light(vec3(0.0), vec3(0.0), 0.0);
uniform vec3 cameraPos;

void main() {
    // Material variables
    float ambientStrength = 0.3;
    float specularStrength = 0.7;
    float shininess = 65.0;
    // Calculate the diffuse factor
    vec3 lightDirection = normalize(light.pos - fragmentPos);
    float diffuseFactor = max(0.0, dot(normalize(normal), lightDirection));
    // Calculate the specular factor
    vec3 viewDirection = normalize(cameraPos - fragmentPos);
    vec3 reflectionDirection = reflect(-lightDirection, normalize(normal));
    float specularFactor = pow(max(dot(viewDirection, reflectionDirection), 0.0), shininess);
    // Calculate final fragment color;
    FragColor = texture(material.u_currentTexture, texCoord)
                * light.intensity 
                * (vec4(light.lightColor, 1.0) 
                    * (diffuseFactor 
                        + ambientStrength
                        + specularFactor * texture(material.u_specularMap, texCoord)));         // [scalar] + [vector/matrix] is component-wise on GPU
} 