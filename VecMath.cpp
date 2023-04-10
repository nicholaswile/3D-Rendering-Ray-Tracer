#include "VecMath.h"

VecMath::vec3 VecMath::Vector3(float x, float y, float z) {
    return vec3{ x, y, z };
}

VecMath::vec2 VecMath::Vector2(float x, float y) {
    return vec2{ x, y };
}

VecMath::vec3 VecMath::Add(vec3 a, vec3 b) {
    return { a.x + b.x, a.y + b.y, a.z + b.z };
}

VecMath::vec3 VecMath::Subtract(vec3 a, vec3 b) {
    return vec3{ a.x - b.x, a.y - b.y, a.z - b.z };
}

float VecMath::Dot(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z + b.z;
}

VecMath::vec3 VecMath::Scale(vec3 a, float scalar) {
    return vec3{ a.x * scalar, a.y * scalar, a.z * scalar };
}

float VecMath::Length(vec3 a) {
    return sqrt(Dot(a, a));
}