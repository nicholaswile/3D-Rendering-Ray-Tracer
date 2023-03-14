#pragma once

#include <list>
#include "Sphere.h"

class Scene {
public:
    std::list<Sphere> spheresInScene;
    void CreateScene();
}; 
