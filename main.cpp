#include <windows.h> // gives ConsoleWindow and SetPixel
#include "RayTracer.h"

#define MAXFLOAT 4294967296.0f

void DrawPixel(HDC hdc, int viewportX, int viewportY, int screenWidth, int screenHeight, float color[3]) {
    int screenX = screenWidth / 2 + viewportX;
    int screenY = screenHeight / 2 - viewportY;
    SetPixel(hdc, screenX, screenY, RGB(color[0], color[1], color[2]));
}

int main()
{
    RayTracer renderer;
    renderer.scene.CreateScene();

    HDC hdc = GetDC(GetConsoleWindow());

    float projectionCoord[3]; // the coords of the viewport in the scene
    float color[3] = { 0, 0, 0 };

    int screenWidth = renderer.camera.GetScreenWidth();
    int screenHeight = renderer.camera.GetScreenHeight();

    while (true) {
        for (int x = - screenWidth / 2; x <= screenWidth / 2; x++) {
            for (int y = -screenHeight / 2; y <= screenHeight / 2; y++) {
                memcpy(projectionCoord, renderer.camera.CanvasToViewport(x, y), sizeof(projectionCoord));
                memcpy(color, renderer.TraceRay(renderer.camera.GetPosition(), projectionCoord, 1, MAXFLOAT, renderer.scene), sizeof(color));
                DrawPixel(hdc, x, y, screenWidth, screenHeight, color);
            }
        }
    }
}