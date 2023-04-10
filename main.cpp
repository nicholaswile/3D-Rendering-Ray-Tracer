#include <windows.h> // gives ConsoleWindow and SetPixel
#include "RayTracer.h"

#define MAXFLOAT 4294967296.0f

void DrawPixel(HDC hdc, int viewportX, int viewportY, int screenWidth, int screenHeight, VecMath::vec3 color) {
    int screenX = screenWidth / 2 + viewportX;
    int screenY = screenHeight / 2 - viewportY;
    if (color.x < 0) {
        color.x = 0;
    }
    else if (color.x > 255) {
        color.x = 255;
    }
    if (color.y < 0) {
        color.y = 0;
    }
    else if (color.y > 255) {
        color.y = 255;
    }
    if (color.z < 0) {
        color.z = 0;
    }
    else if (color.z > 255) {
        color.z = 255;
    }
    SetPixel(hdc, screenX, screenY, RGB(color.x, color.y, color.z));
}

int main()
{
    RayTracer renderer;
    renderer.scene.CreateScene();

    HDC hdc = GetDC(GetConsoleWindow());

    float recursionDepth = 3;

    // 3D viewport coordinates
    VecMath::vec3 D;

    VecMath::vec3 color;


    int screenWidth = (int) renderer.camera.GetScreenWidth();
    int screenHeight = (int) renderer.camera.GetScreenHeight();

    while (true) {
        for (int x = - screenWidth / 2; x <= screenWidth / 2; x++) {
            for (int y = -screenHeight / 2; y <= screenHeight / 2; y++) {

                D = renderer.camera.CanvasToViewport(x, y);

                color = renderer.TraceRay(renderer.camera.GetPosition(), D, 1, MAXFLOAT, renderer.scene, recursionDepth);

                DrawPixel(hdc, x, y, screenWidth, screenHeight, color);
            }
        }
    }
}
