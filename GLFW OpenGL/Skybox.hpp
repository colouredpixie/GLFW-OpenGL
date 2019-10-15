#pragma once

#ifndef Skybox_hpp
#define Skybox_hpp

#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

#include "CommonValues.h"
#include "Shader.hpp"
#include "Mesh.hpp"

#endif /* Skybox_hpp */

class Skybox {
public:
    Skybox();
    
    Skybox(std::vector<std::string> faceLocations);
    
    void DrawSkyBox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
    
    ~Skybox();
    
private:
    Mesh * skyMesh;
    Shader * skyShader;
    
    GLuint textureId;
    GLuint uniformProjection, uniformView;
};
