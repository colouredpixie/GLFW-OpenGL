//#include "DirectionalLight.hpp"
//
//DirectionalLight::DirectionalLight() : Light() {
//    direction = glm::vec3(0.0f, -1.0f, 0.0f);
//}
//
//DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
//                                   GLfloat aIntensity, GLfloat dIntensity,
//                                   GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(red, green, blue, aIntensity, dIntensity) {
//    direction = glm::vec3(xDir, yDir, zDir);
//}
//
//void DirectionalLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
//                                GLuint diffuseIntensityLocation, GLuint directionLocation) {
//    glUniform1f(ambientIntensityLocation, ambientIntensity);
//    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
//
//    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
//    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
//}
//
//DirectionalLight::~DirectionalLight() {
//
//}
