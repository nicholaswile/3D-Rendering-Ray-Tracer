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
    // a + b is the same as a - (-b)
    float bReverse[3];
    float sum[3];
    memcpy(bReverse, Scale(b, -1), sizeof(bReverse));
    memcpy(sum, aTob(a, bReverse), sizeof(sum));
    return sum;
}

float VecMath::Length(float a[3]) {
    return sqrt(aDotb(a, a));
}