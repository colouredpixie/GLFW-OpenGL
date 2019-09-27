#include "PointLight.hpp"


PointLight::PointLight() {
    position =  glm::vec3(0.0f, 0.0f, 0.0f);
    constant = 1.0f; //to have a divider not equal to 0
    linear = 0.0f;
    exponent = 0.0f;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
                       GLfloat aIntensity, GLfloat dIntensity,
                       GLfloat xPos, GLfloat yPos, GLfloat zPos,
                       GLfloat cons, GLfloat lin, GLfloat exp,
                       GLfloat shadowWidth, GLfloat shadowHeight,
                       GLfloat near, GLfloat far) : Light(red, green, blue, aIntensity, dIntensity, shadowWidth, shadowHeight) {
    position =  glm::vec3(xPos, yPos, zPos);
    constant = cons;
    linear = lin;
    exponent = exp;
    
    farPlane = far;
    
    float aspect = shadowWidth / shadowHeight;
    lightProj = glm::perspective(glm::radians(90.0f), aspect, near, far);
    
    shadowMap = new OmniShadowMap();
    shadowMap->Init(shadowWidth, shadowHeight);
}

void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
                          GLuint diffuseIntensityLocation, GLuint positionLocation,
                          GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation) {
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
    
    glUniform3f(positionLocation, position.x, position.y, position.z);
    
    glUniform1f(constantLocation, constant);
    glUniform1f(linearLocation, linear);
    glUniform1f(exponentLocation, exponent);
}

std::vector<glm::mat4> PointLight::CalculateLightTransform() {
    std::vector<glm::mat4> lightMatrices;
    // +x, -x
    lightMatrices.push_back(lightProj * glm::lookAt(position, (position + glm::vec3(1.0, 0.0, 0.0)), glm::vec3(0.0, -1.0, 0.0)));
    lightMatrices.push_back(lightProj * glm::lookAt(position, (position + glm::vec3(-1.0, 0.0, 0.0)), glm::vec3(0.0, -1.0, 0.0)));
    // +y, -y
    lightMatrices.push_back(lightProj * glm::lookAt(position, (position + glm::vec3(0.0, 1.0, 0.0)), glm::vec3(0.0, 0.0, 1.0)));
    lightMatrices.push_back(lightProj * glm::lookAt(position, (position + glm::vec3(0.0, -1.0, 0.0)), glm::vec3(0.0, 0.0, -1.0)));
    // +z, -z
    lightMatrices.push_back(lightProj * glm::lookAt(position, (position + glm::vec3(0.0, 0.0, 1.0)), glm::vec3(0.0, -1.0, 0.0)));
    lightMatrices.push_back(lightProj * glm::lookAt(position, (position + glm::vec3(0.0, 0.0, -1.0)), glm::vec3(0.0, -1.0, 0.0)));
    
    return lightMatrices;
}

GLfloat PointLight::GetFarPlane() {
    return farPlane;
}

glm::vec3 PointLight::GetPosition() {
    return position;
}

PointLight::~PointLight() {
    
}
