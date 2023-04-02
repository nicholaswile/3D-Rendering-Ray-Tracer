# 3D Rendering Ray Tracer
This is a ray tracer for rendering simple 3D scenes built from scratch using C++ and the Windows API to draw pixels directly to the console. It currently implements ray intersection (sphere); ambient, diffuse, and specular lighting models; and shadows. The 3D math / linear algebra functions are also custom made. 

## Shadows
<img width="600" src="https://user-images.githubusercontent.com/74445404/229344983-2e3027b3-f02c-4f9b-8b37-f08d0ccf6852.png">

## Lighting
### Specular
<img width="600" src="https://user-images.githubusercontent.com/74445404/229345083-a752cac3-74b9-441c-be89-cf27cf437a71.png">

### Diffuse
<img width="600" src="https://user-images.githubusercontent.com/74445404/229345168-d5d4e442-fbf4-4144-835f-6635343a92a9.png">

### Ambient
<img width="600" src="https://user-images.githubusercontent.com/74445404/229345278-884f8b99-ea17-4449-a5cb-aad9e6b0e11c.png">

## Flat Color 
Note that flat color looks the same as ambient lighting. This is because the intensity of the ambient light in the previous photo is set to 1.0f, so the effect of the ambient light on the scene is multiplying the RGB color values of each sphere by 1.0f. The result is the same. 

<img width="600" src="https://user-images.githubusercontent.com/74445404/229345460-cd4c33f9-8b84-4048-abcd-324774c97abb.png">

---

# Funny troubleshooting pictures and old updates

## Lighting

### Specular 
Specular reflection with glossy material is implemented. If materials are specified as matte, then specular calculation is ignored for them.

<img width="400" alt="Four glossy spheres; they are blue, white, purple, and pink." src="https://user-images.githubusercontent.com/74445404/226090987-0e871318-bd65-4f9d-9acb-572592b5fc46.png">

<img width="400" alt="A white glossy sphere." src="https://user-images.githubusercontent.com/74445404/226090870-d2b8a464-f53f-4f02-99d2-8845995f6058.png">

<img width="400" alt="Three spheres with specular lighting." src="https://user-images.githubusercontent.com/74445404/226090908-f7789d0b-b18a-4fd3-ac78-79df5d5ac902.png">

#### Troubleshooting

Problems with specular lighting and glossy materials arise when intensity exceeds 1 from the Compute Light function. When this happens, black pixels are drawn where white highlights are expected to occur. (This has been fixed).

<img width="400" alt="Glossy spheres with black pixels where white highlights are expected." src="https://user-images.githubusercontent.com/74445404/226090800-5c1bb8b3-baf2-4c22-9155-e1fdf3066f05.png">

<img width="400" alt="Glossy sphere with black pixels where white highlights are expected." src="https://user-images.githubusercontent.com/74445404/226090730-8384436b-7385-4d72-a575-d05471f1f663.png">

### Diffuse
Ambient, point, and directional light reflections are implemented. 

<img width="400" alt="Three spheres with diffuse lighting. They look 3D now." src="https://user-images.githubusercontent.com/74445404/226056722-219a84e7-3642-4a58-9305-8df862eaae81.png">

#### Troubleshooting

There are some weird deformations with the spheres caused by an error in the diffuse intensity calculation for point and directional lights. (This has been fixed). 

<img width="400" alt="Three spheres with diffuse lighting and irregularities. Certain spots on the spheres are unexpected colors." src="https://user-images.githubusercontent.com/74445404/225863027-b5810131-a25b-4c0c-a792-f445967d8d31.png">

### Ambient only 
Flat shading with an equal intensity for all objects in the scene. 

<img width="400" alt="Three flat shaded spheres on a floor. They look 2D." src="https://user-images.githubusercontent.com/74445404/225862524-725356ea-92eb-4f33-9cd5-562a88333dfc.png">

## Flat Color
Parameterized spheres are rendered with flat colors. 

<img width="400" alt="Three flat shaded spheres, one blue, one pink, and one purple, displayed on a Windows console." src="https://user-images.githubusercontent.com/74445404/225229690-5caf386b-8999-445a-b5bb-bc3540a1ee8d.png">
