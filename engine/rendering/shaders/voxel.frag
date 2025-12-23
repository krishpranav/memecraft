#version 330 core
out vec4 FragColor;

in vec3 vWorldPos;
in float vFace;

uniform vec3 u_CameraPos;
uniform float u_WorldRadius;

vec3 lightDir = normalize(vec3(0.4, 1.0, 0.6));

vec3 skyTop    = vec3(0.52, 0.74, 0.96);
vec3 skyHorizon= vec3(0.78, 0.86, 0.92);
vec3 fogColor  = skyHorizon;

void main() {
    vec3 color = vec3(0.35, 0.65, 0.35);

    float faceShade = 1.0;
    if (vFace == 1.0) faceShade = 0.55;
    else if (vFace == 2.0) faceShade = 0.8;

    float diff = clamp(dot(lightDir, vec3(0,1,0)), 0.25, 1.0);
    vec3 lit = color * diff * faceShade;

    float dist = length(vWorldPos - u_CameraPos);
    float fogDist = 1.0 - exp(-dist * 0.015);

    float heightFog = clamp((vWorldPos.y - 40.0) / 120.0, 0.0, 1.0);

    float fog = clamp(fogDist + heightFog * 0.35, 0.0, 1.0);

    vec3 finalColor = mix(lit, fogColor, fog);

    float borderDist = length(vWorldPos.xz);
    float borderFade = smoothstep(
        u_WorldRadius - 40.0,
        u_WorldRadius,
        borderDist
    );

    finalColor = mix(finalColor, fogColor, borderFade);

    finalColor = pow(finalColor, vec3(1.0 / 2.2));
    FragColor = vec4(finalColor, 1.0);
}