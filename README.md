# Code OpenGL using C++

Please find the code of our project on the branch named "final".

# Installation

You would need CMake(to build our project) which can be downloaded from [here](https://cmake.org/download/).

# Setup

After cloning this repo, you also need to load the submodules GLEW, GLFW and GLM using the following command.

    git submodule update --init --recursive


## Run the Application

To launch the window, simply run:

    cmake .
    make
    ./opengl_program

## Context of the Application

You can see an entity floating in an abandonned shed, move the camera with the mouse and the directionnal arrows.
