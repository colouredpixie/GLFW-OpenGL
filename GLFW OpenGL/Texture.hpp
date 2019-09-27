#pragma once

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <GL/glew.h>
#include "stb_image.h"

#endif /* Texture_hpp */

class Texture {
public:
    Texture();
    Texture(const char* fileLoc);
    
    bool LoadTexture();
    bool LoadTextureA();
    
    void UseTexture();
    void ClearTexture();
    
    ~Texture();
    
private:
    GLuint textureID;
    int width, height, bitDepth;
    
    const char* fileLocation;
};
