#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 vUV;

uniform mat4 u_ViewProj;
uniform mat4 u_Model;

void main() {
    vUV = aUV;
    gl_Position = u_ViewProj * u_Model * vec4(aPos, 1.0);
}