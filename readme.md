# Vulkan Initium

<!-- ![Vulkan](https://cdn.arstechnica.net/wp-content/uploads/2016/02/vulkan.jpg) -->
<!-- <sub><sup>Image credit <a href="https://arstechnica.com/gaming/2016/02/vulkan-benchmarks-a-boost-for-amd-and-nvidia-but-theres-work-to-be-done/">Ars Technica</a></sup></sub> -->

Following in the vein of the amazing [Glitter](https://github.com/Polytonic/Glitter) by [@Polytonic](https://github.com/Polytonic), here is a barebones repo for starting your [Vulkan](https://www.khronos.org/vulkan/) projects!

## Pulling
```git clone --recurse-submodules -j8 https://github.com/newyork167/VulkanInitium```

*The -j8 allows multiple modules to be pulled at once to be faster*

## Overview
### Why?
I've found that attempting to get beginner developers or even seasoned developers setup to get going on learning to build Vulkan applications has been just as hard, if not harder, than getting them set up for OpenGL. So I made this repository to help out others who want to venture forth into this brave new world of Vulkan! 

### What's in this Repo?
This repo contains a basic main file and submodule links to common libraries that are used within computer graphics.

### Prerequisites
For Windows:
- Visual Studio IDE (tested on VS 2017+ but should be fine on any which supports CMake), CLion, Code::Blocks, or any C/C++ IDE
- CMake 3.1+: https://cmake.org/download/

For Mac:
- XCode (or at least the developer tools installed), CLon, Code::Blocks, or any C/C++ IDE
- CMake: ```brew install cmake``` or https://cmake.org/download/

For Linux:
- CMake: 
    - For apt based systems: ```apt install cmake```
    - for rpm based systems: todo
    - https://cmake.org/download/
- Any IDE capable of using CMake: Code::Blocks, Eclipse, etc.

Of course you can use any IDE/Text Editor (vi, vim, not emacs, nano, etc...) and just use the CMake to do the building but for beginners it's generally easier to have an IDE that will allow you to get going out of the gate.  
