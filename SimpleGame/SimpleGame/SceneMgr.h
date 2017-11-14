#pragma once
#include <iostream>
#include <random>
#include <cstdlib>
#include "stdafx.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "Rect.h"

class SceneMgr
{
private:
    Rect		*rect[RECTSIZE];
	Rect		*bullet[BULLETSIZE];
	Rect		*arrow[ARROWSIZE];
	Rect		*building;
	Renderer	*m_renderer;
	GLuint		buildingTex;

	int m_windowWidth;
	int m_windowHeight;
    int     rectNum = 0;
    float   pTime;

    void    insertRect(float x, float y, float r, float g, float b, float speed, int type);
    int     getRandomNumber(int min, int max);
    float   getRandomfloat(float min, float max);

public:
    SceneMgr(int width, int height);
    ~SceneMgr();
    void    Update();
    void    RenderObject();
    void    Click(float x, float y);
    void    CollisionTest(Rect& a, Rect& b);
    float   distCalculate(Rect& a, Rect& b);
	bool	BoxBoxCol(float aMinX, float aMinY, float aMaxX, float aMaxY, float bMinX, float bMinY, float bMaxX, float bMaxY);
};

