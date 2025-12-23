#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aData;

uniform mat4 u_ViewProj;
uniform mat4 u_Model;

out vec3 vWorldPos;
out float vFace;

void main() {
    vec4 world = u_Model * vec4(aPos, 1.0);
    vWorldPos = world.xyz;
    vFace = aData.y;

    gl_Position = u_ViewProj * world;
}