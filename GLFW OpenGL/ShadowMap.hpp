#pragma once

#ifndef ShadowMap_hpp
#define ShadowMap_hpp

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>

#endif /* ShadowMap_hpp */

class ShadowMap {
public:
    ShadowMap();
    
    virtual bool Init(GLuint width, GLuint height);
    
    virtual void Write();
    virtual void Read(GLenum textureUnit);
    
    GLuint GetShadowWidth() { return shadowWidth; }
    GLuint GetShadowHeight() { return shadowHeight; }
    
    ~ShadowMap();
    
protected:
    GLuint FBO, shadowMap;
    GLuint shadowWidth, shadowHeight;
    
};
