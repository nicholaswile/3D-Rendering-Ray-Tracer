# 3D Renderer - Ray Tracing
This is a work in progress. Each branch represents a different basic feature of the ray tracer. Currently flat colors are rendered. I plan to add lighting, shadows, and reflections.

## Lighting (Current)

### Specular 
Up next after I fix diffuse reflections. 

### Diffuse
Ambient, point, and directional light reflections are implemented. 

<img width="400" alt="Three spheres with diffuse lighting. They look 3D now." src="https://user-images.githubusercontent.com/74445404/226056722-219a84e7-3642-4a58-9305-8df862eaae81.png">

There are some weird deformations with the spheres. (This has been fixed). 

<img width="400" alt="Three spheres with diffuse lighting and irregularities. Certain spots on the spheres are unexpected colors." src="https://user-images.githubusercontent.com/74445404/225863027-b5810131-a25b-4c0c-a792-f445967d8d31.png">

### Ambient only 
Flat shading with an equal intensity for all objects in the scene. 

<img width="400" alt="Three flat shaded spheres on a floor. They look 2D." src="https://user-images.githubusercontent.com/74445404/225862524-725356ea-92eb-4f33-9cd5-562a88333dfc.png">

## Flat Color (Done)
Parameterized spheres are rendered with flat colors. 

<img width="400" alt="Three flat shaded spheres, one blue, one pink, and one purple, displayed on a Windows console." src="https://user-images.githubusercontent.com/74445404/225229690-5caf386b-8999-445a-b5bb-bc3540a1ee8d.png">
