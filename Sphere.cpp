#include <windows.h> 
#include "Sphere.h"

Sphere::Sphere(float col[3], float radius, float cent[3]) {
    memcpy(color, col, sizeof(color));
    this->radius = radius;
    memcpy(center, cent, sizeof(center));
}