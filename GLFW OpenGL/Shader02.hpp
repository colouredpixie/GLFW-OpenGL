//#ifndef Shader_hpp
//#define Shader_hpp
//
//#include <stdio.h>
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <GL/glew.h>
//
//#endif /* Shader_hpp */
//
//class Shader {
//public:
//    Shader();
//    
//    void CreateFromString(const char* vertexCode, const char* fragmentCode);
//    void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
//    
//    std::string ReadFile(const char* fileLocation);
//    
//    GLuint GetProjectionLocation();
//    GLuint GetModelLocation();
//    GLuint GetViewLocation(); //added for use with camera movement
//    GLuint GetAmbientIntensityLocation(); //added with Lights
//    GLuint GetAmbientColourLocation();
//    GLuint GetDiffuseIntensityLocation();
//    GLuint GetDirectionLocation();
//    GLuint GetEyePositionLocation();
//    GLuint GetSpecularIntensityLocation();
//    GLuint GetShininessLocation();
//    
//    void UseShader();
//    void ClearShader();
//    void ValidateProgram();
//    
//    ~Shader();
//    
//private:
//    GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
//    uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection,
//    uniformSpecularIntensity, uniformShininess;
//    
//    void CompileShader(const char* vertexCode, const char* fragmentCode);
//    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
//};
