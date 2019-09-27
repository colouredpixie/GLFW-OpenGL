#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight() : Light() {
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
    //lightProj = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 20.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
                                   GLfloat aIntensity, GLfloat dIntensity,
                                   GLfloat xDir, GLfloat yDir, GLfloat zDir,
                                   GLfloat shadowWidth, GLfloat shadowHeight) : Light(red, green, blue, aIntensity, dIntensity, shadowWidth, shadowHeight) {
    direction = glm::vec3(xDir, yDir, zDir);
    lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

void DirectionalLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
                     GLuint diffuseIntensityLocation, GLuint directionLocation) {
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);

    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
}

glm::mat4 DirectionalLight::CalculateLightTransform(){
    glm::mat4 temp = (lightProj * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    return temp;
}

DirectionalLight::~DirectionalLight() {

}


