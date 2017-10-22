#pragma once
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <Windows.h>

#include "Dependencies\glew.h"
class Rect
{
private:
    bool bounceH();
    bool bounceV();
    void changeColor(float r, float g, float b);

public:
    float x;
    float y;
    float z;
    float size;
    float red;
    float green;
    float blue;
    float alhpa;
    float vectorX;
    float vectorY;
    float vectorZ;

    Rect(float x, float y, float z, float s, float r, float g, float b, float a, float vx, float vy, float vz);
    Rect();
    ~Rect();
    void update();
};