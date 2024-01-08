#ifndef LIGHTCASTERS_HPP
#define LIGHTCASTERS_HPP

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec3.hpp"

struct LightCaster {
    glm::vec3 lightColor;
    float intensity;
    float ambientStrength;
    float diffuseStrength;
    float specularStrength;

    LightCaster(glm::vec3 lightColor = glm::vec3(1.0f),
        float intensity = 1.0f,
        float ambientStrength = 0.5f,
        float diffuseStrength = 0.5f,
        float specularStrength = 0.5f)

        : intensity(intensity),
        ambientStrength(ambientStrength),
        diffuseStrength(diffuseStrength),
        specularStrength(specularStrength) {}
};

struct PointLight : public LightCaster {
    glm::vec3 pos;
    
    PointLight(glm::vec3 pos = glm::vec3(0.0f),
        glm::vec3 lightColor = glm::vec3(1.0f),
        float intensity = 1.0f,
        float ambientStrength = 0.5f,
        float diffuseStrength = 0.5f,
        float specularStrength = 0.5f)

        : LightCaster(lightColor, intensity, ambientStrength, diffuseStrength, specularStrength),
        pos(pos) {}
};

struct DirectionalLight : public LightCaster {

    DirectionalLight(glm::vec3 pos = glm::vec3(0.0f),
        glm::vec3 lightColor = glm::vec3(1.0f),
        float intensity = 1.0f,
        float ambientStrength = 0.5f,
        float diffuseStrength = 0.5f,
        float specularStrength = 0.5f)

        : LightCaster(lightColor, intensity, ambientStrength, diffuseStrength, specularStrength) {}
};

#endif