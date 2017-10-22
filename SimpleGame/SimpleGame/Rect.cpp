#include "stdafx.h"
#include "Rect.h"

Rect::Rect(float px, float py, float pz, float s, float r, float g, float b, float a, float vx, float vy, float vz)
{
    x = px;
    y = py;
    z = pz;
    size = s;
    red = r;
    green = g;
    blue = b;
    alhpa = a;
    vectorX = vx;
    vectorY = vy;
    vectorZ = vz;
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

    if (bounceH())
    {
        changeColor(1,0,0);
    }
    else
    {
        changeColor(1, 1, 1);
    }

    if (bounceV())
    {
        changeColor(1, 0, 0);
    }
    else
    {
        changeColor(1, 1, 1);
    }
}

bool Rect::bounceH()
{
    if (x > 250 || x < -250)
    {
        vectorX = -vectorX;
        return true;
    }
    return false;
}

bool Rect::bounceV()
{
    if (y > 250 || y < -250)
    {
        vectorY = -vectorY;
        return true;
    }
    return false;
}

void Rect::changeColor(float r, float g, float b)
{
    red = r;
    green = g;
    blue = b;
}