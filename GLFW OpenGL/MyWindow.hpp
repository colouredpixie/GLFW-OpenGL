#pragma once

#ifndef MyWindow_hpp
#define MyWindow_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#endif /* MyWindow_hpp */

class MyWindow {
public:
    MyWindow();
    MyWindow(GLint windowWidth, GLint windowHeight);
    
    int Initialise();
    
    GLfloat getBufferWidth() { return bufferWidth; }
    GLfloat getBufferHeight() { return bufferHeight; }
    
    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
    
    bool* getKeys() { return keys; } //getters and setters?
    // For games: check if mouse was moved, otherwise don't act
    GLfloat getXChange();
    GLfloat getYChange();
    
    void swapBuffers() { glfwSwapBuffers(mainWindow); } 
    
    ~MyWindow();
    
private:
    GLFWwindow *mainWindow;
    
    GLint width, height;
    GLint bufferWidth, bufferHeight;
    
    bool keys[1024];
    
    GLfloat lastX;
    GLfloat lastY;
    GLfloat xChange;
    GLfloat yChange;
    bool mouseFirstMoved;
    
    void createCallbacks();
    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};
