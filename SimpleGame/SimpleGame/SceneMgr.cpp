#include "stdafx.h"
#include "SceneMgr.h"

#define RectSize 10

using namespace std;

SceneMgr::SceneMgr()
{
    rect = new Rect[RectSize];
    for (int i = 0; i < RectSize; ++i)
    {
        rect[i] = { getRandomfloat(-100,100), getRandomfloat(-100,100), 0, 10, 1, 1, 1, 1.0 ,getRandomfloat(-10.0, 10.0) ,getRandomfloat(-10.0, 10.0) , 0, getRandomNumber(3, 5),getRandomfloat(10.0, 20.0)};
    }
    pTime = timeGetTime();

}

SceneMgr::~SceneMgr()
{

}

void SceneMgr::Update()
{
    float nTime =  timeGetTime();
    for (int i = 0; i < RectSize; ++i)
    {
        if (rect[i].getLife() <= -1) { break; }

        rect[i].update(nTime - pTime);
        CollisionTest();
        if (rect[i].getLife() <= 0)
        {
            rect[i].setLife();
        }
        else if (rect[i].getLifeTime() <= 0)
        {
            rect[i].setLife();
        }
    }
    pTime = nTime;
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
    rect[rectNum] = { x - 250, 500 - y - 250, 0, 1, 1, 1, 1, 1.0 ,getRandomfloat(-10.0, 10.0) ,getRandomfloat(-10.0, 10.0) ,0 , getRandomNumber(3, 5),getRandomfloat(10.0, 20.0) };
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

void SceneMgr::CollisionTest()
{
	for (int i = 0; i < RectSize - 1; ++i)
	{
		rect[i].changeColor(1, 1, 1);
	}

    for (int i = 0; i < RectSize - 1; ++i)
    {
        for (int j = i + 1; j < RectSize; ++j)
        {
            if (rect[i].getX() + (rect[i].getSize() / 2) < rect[j].getX() - (rect[j].getSize() / 2))
            {
                break;
            }
            else if (rect[i].getX() - (rect[i].getSize() / 2) > rect[j].getX() + (rect[j].getSize() / 2))
            {
                break;
            }
            if (rect[i].getY() + (rect[i].getSize() / 2) < rect[j].getY() - (rect[j].getSize() / 2))
            {
                break; 
            }
            else if (rect[i].getY() - (rect[i].getSize() / 2) > rect[j].getY() + (rect[j].getSize() / 2))
            {
                break;
            }
            rect[i].changeColor(1, 0, 0);
            rect[j].changeColor(1, 0, 0);
        }
    }
}

float SceneMgr::distCalculate(Rect& a, Rect& b)
{
    float distX = a.getX() - b.getX();
    float distY = a.getY() - b.getY();
    
    return sqrtf(distX) + sqrtf(distY);
}
