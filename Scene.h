#pragma once

#include <vector>
#include "Sphere.h"
#include "Light.h"
class Scene {
public:
    std::vector<Sphere> spheresInScene;
    std::vector<Light> lightsInScene;

    void CreateScene();
}; 
