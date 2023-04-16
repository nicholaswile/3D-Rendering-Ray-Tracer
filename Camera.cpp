#include "Camera.h"

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080

Camera::Camera() {
    // Default
    SetPosition(0, 0, 0);

    // Uncomment to test changing position
    
    // SetPosition(2, 0, 0);

    // Default
    SetOrientation(VecMath::Mat3x3{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
        });

    // Uncomment to test changing rotation

    /*
    SetOrientation(VecMath::Mat3x3{
        .7, 0, -.7,
        0, 1, 0,
        .7, 0, .7
        });
    */

    float vpX = (float) SCREENWIDTH / (float) SCREENHEIGHT;
    SetViewportWidth(vpX);
    SetViewportHeight(1);
    SetViewportDistance(1);
    SetScreenWidth(SCREENWIDTH);
    SetScreenHeight(SCREENHEIGHT);
}