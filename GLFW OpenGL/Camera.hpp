#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>

#include <GL/glew.h>
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

#endif /* Camera_hpp */

class Camera {
public:
    Camera();
    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
    
    void keyControl(bool* keys, GLfloat deltaTime);
    void mouseControl(GLfloat xChange, GLfloat yChange);
    
    glm::vec3 getCameraPosition();
    glm::vec3 getCameraDirection();
    
    glm::mat4 calculateViewMatrix();
    
    ~Camera();
    
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    
    glm::vec3 forward;
    
    GLfloat yaw;
    GLfloat pitch;
    
    GLfloat moveSpeed;
    GLfloat turnSpeed;
    
    void update();
};
