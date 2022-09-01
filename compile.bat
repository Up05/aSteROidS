@echo off
cls
C:\msys64\mingw64\bin\gcc src/* -I lib/GLFW/include/ -I headers lib\GLFW\lib-mingw-w64\libglfw3.a -lopengl32 -lkernel32 -luser32 -lgdi32 -lws2_32 -o asteroids.exe
asteroids.exe
@echo on