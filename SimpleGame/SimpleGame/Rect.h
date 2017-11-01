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
    float   x;
    float   y;
    float   z;
    float   size;
    float   red;
    float   green;
    float   blue;
    float   alhpa;
    float   vectorX;
    float   vectorY;
    float   vectorZ;
    int     life;
    float   lifeTime;

    bool bounceH();
    bool bounceV();

public:

    Rect(float x, float y, float z, float s, float r, float g, float b, float a, float vx, float vy, float vz, int lifeNum, float lifeT);
    Rect();
    ~Rect();
    float   getX        ()                          { return x; }
    float   getY        ()                          { return y; }
    float   getZ        ()                          { return z; }
    float   getSize     ()                          { return size; }
    float   getRed      ()                          { return red; }
    float   getGreen    ()                          { return green; }
    float   getBlue     ()                          { return blue; }
    float   getAlhpa    ()                          { return alhpa; }
    float   getVectorX  ()                          { return vectorX; }
    float   getVectorY  ()                          { return vectorY; }
    float   getVectorZ  ()                          { return vectorZ; }
    int     getLife     ()                          { return life; }
    float   getLifeTime ()                          { return lifeTime; }
    void    setLife     ()                          { life--; }
    void    update      (float time);
    void    changeColor (float r, float g, float b);
};