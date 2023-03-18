#include "RayTracer.h"

#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"
#include "Light.h"
#include "VecMath.h"

//-------------------------------------------------------------------------------------------------

float RayTracer::ComputeLighting(float pointOfIntersection[3], float normal[3], Scene scene, float pointTocam [3], float specularExponent) {
    float intensity = 0.0;
    float lightDirection[3] = { 0, 0, 0 };

    for (const auto& light : scene.lightsInScene) {
        if (light.type == light.ambient) {
            intensity += light.intensity;
        }
        else {
            float normalDotLightDir;

            if (light.type == light.point) {
                float lightPosition[3];
                memcpy(lightPosition, light.position, sizeof(lightPosition));
                memcpy(lightDirection, math.aTob(lightPosition, pointOfIntersection), sizeof(lightDirection));
            }
            else if (light.type == light.directional) {
                memcpy(lightDirection, light.direction, sizeof(lightDirection));
            }
            normalDotLightDir = math.aDotb(normal, lightDirection);

        // Diffuse
            // cos x = Dot (Surface Normal N, Light Direction L) / |N| * |L|
            // If cosine is negative, then that means light is shining behind the object so we won't count it
            if (normalDotLightDir > 0 ) {
                float normalLenTimesLightDirLen = math.Length(normal) * math.Length(lightDirection);
                intensity += light.intensity * normalDotLightDir / normalLenTimesLightDirLen;
            }

        // Specular
            if (specularExponent != -1) {
                // R = 2 N (L dot N) - L
                float reflectionVector[3], lightProjectionOntoNormal[3];
                float lightDotnormal = math.aDotb(lightDirection, normal);
                memcpy(lightProjectionOntoNormal, math.Scale(normal, 2 * lightDotnormal), sizeof(lightProjectionOntoNormal));
         
                memcpy(reflectionVector, math.aTob(lightProjectionOntoNormal, lightDirection), sizeof(reflectionVector));

                float reflectionDotpointToCam = math.aDotb(reflectionVector, pointTocam);

                if (reflectionDotpointToCam > 0) {
                    intensity += light.intensity * pow((reflectionDotpointToCam / (math.Length(reflectionVector) * math.Length(pointTocam))), specularExponent);
                }
            }
        }

    }
    return intensity;
}

//-------------------------------------------------------------------------------------------------

float* RayTracer::IntersectRaySphere(float cameraPos[3], float rayDirection[3], Sphere sphere) {
    float radius;
    float camToSphere[3];
    float coeff_a, coeff_b, coeff_c, discriminant;
    float param_t1, param_t2;

    radius = sphere.radius;
    
    memcpy(camToSphere, math.aTob(cameraPos, sphere.center), sizeof(camToSphere));
    
    coeff_a = math.aDotb(rayDirection, rayDirection);
    coeff_b = 2 * math.aDotb(camToSphere, rayDirection);
    coeff_c = math.aDotb(camToSphere, camToSphere) - radius * radius;

    // No real solution, therefore the ray does not intersect the sphere
    discriminant = coeff_b * coeff_b - 4 * coeff_a * coeff_c;
    if (discriminant < 0) {
        return new float[2] {MAXFLOAT, MAXFLOAT};
    }
    // Quadratic formula to find two positions where the ray intersects the sphere
    param_t1 = (-coeff_b + (float)sqrt(discriminant)) / 2.0f * coeff_a;
    param_t2 = (-coeff_b - (float)sqrt(discriminant)) / 2.0f * coeff_a;

    return new float[2] {param_t1, param_t2};
}

//-------------------------------------------------------------------------------------------------

// Determine color of ray passing through the viewport position seen from the camera position
float * RayTracer::TraceRay(float cameraPos[3], float rayDirection[3], float min_param, float max_param, Scene scene) {
    float closestParam = MAXFLOAT;
    float param_t1 = MAXFLOAT, param_t2 = MAXFLOAT;
    float parameters[2] = { param_t1, param_t2 };

    Sphere* closestSphere = NULL;

    // If no circle is intersected by a ray, then return the background color
    // Else, return the color of the closest circle to the camera at that point in the viewport
    float closestColor[3] = BACKGROUNDCOLOR;
    bool closestSphereNull = true;
    float closestCenter[3] = { 0, 0, 0 };
    float closestSphereSpecular = -1;

    int i = 0;
    for (const Sphere &sphere : scene.spheresInScene) {
        memcpy(parameters, IntersectRaySphere(cameraPos, rayDirection, sphere), sizeof(parameters));
        param_t1 = parameters[0], param_t2 = parameters[1];
        i++;
        if (param_t1 > min_param && param_t1 < max_param && param_t1 < closestParam) {

            closestParam = param_t1;
            memcpy (closestColor, sphere.color, sizeof(closestColor));
            memcpy(closestCenter, sphere.center, sizeof(closestCenter));
            closestSphereNull = false;
            closestSphereSpecular = sphere.specularExponent;
        }
        if (param_t2 > min_param && param_t2 < max_param && param_t2 < closestParam) {

            closestParam = param_t2;
            memcpy(closestColor, sphere.color, sizeof(closestColor));
            memcpy(closestCenter, sphere.center, sizeof(closestCenter));
            closestSphereNull = false;
            closestSphereSpecular = sphere.specularExponent;
        }
        
    }
   
    // Background Color
    if (closestSphereNull) {
        return closestColor;
    }
       
    // Calculate point of intersection of ray with sphere

    float posX = cameraPos[0] + closestParam * rayDirection[0];
    float posY = cameraPos[1] + closestParam * rayDirection[1];
    float posZ = cameraPos[2] + closestParam * rayDirection[2];

    float pointOnSphereToColor[3] = { posX, posY, posZ };

    float normal[3];

    // Calculate surface normal at that intersection point 
    memcpy(normal, math.aTob(pointOnSphereToColor, closestCenter), sizeof(normal));

    // Normalize normal vector to unit length of 1
    float factor = 1/math.Length(normal);
    memcpy(normal, math.Scale(normal, factor), sizeof(normal));

    float intensity = ComputeLighting(pointOnSphereToColor, normal, scene, math.Scale(rayDirection, -1), closestSphereSpecular);

    memcpy(closestColor, math.Scale(closestColor, intensity), sizeof(closestColor));
    
    return closestColor;
}

