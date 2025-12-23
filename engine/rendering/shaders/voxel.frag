#version 330 core

in vec2 vUV;
out vec4 FragColor;

vec3 grassTop  = vec3(0.30, 0.60, 0.30);
vec3 dirtSide  = vec3(0.45, 0.30, 0.15);
vec3 dirtBottom= vec3(0.35, 0.25, 0.15);

void main() {
    // vUV.y encodes face type (explained below)
    if (vUV.y < 0.33) {
        FragColor = vec4(grassTop, 1.0);
    } else if (vUV.y < 0.66) {
        FragColor = vec4(dirtSide, 1.0);
    } else {
        FragColor = vec4(dirtBottom, 1.0);
    }
}