//#include <iostream>
//
//// GLEW
//#define GLEW_STATIC
//#include <GL/glew.h>
//
//// GLFW
//#include <GLFW/glfw3.h>
//
//#include<stdio.h>
////#include<stdafx.h> //For Microsoft Visual Studio
//#include<string.h>
//#include<cmath>
//#include<vector>
//
//#include "GLM/glm.hpp"
//#include "GLM/gtc/matrix_transform.hpp"
//#include "GLM/gtc/type_ptr.hpp"
//
//#include "Mesh.hpp"
//#include "Shader.hpp"
//#include "MyWindow.hpp"
//
// //Degrees to radians constant
//const float toRadians = 3.14159265f / 180.0f;
//
//MyWindow mainWindow;
//std::vector<Mesh*> meshList;
//std::vector<Shader> shaderList;
//
// //Movement Offset
//bool direction = true;
//float triOffset = 0.0f;
//float triMaxOffset = 0.7f;
//float triIncrement = 0.0005f;
//
//float curAngle = 0.0f;
//
//bool sizeDirection = true;
//float curSize = 0.4f;
//float maxSize = 0.8f;
//float minSize = 0.1f;
//
// //Shader path
//static const char* vShader = "Shaders/shader.vert";
//static const char* fShader = "Shaders/shader.frag";
//
// //Indices matrices
//void CreateObjects(){
//    unsigned int indices[] = {
//        0, 3, 1,
//        1, 3, 2,
//        2, 3, 0,
//        0, 1, 2
//    };
//
// //Vertices matrices
//    GLfloat vertices[] = {
//        -1.0f, -1.0f, 0.0f,
//        0.0f, -1.0f, 1.0f,
//        1.0f, -1.0f, 0.0f,
//        0.0f, 1.0f, 0.0f
//    };
//
// //Create Meshes (duplicate)
//    Mesh *obj1 = new Mesh();
//    obj1->CreateMesh(vertices, indices, 12, 12);
//    meshList.push_back(obj1);
//    
//    Mesh *obj2 = new Mesh();
//    obj2->CreateMesh(vertices, indices, 12, 12);
//    meshList.push_back(obj2);
//}
//
// //Create Shaders (from external classes)
//void CreateShaders() {
//    Shader *shader1 = new Shader();
//    shader1->CreateFromFiles(vShader, fShader);
//    shaderList.push_back(*shader1);
//}
//
//int main() {
//    
//    mainWindow = MyWindow(800, 600);
//    mainWindow.Initialise();
//    
//    CreateObjects();
//    CreateShaders();
//    
//    GLuint uniformProjection = 0, uniformModel = 0;
//    
//    glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
//    
//    //Loop
//    while (!mainWindow.getShouldClose()) {
//        glfwPollEvents();
//
//        // Movement logic
//        if(direction ) {
//            triOffset += triIncrement;
//        } else {
//            triOffset -= triIncrement;
//        }
//        
//        if(abs(triOffset) >= triMaxOffset) {
//            direction = !direction;
//        }
//        
//        curAngle += 0.01f;
//        if(curAngle >= 360) {
//            curAngle = 0; // -= 360;
//        }
//        
//        if (sizeDirection) {
//            curSize += 0.0005f;
//        } else {
//            
//            curSize -= 0.0005f;
//        }
//        
//        if (curSize >= maxSize || curSize <= minSize) {
//            sizeDirection = !sizeDirection;
//        }
//        
//        //Clear the window
//        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//        shaderList[0].UseShader();
//        uniformModel = shaderList[0].GetModelLocation();
//        uniformProjection = shaderList[0].GetProjectionLocation();
//
//        //Models position and rendering (twice)
//        //To create an identity matrix, you now need to use glm::mat4 model(1.0f);
//        glm::mat4 model(1.0f);
//        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
//        model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
//        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        meshList[0]->RenderMesh();
//        
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(triOffset, 1.0f, -2.5f));
//        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        meshList[1]->RenderMesh();
//        //shaderList[0].ValidateProgram(); //Doesn't work
//        
//        glUseProgram(0);
//
//        //Window refresh, using older of two buffers to fill info for new frame
//        mainWindow.swapBuffers();
//    }
//    
//    glfwTerminate();
//    
//    return 0;
//}
