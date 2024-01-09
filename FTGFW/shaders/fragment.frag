#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragmentPos;

struct PointLight {
    vec3 pos;
    vec3 lightColor;

    float intensity;
    float ambientStrength;
    float diffuseStrength;
    float specularStrength;
};

struct DirectionalLight {
    vec3 direction;
    vec3 lightColor;

    float intensity;
    float ambientStrength;
    float diffuseStrength;
    float specularStrength;
};

struct Material {
    sampler2D u_diffuseMap;
    sampler2D u_specularMap;
    float shininess;
};

#define NUM_POINT_LIGHTS 4
uniform PointLight pointLights[NUM_POINT_LIGHTS];
uniform DirectionalLight dirLight = DirectionalLight(vec3(0.4, -0.2, 0.0), vec3(1.0, 0.93, 0.8), 0.8, 0.5, 0.5, 0.5);
uniform Material material;
uniform vec3 cameraPos;

vec3 calculateDirectionalLight(vec3 diffuseColor, vec3 specularCOlor);
vec3 calculatePointLight(PointLight light, vec3 diffuseColor, vec3 specularColor);
vec3 calculteSpotLight(vec4 texelColor);

void main() {
    
    vec3 diffuseColor = texture(material.u_diffuseMap, texCoord).rgb;
    vec3 specularColor = texture(material.u_specularMap, texCoord).rgb;
    vec3 pointLightsColor = vec3(0.0);

    for (int i = 0; i < NUM_POINT_LIGHTS; i++)
        pointLightsColor += calculatePointLight(pointLights[i], diffuseColor, specularColor);

    FragColor = vec4((calculateDirectionalLight(diffuseColor, specularColor) + pointLightsColor), 0.0);
               // + calculteSpotLight(texelColor);
}

/**
 * Calculates the contribution of a directional light
 * 
 * @param texelColor - the color of the texel
 * @returns a vec4 representing the resultant color of the fragment */
vec3 calculateDirectionalLight(vec3 diffuseColor, vec3 specularColor) {
    float diffuse, specular;
    vec3 reflectionDirection;
    vec3 eyePos;
    vec3 ambientValue, diffuseValue, specularValue;

    // Calculate diffuse lighting
    diffuse = max(0.0, dot(normal, normalize(-dirLight.direction)));
    // Calculate specular lighting
    eyePos = normalize(cameraPos - fragmentPos);
    reflectionDirection = reflect(normalize(dirLight.direction), normal);
    specular = pow(max(0.0, dot(eyePos, reflectionDirection)), 65);        // Shininess is set to 65
    
    ambientValue = dirLight.ambientStrength * diffuseColor;
    diffuseValue = dirLight.diffuseStrength * diffuseColor * diffuse;
    specularValue = dirLight.specularStrength * specularColor * specular;

    return dirLight.intensity * dirLight.lightColor * (ambientValue + diffuseValue + specularValue);
}

vec3 calculatePointLight(PointLight light, vec3 diffuseColor, vec3 specularColor) {

    vec3 lightDirection;
    vec3 viewDirection;
    vec3 reflectionDirection;
    vec3 ambientValue, diffuseValue, specularValue;
    float dist;
    float attenuation;
    float diffuse, specular;

    lightDirection = normalize(light.pos - fragmentPos);
    // Calculate the diffuse factor
    diffuse = max(0.0, dot(normal, lightDirection));
    // Calculate the specular factor
    viewDirection = normalize(cameraPos - fragmentPos);
    reflectionDirection = reflect(-lightDirection, normal);
    specular = pow(max(dot(viewDirection, reflectionDirection), 0.0), 65);
    // Calculate attenuation
    dist = length(light.pos - fragmentPos);
    attenuation = 1.0 / (1.0 + 0.07 * dist + 0.017 * pow(dist, 2));

    ambientValue = light.ambientStrength * diffuseColor;
    diffuseValue = light.diffuseStrength * diffuseColor * diffuse;
    specularValue = light.specularStrength * specularColor * specular;
    
    return light.intensity * light.lightColor * attenuation * (ambientValue + diffuseValue + specularValue);
}