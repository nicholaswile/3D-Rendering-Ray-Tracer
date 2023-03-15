#pragma once

#include <vector>
#include "Sphere.h"

class Scene {
public:
    std::vector<Sphere> spheresInScene;
    void CreateScene();
}; 
