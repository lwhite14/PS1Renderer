# PS1 Renderer
A render pipeline for rendering a first person scene with shading techniques aimed at emulating the aethetic/artifacts the PS1 and other 5th generation consoles. OpenGL is used for the rendering API.

![PS1Renderer](https://user-images.githubusercontent.com/55700734/172072925-bb5add5b-f14d-4937-918a-fd2ced188e59.gif)

## Navigating The Codebase
The runner.h file is responsible for setting up OpenGL and running the main loop. Functions from a scene are executed every frame in the main loop. The scene used within the runner is where the bulk of the program is executed. The update function updates various properties of the scene, while the render function is responsible for rendering the scene. The psx and quad shaders are used for the rendering. The psx shaders render the scene, while the quad shaders are used to render the scene to a textured quad and applying post-processing effects.
## Getting Started
### Source Code
To run the source code, you are going to need the dependancies for [GLFW](https://www.glfw.org/download.html), [GLM](https://glm.g-truc.net/0.9.8/index.html), and [GLAD](https://glad.dav1d.de/). You will need to link these dependancies in the VS properties, and add the generated glad.c file to the project. 
### Build
You can download a build of the renderer by going to the releases tab. Download a release zip, extract the zip file, and run the exe file. Do not remove the exe file from the folder structure, as the executable relies on files in these folders.
#
Made by Luke White!
