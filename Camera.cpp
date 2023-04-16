#include "Camera.h"

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080

Camera::Camera() {
    SetPosition(2, 0, 0);
    // for default, set to 1, 0, 0, 0, 1, 0, 0, 0, 1
    SetOrientation(VecMath::Mat3x3{
        .7, 0, -.7,
        0, 1, 0,
        .7, 0, .7
        });
    float vpX = (float) SCREENWIDTH / (float) SCREENHEIGHT;
    SetViewportWidth(vpX);
    SetViewportHeight(1);
    SetViewportDistance(1);
    SetScreenWidth(SCREENWIDTH);
    SetScreenHeight(SCREENHEIGHT);
}