//#define STB_IMAGE_IMPLEMENTATION
//
//#include <iostream>
//#include<stdio.h>
//#include<string.h>
//#include<cmath>
//#include<vector>
//
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//#include "GLM/glm.hpp"
//#include "GLM/gtc/matrix_transform.hpp"
//#include "GLM/gtc/type_ptr.hpp"
//#include "assimp/Importer.hpp"
//
//#include "CommonValues.h"
//
//#include "Mesh.hpp"
//#include "Shader.hpp"
//#include "MyWindow.hpp"
//#include "Camera.hpp"
//#include "Texture.hpp"
//#include "DirectionalLight.hpp"
//#include "PointLight.hpp"
//#include "SpotLight.hpp"
//#include "Material.hpp"
//#include "Model.hpp"
//
//
////const float toRadians = 3.14159265f / 180.0f;
//
//MyWindow mainWindow;
//std::vector<Mesh*> meshList;
//std::vector<Shader> shaderList;
//Camera camera;
//
//Texture brickTexture;
//Texture dirtTexture;
//Texture plainTexture;
//
//
//Material shinyMaterial;
//Material dullMaterial;
//
//Model plant;
//
//DirectionalLight mainLight;
//PointLight pointLights[MAX_POINT_LIGHTS];
//SpotLight spotLights[MAX_SPOT_LIGHTS];
//
//GLfloat deltaTime = 0.0f;
//GLfloat lastTime = 0.0f;
//
//static const char* vShader = "Shaders/shader.vert";
//static const char* fShader = "Shaders/shader.frag";
//
//void calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset) {
//    for(size_t i = 0;i < indiceCount; i += 3) {
//        unsigned int in0 = indices[i] * vLength;
//        unsigned int in1 = indices[i+1] * vLength;
//        unsigned int in2 = indices[i+2] * vLength;
//        
//        glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]); //Why minus?
//        glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
//        glm::vec3 normal = glm::cross(v1, v2);
//        normal = glm::normalize(normal);
//        
//        in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
//        vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
//        vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
//        vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
//    }
//    
//    for(size_t i = 0; i < verticeCount / vLength; i++) {
//        unsigned int nOffset = static_cast<int>(i * vLength + normalOffset);
//        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
//        vec = glm::normalize(vec);
//        vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
//    }
//}
//
//void CreateObjects(){
//    unsigned int indices[] = {
//        0, 3, 1,
//        1, 3, 2,
//        2, 3, 0,
//        0, 1, 2
//    };
//    
//    GLfloat vertices[] = {
//        //x      y     z        u     v         normals.x .y .z
//        -1.0f, -1.0f, -0.5f,    0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
//        0.0f, -1.0f, 1.0f,      0.5f, 0.0f,     0.0f, 0.0f, 0.0f,
//        1.0f, -1.0f,  -0.5f,    1.0f, 0.0f,     0.0f, 0.0f, 0.0f,
//        0.0f, 1.0f,  0.0f,      0.5f, 1.0f,     0.0f, 0.0f, 0.0f
//    };
//    
//    unsigned int floorIndices[] = {
//        0, 2, 1,
//        2, 0, 3
//    };
//    
//    GLfloat floorVertices[] = {
//        -10.0f, 0.0f, -10.0f,    0.0f, 0.0f,    0.0f, -1.0f, 0.0f,
//        10.0f, 0.0f, -10.0f,     10.0f, 0.0f,   0.0f, -1.0f, 0.0f,
//        10.0f, 0.0f, 10.0f,      10.0f, 10.0f,  0.0f, -1.0f, 0.0f,
//        -10.0f, 0.0f, 10.0f,     0.0f, 10.0f,   0.0f, -1.0f, 0.0f
//    };
//    
//    calcAverageNormals(indices, 12, vertices, 32, 8, 5);
//    
//    Mesh *obj1 = new Mesh();
//    obj1->CreateMesh(vertices, indices, 32, 12);
//    meshList.push_back(obj1);
//    
//    Mesh *obj2 = new Mesh();
//    obj2->CreateMesh(vertices, indices, 32, 12);
//    meshList.push_back(obj2);
//    
//    Mesh *obj3 = new Mesh();
//    obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
//    meshList.push_back(obj3);
//}
//
//void CreateShaders() {
//    Shader *shader1 = new Shader();
//    shader1->CreateFromFiles(vShader, fShader);
//    shaderList.push_back(*shader1);
//}
//
//int main() {
//    
//    mainWindow = MyWindow(1366, 768);
//    mainWindow.Initialise();
//    
//    CreateObjects();
//    CreateShaders();
//    
//    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f, 5.0f, 0.5f); //-90? - rotates camera's startYaw
//    
//    brickTexture = Texture("Textures/brick.png");
//    brickTexture.LoadTextureA();
//    dirtTexture = Texture("Textures/dirt.png");
//    dirtTexture.LoadTextureA();
//    plainTexture = Texture("Textures/plain.png");
//    plainTexture.LoadTextureA();
//    
//    //brickTexture.UseTexture();
//    
//    shinyMaterial = Material(1.0f, 32); //typical average shiny specular
//    dullMaterial = Material(0.3f, 4);
//    
//    plant = Model();
//    plant.LoadModel("Models/01Alocasia_obj.obj");
//    
//    mainLight = DirectionalLight(0.5f, 0.5f, 0.5f,
//                                 1.0f, 0.5f,
//                                 2.0f, -1.0f, -2.0f);
//    
//    unsigned int pointLightCount = 0;
//    pointLights[0] = PointLight(0.0f, 1.0f, 0.0f,
//                                0.1f, 0.3f,
//                                -4.0f, 0.0f, 0.0f,
//                                0.3f, 0.2f, 0.1f);
//    pointLightCount++;
//    pointLights[1] = PointLight(1.0f, 0.0f, 0.0f,
//                                0.1f, 0.5f,
//                                4.0f, 2.0f, 0.0f,
//                                0.2f, 0.1f, 0.1f);
//    pointLightCount++;
//    
//    unsigned int spotLightCount = 0;
//    spotLights[0] = SpotLight(0.2f, 0.2f, 0.8f,
//                              0.0f, 2.0f,
//                              1.0f, 3.0f, -1.0f,
//                              0.0f, -1.0f, 1.0f,
//                              1.0f, 0.1f, 0.0f,
//                              20.0f);
//    spotLightCount++;
//    spotLights[1] = SpotLight(0.7f, 1.0f, 1.0f,
//                              0.0f, 0.0f,       // 0.5f, 0.1f,
//                              0.0f, 0.0f, 0.0f,
//                              -100.0f, -1.0f, 0.0f,
//                              0.0f, 0.1f, 0.0f,
//                              20.0f);
//    spotLightCount++;
//    
//    
//    GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
//    uniformSpecularIntensity = 0, uniformShininess = 0;
//    
//    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f); //glm::radians(45.0f)?
//    
//    //Loop
//    while (!mainWindow.getShouldClose()) {
//        GLfloat now = glfwGetTime(); // For SDL - SDL_GetPerformanceCounter();
//        deltaTime = now - lastTime; // ((now - lastTime) * 1000) / SDL_GetPerformanceFrequency();
//        lastTime = now;
//        
//        glfwPollEvents();
//        
//        camera.keyControl(mainWindow.getKeys(), deltaTime);
//        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
//        
//        //Clear the window
//        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        
//        shaderList[0].UseShader();
//        uniformModel = shaderList[0].GetModelLocation();
//        uniformProjection = shaderList[0].GetProjectionLocation();
//        uniformView = shaderList[0].GetViewLocation();
//        uniformEyePosition = shaderList[0].GetEyePositionLocation();
//        uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
//        uniformShininess = shaderList[0].GetShininessLocation();
//        
//        glm::vec3 lowerLight = glm::vec3(0.0f, 1.0f, 0.0f);
//        spotLights[1].SetFlash((camera.getCameraPosition() - lowerLight), camera.getCameraDirection());
//        
//        shaderList[0].SetDirectionalLight(&mainLight);
//        shaderList[0].SetPointLights(pointLights, pointLightCount);
//        shaderList[0].SetSpotLights(spotLights, spotLightCount);
//        
//        
//        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
//        glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z); //vec3(camera.getCameraPosition())
//        
//        //To create an identity matrix, you now need to use glm::mat4 model(1.0f);
//        glm::mat4 model(1.0f);
//        model = glm::translate(model, glm::vec3(0.0f, -1.0f, 2.5f)); //Is "-z" or "+z" correct?
//        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//        brickTexture.UseTexture();
//        shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
//        meshList[0]->RenderMesh();
//        
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(0.0f, 0.5f, 2.5f));
//        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.5f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//        dirtTexture.UseTexture();
//        dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
//        meshList[1]->RenderMesh();
//        
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//        dirtTexture.UseTexture();
//        shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
//        meshList[2]->RenderMesh();
//        
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(3.0f, -3.0f, 3.0f));
//        model = glm::scale(model, glm::vec3(0.002f, 0.002f, 0.002f));
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//        shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
//        plant.RenderModel();
//        
//        glUseProgram(0);
//        
//        mainWindow.swapBuffers();
//    }
//    
//    //glfwTerminate();
//    return 0;
//}
