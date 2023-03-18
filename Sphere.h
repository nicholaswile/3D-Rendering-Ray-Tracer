#pragma once
class Sphere {
public:
    float color[3];
    float radius;
    float center[3];
    float specularExponent;
    // Matte
    Sphere(float color[3], float radius, float center[3]);
    // Specular
    Sphere(float color[3], float radius, float center[3], float specularExponent);
};