// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h> // gives ConsoleWindow and SetPixel
#include <list> // gives std::list<Type>
#include <math.h> // gives sqrt()

#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"

#define SCREENWIDTH 1080
#define SCREENHEIGHT 1080
#define MAXFLOAT 4294967296.0f
#define BACKGROUNDCOLOR {0, 0, 0}

float * VectorDirection(float vector1[3], float vector2[3]) {
    return new float[3] {vector1[0] - vector2[0], vector1[1] - vector2[1], vector1[2] - vector2[2]};
}

float VectorDotProduct(float vector1[3], float vector2[3]) {
    return vector1[0] * vector2[0] + vector1[1] * vector2[1] + vector1[2] * vector2[2];
}

// Determines at what point(s) the ray intersects the sphere
float* IntersectRaySphere(float cameraPos[3], float rayDirection[3], Sphere sphere) {
    float radius;
    float camToSphere[3];
    float coeff_a, coeff_b, coeff_c, discriminant;
    float param_t1, param_t2;

    radius = sphere.radius;

    memcpy(camToSphere, VectorDirection(cameraPos, sphere.center), sizeof(camToSphere));
    
    coeff_a = VectorDotProduct(rayDirection, rayDirection);
    coeff_b = 2 * VectorDotProduct(camToSphere, rayDirection);
    coeff_c = VectorDotProduct(camToSphere, camToSphere) - radius * radius;

    // No real solution, therefore the ray does not intersect the sphere
    discriminant = coeff_b * coeff_b - 4 * coeff_a * coeff_c;
    if (discriminant < 0) {
        return new float[2] {MAXFLOAT, MAXFLOAT};
    }

    // Quadratic formula to find two positions where the ray intersects the sphere
    param_t1 = (-coeff_b + sqrt(discriminant)) / 2 * coeff_a;
    param_t2 = (-coeff_b - sqrt(discriminant)) / 2 * coeff_a;

    return new float[2] {param_t1, param_t2};
}

// Determine color of ray passing through the viewport position seen from the camera position
float * TraceRay(float cameraPos[3], float rayDirection[3], float min_param, float max_param, Scene scene) {
    float closestParam = MAXFLOAT;
    float parameters[2];

    Sphere * closestSphere = NULL;

    for (Sphere sphere : scene.spheresInScene) {
        memcpy(parameters, IntersectRaySphere(cameraPos, rayDirection, sphere), sizeof(parameters));
        float param_t1 = parameters[0], param_t2 = parameters[1];
        if (param_t1 >= min_param && param_t1 <= max_param && param_t1 < closestParam) {
            closestParam = param_t1;
            closestSphere = &sphere;
        }
        if (param_t2 >= min_param && param_t2 <= max_param && param_t2 < closestParam) {
            closestParam = param_t2;
            closestSphere = &sphere;
        }
    }
    if (closestSphere == NULL) {
        return new float[3] BACKGROUNDCOLOR;
    }
    
    return (*closestSphere).color;
}

void DrawPixel(HDC hdc, int viewportX, int viewportY, float color[3]) {
    int screenX = SCREENWIDTH / 2 + viewportX;
    int screenY = SCREENHEIGHT / 2 - viewportY;
    SetPixel(hdc, screenX, screenY, RGB(color[0], color[1], color[2]));
}


int main()
{
    Camera camera;
    Scene scene;
    scene.CreateScene();
    HDC hdc = GetDC(GetConsoleWindow());

    float projectionCoord[3]; // the coords of the viewport in the scene
    float color[3] = { 0, 0, 0 };
    
    while (true) {
        for (int x = -SCREENWIDTH / 2; x <= SCREENWIDTH / 2; x++) {
            for (int y = -SCREENHEIGHT / 2; y <= SCREENHEIGHT / 2; y++) {
                memcpy(projectionCoord, camera.CanvasToViewport(x, y), sizeof(projectionCoord));
                memcpy(color, TraceRay(camera.GetPosition(), projectionCoord, 1, MAXFLOAT, scene), sizeof(color));
                DrawPixel(hdc, x, y, color);
            }
        }
    }
    
}
