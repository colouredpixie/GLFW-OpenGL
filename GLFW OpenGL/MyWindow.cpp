#include "MyWindow.hpp"
#include <iostream>
#include <stdio.h>


MyWindow::MyWindow() {
    width = 800;
    height = 600;
    
    xChange = 0.0f;
    yChange = 0.0f;
    mouseFirstMoved = true;
    
    for (size_t i = 0; i < 1024; i++) {
        keys[i] = 0;
    }
    
}

MyWindow::MyWindow(GLint windowWidth, GLint windowHeight) {
    width = windowWidth;
    height = windowHeight;
    
    xChange = 0.0f;
    yChange = 0.0f;
    mouseFirstMoved = true;
    
    for (size_t i = 0; i < 1024; i++) {
        keys[i] = 0;
    }
}

int MyWindow::Initialise() {
    
    //glfwInit();
    if (!glfwInit()) {
        std::cout << "GLFW initialisation failed." << std::endl;
        glfwTerminate();
        return 1;
    }
    
    //Setup GLFW window properties
    //OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //CORE PROFILE = no backward compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    mainWindow = glfwCreateWindow(width, height, "Test window", nullptr, nullptr); //NULL, NULL);
    
    //Get buffer size information
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    
    //    if (!mainWindow) {
    //        printf("GLFW window creation failed.");
    //        glfwTerminate();
    //        return 1;
    //    }
    if (nullptr == mainWindow) {
        std::cout << "GLFW window creation failed." << std::endl;
        glfwTerminate();
        return -1;
    }
    
    //Set the current context
    glfwMakeContextCurrent(mainWindow);
    
    //Handle key & mouse input
    createCallbacks();
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    //Allow modern extension access
    glewExperimental = GL_TRUE;
    
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialize GLEW." << std::endl;
        return -1;
    }
    
    //Depth buffer
    glEnable(GL_DEPTH_TEST);
    
    //Create Viewport
    glViewport(0, 0, bufferWidth, bufferHeight);
    
    glfwSetWindowUserPointer(mainWindow, this);
    
    return 0; //??
}

void MyWindow::createCallbacks() {
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat MyWindow::getXChange() {
    GLfloat theChange = xChange;
    xChange = 0.0f;
    return theChange;
}

GLfloat MyWindow::getYChange() {
    GLfloat theChange = yChange;
    yChange = 0.0f;
    return theChange;
}

void MyWindow::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
    MyWindow* theWindow = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));
    
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            theWindow->keys[key]  = true;
            //std::cout << "Pressed: " << key << "\n";
        } else if (action == GLFW_RELEASE) {
            theWindow->keys[key] = false;
            //std::cout << "Released: " << key << "\n";
        }
    }
}

void MyWindow::handleMouse(GLFWwindow *window, double xPos, double yPos) {
    MyWindow* theWindow = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));
    
    if (theWindow->mouseFirstMoved) {
        theWindow->lastX = (GLfloat) xPos;
        theWindow->lastY = (GLfloat) yPos;
        theWindow->mouseFirstMoved = false;
    }
    
    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;
    
    theWindow->lastX = (GLfloat) xPos;
    theWindow->lastY = (GLfloat) yPos;
    
    //std::cout << "x: " << theWindow->xChange << ", y: " << theWindow->yChange << "\n";
}


MyWindow::~MyWindow() {
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
