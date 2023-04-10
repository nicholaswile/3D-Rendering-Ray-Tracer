#include "RayTracer.h"

//-------------------------------------------------------------------------------------------------
// P is the point of intersection
// N is the normal on the surface at the point of intersection
// V is the direction from the point P to the camera 
float RayTracer::ComputeLighting(VecMath::vec3 P, VecMath::vec3 N, Scene scene, VecMath::vec3 V, float spec) {
    
    float intensity = 0.0f;
    float t_max = 1;
    
    VecMath::vec3 L;

    for (const Light &light : scene.lightsInScene) {
        
        // Ambient light
        
        if (light.type == light.ambient) {
            intensity += light.intensity;
        }
        
        else{
            if (light.type == light.point) {
                // L = light.position - P

                VecMath::vec3 lightPos = { light.position[0], light.position[1], light.position[2] };

                L = math.Subtract(lightPos, P);

                t_max = 1.0f;
            }
            // Directional lights work in isolation, but combined with ambient and point they look a little weird
            else if (light.type == light.directional) {
                // L = light.direction
                
                L = { light.direction[0], light.direction[1], light.direction[2] };

                t_max = MAXFLOAT;
            }
             

            float n_dot_l = math.Dot(N, L);
            

            // Shadow check
            bool shadowcheck = false;
            float param1, param2, closestParam = MAXFLOAT;

            VecMath::vec2 params;

            Sphere shadowSphere;

            for (const Sphere& sphere : scene.spheresInScene) {
                
                params = IntersectRaySphere(P, L, sphere);
                param1 = params.x;
                param2 = params.y;

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
                VecMath::vec3 R = ReflectRay(L, N);

                float r_dot_v = math.Dot(R, V);
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

VecMath::vec3 RayTracer::ReflectRay(VecMath::vec3 R, VecMath::vec3 N) {
    // 2 * N * Dot(N, R) - R
    VecMath::vec3 reflectedRay = math.Subtract(math.Scale(N, 2 * math.Dot(R, N)), R);
    return reflectedRay;
}

//-------------------------------------------------------------------------------------------------
// O is the position of the camera
// D is the direction of the ray from the camera to a point in the viewport
VecMath::vec2 RayTracer::IntersectRaySphere(VecMath::vec3 O, VecMath::vec3 D, Sphere sphere) {

    float r = sphere.radius;

    // CO = O - sphere.center 

    VecMath::vec3 C = math.Vector3(sphere.center[0], sphere.center[1], sphere.center[2]);
    VecMath::vec3 CO = math.Subtract(O, C);
    
    // a^2x + bx + c
    float a = math.Dot(D, D);
    float b = 2 * math.Dot(CO, D);
    float c = math.Dot(CO, CO) - r * r;

    // No real solution, therefore the ray does not intersect the sphere
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return math.Vector2(MAXFLOAT, MAXFLOAT);
    }

    // Quadratic formula to find two positions where the ray intersects the sphere
    float param_t1 = (-b + (float)sqrt(discriminant)) / (2 * a);
    float param_t2 = (-b - (float)sqrt(discriminant)) / (2 * a);

    return math.Vector2(param_t1, param_t2);
}

//-------------------------------------------------------------------------------------------------


// Determine color of ray passing through the viewport position seen from the camera position
VecMath::vec3 RayTracer::TraceRay(VecMath::vec3 O, VecMath::vec3 D, float min_param, float max_param, Scene scene, float recursionDepth) {

    float closestParam = MAXFLOAT, param_t1 = MAXFLOAT, param_t2 = MAXFLOAT;

    Sphere closestSphere;
    bool closestSphereNull = true;

    VecMath::vec2 parameters;


    // If no circle is intersected by a ray, then return the background color
    // Else, return the color of the closest circle to the camera at that point in the viewport

    for (const Sphere &sphere : scene.spheresInScene) {

        parameters = IntersectRaySphere(O, D, sphere);

        param_t1 = parameters.x;
        param_t2 = parameters.y;

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

        return math.Vector3(BACKGROUNDCOLOR);

    }
    
    // Calculate point of intersection of ray with sphere
   
    // P = O + t * D
    VecMath::vec3 P = math.Add(O, math.Scale(D, closestParam));
    
    // Point of intersection P
    
    // Calculate surface normal at that intersection point 
    // N = P - closestSphere.center
    
    VecMath::vec3 VectorC = math.Vector3(closestSphere.center[0], closestSphere.center[1], closestSphere.center[2]);
    VecMath::vec3 N = math.Subtract(P, VectorC);

    // Normalize normal vector to unit length of 1
    
    N = math.Scale(N, 1.0f / math.Length(N));

    // Color * Intensity from ComputeLighting()

    float scalar = ComputeLighting(P, N, scene, math.Scale(D, -1), closestSphere.specularExponent);

    VecMath::vec3 sphereColor = math.Vector3(closestSphere.color[0], closestSphere.color[1], closestSphere.color[2]);
    VecMath::vec3 localColor = math.Scale(sphereColor, scalar);

    // if recursion limit is reached or object is not reflective, base case
    float r = closestSphere.reflective;

    if (r <= 0 || recursionDepth <= 0) {
        return localColor;
    }
    
    // Reflections
    VecMath::vec3 R, reflectedColor;
    
    R = ReflectRay(math.Scale(D, -1), N);

    reflectedColor = TraceRay(P, R, .001f, MAXFLOAT, scene, recursionDepth - 1);

    float term = (1.0f - r);

    // Local Color * (1 - r)

    VecMath::vec3 localComponent = math.Scale(localColor, term);

    // Reflected Color * (r)

    VecMath::vec3 reflectedComponent = math.Scale(reflectedColor, r);

    // factor1 + factor2

    VecMath::vec3 finalColor = math.Add(localComponent, reflectedComponent);

    // Local Color * (1 - r) + reflected color * r
    return finalColor;
}