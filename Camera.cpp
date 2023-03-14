#include "Camera.h"

#define SCREENWIDTH = 1920
#define SCREENHEIGHT = 1080

Camera::Camera() {
    SetPosition(0, 0, 0);
    SetOrientation(0, 0, 0);
    SetViewportWidth(1);
    SetViewportHeight(1);
    SetViewportDistance(1);
}