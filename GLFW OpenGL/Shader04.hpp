//#ifndef Shader_hpp
//#define Shader_hpp
//
//#include <stdio.h>
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <GL/glew.h>
//
//#include "DirectionalLight.hpp"
//#include "PointLight.hpp"
//#include "SpotLight.hpp"
//
//#include "CommonValues.h"
//
//#endif /* Shader_hpp */
//
//class Shader {
//    public:
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
//    void SetDirectionalLight(DirectionalLight * dLight);
//    void SetPointLights(PointLight * pLight, unsigned int lightCount);
//    void SetSpotLights(SpotLight * sLight, unsigned int lightCount);
//    
//    void UseShader();
//    void ClearShader();
//    void ValidateProgram();
//    
//    ~Shader();
//    
//    private:
//    int pointLightCount;
//    int spotLightCount;
//    
//    GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
//    uniformSpecularIntensity, uniformShininess;
//    
//    struct {
//        GLuint uniformColour;
//        GLuint uniformAmbientIntensity;
//        GLuint uniformDiffuseIntensity;
//        
//        GLuint uniformDirection;
//    } uniformDirectionalLight;
//    
//    GLuint uniformPointLightCount;
//    
//    struct {
//        GLuint uniformColour;
//        GLuint uniformAmbientIntensity;
//        GLuint uniformDiffuseIntensity;
//        
//        GLuint uniformPosition;
//        
//        GLuint uniformConstant;                 // Should these be "float"?
//        GLuint uniformLinear;                   //
//        GLuint uniformExponent;                 //
//    } uniformPointLight[MAX_POINT_LIGHTS];
//    
//    GLuint uniformSpotLightCount;
//    
//    struct {
//        GLuint uniformColour;
//        GLuint uniformAmbientIntensity;
//        GLuint uniformDiffuseIntensity;
//        
//        GLuint uniformPosition;
//        GLuint uniformDirection;
//        
//        GLuint uniformConstant;
//        GLuint uniformLinear;
//        GLuint uniformExponent;
//        
//        GLuint uniformEdge;
//    } uniformSpotLight[MAX_SPOT_LIGHTS];
//    
//    void CompileShader(const char* vertexCode, const char* fragmentCode);
//    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
//};
