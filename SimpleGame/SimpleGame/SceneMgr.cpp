#include <iostream>
#include <random>
#include "stdafx.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "SceneMgr.h"
#include "Renderer.h"
#include "tempObject.h"

#define RectSize 50

using namespace std;

SceneMgr::SceneMgr(int inputargc, char **inputargv)
{
    Rect *rect = new Rect[RectSize];
}

void SceneMgr::Update()
{
    for (int i  = 0; i < RectSize; ++i)
    {
        rect[i].update();
    }
}

Rect SceneMgr::RenderObject(int i)
{
    return rect[i];
}

void SceneMgr::Click(float x, float y)
{
    insertRect(x, y);
}

void SceneMgr::insertRect(float x, float y)
{
    rect[rectNum] = { x - 250, 500 - y - 250, 0, getRandomfloat(10,100), getRandomfloat(0.0,1.0), getRandomfloat(0.0,1.0), getRandomfloat(0.0,1.0), 1.0 };
    rect[rectNum].vectorX = getRandomfloat(-0.1, 0.1);
    rect[rectNum].vectorY = getRandomfloat(-0.1, 0.1);
    if (rectNum >= RectSize)
    {
        rectNum = 0;
    }
    else
    {
        rectNum++;
    }
}

int SceneMgr::getRandomNumber(int min, int max)
{
    //< 1단계. 시드 설정
    random_device rn;
    default_random_engine rnd(rn());

    //< 2단계. 분포 설정 ( 정수 )
    uniform_int_distribution<int> range(min, max);

    //< 3단계. 값 추출
    return range(rnd);
}

float SceneMgr::getRandomfloat(float min, float max)
{
    //< 1단계. 시드 설정
    random_device rn;
    default_random_engine rnd(rn());

    //< 2단계. 분포 설정 ( 정수 )
    uniform_real_distribution<float> range(min, max);

    //< 3단계. 값 추출
    return range(rnd);
}