#include <windows.h> // gives ConsoleWindow and SetPixel
#include "RayTracer.h"

#define SCREENWIDTH 1080
#define SCREENHEIGHT 1080
#define MAXFLOAT 4294967296.0f

void DrawPixel(HDC hdc, int viewportX, int viewportY, float color[3]) {
    int screenX = SCREENWIDTH / 2 + viewportX;
    int screenY = SCREENHEIGHT / 2 - viewportY;
    SetPixel(hdc, screenX, screenY, RGB(color[0], color[1], color[2]));
}

int main()
{
    RayTracer renderer;
    renderer.scene.CreateScene();

    HDC hdc = GetDC(GetConsoleWindow());

    float projectionCoord[3]; // the coords of the viewport in the scene
    float color[3] = { 0, 0, 0 };

    while (true) {
        for (int x = -SCREENWIDTH / 2; x <= SCREENWIDTH / 2; x++) {
            for (int y = -SCREENHEIGHT / 2; y <= SCREENHEIGHT / 2; y++) {
                memcpy(projectionCoord, renderer.camera.CanvasToViewport(x, y), sizeof(projectionCoord));
                memcpy(color, renderer.TraceRay(renderer.camera.GetPosition(), projectionCoord, 1, MAXFLOAT, renderer.scene), sizeof(color));
                DrawPixel(hdc, x, y, color);
            }
        }
    }
}