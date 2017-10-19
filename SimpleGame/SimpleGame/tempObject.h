#pragma once
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <Windows.h>

#include "Dependencies\glew.h"
class tempObject
{
public:
    tempObject();
    ~tempObject();

};

class Rect
{
private:
    bool bounceH();
    bool bounceV();

public:
    Rect(float x, float y, float z, float s, float r, float g, float b, float a);
    Rect();
    ~Rect();
    void update();

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
};