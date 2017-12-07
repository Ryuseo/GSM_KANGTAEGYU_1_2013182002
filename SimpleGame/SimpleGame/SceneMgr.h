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
    Rect		*red_Char[RECTSIZE];
	Rect		*red_Bullet[BULLETSIZE];
	Rect		*red_Arrow[ARROWSIZE];
	Rect		*red_building[BUILDSIZE];
	Rect		*blue_Char[RECTSIZE];
	Rect		*blue_Bullet[BULLETSIZE];
	Rect		*blue_Arrow[ARROWSIZE];
	Rect		*blue_building[BUILDSIZE];
	Rect		*particleArr[1000];
	Renderer	*m_renderer;
	GLuint		buildingTex[2];
	GLuint		backGround;
	GLuint		char_ani;
	GLuint		partice_tex;

	int count = 0;
	float	temptime;
    float   pTime;
	float	red_Char_spwn_t = 0;
	float	blue_Char_spwn_t = 0;
	bool	blue_Char_spwn_flag = false;
	int		blue_Char_spwn_posX;
	int		blue_Char_spwn_posY;
	long	particleTime;

    int     getRandomNumber(int min, int max);
    float   getRandomfloat(float min, float max);

public:
    SceneMgr(int width, int height);
    ~SceneMgr();
    void    Update();
    void    RenderObject();
    void    Click(float x, float y);
    void    CollisionTest(Rect& a, Rect& b);
	bool	BoxBoxCol(float aMinX, float aMinY, float aMaxX, float aMaxY, float bMinX, float bMinY, float bMaxX, float bMaxY);
	vec2	calculateVector(float speed);
};

