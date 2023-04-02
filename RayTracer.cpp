#include "RayTracer.h"

//-------------------------------------------------------------------------------------------------
// P is the point of intersection
// N is the normal on the surface at the point of intersection
// V is the direction from the point P to the camera 
float RayTracer::ComputeLighting(float P[3], float N[3], Scene scene, float V[3], float spec) {
    
    float intensity = 0.0f;
    float L[3];
    float t_max = 1;
    
    for (const Light &light : scene.lightsInScene) {
        
        // Ambient light
        
        if (light.type == light.ambient) {
            intensity += light.intensity;
        }
        
        else{
            if (light.type == light.point) {
                // L = light.position - P
                float lightPos[3] = { light.position[0], light.position[1], light.position[2] };

                memcpy(L, math.aTob(lightPos, P), sizeof(L));

                t_max = 1.0f;
            }
            // Directional lights work in isolation, but combined with ambient and point they look a little weird
            else if (light.type == light.directional) {
                // L = light.direction
                memcpy(L, light.direction, sizeof(L));

                t_max = MAXFLOAT;
            }
             

            float n_dot_l = math.aDotb(N, L);
            

            // Shadow check
            bool shadowcheck = false;
            float params[2], param1, param2, closestParam = MAXFLOAT;
            Sphere shadowSphere;

            for (const Sphere& sphere : scene.spheresInScene) {
                
                memcpy(params, IntersectRaySphere(P, L, sphere), sizeof(params));
                param1 = params[0];
                param2 = params[1];
                if ((param1 > .001f && param1 < t_max && param1 < closestParam)) {
                    shadowcheck = true;
                    closestParam = param1;
                    shadowSphere = sphere;
                }
                    
                if (param2 > .001f && param2 < t_max && param2 < closestParam) {
                    shadowcheck = true;
                    closestParam = param2;
                    shadowSphere = sphere;
                }
            }
            if (shadowcheck) {
               continue;
            }


            // Diffuse
            // cos x = Dot (Surface Normal N, Light Direction L) / |N| * |L|
            // If cosine is negative, then that means light is shining behind the object so we won't count it
            
            if (n_dot_l > 0 ) {
                intensity += (light.intensity * n_dot_l / (math.Length(N) * math.Length(L)));
            }
            
        
            // Specular
            if (spec != -1) {
                float R[3];
                memcpy(R, ReflectRay(L,N), sizeof(R));

                float r_dot_v = math.aDotb(R, V);
                if (r_dot_v > 0) {
                    intensity += light.intensity * (float)pow(r_dot_v / (math.Length(R) * math.Length(V)), spec);
                }
            }
        

        }

    }
    if (intensity > 1) {
        intensity = 1;
    }
   
    
    return intensity;
}

float* RayTracer::ReflectRay(float R[3], float N[3]) {
    return math.aTob(math.Scale(N,2*math.aDotb(R, N)), R);
}

//-------------------------------------------------------------------------------------------------
// O is the position of the camera
// D is the direction of the ray from the camera to a point in the viewport
float* RayTracer::IntersectRaySphere(float O[3], float D[3], Sphere sphere) {
    float r = sphere.radius;

    // CO = O - sphere.center 
    float CO[3];
    memcpy(CO, math.aTob(O, sphere.center), sizeof(CO));
    
    // a^2x + bx + c
    float a = math.aDotb(D, D);
    float b = 2 * math.aDotb(CO, D);
    float c = math.aDotb(CO, CO) - r * r;

    // No real solution, therefore the ray does not intersect the sphere
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return new float[2] {MAXFLOAT, MAXFLOAT};
    }

    // Quadratic formula to find two positions where the ray intersects the sphere
    float param_t1 = (-b + (float)sqrt(discriminant)) / (2 * a);
    float param_t2 = (-b - (float)sqrt(discriminant)) / (2 * a);

    return new float[2] {param_t1, param_t2};
}

//-------------------------------------------------------------------------------------------------


// Determine color of ray passing through the viewport position seen from the camera position
float * RayTracer::TraceRay(float O[3], float D[3], float min_param, float max_param, Scene scene, float recursionDepth) {
    float closestParam = MAXFLOAT, param_t1 = MAXFLOAT, param_t2 = MAXFLOAT;
    float parameters[2] = { param_t1, param_t2 };
    
    Sphere closestSphere;
    bool closestSphereNull = true;

    // If no circle is intersected by a ray, then return the background color
    // Else, return the color of the closest circle to the camera at that point in the viewport

    for (const Sphere &sphere : scene.spheresInScene) {
        memcpy(parameters, IntersectRaySphere(O, D, sphere), sizeof(parameters));
        param_t1 = parameters[0], param_t2 = parameters[1];

        if (param_t1 > min_param && param_t1 < max_param && param_t1 < closestParam) {
            closestParam = param_t1;
            (closestSphere).Copy(sphere);
            closestSphereNull = false;
        }

        if (param_t2 > min_param && param_t2 < max_param && param_t2 < closestParam) {
            closestParam = param_t2;
            (closestSphere).Copy(sphere);
            closestSphereNull = false;
        }
    }

    if (closestSphereNull) {
        return new float[3] BACKGROUNDCOLOR;
    }
    
    // Calculate point of intersection of ray with sphere
    // P = O + t * D
    float posX = O[0] + closestParam * D[0];
    float posY = O[1] + closestParam * D[1];
    float posZ = O[2] + closestParam * D[2];

    // Point of intersection P
    float P[3] = { posX, posY, posZ };

    // Calculate surface normal at that intersection point 
    // N = P - closestSphere.center
    float N[3];
    memcpy(N, math.aTob(P, closestSphere.center), sizeof(N));

    // Normalize normal vector to unit length of 1
    memcpy(N, math.Scale(N, 1.0f/math.Length(N)), sizeof(N));

    // Color * Intensity from ComputeLighting()
    float localColor[3];
    memcpy(localColor, math.Scale(closestSphere.color, ComputeLighting(P, N, scene, math.Scale(D, -1), closestSphere.specularExponent)), sizeof(localColor));

    // if recursion limit is reached or object is not reflective, base case
    float r = closestSphere.reflective;
    if (r <= 0 || recursionDepth <= 0) {
        return localColor;
    }
   return localColor;

    // Reflections: doesn't work
    float minusD[3],  R[3],  reflectedColor[3];
    memcpy(minusD, math.Scale(D, -1), sizeof(minusD));
    memcpy(R,ReflectRay(minusD, N), sizeof(R));
    memcpy(reflectedColor, TraceRay(P, R, 0.001f, MAXFLOAT, scene, recursionDepth - 1), sizeof(reflectedColor));
    return math.Add(math.Scale(localColor, float(1.0f-r)), math.Scale(reflectedColor, r));
}