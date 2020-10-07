# Vulkan Initium

<!-- ![Vulkan](https://cdn.arstechnica.net/wp-content/uploads/2016/02/vulkan.jpg) -->
<!-- <sub><sup>Image credit <a href="https://arstechnica.com/gaming/2016/02/vulkan-benchmarks-a-boost-for-amd-and-nvidia-but-theres-work-to-be-done/">Ars Technica</a></sup></sub> -->

Following in the vein of (and building upon) the great <!-- Since people thought amazing was a bit much... --> [Glitter](https://github.com/Polytonic/Glitter) by [@Polytonic](https://github.com/Polytonic), here is a barebones repo for starting your [Vulkan](https://www.khronos.org/vulkan/) projects!

## Pulling
```git clone --recurse-submodules -j8 https://github.com/newyork167/VulkanInitium```

*The -j8 allows multiple modules to be pulled at once to be faster*

## Overview
### Why?
I've found that attempting to get beginner or even seasoned developers setup to get going on learning to build Vulkan applications has been just as hard, if not harder, than getting them set up for OpenGL. So I made this repository to help out others who want to venture forth into this brave new world of Vulkan!

Hopefully this helps out those in the advanced computer graphics courses we are offering get set up with the basics so they can get building! 

The main branch now includes the hello triangle from [Vulkan Tutorial](https://vulkan-tutorial.com/) as the default program being ran and an empty program with a basic instance setup.

### What's in this Repo?
This repo contains a basic main file and submodule links to common libraries that are used within computer graphics. 

### Prerequisites
Vulkan Drivers: [LunarG Downloads](https://vulkan.lunarg.com/sdk/home), [Nvidia](https://developer.nvidia.com/vulkan-driver), [AMD](http://gpuopen.com/gaming-product/vulkan/), [Source Code](https://github.com/KhronosGroup/Vulkan-Hpp)

For Mac:
- XCode (or at least the developer tools installed), Vim, CLon, Code::Blocks, or any C/C++ IDE
- CMake 3.10+: ```brew install cmake``` or https://cmake.org/download/

For Linux:
- CLion, Vim, Code::Blocks, or any C/C++ IDE or text editor
- CMake 3.10+: Use whatever package manager your distro uses or https://cmake.org/download/

For Windows:
- Visual Studio IDE (tested on VS 2017/2019 with CMake), CLion, Code::Blocks, or any C/C++ IDE
- CMake 3.10+: [Chocolatey](https://chocolatey.org/packages/cmake) or https://cmake.org/download/

Of course you can use any IDE/Text Editor (vi, vim, not emacs, nano, etc...) and just use the CMake to do the building. For beginners (to which I would recommend instead learning OpenGL or DX11 first to learn more about the graphics pipeline) it's generally easier to have an IDE that will allow you to get going out of the gate. For those taking our CS 32100/42100/52100 classes it's recommended to use CLion/XCode/VS2019 depending on your platform.

## Future Plans / TODO
I will make branches for basic rendering as I have time, and to the base branch I will add in the simple default cube in a non-intrusive way. For now, it contains a basic triangle to get you going.
