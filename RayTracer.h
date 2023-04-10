// Ray Tracer works like this:

// Determines at what point(s) the ray intersects the sphere

// Vector V = PointOnSphere P - SphereCenter C
// Radius = | V | = sqrt ( VectorDotProduct (V, V) )
// => Radius^2 = VectorDotProduct (V, V) = VectorDotProduct (P - C, P - C)

// RayDirection = SecondPointRayPassesThru - FirstPointRayPassesThru
//              = ViewportPoint - CameraPoint 
// PointOnRay = PointThatRayPassesThru + Parameter_t * RayDirection
// PointOnRay = CameraPosition + Parameter_t * RayDirection

// Want to know Parameter_t when PointOnRay = PointOnSphere,
// Radius^2 = Dot (PointOnSphere - SphereCenter, PointOnSpherePoint - SphereCenter) 
// 
// Sub PointOnRay for PointOnSphere
// => Radius^2 = Dot ( CameraPosition + Parameter_t * RayDirection - SphereCenter, Again )
// 
// CamToSphereCenter = CameraPosition - SphereCenter
// => Radius^2 = Dot (
    // CamToSphereCenter + Parameter_t * RayDirection, 
    // CamToSphereCenter + Parameter_t * RayDirection
    // )

// => Radius^2 = Dot (CamToSphereCenter + Parameter_t * RayDirection, CamToSphereCenter) + 
    // Dot (CamToSphereCenter + Paramter_t * RayDirection, Parameter_t * RayDirection)

// => Radius^2 = Dot (CamToSphereCenter, CamToSphereCenter) + Dot (CamToSphereCenter, Parameter_t*RayDir) + Dot (CamToSphereCenter, Parameter_t*RayDir) + Dot(Parameter_t*RayDir, Parameter_t*RayDir)

// => 0 = - Radius^2 + Dot (Cam, Cam) + 2*Parameter_t*Dot (Cam, Dir) + Parameter_t^2*Dot (Dir, Dir)

// Quadratic forumla : 0 = a(t^2) + b(t) + c, solve for t to find where P = P

#pragma once

#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"
#include "Light.h"
#include "VecMath.h"
#include <iostream>
#include <array> // gives std::array used in RayTracer.cpp to compare sphere color to background

#define MAXFLOAT 4294967296.0f
#define BACKGROUNDCOLOR 255, 255, 255


class RayTracer {
public:
    VecMath math;
    Camera camera;
    Scene scene;
    // Vector Point of Intersection P where the light ray intersects the surface 
    // Normal vector N is perpendicular to the surface that light ray intersects
    // Scene holds data about the spheres and lights in the game 
    // Vector Point to Cam V where the camera is positioned relative to the object (for specular)
    // Specular Exponent S is the exponent that the cosine of the angle between V and R, the reflection of the Light direction vector, is raised to; depends on material property of the sphere 
    float ComputeLighting(VecMath::vec3 pointOfIntersection, VecMath::vec3 normal, Scene scene, VecMath::vec3 pointTocam, float specularExponent);

    // Position (x, y, z) Camera Pos holds the coords where the camera is located
    // Vector RayDirection is the direction of the light ray from the camera thru the viewport to the sphere
    // Sphere sphere is the current sphere being checked
    VecMath::vec2 IntersectRaySphere(VecMath::vec3 cameraPos, VecMath::vec3 rayDirection, Sphere sphere);

    // Camera Pos is the original cam position
    // Ray direction is the direction of light determined by Point on Viewport - Camera Position 
    // min and max parameters determine which segments of the light ray we want to look at
    // Scene includes the lights and objects in the scene
    VecMath::vec3 TraceRay(VecMath::vec3 cameraPos, VecMath::vec3 rayDirection, float min_param, float max_param, Scene scene, float recursionDepth);

    VecMath::vec3 ReflectRay(VecMath::vec3 R, VecMath::vec3 N);

    

};
