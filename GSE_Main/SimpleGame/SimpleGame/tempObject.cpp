#include "stdafx.h"
#include "tempObject.h"


tempObject::tempObject()
{
    
}


tempObject::~tempObject()
{
}


Rect::Rect(float x, float y, float z, float s, float r, float g, float b, float a)
{
    x = x;
    y = y;
    z = z;
    size = s;
    red = r;
    green = g;
    blue = b;
    alhpa = a;
    vectorX = 0.1;
    vectorY = 0.1;
    vectorZ = 0;
}

Rect::~Rect()
{

}

void Rect::update()
{
    x += vectorX;
    y += vectorY;
    z += vectorZ;

    if (x > 250)
    {
        vectorX = -vectorX;
    }
    else if (x < -250)
    {
        vectorX = -vectorX;
    }

    if (y > 250)
    {
        vectorY = -vectorY;
    }
    else if (y < -250)
    {
        vectorY = -vectorY;
    }
}