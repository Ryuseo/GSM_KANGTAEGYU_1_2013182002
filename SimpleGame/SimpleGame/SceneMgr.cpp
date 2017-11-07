#include <iostream>

#include "stdafx.h"
#include "SceneMgr.h"


using namespace std;

enum OBJECT_TYPE
{
	OBJECT_BUILDING,
	OBJECT_CHARACTER,
	OBJECT_BULLET,
	OBJECT_ARROW,
};


SceneMgr::SceneMgr(int width, int height)
{
	m_renderer = new Renderer(width, height);

	if (!m_renderer->IsInitialized())
	{
		std::cout << "SceneMgr::Renderer could not be initialized.. \n";
	}

	m_windowWidth = width;
	m_windowHeight = height;

	for (int i = 0; i < RECTSIZE; ++i )
	{
		rect[i] = NULL;
	}
	for (int i = 0; i < BULLETSIZE; ++i)
	{
		bullet[i] = NULL;
	}

	building = new Rect(0, 0, 0, 50, 1, 1, 0, 1.0, 0, 0, 0, 500, 100000000, OBJECT_BUILDING);

    pTime = timeGetTime();
}

SceneMgr::~SceneMgr()
{

}

float spawnBT = 0;

void SceneMgr::Update()
{
    float nTime =  timeGetTime();

	// 충돌
	for (int i = 0; i < RECTSIZE; ++i)
	{
		if (rect[i] != NULL && building != NULL)
		{
			CollisionTest(*building, *rect[i]);
		}
	}

	for (int i = 0; i < RECTSIZE; ++i)
	{
		if (rect[i] != NULL)
		{
			for (int j = 0; j < BULLETSIZE; ++j)
			{
				if (bullet[j] != NULL)
				{
					CollisionTest(*rect[i], *bullet[j]);
				}
			}
		}
	}

	// 업데이트
	if (building != NULL)
	{
		building->update(nTime - pTime);
		if (building->getLife() <= 0 || building->getLifeTime() <= 0)
		{
			building = NULL;
		}
	}

    for (int i = 0; i < RECTSIZE; ++i)
    {
		if (rect[i] != NULL)
		{
			rect[i]->update(nTime - pTime);
			if (rect[i]->getLife() <= 0 || rect[i]->getLifeTime() <= 0)
			{
				rect[i] = NULL;
			}
		}
    }

	for (int i = 0; i < BULLETSIZE; ++i)
	{
		if (bullet[i] != NULL)
		{
			bullet[i]->update(nTime - pTime);
			if (bullet[i]->getLife() <= 0 || bullet[i]->getLifeTime() <= 0)
			{
				bullet[i] = NULL;
			}
		}
	}

	//총알 생성
	if (1000 < nTime - spawnBT)
	{
		for (int i = 0; i < BULLETSIZE; ++i)
		{
			if (bullet[i] == NULL)
			{
				float temp = getRandomNumber(1, 2);
				if (temp == 2)
				{
					temp = -1;
				}
				float vectorX = getRandomfloat(0.0, 6000.0);
				float vectorY = sqrt(6000.0 - vectorX) * temp;
				temp = getRandomNumber(1, 2);
				if (temp == 2)
				{
					temp = -1;
				}
				vectorX = sqrt(vectorX) * temp;
				bullet[i] = new Rect(0, 0, 0, 10, 1, 0, 0, 1.0, vectorX, vectorY, 0, 20, 10, OBJECT_BULLET);
				break;
			}
		}
		spawnBT = nTime;
	}
    pTime = nTime;
}

