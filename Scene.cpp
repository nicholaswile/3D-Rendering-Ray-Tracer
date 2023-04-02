#include "Scene.h"

void Scene::CreateScene() {

   /* Sphere sphere1(color.pink, 1.5f, new float[3] { 0.0f, 0.5f, 6.0f }, 500);
    spheresInScene.push_back(sphere1);

    Sphere sphere2 (color.purple, .5f, new float[3] { 1.0f, -.5f, 4.0f }, 250);
    spheresInScene.push_back(sphere2);

    Sphere sphere3 (color.blue, .5f, new float[3] { -1.0f, -.5f, 4.0f }, 250);
    spheresInScene.push_back(sphere3);

    Sphere sphere4(color.grey, 5000, new float[3] {0, -5001, 0}, 1000);
    spheresInScene.push_back(sphere4);

    Sphere sphere5(color.white, .5, new float[3] { 0, -.5, 2.5}, 250);
    spheresInScene.push_back(sphere5);
    
    Sphere sphere5(color.grey, 5000, new float[3] { -1, -5001, 4}, 500, .2f);
    spheresInScene.push_back(sphere5);*/

    Sphere sphere6(color.purple, 1, new float[3] { 0, 0, 3}, 500, .2f);
    spheresInScene.push_back(sphere6);

    Sphere sphere7(color.blue, 1, new float[3] { 2, 0, 4 }, 500, .3f);
    spheresInScene.push_back(sphere7);

    Sphere sphere8(color.pink, 1, new float[3] { -2, 0, 4 }, 10, .4f);
    spheresInScene.push_back(sphere8);

    Sphere sphere9(color.grey, 5000, new float[3] {0, -5001, 0}, 1000, .5f);
    spheresInScene.push_back(sphere9);

    //-------------------------------------------------------------------------------------------------
    
   /* AmbientLight light1(0.2f);
    lightsInScene.push_back(light1);

    PointLight light2(0.6f, new float[3] {0, 7, -10});
    lightsInScene.push_back(light2);

    DirectionalLight light3(0.2f, new float[3] {1, 4, 4});
    lightsInScene.push_back(light3);*/

    // . . .
    AmbientLight light1(.2f);
    lightsInScene.push_back(light1);
    // . . .
    PointLight light2(0.6f, new float[3] {2, 1, 0});
    lightsInScene.push_back(light2);

    // . . .
    DirectionalLight light3(.2f, new float[3] {1, 4, 4});
    lightsInScene.push_back(light3);
    // . . .

}