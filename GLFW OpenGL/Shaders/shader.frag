#version 410

in vec4 vCol;
in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 DirectionalLightSpacePos;

out vec4 colour;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

struct Light {
    vec3 colour;
    float ambientIntensity;
    float diffuseIntensity;
};

struct DirectionalLight {
    Light base;
    vec3 direction;
};

struct PointLight {
    Light base;
    vec3 position;
    float constant;
    float linear;
    float exponent;
};

struct SpotLight{
    PointLight base;
    vec3 direction;
    float edge;
};

struct Material {
    float specularIntensity;
    float shininess;
};

struct OmniShadowMap {
    samplerCube shadowMap;
    float farPlane;
};

uniform int pointLightCount;
uniform int spotLightCount;


uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform sampler2D theTexture;
uniform sampler2D directionalShadowMap;
uniform OmniShadowMap omniShadowMaps[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];

uniform Material material;

uniform vec3 eyePosition;

vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1),
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);


float CalcDirectionalShadowFactor(DirectionalLight light) {
    vec3 projCoords = DirectionalLightSpacePos.xyz / DirectionalLightSpacePos.w;
    projCoords = (projCoords * 0.5) + 0.5;
    
    float current = projCoords.z;
    //float closest = texture(directionalShadowMap, projCoords.xy).r; // ".r" gets the first value of "texture" like red in RGB
    
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(light.direction);
    
    float bias = max (0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    
    float shadow = 0.0;
    
    vec2 texelSize = 1.0 / textureSize(directionalShadowMap, 0);
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(directionalShadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += (current - bias) > pcfDepth ? 1.0 : 0.0;
        }
    }
    
    shadow /= 9.0;
    
    if (projCoords.z > 1.0) {
        shadow = 0.0;
    }
    
    return shadow;
}

float CalcOmniShadowFactor(PointLight light, int shadowIndex) {
    vec3 fragToLight = FragPos - light.position;
    float current = length(fragToLight);
        
    float shadow = 0.0;
    float bias = 0.05;
    
//    int samples = 20;
//    
//    float viewDistance = length(eyePosition - FragPos);
//    float diskRadius = (1.0 + (viewDistance / omniShadowMaps[shadowIndex].farPlane)) / 25.0;
//
//    float closest = 0.0;
//    for(int i = 0; i < samples; i++) {
//        closest = texture(omniShadowMaps[shadowIndex].shadowMap, fragToLight + (gridSamplingDisk[i] * diskRadius)).r;
//        closest *= omniShadowMaps[shadowIndex].farPlane;
//
//        if ((current - bias) > closest) {
//            shadow += 1.0;
//        }
//    }
//
//    shadow /= float(samples);
    
    float closest = texture(omniShadowMaps[shadowIndex].shadowMap, fragToLight).r;
    closest *= omniShadowMaps[shadowIndex].farPlane;

    shadow = (current - bias) > closest ? 1.0 : 0.0;
    
    return shadow;
}

vec4 CalcLightByDirection(Light light, vec3 direction, float shadowFactor) {
    vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;
    
    float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);
    vec4 diffuseColour = vec4(light.colour, 1.0f) * light.diffuseIntensity * diffuseFactor;
    
    vec4 specularColour = vec4(0, 0, 0, 0);
    
    if (diffuseFactor > 0.0f) {
        vec3 fragToEye = normalize(eyePosition - FragPos);
        vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));
        
        float specularFactor = dot(fragToEye, reflectedVertex);
        if (specularFactor > 0.0f) {
            specularFactor = pow(specularFactor, material.shininess);
            specularColour = vec4(light.colour * material.specularIntensity * specularFactor, 1.0f);
        }
    }
    
    return (ambientColour + (1.0 - shadowFactor) * (diffuseColour + specularColour));
}

vec4 CalcDirectionalLight() {
    float shadowFactor = CalcDirectionalShadowFactor(directionalLight);
    return CalcLightByDirection(directionalLight.base, directionalLight.direction, shadowFactor);
}

vec4 CalcPointLight(PointLight pLight, int shadowIndex) {
    vec3 direction = FragPos - pLight.position;
    float distance = length(direction);
    direction = normalize(direction);
    
    float shadowFactor = CalcOmniShadowFactor(pLight, shadowIndex);
    
    vec4 colour = CalcLightByDirection(pLight.base, direction, shadowFactor);
    float attenuation = pLight.exponent * distance * distance +
    pLight.linear * distance +
    pLight.constant;
    
    return (colour / attenuation);
}

vec4 CalcSpotLight(SpotLight sLight, int shadowIndex) {
    vec3 rayDirection = normalize(FragPos - sLight.base.position);
    float slFactor = dot(rayDirection, sLight.direction); //slFactor = angle between fragment and spotlight center
    
    if (slFactor > sLight.edge) {
        vec4 colour = CalcPointLight(sLight.base, shadowIndex);

        return colour * (1.0f - (1.0f - slFactor) * (1.0f /(1.0f - sLight.edge)));
    } else {
        return vec4(0, 0, 0, 0);
    }
}

vec4 CalcPointLights() {
    vec4 totalColour = vec4(0, 0, 0, 0);
    for (int i = 0; i < pointLightCount; i++) {
        totalColour += CalcPointLight(pointLights[i], i); // Will work if point lights are rendered first
    }
    
    return totalColour;
}

vec4 CalcSpotLights() {
    vec4 totalColour = vec4(0, 0, 0, 0);
    for (int i = 0; i < spotLightCount; i++) {
        totalColour += CalcSpotLight(spotLights[i], (i + pointLightCount));
    }
    
    return totalColour;
}

void main(){
    vec4 finalColour = CalcDirectionalLight() + CalcPointLights() + CalcSpotLights(); //Should they be separated into three += ?
    
    colour = texture(theTexture, texCoord) * finalColour;
}
