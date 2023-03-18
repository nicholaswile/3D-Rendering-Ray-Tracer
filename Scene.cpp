#include "Scene.h"

void Scene::CreateScene() {

  /*  Sphere sphere1(color.pink, 1.5f, new float[3] { 0.0f, 0.5f, 6.0f }, 500);
    spheresInScene.push_back(sphere1);

    Sphere sphere2 (color.purple, 1.0f, new float[3] { 1.5f, -.25f, 4.0f }, 500);
    spheresInScene.push_back(sphere2);

    Sphere sphere3 (color.blue, 1.0f, new float[3] { -1.5f, -.25f, 4.0f });
    spheresInScene.push_back(sphere3);

    Sphere sphere4(color.grey, 5000, new float[3] {0, -5001, 0}, 1000);
    spheresInScene.push_back(sphere4);*/
    
    Sphere sphere1(color.pink, 1, new float[3] { 0, -1, 3}, 500);
    spheresInScene.push_back(sphere1);

    Sphere sphere2(color.purple, 1, new float[3] { 2, 0, 4 }, 500);
    spheresInScene.push_back(sphere2);

    Sphere sphere3(color.blue, 1, new float[3] { -2, 0, 4 }, 10);
    spheresInScene.push_back(sphere3);

    Sphere sphere4(color.grey, 5000, new float[3] {0, -5001, 0}, 1000);
    spheresInScene.push_back(sphere4);

    //-------------------------------------------------------------------------------------------------
    
  /*  AmbientLight light1(0.2f);
    lightsInScene.push_back(light1);

    PointLight light2(0.6f, new float[3] {5, 10, -10});
    lightsInScene.push_back(light2);

    DirectionalLight light3(0.2f, new float[3] {1, 4, 4});
    lightsInScene.push_back(light3);*/

    AmbientLight light1(0.2f);
    lightsInScene.push_back(light1);

    PointLight light2(0.6f, new float[3] {2, 1, 0});
    lightsInScene.push_back(light2);

    DirectionalLight light3(0.2f, new float[3] {1, 4, 4});
    lightsInScene.push_back(light3);
}