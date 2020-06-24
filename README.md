# Hoowan
Personal game engine project developed using C++ and OpenGL

# Overview
Hoowan is my game engine developed in C++ and OpenGL. I’m following “The Cherno’s” Game Engine development YouTube series in addition to following some design patterns from Jason Gregory’s “Game Engine Architecture”, Third Edition. This likely won’t become a huge commercial game engine (duh). This is mostly for me to learn more about C++ development, real-time rendering, and game engine architecture. I also hope to develop a basic game using this engine.

The Cherno's Game Engine YouTube series: https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT

Game Engine Architecture, Third Edition buy/rent: https://www.amazon.com/Engine-Architecture-Third-Jason-Gregory/dp/1138035459/ref=sr_1_2?dchild=1&keywords=game+engine&qid=1591651300&sr=8-2

# Log
### 06/24/2020 - Object Transformations, Delta Time, and Material System
![2](RMImages/2.PNG)
Officially graduated from just rendering a single Dorito!

In this update, I abstracted more OpenGL/GLFW components in order to keep the sandbox environment clean. Hoowan now keeps track of object vertex and shader data internally, so users can focus on just supplying vertices and GLSL code. From there, users can apply position, scaling, quaternion rotations, and shear transformations (assuming the vertex shader takes in a proper model matrix). In addition, these components can change over time now that the Sandbox environment is exposed to a global DeltaTime variable. In addition to all of this, I created a shader file parser (so we don’t have to write shader source inline). The shader compiler also dynamically handles uniforms, so it’s pretty easy to upload texture bitmaps.

For the next update, I’ll be focusing on making a proper 2D renderer, as my current setup isn’t extremely efficient. This will mean diving into profiling, instrumentation, and batch rendering.

### 06/21/2020 - Hello, Abstraction!
![1](RMImages/1.PNG)
This took way too much code…

In this update, I set up an empty C++ project with an engine and corresponding sandbox solution. I imported several APIs and libraries, including spdlog for console logging, GLFW for setting up the OpenGL rendering context and input handling, Glad for load generating, glm for an OpenGL math library, and imgui for in-app user interface customization. Then came the monstrous task of abstracting all of these elements away for use by the sandbox environment…

However, I’m very happy with the result. The current configuration allows me to focus on the fun stuff, like cameras, transforms, and materials systems. I hope to actually be able to make a basic 2D game within the next few updates!
