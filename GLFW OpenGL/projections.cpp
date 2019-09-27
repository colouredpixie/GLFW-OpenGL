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
//
//#include "GLM/glm.hpp"
//#include "GLM/gtc/matrix_transform.hpp"
//#include "GLM/gtc/type_ptr.hpp"
//
//
////Window dimensions
//const GLint WIDTH = 800, HEIGHT = 600;
//const float toRadians = 3.14159265f / 180.0f;
//
//GLuint VAO, VBO, IBO, shader, uniformModel, uniformProjection;
//
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
//
//// Vertex Shader
//static const char* vShader = "                                  \n\
//#version 330                                                    \n\
//\n\
//layout (location = 0) in vec3 pos;                              \n\
//\n\
//out vec4 vCol;                                                  \n\
//\n\
//uniform mat4 model;                                             \n\
//uniform mat4 projection;                                        \n\
//\n\
//void main(){                                                    \n\
//gl_Position = projection * model * vec4(pos, 1.0);          \n\
//vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);                  \n\
//\n\
//}";
//
////Fragment Shader
//static const char* fShader = "                                  \n\
//#version 330                                                    \n\
//\n\
//in vec4 vCol;                                                   \n\
//\n\
//out vec4 colour;                                                \n\
//\n\
//void main(){                                                    \n\
//colour = vCol;                                              \n\
//}";
//
//void CreateTriangle(){
//    unsigned int indices[] = {
//        0, 3, 1,
//        1, 3, 2,
//        2, 3, 0,
//        0, 1, 2
//    };
//    
//    GLfloat vertices[] = {
//        -1.0f, -1.0f, 0.0f,
//        0.0f, -1.0f, 1.0f,
//        1.0f, -1.0f, 0.0f,
//        0.0f, 1.0f, 0.0f
//    };
//    
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//    
//    glGenBuffers(1, &IBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//    
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//    glEnableVertexAttribArray(0);
//    
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    
//    glBindVertexArray(0);
//    //Should unbind EBO / IBO after unbinding VAO!
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//    
//}
//
//void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
//    GLuint theShader = glCreateShader(shaderType);
//    
//    const GLchar* theCode[1];
//    theCode[0] = shaderCode;
//    
//    GLint codeLength[1];
//    codeLength[0] = strlen(shaderCode);
//    
//    glShaderSource(theShader, 1, theCode, codeLength);
//    glCompileShader(theShader);
//    
//    GLint result = 0;
//    GLchar eLog[1024] =  { 0 };
//    
//    glLinkProgram(theShader);
//    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
//    if (!result) {
//        glGetShaderInfoLog(theShader,sizeof(eLog), NULL, eLog);
//        std::cout << "Error compiling the " << shaderType << " shader: " << eLog << std::endl;
//        return;
//    }
//    
//    glAttachShader(theProgram, theShader);
//}
//
//void ValidateProgram(GLuint testShader) {
//    GLint result = 0;
//    GLchar eLog[1024] =  { 0 };
//    
//    glValidateProgram(testShader);
//    glGetProgramiv(testShader, GL_VALIDATE_STATUS, &result);
//    if (!result) {
//        glGetProgramInfoLog(testShader, sizeof(eLog), NULL, eLog);
//        std::cout << "Error validating program: " << eLog << std::endl;
//        return;
//    }
//}
//
//void CompileShaders(){
//    shader = glCreateProgram();
//    
//    if (!shader){
//        std::cout << "Error creating shader program." << std::endl;
//        return; //Will crash the program, because returns straight to main()
//    }
//    
//    AddShader(shader, vShader, GL_VERTEX_SHADER);
//    AddShader(shader, fShader, GL_FRAGMENT_SHADER);
//    
//    GLint result = 0;
//    GLchar eLog[1024] =  { 0 };
//    
//    glLinkProgram(shader);
//    glGetProgramiv(shader, GL_LINK_STATUS, &result);
//    if (!result) {
//        glGetProgramInfoLog(shader,sizeof(eLog), NULL, eLog);
//        std::cout << "Error linking program:: " << eLog  << std::endl;
//        return;
//    }
//    
//    uniformModel = glGetUniformLocation(shader, "model");
//    uniformProjection = glGetUniformLocation(shader, "projection");
//}
//
//int main() {
//    
//    //glfwInit();
//    if (!glfwInit()) {
//        std::cout << "GLFW initialisation failed." << std::endl;
//        glfwTerminate();
//        return 1;
//    }
//    
//    //Setup GLFW window properties
//    //OpenGL version
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    //CORE PROFILE = no backward compatibility
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    //allow forward compatibility
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//    
//    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test window", nullptr, nullptr); //NULL, NULL);
//    
//    
//    //Get buffer size information
//    int bufferWidth, bufferHeight;
//    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
//    
//    //    if (!mainWindow) {
//    //        printf("GLFW window creation failed.");
//    //        glfwTerminate();
//    //        return 1;
//    //    }
//    if (nullptr == mainWindow) {
//        std::cout << "GLFW window creation failed." << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    
//    glfwMakeContextCurrent(mainWindow);
//    
//    glewExperimental = GL_TRUE;
//    
//    if (GLEW_OK != glewInit()) {
//        std::cout << "Failed to initialize GLEW." << std::endl;
//        return -1;
//    }
//    
//    //Depth buffer
//    glEnable(GL_DEPTH_TEST);
//    
//    
//    //Create Viewport
//    glViewport(0, 0, bufferWidth, bufferHeight);
//    
//    CreateTriangle();
//    CompileShaders();
//    
//    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)bufferWidth / (GLfloat)bufferHeight, 0.1f, 100.0f);
//    
//    //Loop
//    while (!glfwWindowShouldClose( mainWindow )) {
//        glfwPollEvents();
//        
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
//        glUseProgram(shader);
//        
//        //To create an identity matrix, you now need to use glm::mat4 model(1.0f);
//        glm::mat4 model(1.0f);
//        model = glm::translate(model, glm::vec3(triOffset, 0.0f, -2.5f));
//        model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
//        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
//        
//        
//        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
//        
//        glBindVertexArray(VAO);
//        ValidateProgram(shader);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //?
//        glBindVertexArray(0);
//        
//        glUseProgram(0);
//        
//        glfwSwapBuffers(mainWindow);
//    }
//    
//    glfwTerminate();
//    
//    return 0;
//}
