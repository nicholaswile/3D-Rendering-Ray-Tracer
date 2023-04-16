#include <windows.h> // gives ConsoleWindow and SetPixel
#include "RayTracer.h"
#include "VecMath.h"
#define MAXFLOAT 4294967296.0f

void DrawPixel(HDC hdc, int viewportX, int viewportY, int screenWidth, int screenHeight, float color[3]) {
    int screenX = screenWidth / 2 + viewportX;
    int screenY = screenHeight / 2 - viewportY;
    if (color[0] < 0) {
        color[0] = 0;
    }
    else if (color[0] > 255) {
        color[0] = 255;
    }
    if (color[1] < 0) {
        color[1] = 0;
    }
    else if (color[1] > 255) {
        color[1] = 255;
    }
    if (color[2] < 0) {
        color[2] = 0;
    }
    else if (color[2] > 255) {
        color[2] = 255;
    }
    SetPixel(hdc, screenX, screenY, RGB(color[0], color[1], color[2]));
}

int main()
{
    RayTracer renderer;
    renderer.scene.CreateScene();

    VecMath math;

    HDC hdc = GetDC(GetConsoleWindow());

    float recursionDepth = 3;

    // 3D viewport coordinates
    float D[3]; 

    float color[3] = { 0, 0, 0 };

    int screenWidth = (int) renderer.camera.GetScreenWidth();
    int screenHeight = (int) renderer.camera.GetScreenHeight();

    while (true) {
        for (int x = - screenWidth / 2; x <= screenWidth / 2; x++) {
            for (int y = -screenHeight / 2; y <= screenHeight / 2; y++) {
                memcpy(D, 
                        math.MultMatByVec(renderer.camera.CanvasToViewport(x, y), renderer.camera.GetOrientation()
                        ),
                    sizeof(D));
                memcpy(color, renderer.TraceRay(renderer.camera.GetPosition(), D, 1, MAXFLOAT, renderer.scene, recursionDepth), sizeof(color));
                DrawPixel(hdc, x, y, screenWidth, screenHeight, color);
            }
        }
    }
}
