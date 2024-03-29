#pragma once

#ifndef PointLight_hpp
#define PointLight_hpp

#include <vector>
#include "Light.hpp"
#include "OmniShadowMap.hpp"

#endif /* PointLight_hpp */

class PointLight :
public Light {
public:
    PointLight();
    
    PointLight(GLfloat red, GLfloat green, GLfloat blue,
                     GLfloat aIntensity, GLfloat dIntensity,
                     GLfloat xPos, GLfloat yPos, GLfloat zPos,
                     GLfloat cons, GLfloat lin, GLfloat exp,
                     GLfloat shadowWidth, GLfloat shadowHeight,
                     GLfloat near, GLfloat far);
    
    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
                  GLuint diffuseIntensityLocation, GLuint positionLocation,
                  GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);
    
    std::vector<glm::mat4> CalculateLightTransform();
    GLfloat GetFarPlane();
    glm::vec3 GetPosition();
    
    void Toggle() { isOn = !isOn; }
    
    ~PointLight();
    
protected:
    glm::vec3 position;
    
    GLfloat constant, linear, exponent;
    
    GLfloat farPlane;
    
    bool isOn;
};

