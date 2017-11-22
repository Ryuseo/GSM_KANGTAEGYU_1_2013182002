#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

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

struct vec2
{
	float x;
	float y;
};