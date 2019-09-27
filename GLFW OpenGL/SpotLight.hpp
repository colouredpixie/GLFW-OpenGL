#pragma once

#ifndef SpotLight_hpp
#define SpotLight_hpp

#include <stdio.h>
#include "PointLight.hpp"

#endif /* SpotLight_hpp */


class SpotLight :
public PointLight {
public:
    SpotLight();
    
    SpotLight(GLfloat red, GLfloat green, GLfloat blue,
               GLfloat aIntensity, GLfloat dIntensity,
               GLfloat xPos, GLfloat yPos, GLfloat zPos,
               GLfloat xDir, GLfloat yDir, GLfloat zDir,
               GLfloat cons, GLfloat lin, GLfloat exp,
               GLfloat edg,
               GLfloat shadowWidth, GLfloat shadowHeight,
               GLfloat near, GLfloat far);
    
    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
                  GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation,
                  GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation,
                  GLuint edgeLocation);
    
    void SetFlash(glm::vec3 pos, glm::vec3 dir);
    
    ~SpotLight();
    
protected:
    glm::vec3 direction;
    
    GLfloat edge, procEdge;
};

