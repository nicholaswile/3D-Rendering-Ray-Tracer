#include "Windows.h"
#include <math.h> // gives sqrt()


#pragma once

class VecMath {
public: 
    struct vec3 {
        float x;
        float y;
        float z;
    };

    struct vec2 {
        float x;
        float y;
    };

    vec3 Vector3(float x, float y, float z);
    vec2 Vector2(float x, float y);

    //float* Subtract(float a[3], float b[3]);
    //float Dot(float a[3], float b[3]);
    //float* Scale(float a[3], float scalar);
    //float* Add(float a[3], float b[3]);
    //float Length(float a[3]);

    vec3 Add(vec3 a, vec3 b);
    vec3 Subtract(vec3 a, vec3 b);
    float Dot(vec3 a, vec3 b);
    vec3 Scale(vec3 a, float scalar);
    float Length(vec3 a);
};