void SceneMgr::RenderObject()
{
	for (int i = 0; i < RECTSIZE; i++)
	{
		if (rect[i] != NULL)
		{
			// Renderer Test
			m_renderer->DrawSolidRect(
				rect[i]->getX(),
				rect[i]->getY(),
				0,
				rect[i]->getSize(),
				rect[i]->getRed(),
				rect[i]->getGreen(),
				rect[i]->getBlue(),
				rect[i]->getAlhpa()
			);
		}
	}

	for (int i = 0; i < BULLETSIZE; i++)
	{
		if (bullet[i] != NULL)
		{
			// Renderer Test
			m_renderer->DrawSolidRect(
				bullet[i]->getX(),
				bullet[i]->getY(),
				0,
				bullet[i]->getSize(),
				bullet[i]->getRed(),
				bullet[i]->getGreen(),
				bullet[i]->getBlue(),
				bullet[i]->getAlhpa()
			);
		}
	}

	if (building != NULL)
	{
		m_renderer->DrawSolidRect(
			building->getX(),
			building->getY(),
			0,
			building->getSize(),
			building->getRed(),
			building->getGreen(),
			building->getBlue(),
			building->getAlhpa()
		);
	}
}

void SceneMgr::Click(float x, float y)
{
	for (int i = 0; i < RECTSIZE; ++i)
	{
		if (rect[i] == NULL)
		{
			insertRect(x - 250, 250 - y,1,1,1,300, OBJECT_CHARACTER);
			break;
		}
	}
}

void SceneMgr::insertRect(float x, float y,float r, float g, float b, float speed, int type)
{
	for (int i = 0; i < RECTSIZE; ++i)
	{
		if (rect[i] == NULL)
		{
			float temp = getRandomNumber(1, 2);
			if (temp == 2)
			{
				temp = -1;
			}
			float vectorX = getRandomfloat(0.0, speed);
			float vectorY = sqrt(speed - vectorX) * temp;
			temp = getRandomNumber(1, 2);
			if (temp == 2)
			{
				temp = -1;
			}
			vectorX = sqrt(vectorX) * temp;
			rect[i] = new Rect(x,  y, 0, 10, r, g, b, 1.0, vectorX, vectorY, 0, 40, 10000000, type);
			break;
		}
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

void SceneMgr::CollisionTest(Rect& a, Rect& b)
{
	float aMinX, aMinY;
	float aMaxX, aMaxY;

	float bMinX, bMinY;
	float bMaxX, bMaxY;

	aMinX = a.getX() - a.getSize() / 2.f;
	aMinY = a.getY() - a.getSize() / 2.f;
	aMaxX = a.getX() + a.getSize() / 2.f;
	aMaxY = a.getY() + a.getSize() / 2.f;
	bMinX = b.getX() - b.getSize() / 2.f;
	bMinY = b.getY() - b.getSize() / 2.f;
	bMaxX = b.getX() + b.getSize() / 2.f;
	bMaxY = b.getY() + b.getSize() / 2.f;

	if (BoxBoxCol(aMinX, aMinY, aMaxX, aMaxY, bMinX, bMinY, bMaxX, bMaxY))
	{
		if (a.getType() == OBJECT_BUILDING && b.getType() == OBJECT_CHARACTER)
		{
			a.setLife(b.getLife());
			b.setLife(b.getLife());
			cout << a.getLife() << endl;
		}
		else if (a.getType() == OBJECT_CHARACTER && b.getType() == OBJECT_BULLET)
		{
			a.setLife(b.getLife());
			b.setLife(b.getLife());
		}
	}
}

bool SceneMgr::BoxBoxCol(float aMinX, float aMinY, float aMaxX, float aMaxY, float bMinX, float bMinY, float bMaxX, float bMaxY)
{
	if (aMinX > bMaxX)
		return false;
	if (aMaxX < bMinX)
		return false;

	if (aMinY > bMaxY)
		return false;
	if (aMaxY < bMinY)
		return false;

	return true;
}

float SceneMgr::distCalculate(Rect& a, Rect& b)
{
    float distX = a.getX() - b.getX();
    float distY = a.getY() - b.getY();
    
    return sqrtf(distX) + sqrtf(distY);
}
