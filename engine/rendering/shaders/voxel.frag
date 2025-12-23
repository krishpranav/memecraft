#version 330 core
out vec4 FragColor;

in vec3 vWorldPos;
in float vFace;

uniform vec3 u_CameraPos;

vec3 lightDir = normalize(vec3(0.4, 1.0, 0.6));
vec3 skyColor = vec3(0.55, 0.75, 0.95);
vec3 fogColor = skyColor;

void main() {

    vec3 color = vec3(0.35, 0.65, 0.35);

    float faceShade = 1.0;
    if (vFace == 0.0) faceShade = 1.0;
    else if (vFace == 1.0) faceShade = 0.55;
    else faceShade = 0.8;

    float diff = clamp(dot(lightDir, vec3(0,1,0)), 0.2, 1.0);
    vec3 lit = color * diff * faceShade;

    float dist = length(vWorldPos - u_CameraPos);
    float fog = clamp(dist / 120.0, 0.0, 1.0);

    vec3 finalColor = mix(lit, fogColor, fog);

    finalColor = pow(finalColor, vec3(1.0 / 2.2));

    FragColor = vec4(finalColor, 1.0);
}