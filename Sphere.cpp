#include <windows.h> 
#include "Sphere.h"

// Default for matte materials
Sphere::Sphere(float color[3], float radius, float center[3]) {
    memcpy(this->color, color, sizeof(this->color));
    this->radius = radius;
    memcpy(this->center, center, sizeof(this->center));
    this->specularExponent = -1;
}

// Override for glossy materials
Sphere::Sphere(float color[3], float radius, float center[3], float specularExponent) {
    memcpy(this->color, color, sizeof(this->color));
    this->radius = radius;
    memcpy(this->center, center, sizeof(this->center));
    this->specularExponent = specularExponent;
}