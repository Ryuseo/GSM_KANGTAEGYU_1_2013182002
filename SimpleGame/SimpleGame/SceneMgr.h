#pragma once
#include <iostream>
#include <random>
#include <cstdlib>
#include "stdafx.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "Rect.h"

#define RectSize 10
class SceneMgr
{
private:
    Rect    *rect[RectSize];
	Renderer *m_renderer;

	int m_windowWidth;
	int m_windowHeight;
    int     rectNum = 0;
    float   pTime;

    void    insertRect(float x, float y);
    int     getRandomNumber(int min, int max);
    float   getRandomfloat(float min, float max);

public:
    SceneMgr(int width, int height);
    ~SceneMgr();
    void    Update();
    void    RenderObject();
    void    Click(float x, float y);
    void    CollisionTest();
    float   distCalculate(Rect& a, Rect& b);
};

