#pragma once

#ifndef Material_hpp
#define Material_hpp

#include <stdio.h>
#include <GL/glew.h>
//#include "GLM/glm.hpp"

#endif /* Material_hpp */

class Material {
public:
    Material();
    Material(GLfloat sIntensity, GLfloat sshininess);
    
    void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);
    
    ~Material();
    
private:
    GLfloat specularIntensity;
    GLfloat shininess;
};
