#include "Windows.h"
#include <math.h> // gives sqrt()


#pragma once

class VecMath {
public: 

    struct Mat3x3 {
        float x1; float y1; float z1;
        float x2; float y2; float z2;
        float x3; float y3; float z3;
    };

    float* aTob(float a[3], float b[3]);
    float aDotb(float a[3], float b[3]);
    float* Scale(float a[3], float scalar);
    float* Add(float a[3], float b[3]);
    float Length(float a[3]);
    float* MultMatByVec(float v[3], Mat3x3 m);
    float* MultVecByVec(float v1[3], float v2[3]);

    
};

