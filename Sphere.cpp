#include "Sphere.h"

// Default 
Sphere::Sphere() {
    memcpy(this->color, new float[3] {0, 0, 0}, sizeof(this->color));
    this->radius = 0;
    memcpy(this->center, new float[3] {0, 0, 0}, sizeof(this->center));
    this->specularExponent = -1;
    this->reflective = 0.0f;
}

// Override for matte materials
Sphere::Sphere(float color[3], float radius, float center[3], float reflective) {
    memcpy(this->color, color, sizeof(this->color));
    this->radius = radius;
    memcpy(this->center, center, sizeof(this->center));
    this->specularExponent = -1;
    this->reflective = reflective;
}

// Override for glossy materials
Sphere::Sphere(float color[3], float radius, float center[3], float specularExponent, float reflective) {
    memcpy(this->color, color, sizeof(this->color));
    this->radius = radius;
    memcpy(this->center, center, sizeof(this->center));
    this->specularExponent = specularExponent;
    this->reflective = reflective;
}