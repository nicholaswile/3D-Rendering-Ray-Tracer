// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h> // gives ConsoleWindow and SetPixel
#include <math.h> // gives sqrt()

#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"
#include "Light.h"

#define SCREENWIDTH 1080
#define SCREENHEIGHT 1080
#define MAXFLOAT 4294967296.0f
#define BACKGROUNDCOLOR {0, 0, 0}

//-------------------------------------------------------------------------------------------------

float * VectorDirection(float vector1[3], float vector2[3]) {
    return new float[3] {vector1[0] - vector2[0], vector1[1] - vector2[1], vector1[2] - vector2[2]};
}

float VectorDotProduct(float vector1[3], float vector2[3]) {
    return vector1[0] * vector2[0] + vector1[1] * vector2[1] + vector1[2] * vector2[2];
}

float ComputeLighting(float pointOfIntersection[3], float normal[3], Scene scene) {
    float intensity = 0.0;
    float lightDirection[3] = { 0, 0, 0 };
    float normalDotLightDir;

    for (const auto& light : scene.lightsInScene) {
        if (light.type == light.ambient) {
            intensity += light.intensity;
        }
        else {
            if (light.type == light.point) {
                float lightPosition[3];
                memcpy(lightPosition, light.position, sizeof(lightPosition));
                memcpy(lightDirection, VectorDirection(lightPosition, pointOfIntersection), sizeof(lightDirection));
            }
            else if (light.type == light.directional) {
                memcpy(lightDirection, light.direction, sizeof(lightDirection));
            }
            normalDotLightDir = VectorDotProduct(normal, lightDirection);

            // cos x = Dot (Surface Normal N, Light Direction L) / |N| * |L|
            // If cosine is negative, then that means light is shining behind the object so we won't count it
            if (normalDotLightDir > 0) {
                intensity += light.intensity * normalDotLightDir / (sqrt((VectorDotProduct(normal, normal)) * sqrt(VectorDotProduct(lightDirection, lightDirection))));
            }
        }

    }
    return intensity;
}

//-------------------------------------------------------------------------------------------------

// Determines at what point(s) the ray intersects the sphere

// Vector V = PointOnSphere P - SphereCenter C
// Radius = | V | = sqrt ( VectorDotProduct (V, V) )
// => Radius^2 = VectorDotProduct (V, V) = VectorDotProduct (P - C, P - C)

// RayDirection = SecondPointRayPassesThru - FirstPointRayPassesThru
//              = ViewportPoint - CameraPoint 
// PointOnRay = PointThatRayPassesThru + Parameter_t * RayDirection
// PointOnRay = CameraPosition + Parameter_t * RayDirection

// Want to know Parameter_t when PointOnRay = PointOnSphere,
// Radius^2 = Dot (PointOnSphere - SphereCenter, PointOnSpherePoint - SphereCenter) 
// 
// Sub PointOnRay for PointOnSphere
// => Radius^2 = Dot ( CameraPosition + Parameter_t * RayDirection - SphereCenter, Again )
// 
// CamToSphereCenter = CameraPosition - SphereCenter
// => Radius^2 = Dot (
    // CamToSphereCenter + Parameter_t * RayDirection, 
    // CamToSphereCenter + Parameter_t * RayDirection
    // )

// => Radius^2 = Dot (CamToSphereCenter + Parameter_t * RayDirection, CamToSphereCenter) + 
    // Dot (CamToSphereCenter + Paramter_t * RayDirection, Parameter_t * RayDirection)

// => Radius^2 = Dot (CamToSphereCenter, CamToSphereCenter) + Dot (CamToSphereCenter, Parameter_t*RayDir) + Dot (CamToSphereCenter, Parameter_t*RayDir) + Dot(Parameter_t*RayDir, Parameter_t*RayDir)

// => 0 = - Radius^2 + Dot (Cam, Cam) + 2*Parameter_t*Dot (Cam, Dir) + Parameter_t^2*Dot (Dir, Dir)

// Quadratic forumla : 0 = a(t^2) + b(t) + c, solve for t to find where P = P

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
    param_t1 = (-coeff_b + (float)sqrt(discriminant)) / 2.0f * coeff_a;
    param_t2 = (-coeff_b - (float)sqrt(discriminant)) / 2.0f * coeff_a;

    return new float[2] {param_t1, param_t2};
}

// Determine color of ray passing through the viewport position seen from the camera position
float * TraceRay(float cameraPos[3], float rayDirection[3], float min_param, float max_param, Scene scene) {
    float closestParam = MAXFLOAT;
    float param_t1 = MAXFLOAT, param_t2 = MAXFLOAT;
    float parameters[2] = { param_t1, param_t2 };

    Sphere* closestSphere = NULL;

    // If no circle is intersected by a ray, then return the background color
    // Else, return the color of the closest circle to the camera at that point in the viewport
    float closestColor[3] = BACKGROUNDCOLOR;
    float closestCenter[3] = { 0, 0, 0 };

    int i = 0;
    for (const Sphere &sphere : scene.spheresInScene) {
        memcpy(parameters, IntersectRaySphere(cameraPos, rayDirection, sphere), sizeof(parameters));
        param_t1 = parameters[0], param_t2 = parameters[1];
        i++;
        if (param_t1 > min_param && param_t1 < max_param && param_t1 < closestParam) {

            closestParam = param_t1;
            memcpy (closestColor, sphere.color, sizeof(closestColor));
            memcpy(closestCenter, sphere.center, sizeof(closestCenter));
        }
        if (param_t2 > min_param && param_t2 < max_param && param_t2 < closestParam) {

            closestParam = param_t2;
            memcpy(closestColor, sphere.color, sizeof(closestColor));
            memcpy(closestCenter, sphere.center, sizeof(closestCenter));
        }
        
    }
    
    //return closestColor;
    
    // TODO: REFACTOR THIS 
    
    // Calculate point of intersection of ray with sphere
    float posX = cameraPos[0] + closestParam * rayDirection[0];
    float posY = cameraPos[1] + closestParam * rayDirection[1];
    float posZ = cameraPos[2] + closestParam * rayDirection[2];

    float pointOnSphereToColor[3] = { posX, posY, posZ };

    float normal[3];

    // Calculate surface normal at that intersection point 
    memcpy(normal, VectorDirection(pointOnSphereToColor, closestCenter), sizeof(normal));

    // Normalize normal vector to unit length of 1
    float factor = sqrt(VectorDotProduct(normal, normal));
    normal[0] /= factor;
    normal[1] /= factor;
    normal[2] /= factor;

    float intensity = ComputeLighting(pointOnSphereToColor, normal, scene);

    closestColor[0] *= intensity;
    closestColor[1] *= intensity;
    closestColor[2] *= intensity;
    
    return closestColor;
}

//-------------------------------------------------------------------------------------------------

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
