#pragma once

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include <GL/glew.h>

#endif /* Mesh_hpp */

class Mesh {
public:
    Mesh();
    
    void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void RenderMesh();
    void ClearMesh();
    
    ~Mesh();
    
private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
};
