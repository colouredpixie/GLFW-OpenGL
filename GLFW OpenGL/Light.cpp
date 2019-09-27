#include "Light.hpp"

Light::Light() {
    colour = glm::vec3(1.0f, 1.0f, 1.0f);
    ambientIntensity = 1.0f;
    diffuseIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, GLfloat shadowWidth, GLfloat shadowHeight) {
    colour = glm::vec3(red, green, blue);
    ambientIntensity = aIntensity;
    diffuseIntensity = dIntensity;

    shadowMap = new ShadowMap();
    shadowMap->Init(shadowWidth, shadowHeight);
}

Light::~Light() {
}

