#pragma once

#ifndef OmniShadowMap_hpp
#define OmniShadowMap_hpp

//#include <stdio.h>
//#include <iostream>
#include "ShadowMap.hpp"

#endif /* OmniShadowMap_hpp */

class OmniShadowMap : public ShadowMap {
public:
    OmniShadowMap();
    
    bool Init(GLuint width, GLuint height);
    
    void Write();
    void Read(GLenum textureUnit);
    
    ~OmniShadowMap();
};
