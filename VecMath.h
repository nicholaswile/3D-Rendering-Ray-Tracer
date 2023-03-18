#include "Windows.h"
#include <math.h> // gives sqrt()


#pragma once

class VecMath {
public: 
    float* aTob(float a[3], float b[3]);
    float aDotb(float a[3], float b[3]);
    float* Scale(float a[3], float scalar);
    float* Add(float a[3], float b[3]);
    float Length(float a[3]);
};

