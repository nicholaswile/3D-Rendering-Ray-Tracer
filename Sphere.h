#pragma once
#include <windows.h> // gives memcpy used in Sphere.cpp

class Sphere {
public:
    float color[3];
    float radius;
    float center[3];
    float specularExponent;
    float reflective;
    // Default
    Sphere();
    // Matte
    Sphere(float color[3], float radius, float center[3], float reflective);
    // Specular
    Sphere(float color[3], float radius, float center[3], float specularExponent, float reflective);
    void Copy(Sphere sphere2) {
        memcpy(this->color, sphere2.color, sizeof(this->color));
        this->radius = sphere2.radius;
        memcpy(this->center, sphere2.center, sizeof(this->center));
        this->specularExponent = sphere2.specularExponent;
        this->reflective = sphere2.reflective;
    }
};