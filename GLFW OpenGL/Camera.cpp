#include "Camera.hpp"

//TODO Why camera looks backwards?

Camera::Camera() {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    yaw = 90.0f;
    pitch = 0.0f;
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    
    moveSpeed = 0.01f;
    turnSpeed = 1.0f;
    
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed) {
    position = startPosition;
    worldUp = startUp;
    yaw = startYaw;
    pitch = startPitch;
    front = glm::vec3(0.0f, 0.0f, -1.0f);

    moveSpeed = startMoveSpeed;
    turnSpeed = startTurnSpeed;
    
    update();
}

void Camera::update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch)); //Requires "-" to be faced toward -z axis
    front = glm::normalize(front);
    
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
    
    // Added a new call to calculate 'forward' by doing the cross product of 'worldUp' and 'right', then normalizing it.
    forward = glm::normalize(glm::cross(worldUp, right));
}

glm::mat4 Camera::calculateViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition() {
    return position;
}

glm::vec3 Camera::getCameraDirection() {
    return glm::normalize(front);
}


void Camera::keyControl(bool* keys, GLfloat deltaTime) {
    GLfloat velocity = moveSpeed * deltaTime;
    
    if (keys[GLFW_KEY_W]) {
        //position += front * velocity;
        
        //For movement in xz plane only
        position += forward * velocity;
    } else if (keys[GLFW_KEY_S]) {
        //position -= front * velocity;
        
        //For movement in xz plane only
        position -= forward * velocity;
    } else if (keys[GLFW_KEY_A]) {
        position -= right * velocity;
    } else if (keys[GLFW_KEY_D]) {
        position += right * velocity;
    }
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
    xChange *= turnSpeed;
    yChange *= turnSpeed;
    
    yaw += xChange; //Requires "-=" if front.z update has a "-"
    pitch += yChange;
   
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89) {
        pitch = -89.0f;
    }
    
    update();
    
    
}

Camera::~Camera() {
    
}

