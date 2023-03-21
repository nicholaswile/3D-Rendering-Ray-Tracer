#include "Sphere.h"

// Default 
Sphere::Sphere() {
    memcpy(this->color, new float[3] {0, 0, 0}, sizeof(this->color));
    this->radius = 0;
    memcpy(this->center, new float[3] {0, 0, 0}, sizeof(this->center));
    this->specularExponent = -1;
}

// Override for matte materials
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