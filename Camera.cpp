#include "Camera.h"

Camera::Camera() {
    SetPosition(0, 0, 0);
    SetOrientation(0, 0, 0);
    SetViewportWidth(1);
    SetViewportHeight(1);
    SetViewportDistance(1);
}