#include "Scene.h"
#include <iostream>

void Scene::CreateScene() {
    
    Sphere sphere1(new float[3] { 255.0f, 0.0f, 128.0f }, 1.5f, new float[3] { 0.0f, 0.5f, 6.0f });
    spheresInScene.push_back(sphere1);

    Sphere sphere2 (new float[3] { 163.0f, 73.0f, 164.0f }, 1.0f, new float[3] { 1.5f, -.25f, 4.0f });
    spheresInScene.push_back(sphere2);

    Sphere sphere3 (new float[3] { 0.0f, 0.0f, 255.0f }, 1.0f, new float[3] { -1.5f, -.25f, 4.0f });
    spheresInScene.push_back(sphere3);
    
}
