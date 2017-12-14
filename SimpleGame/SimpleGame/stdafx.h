#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

enum OBJECT_TYPE
{
	OBJECT_BUILDING,
	OBJECT_CHARACTER,
	OBJECT_BULLET,
	OBJECT_ARROW,
	OBJECT_PARTICLE
};


#define RECTSIZE		10
#define BULLETSIZE		100
#define ARROWSIZE		100
#define BUILDSIZE		3
#define WINHIGHT		800
#define WINWIDE			500
#define WIN_HALF_WIDE	WINWIDE / 2
#define WIN_HALF_HIGHT	WINHIGHT / 2
#define RED_TEAM		1
#define BLUE_TEAM		2

#define GLUT_STROKE_ROMAN
#define GLUT_STROKE_MONO_ROMAN
#define GLUT_BITMAP_9_BY_15
#define GLUT_BITMAP_8_BY_13
#define GLUT_BITMAP_TIMES_ROMAN_10
#define GLUT_BITMAP_TIMES_ROMAN_24
#define GLUT_BITMAP_HELVETICA_10
#define GLUT_BITMAP_HELVETICA_12
#define GLUT_BITMAP_HELVETICA_18


struct vec2
{
	float x;
	float y;
};