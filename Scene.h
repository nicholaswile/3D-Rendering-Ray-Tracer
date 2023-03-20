#pragma once

#include <vector>
#include "Sphere.h"
#include "Light.h"
#include "Color.h"

class Scene {
public:
    std::vector<Sphere> spheresInScene;
    std::vector<Light> lightsInScene;
    Color color;

    void CreateScene();
}; 
