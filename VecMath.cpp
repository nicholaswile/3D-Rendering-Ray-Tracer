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

float* VecMath::MultMatByVec(float v[3], VecMath::Mat3x3 m) {
    float result[3] = { 0, 0, 0 };

    result[0] = m.x1 * v[0] + m.y1 * v[1] + m.z1 * v[2];
    result[1] = m.x2 * v[0] + m.y2 * v[1] + m.z2 * v[2];
    result[2] = m.x3 * v[0] + m.y3 * v[1] + m.z3 * v[2];

    return result;
}

float* VecMath::MultVecByVec(float v1[3], float v2[3]) {
    return new float[3] {v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]};
}