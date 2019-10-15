#include "Shader.hpp"

Shader::Shader() {
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
    
    pointLightCount = 0;
    spotLightCount = 0;
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {
    CompileShader(vertexCode, fragmentCode);
    
}

std::string Shader::ReadFile(const char* fileLocation) {
    std::string content;
    std::ifstream fileStream(fileLocation, std::ios::in);
    
    if (!fileStream.is_open()) {
        std::cout << "Failed to read " << fileLocation << " File doesn't exist." << std::endl;
        return "";
    }
    
    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    
    fileStream.close();
    return content;
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation) {
    std::string vertexString = ReadFile(vertexLocation);
    std::string fragmentString = ReadFile(fragmentLocation);
    
    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();
    
    CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation) {
    std::string vertexString = ReadFile(vertexLocation);
    std::string geometryString = ReadFile(geometryLocation);
    std::string fragmentString = ReadFile(fragmentLocation);
    
    const char* vertexCode = vertexString.c_str();
    const char* geometryCode = geometryString.c_str();
    const char* fragmentCode = fragmentString.c_str();
    
    CompileShader(vertexCode, geometryCode, fragmentCode);
}

void Shader::CompileProgram() {
    GLint result = 0;
    GLchar eLog[1024] =  { 0 };
    
    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        std::cout << "Error linking program:: " << eLog  << std::endl;
        return;
    }
    
    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
    uniformDirectionalLight.uniformColour = glGetUniformLocation(shaderID, "directionalLight.base.colour");
    uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
    uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
    uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
    uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");
    uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
    uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
    
    uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");
    
    for(size_t i = 0; i < MAX_POINT_LIGHTS; i++) {
        char locBuff[100] = { '\0' };
        
        snprintf( locBuff, sizeof(locBuff), "pointLights[%zu].base.colour", i);
        uniformPointLight[i].uniformColour = glGetUniformLocation(shaderID, locBuff);
        
        snprintf( locBuff, sizeof(locBuff), "pointLights[%zu].base.ambientIntensity", i);
        uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);
        
        snprintf( locBuff, sizeof(locBuff), "pointLights[%zu].base.diffuseIntensity", i);
        uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);
        
        snprintf( locBuff, sizeof(locBuff), "pointLights[%zu].position", i);
        uniformPointLight[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);
        
        snprintf( locBuff, sizeof(locBuff), "pointLights[%zu].constant", i);
        uniformPointLight[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);
        
        snprintf( locBuff, sizeof(locBuff), "pointLights[%zu].linear", i);
        uniformPointLight[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);
        
        snprintf( locBuff, sizeof(locBuff), "pointLights[%zu].exponent", i);
        uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderID, locBuff);
    }
    
    uniformSpotLightCount = glGetUniformLocation(shaderID, "spotLightCount");
    
    for(size_t i = 0; i < MAX_SPOT_LIGHTS; i++) {
        char locBuff[100] = { '\0' };
        
        snprintf( locBuff, sizeof(locBuff), "spotLights[%zu].base.base.colour", i);
        uniformSpotLight[i].uniformColour = glGetUniformLocation(shaderID, locBuff);
        
        snprintf( locBuff, sizeof(locBuff), "spotLights[%zu].base.base.ambientIntensity", i);
        uniformSpotLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);
        
        snprintf( locBuff, sizeof(locBuff), "spotLights[%zu].base.base.diffuseIntensity", i);
        uniformSpotLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);
        
        snprintf( locBuff, sizeof(locBuff), "spotLights[%zu].base.position", i);
        uniformSpotLight[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);
        
        snprintf( locBuff, sizeof(locBuff), "spotLights[%zu].direction", i);
        uniformSpotLight[i].uniformDirection = glGetUniformLocation(shaderID, locBuff);
        
        snprintf( locBuff, sizeof(locBuff), "spotLights[%zu].base.constant", i);
        uniformSpotLight[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);
        
        snprintf( locBuff, sizeof(locBuff), "spotLights[%zu].base.linear", i);
        uniformSpotLight[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);
        
        snprintf( locBuff, sizeof(locBuff), "spotLights[%zu].base.exponent", i);
        uniformSpotLight[i].uniformExponent = glGetUniformLocation(shaderID, locBuff);
        
        snprintf( locBuff, sizeof(locBuff), "spotLights[%zu].edge", i);
        uniformSpotLight[i].uniformEdge = glGetUniformLocation(shaderID, locBuff);
    }
    
    for (size_t i = 0; i < (MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS); i++) {
        char locBuff[100] = { '\0' };
        
        snprintf( locBuff, sizeof(locBuff), "omniShadowMaps[%zu].shadowMap", i);
        uniformOmniShadowMap[i].uniformShadowMap = glGetUniformLocation(shaderID, locBuff);
        
        snprintf( locBuff, sizeof(locBuff), "omniShadowMaps[%zu].farPlane", i);
        uniformOmniShadowMap[i].uniformFarPlane = glGetUniformLocation(shaderID, locBuff);
    }
    
    uniformTexture = glGetUniformLocation(shaderID, "theTexture");
    uniformDirectionalLightTransform = glGetUniformLocation(shaderID, "directionalLightTransform");
    uniformDirectionalShadowMap = glGetUniformLocation(shaderID, "directionalShadowMap");
    
    uniformOmniLightPos = glGetUniformLocation(shaderID, "lightPos");
    uniformFarPlane = glGetUniformLocation(shaderID, "farPlane");
    
    for (size_t i = 0; i < 6; i++) {
        char locBuff[100] = { '\0' };
        
        snprintf( locBuff, sizeof(locBuff), "lightMatrices[%zu]", i);
        uniformLightMatrices[i] = glGetUniformLocation(shaderID, locBuff);
    }
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode) {
    shaderID = glCreateProgram();
    
    if (!shaderID){
        std::cout << "Error creating 2-shader program." << std::endl;
        return; //Will crash the program, because returns straight to main()
    }
    
    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);
    
    CompileProgram();
}

