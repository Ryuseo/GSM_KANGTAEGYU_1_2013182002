#pragma once
#include <iostream>
#include <random>
#include "stdafx.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "SceneMgr.h"
#include "Renderer.h"
#include "Rect.h"
class SceneMgr
{
private:
    Rect    *rect;
    int     rectNum = 0;
    float   pTime;

    void    insertRect(float x, float y);
    int     getRandomNumber(int min, int max);
    float   getRandomfloat(float min, float max);

public:
    SceneMgr();
    ~SceneMgr();
    void    Update();
    Rect    RenderObject(int i);
    void    Click(float x, float y);
    void    CollisionTest();
    float   distCalculate(Rect& a, Rect& b);
};

