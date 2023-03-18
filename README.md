# 3D Renderer - Ray Tracing
This is a work in progress. Each branch represents a different basic feature of the ray tracer. Currently flat colors are rendered. I plan to add lighting, shadows, and reflections.

## Lighting

### Specular 
Specular reflection with glossy material is implemented. If materials are specified as matte, then specular calculation is ignored for them.

<img width="400" alt="Four glossy spheres; they are blue, white, purple, and pink." src="https://user-images.githubusercontent.com/74445404/226090987-0e871318-bd65-4f9d-9acb-572592b5fc46.png">

<img width="400" alt="A white glossy sphere." src="https://user-images.githubusercontent.com/74445404/226090870-d2b8a464-f53f-4f02-99d2-8845995f6058.png">

<img width="400" alt="Three spheres with specular lighting." src="https://user-images.githubusercontent.com/74445404/226090908-f7789d0b-b18a-4fd3-ac78-79df5d5ac902.png">

Problems with specular lighting and glossy materials arise when intensity exceeds 1 from the Compute Light function. When this happens, black pixels are drawn where white highlights are expected to occur. (This has been fixed).

<img width="400" alt="Glossy spheres with black pixels where white highlights are expected." src="https://user-images.githubusercontent.com/74445404/226090800-5c1bb8b3-baf2-4c22-9155-e1fdf3066f05.png">

<img width="400" alt="Glossy sphere with black pixels where white highlights are expected." src="https://user-images.githubusercontent.com/74445404/226090730-8384436b-7385-4d72-a575-d05471f1f663.png">

### Diffuse
Ambient, point, and directional light reflections are implemented. 

<img width="400" alt="Three spheres with diffuse lighting. They look 3D now." src="https://user-images.githubusercontent.com/74445404/226056722-219a84e7-3642-4a58-9305-8df862eaae81.png">

There are some weird deformations with the spheres. (This has been fixed). 

<img width="400" alt="Three spheres with diffuse lighting and irregularities. Certain spots on the spheres are unexpected colors." src="https://user-images.githubusercontent.com/74445404/225863027-b5810131-a25b-4c0c-a792-f445967d8d31.png">

### Ambient only 
Flat shading with an equal intensity for all objects in the scene. 

<img width="400" alt="Three flat shaded spheres on a floor. They look 2D." src="https://user-images.githubusercontent.com/74445404/225862524-725356ea-92eb-4f33-9cd5-562a88333dfc.png">

## Flat Color
Parameterized spheres are rendered with flat colors. 

<img width="400" alt="Three flat shaded spheres, one blue, one pink, and one purple, displayed on a Windows console." src="https://user-images.githubusercontent.com/74445404/225229690-5caf386b-8999-445a-b5bb-bc3540a1ee8d.png">
