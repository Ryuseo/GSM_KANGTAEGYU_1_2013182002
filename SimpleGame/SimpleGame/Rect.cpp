#include "stdafx.h"
#include "Rect.h"

#define WIDTH 250
#define HEIGHT 250

Rect::Rect(float px, float py, float pz, float s, float r, float g, float b, float a, float vx, float vy, float vz, int lifeNum, float lifeT)
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
    life = lifeNum;
    lifeTime = lifeT;
}

Rect::Rect()
{

}

Rect::~Rect()
{

}

void Rect::update(float time)
{
    float elapsedTime = time / 1000;
    x += vectorX * elapsedTime;
    y += vectorY * elapsedTime;
    z += vectorZ * elapsedTime;
    lifeTime -= elapsedTime;

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
    if (x > WIDTH || x < -WIDTH)
    {
        vectorX = -vectorX;
        return true;
    }
    return false;
}

bool Rect::bounceV()
{
    if (y > HEIGHT || y < -HEIGHT)
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