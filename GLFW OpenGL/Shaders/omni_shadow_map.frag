#version 410

in vec4 FragPos;

uniform vec3 lightPos;
uniform float farPlane;

void main(){
    float distanc = length(FragPos.xyz - lightPos); // "distance" is the name of a geometric function in GLSL
    distanc = distanc / farPlane;
    gl_FragDepth = distanc;
}
