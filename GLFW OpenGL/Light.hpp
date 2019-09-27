#pragma once

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>
#include <GL/glew.h>
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "ShadowMap.hpp"

#endif /* Light_hpp */

class Light {
public:
    Light();

    Light(GLfloat red, GLfloat green, GLfloat blue,
          GLfloat aIntensity, GLfloat dIntensity,
          GLfloat shadowWidth, GLfloat shadowHeight);

    ShadowMap* GetShadowMap() { return shadowMap; }

    ~Light();

protected:
    glm::vec3 colour;
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;

    glm::mat4 lightProj;

    ShadowMap* shadowMap;
};

