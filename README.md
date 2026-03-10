# C-GL
Learning some OpenGL with C as the CPU-side language. Mess around with the inputs to your liking to get the essence of graphics programming.

## Description (Lighting):
There is a black void with a coral cube (main object) and a white cube, which is acting as a lamp. The lamp is sinusoidally revolving around the object to showcase the effects of Phong lighting.

## Building:
Run `build.sh` for **GCC or Clang** or `build.bat` on **MSVC.** You may also go to the CML file and change the build type to `Release` instead of `Debug` if you want the program not to instantly stop when it runs into a problem.

## Running:
Executable is located in `build/` for **GCC or Clang.** It is located in `build\Debug` or `build\Release` for **MSVC** according to the build type.

## Controls:
You can ***move around*** by using **WASD** or **Arrow Keys** and ***move up and down*** by using **Space and Ctrl**, but keep in mind that the controls are toggle based. This is so because I am developing on an Android phone via Termux, which has messed up inputs. 

You can also ***look around*** via mouse input, but keep in mind that the controls are not inverted. If you wish to do so, go to `src/main.c` and make the following change on **line 32**:
```C
boolean mouse_first = true, mouse_invert = true;
```
---
