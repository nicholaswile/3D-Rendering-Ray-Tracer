// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <list>
#include <math.h>

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080
#define MAXFLOAT 4294967296.0
#define BACKGROUNDCOLOR {255, 255, 255}

class Camera {
public:
    Camera() {
        SetPosition(0, 0, 0);
        SetOrientation(0, 0, 0);
        SetViewportWidth(1);
        SetViewportHeight(1);
        SetViewportDistance(1);
    }
    float * GetPosition() {
        return m_Position;
    }
    float* GetOrientation() {
        return m_Orientation;
    }
    float GetViewportWidth() {
        return m_viewportWidth;
    }
    float GetViewportHeight() {
        return m_viewportHeight;
    }
    float GetViewportDistance() {
        return m_viewportDistance;
    }
    void SetPosition(float x, float y, float z) {
        m_Position[0] = x;
        m_Position[1] = y;
        m_Position[2] = z;
    }
    void SetOrientation(float x, float y, float z) {
        m_Orientation[0] = x;
        m_Orientation[1] = y;
        m_Orientation[2] = z;
     }
    void SetViewportWidth(float width) {
        m_viewportWidth = width;
    }
    void SetViewportHeight(float height) {
        m_viewportHeight = height;
    }
    void SetViewportDistance(float d) {
        m_viewportDistance = d;
    }
    float* CanvasToViewport(int canvasX, int canvasY) {
        return new float[3] {
            canvasX*m_viewportWidth/SCREENWIDTH, 
            canvasY*m_viewportHeight/SCREENHEIGHT,
            m_viewportDistance
        };
    }
private:
    float m_Position[3];
    float m_Orientation[3];
    float m_viewportWidth;
    float m_viewportHeight;
    float m_viewportDistance; // the distance between the camera and viewport/projection plane
};

class Sphere {
public: 
    float color[3];
    float radius;
    float center[3];
    Sphere(float col[3], float radius, float cent[3]) {
        memcpy(color, col, sizeof(color));
        this->radius = radius;
        memcpy(center, cent, sizeof(center));
    }
};

//class Scene {
//public:
//   Sphere * spheresInScene [3];
//   Scene() {
//       spheresInScene[0] = NULL;
//       spheresInScene[1] = NULL;
//       spheresInScene[2] = NULL;
//   }
//};

float * VectorDirection(float vector1[3], float vector2[3]) {
    return new float[3] {vector1[0] - vector2[0], vector1[1] - vector2[1], vector1[2] - vector2[2]};
}

float VectorDotProduct(float vector1[3], float vector2[3]) {
    return vector1[0] * vector2[0] + vector1[1] * vector2[1] + vector1[2] * vector2[2];
}

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
    discriminant = coeff_b * coeff_b - 4 * coeff_a * coeff_c;
    // No real solution, therefore the ray does not intersect the sphere
    if (discriminant < 0) {
        return new float[2] {MAXFLOAT, MAXFLOAT};
    }
    param_t1 = (-coeff_b + sqrt(discriminant)) / 2 * coeff_a;
    param_t2 = (-coeff_b - sqrt(discriminant)) / 2 * coeff_a;
    return new float[2] {param_t1, param_t2};
}

std::list<Sphere> spheresInScene;

float * TraceRay(float cameraPos[3], float rayDirection[3], float min_param, float max_param) {
    float closestParam = MAXFLOAT;
    float parameters[2];

    Sphere * closestSphere = NULL;

    for (Sphere sphere : spheresInScene) {
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
    float projectionCoord[3];

    float color[3] = { 0, 0, 0 };

    HDC hdc = GetDC(GetConsoleWindow());


   Sphere sphere1 = Sphere(new float[3] { 255.0f, 0.0f, 0.0f }, 1.0f, new float[3] { 0.0f, -1.0f, 3.0f });
   Sphere sphere2 = Sphere(new float[3] { 0.0f, 255.0f, 0.0f }, 1.0f, new float[3] { -2.0f, 0.0f, 4.0f });
   Sphere sphere3 = Sphere(new float[3] { 0.0f, 0.0f, 255.0f }, 1.0f, new float[3] { 1.0f, 0.0f, 4.0f });

   spheresInScene.push_back(sphere1);
   spheresInScene.push_back(sphere2);
   spheresInScene.push_back(sphere3);

    while (true) {
        for (int x = -SCREENWIDTH / 2; x <= SCREENWIDTH / 2; x++) {
            for (int y = -SCREENHEIGHT / 2; y <= SCREENHEIGHT / 2; y++) {
                memcpy(projectionCoord, camera.CanvasToViewport(x, y), sizeof(projectionCoord));
                memcpy(color, TraceRay(camera.GetPosition(), projectionCoord, 1, MAXFLOAT), sizeof(color));
                DrawPixel(hdc, x, y, color);
            }
        }
    }
    
}
