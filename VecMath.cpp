#include "VecMath.h"

float* VecMath::aTob(float a[3], float b[3])
{
    return new float[3] {a[0] - b[0], a[1] - b[1], a[2] - b[2]};
}

float VecMath::aDotb(float a[3], float b[3]) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float* VecMath::Scale(float a[3], float scalar) {
    return new float[3] {scalar* a[0], scalar* a[1], scalar* a[2]};
}

float* VecMath::Add(float a[3], float b[3]) {
    float sum[3];
    for (int i = 0; i < 3; i++) {
        sum[i] = a[i] + b[i];
    }
    return sum;
}

float VecMath::Length(float a[3]) {
    return sqrt(aDotb(a, a));
}