void Shader::CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode) {
    shaderID = glCreateProgram();
    
    if (!shaderID){
        std::cout << "Error creating 3-shader program." << std::endl;
        return; //Will crash the program, because returns straight to main()
    }
    
    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, geometryCode, GL_GEOMETRY_SHADER);
    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);
    
    CompileProgram();
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);
    
    const GLchar* theCode[1];
    theCode[0] = shaderCode;
    
    GLint codeLength[1];
    codeLength[0] = (static_cast<GLint>(strlen(shaderCode))); //added "static_cast" to implicitly convert long to int
    
    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);
    
    GLint result = 0;
    GLchar eLog[1024] =  { 0 };
    
    glLinkProgram(theShader);
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(theShader,sizeof(eLog), NULL, eLog);
        std::cout << "Error compiling the " << shaderType << " shader: " << eLog << std::endl;
        return;
    }
    
    glAttachShader(theProgram, theShader);
}

GLuint Shader::GetProjectionLocation() {
    return uniformProjection;
}

GLuint Shader::GetModelLocation() {
    return uniformModel;
}

//added for use with camera movement
GLuint Shader::GetViewLocation() {
    return uniformView;
}

GLuint Shader::GetAmbientColourLocation() {
    return uniformDirectionalLight.uniformColour;
}

