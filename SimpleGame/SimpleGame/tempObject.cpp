#include "stdafx.h"
#include "tempObject.h"


tempObject::tempObject()
{
    
}


tempObject::~tempObject()
{
}


Rect::Rect(float px, float py, float pz, float s, float r, float g, float b, float a)
{
    x = px;
    y = py;
    z = pz;
    size = s;
    red = r;
    green = g;
    blue = b;
    alhpa = a;
    vectorX = 0.1;
    vectorY = 0.1;
    vectorZ = 0;
}

Rect::Rect()
{

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