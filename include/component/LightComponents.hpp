#ifndef LightComponentS_HPP
#define LightComponentS_HPP

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec3.hpp"
#include "Component.hpp"

struct LightComponent : public Component{
    glm::vec3 lightColor;
    float intensity;
    float ambientStrength;
    float diffuseStrength;
    float specularStrength;

    LightComponent(glm::vec3 lightColor = glm::vec3(1.0f),
                float intensity = 1.0f,
                float ambientStrength = 0.5f,
                float diffuseStrength = 0.5f,
                float specularStrength = 0.5f)

        : lightColor(lightColor),
        intensity(intensity),
        ambientStrength(ambientStrength),
        diffuseStrength(diffuseStrength),
        specularStrength(specularStrength) {}
};

struct PointLight : public LightComponent {
    glm::vec3 pos;
    
    PointLight(glm::vec3 pos = glm::vec3(0.0f),
        glm::vec3 lightColor = glm::vec3(1.0f),
        float intensity = 1.0f,
        float ambientStrength = 0.5f,
        float diffuseStrength = 0.5f,
        float specularStrength = 0.5f)

        : LightComponent(lightColor, intensity, ambientStrength, diffuseStrength, specularStrength),
        pos(pos) {}
};

struct DirectionalLight : public LightComponent {

    DirectionalLight(glm::vec3 pos = glm::vec3(0.0f),
        glm::vec3 lightColor = glm::vec3(1.0f),
        float intensity = 1.0f,
        float ambientStrength = 0.5f,
        float diffuseStrength = 0.5f,
        float specularStrength = 0.5f)

        : LightComponent(lightColor, intensity, ambientStrength, diffuseStrength, specularStrength) {}
};

#endif