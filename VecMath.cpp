#include "VecMath.h"

VecMath::vec3 VecMath::Vector3(float x, float y, float z) {
    return vec3{ x, y, z };
}

VecMath::vec2 VecMath::Vector2(float x, float y) {
    return vec2{ x, y };
}


float* VecMath::Subtract(float a[3], float b[3])
{
    return new float[3] {a[0] - b[0], a[1] - b[1], a[2] - b[2]};
}

//float VecMath::Dot(float a[3], float b[3]) {
//    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
//}

float VecMath::Dot(VecMath::vec3 a, VecMath::vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
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
    VecMath::vec3 VectorA = { a[0], a[1], a[2] };
    return sqrt(Dot(VectorA, VectorA));
}