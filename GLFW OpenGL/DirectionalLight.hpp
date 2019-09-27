#pragma once

#ifndef DirectionalLight_hpp
#define DirectionalLight_hpp

#include <stdio.h>
#include "Light.hpp"

#endif /* DirectionalLight_hpp */

class DirectionalLight :
    public Light {
    public:
        DirectionalLight();
        
        DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
                         GLfloat aIntensity, GLfloat dIntensity,
                         GLfloat xDir, GLfloat yDir, GLfloat zDir,
                          GLfloat shadowWidth, GLfloat shadowHeight);
        
        void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
                      GLuint diffuseIntensityLocation, GLuint directionLocation);
        
        glm::mat4 CalculateLightTransform();
        
        ~DirectionalLight();
        
    private:
        glm::vec3 direction;
};


