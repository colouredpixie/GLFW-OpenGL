//
//#include "Shader.hpp"
//
//Shader::Shader() {
//    shaderID = 0;
//    uniformModel = 0;
//    uniformProjection = 0;
//}
//
//void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {
//    CompileShader(vertexCode, fragmentCode);
//    
//}
//
//std::string Shader::ReadFile(const char* fileLocation) {
//    std::string content;
//    std::ifstream fileStream(fileLocation, std::ios::in);
//    
//    if (!fileStream.is_open()) {
//        std::cout << "Failed to read " << fileLocation << " File doesn't exist." << std::endl;
//        return "";
//    }
//    
//    std::string line = "";
//    while (!fileStream.eof())
//    {
//        std::getline(fileStream, line);
//        content.append(line + "\n");
//    }
//    
//    fileStream.close();
//    return content;
//}
//
//void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation) {
//    std::string vertexString = ReadFile(vertexLocation);
//    std::string fragmentString = ReadFile(fragmentLocation);
//    
//    const char* vertexCode = vertexString.c_str();
//    const char* fragmentCode = fragmentString.c_str();
//    
//    CompileShader(vertexCode, fragmentCode);
//}
//
//void Shader::CompileShader(const char* vertexCode, const char* fragmentCode) {
//    shaderID = glCreateProgram();
//    
//    if (!shaderID){
//        std::cout << "Error creating shader program." << std::endl;
//        return; //Will crash the program, because returns straight to main()
//    }
//    
//    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
//    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);
//    
//    GLint result = 0;
//    GLchar eLog[1024] =  { 0 };
//    
//    glLinkProgram(shaderID);
//    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
//    if (!result) {
//        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
//        std::cout << "Error linking program:: " << eLog  << std::endl;
//        return;
//    }
//    
//    uniformModel = glGetUniformLocation(shaderID, "model");
//    uniformProjection = glGetUniformLocation(shaderID, "projection");
//    uniformView = glGetUniformLocation(shaderID, "view");
//    uniformAmbientColour = glGetUniformLocation(shaderID, "directionalLight.colour");
//    uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");
//    uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.diffuseIntensity");
//    uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
//    uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");
//    uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
//    uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
//    
//}
//
//void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
//    GLuint theShader = glCreateShader(shaderType);
//    
//    const GLchar* theCode[1];
//    theCode[0] = shaderCode;
//    
//    GLint codeLength[1];
//    codeLength[0] = (static_cast<GLint>(strlen(shaderCode))); //added "static_cast" to implicitly convert long to int
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
//void Shader::ValidateProgram() {
//    GLint result = 0;
//    GLchar eLog[1024] =  { 0 };
//    
//    glValidateProgram(shaderID);
//    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
//    if (!result) {
//        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
//        std::cout << "Error validating program: " << eLog << std::endl;
//        return;
//    }
//}
//
//GLuint Shader::GetProjectionLocation() {
//    return uniformProjection;
//}
//
//GLuint Shader::GetModelLocation() {
//    return uniformModel;
//}
//
////added for use with camera movement
//GLuint Shader::GetViewLocation() {
//    return uniformView;
//}
//
//GLuint Shader::GetAmbientColourLocation() {
//    return uniformAmbientColour;
//}
//
//GLuint Shader::GetAmbientIntensityLocation() {
//    return uniformAmbientIntensity;
//}
//
//GLuint Shader::GetDiffuseIntensityLocation() {
//    return uniformDiffuseIntensity;
//}
//
//GLuint Shader::GetDirectionLocation() {
//    return uniformDirection;
//}
//
//GLuint Shader::GetEyePositionLocation() {
//    return uniformEyePosition;
//}
//
//GLuint Shader::GetSpecularIntensityLocation() {
//    return uniformSpecularIntensity;
//}
//
//GLuint Shader::GetShininessLocation() {
//    return uniformShininess;
//}
//
//
//void Shader::UseShader() {
//    glUseProgram(shaderID);
//}
//
//void Shader::ClearShader() {
//    if (shaderID != 0) {
//        glDeleteProgram(shaderID);
//        shaderID = 0;
//    }
//    
//    uniformModel = 0;
//    uniformProjection = 0;
//}
//
//Shader::~Shader() {
//    ClearShader();
//}
