#include <windows.h> 
#include "Sphere.h"

Sphere::Sphere(float color[3], float radius, float center[3]) {
    memcpy(this->color, color, sizeof(this->color));
    this->radius = radius;
    memcpy(this->center, center, sizeof(this->center));
}