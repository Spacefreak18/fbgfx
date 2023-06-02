# fbgfx
Simple Linux Framebuffer Library with TrueType Text Support

## About
This library started as a complete clone of the [fbgfx](https://github.com/OrangeTide/fbgfx) project by [Orangetide](https://github.com/OrangeTide/fbgfx). I then added support for double buffering and 90 degrees rotation. I then added support to render fonts in
any color and size using the example of [fbtextdemo](https://github.com/kevinboone/fbtextdemo).

This project is very much a means to an end for me and will receive minimal attention. Beyond cleanup, possibly adding 32bpp support, and other small fixes, it will receive next to no 
updates. It's existence is out of necessity to act as a display library for my [simlcd](https://github.com/Spacefreak18/simlcd) project.

That being said I welcome any and all contributions and pull requests, as this project could be useful to others who need to build some sort of simple embedded display support with
proper font rendering into a project.

## Features
- Supports embedded linux framebuffers
- Supports 16bpp
- Supports Double Buffering and display rotation
- Can render truetype fonts in any size and color
- Super lightweight

## Dependencies
- [freetype2](https://freetype.sourceforge.net/freetype2/index.html)

## Building

### demo
The included Makefile will build a demo.

### include in your project
Use the CMakeLists file to include this in a CMake project. Refer to the code in demo.c for the basic setup and API calls.

## Run
run the clock demo on frame buffer device connected to /dev/fb1 with a 90 degree clockwise rotation using software double buffering.
```
FBDEV=/dev/fb1 FBROTATE=1 ./fb16demo c
```

## ToDo
 - add some sort of logging
 - 32bpp support
 - document how to use supported features and cleanup their code
 - much, much more
