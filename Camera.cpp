#include "Camera.h"

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080

Camera::Camera() {
    SetPosition(0, 0, 0);
    SetOrientation(0, 0, 0);
    float vpX = (float) SCREENWIDTH / (float) SCREENHEIGHT;
    SetViewportWidth(vpX);
    SetViewportHeight(1);
    SetViewportDistance(1);
    SetScreenWidth(SCREENWIDTH);
    SetScreenHeight(SCREENHEIGHT);
}