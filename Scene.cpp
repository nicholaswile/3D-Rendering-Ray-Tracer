#include "Scene.h"

void Scene::CreateScene() {
    Sphere sphere1 = Sphere(new float[3] { 255.0f, 0.0f, 0.0f }, 1.0f, new float[3] { 0.0f, -1.0f, 3.0f });
    Sphere sphere2 = Sphere(new float[3] { 0.0f, 255.0f, 0.0f }, 1.0f, new float[3] { -2.0f, 0.0f, 4.0f });
    Sphere sphere3 = Sphere(new float[3] { 0.0f, 0.0f, 255.0f }, 1.0f, new float[3] { 1.0f, 0.0f, 4.0f });

    spheresInScene.push_back(sphere1);
    spheresInScene.push_back(sphere2);
    spheresInScene.push_back(sphere3);
}