GLuint Shader::GetAmbientIntensityLocation() {
    return uniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::GetDiffuseIntensityLocation() {
    return uniformDirectionalLight.uniformDiffuseIntensity;
}

GLuint Shader::GetDirectionLocation() {
    return uniformDirectionalLight.uniformDirection;
}

GLuint Shader::GetEyePositionLocation() {
    return uniformEyePosition;
}

GLuint Shader::GetSpecularIntensityLocation() {
    return uniformSpecularIntensity;
}

GLuint Shader::GetShininessLocation() {
    return uniformShininess;
}

GLuint Shader::GetOmniLightPosLocation() {
    return uniformOmniLightPos;
}

GLuint Shader::GetFarPlaneLocation() {
    return uniformFarPlane;
}


void Shader::SetDirectionalLight(DirectionalLight * dLight) {
    dLight->UseLight(uniformDirectionalLight.uniformAmbientIntensity, uniformDirectionalLight.uniformColour,
                     uniformDirectionalLight.uniformDiffuseIntensity, uniformDirectionalLight.uniformDirection);
}

void Shader::SetPointLights(PointLight * pLight, unsigned int LightCount, unsigned int textureUnit, unsigned int offset) {
    if (LightCount > MAX_POINT_LIGHTS) LightCount = MAX_POINT_LIGHTS;
    
    glUniform1i(uniformPointLightCount, LightCount);
    
    for (size_t i = 0; i < LightCount; i++) {
        pLight[i].UseLight(uniformPointLight[i].uniformAmbientIntensity, uniformPointLight[i].uniformColour, uniformPointLight[i].uniformDiffuseIntensity, uniformPointLight[i].uniformPosition, uniformPointLight[i].uniformConstant, uniformPointLight[i].uniformLinear, uniformPointLight[i].uniformExponent);
        
        pLight[i].GetShadowMap()->Read(GL_TEXTURE0 + textureUnit + i);
        glUniform1i(uniformOmniShadowMap[i + offset].uniformShadowMap, (textureUnit + i));
        glUniform1f(uniformOmniShadowMap[i + offset].uniformFarPlane, pLight[i].GetFarPlane());

    }
}

void Shader::SetSpotLights(SpotLight * sLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset) {
    if (lightCount > MAX_SPOT_LIGHTS) { lightCount = MAX_SPOT_LIGHTS; }
    
    glUniform1i(uniformSpotLightCount, lightCount);
    
    for (size_t i = 0; i < lightCount; i++) {
        sLight[i].UseLight(uniformSpotLight[i].uniformAmbientIntensity, uniformSpotLight[i].uniformColour, uniformSpotLight[i].uniformDiffuseIntensity,
                           uniformSpotLight[i].uniformPosition, uniformSpotLight[i].uniformDirection,
                           uniformSpotLight[i].uniformConstant, uniformSpotLight[i].uniformLinear, uniformSpotLight[i].uniformExponent,
                           uniformSpotLight[i].uniformEdge);
        
        sLight[i].GetShadowMap()->Read(GL_TEXTURE0 + textureUnit + i);
        glUniform1i(uniformOmniShadowMap[i + offset].uniformShadowMap, (textureUnit + i));
        glUniform1f(uniformOmniShadowMap[i + offset].uniformFarPlane, sLight[i].GetFarPlane());
    }
}

void Shader::SetTexture(GLuint textureUnit) {
    glUniform1i(uniformTexture, textureUnit);
}

void Shader::SetDirectionalShadowMap(GLuint textureUnit) {
    glUniform1i(uniformDirectionalShadowMap, textureUnit);
}

void Shader::SetDirectionalLightTransform(glm::mat4 * lTransform) {
    
    glUniformMatrix4fv(uniformDirectionalLightTransform, 1, GL_FALSE, glm::value_ptr(*lTransform));
}

void Shader::SetLightMatrices(std::vector<glm::mat4> lightMatrices) {
    for (size_t i = 0; i < 6; i++) {
        glUniformMatrix4fv(uniformLightMatrices[i], 1, GL_FALSE, glm::value_ptr(lightMatrices[i]));
    }
}


void Shader::UseShader() {
    glUseProgram(shaderID);
}

void Shader::ClearShader() {
    if (shaderID != 0) {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
    
    uniformModel = 0;
    uniformProjection = 0;
}

void Shader::ValidateProgram() {
    GLint result = 0;
    GLchar eLog[1024] =  { 0 };
    
    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        std::cout << "Error validating program: " << eLog << std::endl;
        return;
    }
}

Shader::~Shader() {
    ClearShader();
}
