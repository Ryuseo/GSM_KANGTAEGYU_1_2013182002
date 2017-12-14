#include "stdafx.h"
#include "Rect.h"
#include <iostream>

using namespace std;

Rect::Rect(float px, float py, float pz, float s, float r, float g, float b, float a, float vx, float vy, float vz, int lifeNum, float lifeT, int inputType, int t)
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
	type = inputType;
	coolTime = 0;
	team = t;
	ani_CoolTime = 0.3;
	anisqs = 0;
	countTime = 0;
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
    //z += vectorZ * elapsedTime;
    lifeTime -= elapsedTime;
	coolTime += elapsedTime;
	ani_CoolTime -= elapsedTime;
	countTime += elapsedTime;
	if (ani_CoolTime < 0)
	{
		ani_CoolTime = 0.3;
		anisqs++;
		if (anisqs > 2)
		{
			anisqs = 0;
		}
	}
    if (bounceH(elapsedTime))
    {
        //changeColor(1,0,0);
    }
    else
    {
        //changeColor(1, 1, 1);
    }

    if (bounceV(elapsedTime))
    {
        //changeColor(1, 0, 0);
    }
    else
    {
        //changeColor(1, 1, 1);
    }
}

bool Rect::bounceH(float time)
{
    if (x > WIN_HALF_WIDE || x < -WIN_HALF_WIDE)
    {
		if (type == OBJECT_BULLET || type == OBJECT_ARROW)
		{
			life = -1;
			lifeTime = -1;
		}
		else
		{
			vectorX = -vectorX;
			x += vectorX * time;
		}
        return true;
    }
    return false;
}

bool Rect::bounceV(float time)
{
    if (y > WIN_HALF_HIGHT || y < -WIN_HALF_HIGHT)
    {
		if (type == OBJECT_BULLET || type == OBJECT_ARROW)
		{
			life = -1;
			lifeTime = -1;
		}
		else
		{
			vectorY = -vectorY;
			y += vectorY * time;
		}
        return true;
    }
    return false;
}