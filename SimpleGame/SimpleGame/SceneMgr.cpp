#include <iostream>

#include "stdafx.h"
#include "SceneMgr.h"


using namespace std;


SceneMgr::SceneMgr(int width, int height)
{
	m_renderer = new Renderer(width, height);
	sound = new Sound();

	temptime = timeGetTime();

	if (!m_renderer->IsInitialized())
	{
		std::cout << "SceneMgr::Renderer could not be initialized.. \n";
	}

	for (int i = 0; i < BUILDSIZE; ++i)
	{
		red_building[i] = new Rect(125 * (i + 1) - WIN_HALF_WIDE, 300, 0, 100, 1, 1, 1, 1.0, 0, 0, 0, 500, 100000000, OBJECT_BUILDING, 1);
		blue_building[i] = new Rect(125 * (i + 1) - WIN_HALF_WIDE, -300, 0, 100, 1, 1, 1, 1.0, 0, 0, 0, 500, 100000000, OBJECT_BUILDING, 2);
	}

	for (int i = 0; i < RECTSIZE; ++i )
	{
		red_Char[i] = NULL;
		blue_Char[i] = NULL;
	}
	for (int i = 0; i < BULLETSIZE; ++i)
	{
		red_Bullet[i] = NULL;
		blue_Bullet[i] = NULL;
	}
	for (int i = 0; i < ARROWSIZE; ++i)
	{
		red_Arrow[i] = NULL;
		blue_Arrow[i] = NULL;
	}

	buildingTex[0] = m_renderer->CreatePngTexture("./Resouce/redBuildingTex.png");
	buildingTex[1] = m_renderer->CreatePngTexture("./Resouce/blueBuildingTex.png");
	backGround = m_renderer->CreatePngTexture("./Resouce/backGround.png");
	char_ani = m_renderer->CreatePngTexture("./Resouce/soldier.png");
	partice_tex = m_renderer->CreatePngTexture("./Resouce/particle.png");
	
	soundBGB = sound->CreateSound("./Dependencies/SoundSamples/MF-W-90.XM");

	sound->PlaySound(soundBGB, true, 0.2f);


    pTime = timeGetTime();
}

SceneMgr::~SceneMgr()
{

}

float spawnBT = 0;
float climateTime = 0;

void SceneMgr::Update()
{
    float nTime =  timeGetTime();
	climateTime += (nTime - pTime) / 1000.0;

	// 충돌
	// 건물 - 캐릭터
	for (int i = 0; i < BUILDSIZE; ++i)	//캐릭터 - 건물 
	{
		if (red_building[i] != NULL)
		{
			for (int j = 0; j < RECTSIZE; ++j)
			{
				if (blue_Char[j] != NULL)
				{
					CollisionTest(*red_building[i], *blue_Char[j]);
				}
			}
		}

		if (blue_building[i] != NULL)
		{
			for (int j = 0; j < RECTSIZE; ++j)
			{
				if (red_Char[j] != NULL)
				{
					CollisionTest(*blue_building[i], *red_Char[j]);
				}
			}
		}
	}
	// 캐릭터 - 총알
	for (int i = 0; i < RECTSIZE; ++i)	//총알 - 캐릭터
	{
		if (red_Char[i] != NULL)
		{
			for (int j = 0; j < BULLETSIZE; ++j)
			{
				if (blue_Bullet[j] != NULL)
				{
					CollisionTest(*red_Char[i], *blue_Bullet[j]);
				}
			}
		}

		if (blue_Char[i] != NULL)
		{
			for (int j = 0; j < BULLETSIZE; ++j)
			{
				if (red_Bullet[j] != NULL)
				{
					CollisionTest(*blue_Char[i], *red_Bullet[j]);
				}
			}
		}
	}
	// 화살 - 캐릭터
	for (int i = 0; i < RECTSIZE; ++i)	//화살 - 캐릭터
	{
		if (red_Char[i] != NULL)
		{
			for (int j = 0; j < ARROWSIZE; ++j)
			{
				if (blue_Arrow[j] != NULL)
				{
					CollisionTest(*red_Char[i], *blue_Arrow[j]);
				}
			}
		}

		if (blue_Char[i] != NULL)
		{
			for (int j = 0; j < ARROWSIZE; ++j)
			{
				if (red_Arrow[j] != NULL)
				{
					CollisionTest(*blue_Char[i], *red_Arrow[j]);
				}
			}
		}
	}
	// 총알 - 건물
	for (int i = 0; i < BUILDSIZE; ++i)	//화살 - 건물
	{
		if (red_building[i] != NULL)
		{
			for (int j = 0; j < ARROWSIZE; ++j)
			{
				if (blue_Arrow[j] != NULL)
				{
					CollisionTest(*red_building[i], *blue_Arrow[j]);
				}
			}
		}

		if (blue_building[i] != NULL)
		{
			for (int j = 0; j < ARROWSIZE; ++j)
			{
				if (red_Arrow[j] != NULL)
				{
					CollisionTest(*blue_building[i], *red_Arrow[j]);
				}
			}
		}
	}

	// 업데이트
	red_Char_spwn_t += (nTime - pTime) / 1000.0;
	blue_Char_spwn_t += (nTime - pTime) / 1000.0;

	//건물
	for (int i = 0; i < BUILDSIZE; ++i)
	{
		if (red_building[i] != NULL)
		{
			red_building[i]->update(nTime - pTime);
			if (red_building[i]->getCoolTime() >= 10)
			{
				for (int j = 0; j < BULLETSIZE; ++j)
				{
					if (red_Bullet[j] == NULL)
					{
						vec2 vector = calculateVector(100);

						red_Bullet[j] = new Rect(red_building[i]->getX(), red_building[i]->getY(), 0, 5, 1, 0, 0, 1.0, vector.x, vector.y, 0, 20, 10000000, OBJECT_BULLET, 1);
						red_building[i]->resetCoolTime();
						break;
					}
				}
			}
			if (red_building[i]->getLife() <= 0 || red_building[i]->getLifeTime() <= 0)
			{
				red_building[i] = NULL;
			}
		}
		if (blue_building[i] != NULL)
		{
			blue_building[i]->update(nTime - pTime);
			if (blue_building[i]->getCoolTime() >= 10)
			{
				for (int j = 0; j < BULLETSIZE; ++j)
				{
					if (blue_Bullet[j] == NULL)
					{
						vec2 vector = calculateVector(100);

						blue_Bullet[j] = new Rect(blue_building[i]->getX(), blue_building[i]->getY(), 0, 5, 0, 0, 1, 1.0, vector.x, vector.y, 0, 20, 100000, OBJECT_BULLET, 2);
						blue_building[i]->resetCoolTime();
						break;
					}
				}
			}
			if (blue_building[i]->getLife() <= 0 || blue_building[i]->getLifeTime() <= 0)
			{
				blue_building[i] = NULL;
			}
		}
	}
	//캐릭터
	for (int i = 0; i < RECTSIZE; ++i)
	{
		if (red_Char[i] != NULL)
		{
			red_Char[i]->update(nTime - pTime);

			if (red_Char[i]->getCoolTime() >= 3)
			{
				for (int j = 0; j < ARROWSIZE; ++j)
				{
					if (red_Arrow[j] == NULL)
					{
						vec2 vector = calculateVector(100);

						red_Arrow[j] = new Rect(red_Char[i]->getX(), red_Char[i]->getY(), 0, 2, 0.5, 0.2, 0.7, 1.0, vector.x, vector.y, 0, 10, 100000, OBJECT_ARROW, 1);
						red_Char[i]->resetCoolTime();
						break;
					}
				}
			}

			if (red_Char[i]->getLife() <= 0 || red_Char[i]->getLifeTime() <= 0)
			{
				red_Char[i] = NULL;
			}
		}

		if (red_Char_spwn_t >= 5 && red_Char[i] == NULL)
		{
			vec2 vector = calculateVector(300);

			red_Char[i] = new Rect(getRandomNumber(1 - WIN_HALF_WIDE, WIN_HALF_WIDE - 1), getRandomNumber(1, WIN_HALF_HIGHT - 1), 0, 50, 1, 0, 0, 1.0, vector.x, vector.y, 0, 100, 10000000, OBJECT_CHARACTER, 1);
			red_Char_spwn_t = 0;
		}

		if (blue_Char[i] != NULL)
		{
			blue_Char[i]->update(nTime - pTime);

			if (blue_Char[i]->getCoolTime() >= 3)
			{
				for (int j = 0; j < ARROWSIZE; ++j)
				{
					if (blue_Arrow[j] == NULL)
					{
						vec2 vector = calculateVector(100);

						blue_Arrow[j] = new Rect(blue_Char[i]->getX(), blue_Char[i]->getY(), 0, 2, 1, 1,  0, 1.0, vector.x, vector.y, 0, 10, 100000, OBJECT_ARROW, 1);
						blue_Char[i]->resetCoolTime();
						break;
					}
				}
			}

			if (blue_Char[i]->getLife() <= 0 || blue_Char[i]->getLifeTime() <= 0)
			{
				blue_Char[i] = NULL;
			}
		}

		if (blue_Char_spwn_flag && blue_Char[i] == NULL)
		{
			vec2 vector = calculateVector(300);

			blue_Char[i] = new Rect(blue_Char_spwn_posX, blue_Char_spwn_posY, 0, 50, 0, 0, 1, 1.0, vector.x, vector.y, 0, 100, 10000000, OBJECT_CHARACTER, 2);
			blue_Char_spwn_flag = false;
		}
	}
	// 총알
	for (int i = 0; i < BULLETSIZE; ++i)
	{
		if (red_Bullet[i] != NULL)
		{
			red_Bullet[i]->update(nTime - pTime);
			
			if (red_Bullet[i]->getCoolTime() > 0.1)
			{
				for (int i = 0; i < 1000; ++i)
				{
					if (particleArr[i] != NULL)
					{
						particleArr[i] = new Rect(red_Bullet[i]->getX(), red_Bullet[i]->getY(), 0, 10, 1, 1, 1, 1.0, 0, 0, 0, 500, 100000000, OBJECT_PARTICLE, 1);
					}
				}
			}
			if (red_Bullet[i]->getLife() <= 0 || red_Bullet[i]->getLifeTime() <= 0)
			{
				red_Bullet[i] = NULL;
			}
		}
		if (blue_Bullet[i] != NULL)
		{
			blue_Bullet[i]->update(nTime - pTime);
			if (blue_Bullet[i]->getCoolTime() < 0)
			{
				for (int i = 0; i < 1000; ++i)
				{
					if (particleArr[i] != NULL)
					{
						particleArr[i] = new Rect(blue_Bullet[i]->getX(), blue_Bullet[i]->getY(), 0, 10, 1, 1, 1, 1.0, 0, 0, 0, 500, 100000000, OBJECT_PARTICLE, 2);
					}
				}
			}
			if (blue_Bullet[i]->getLife() <= 0 || blue_Bullet[i]->getLifeTime() <= 0)
			{
				blue_Bullet[i] = NULL;
			}
		}
	}
	// 화살
	for (int i = 0; i < ARROWSIZE; ++i)
	{
		if (red_Arrow[i] != NULL)
		{
			red_Arrow[i]->update(nTime - pTime);
			if (red_Arrow[i]->getLife() <= 0 || red_Arrow[i]->getLifeTime() <= 0)
			{
				red_Arrow[i] = NULL;
			}
		}
		if (blue_Arrow[i] != NULL)
		{
			blue_Arrow[i]->update(nTime - pTime);
			if (blue_Arrow[i]->getLife() <= 0 || blue_Arrow[i]->getLifeTime() <= 0)
			{
				blue_Arrow[i] = NULL;
			}
		}
	}
    pTime = nTime;
}

void SceneMgr::RenderObject()
{
	float nTime = timeGetTime();
	count++;
	// FPS 출력
	//if (nTime - temptime > 1000)
	//{
	//	cout << count << endl;
	//	count = 0;
	//	temptime = timeGetTime();
	//}

	// 배경
	m_renderer->DrawTexturedRect(
		0,
		0,
		0,
		500,
		1,
		1,
		1,
		1,
		backGround,
		0.99
	);

	// 건물
	for (int i = 0; i < BUILDSIZE; i++)
	{
		if (red_building[i] != NULL)
		{
			string tempstr = to_string(red_building[i]->getLife());
			const char* lifeTest = tempstr.c_str();
			// Renderer
			m_renderer->DrawTexturedRect(
				red_building[i]->getX(),
				red_building[i]->getY(),
				0,
				red_building[i]->getSize(),
				red_building[i]->getRed(),
				red_building[i]->getGreen(),
				red_building[i]->getBlue(),
				red_building[i]->getAlhpa(),
				buildingTex[0],
				0.1
			);
			m_renderer->DrawText(red_building[i]->getX(), red_building[i]->getY() + red_building[i]->getSize() / 2, GLUT_BITMAP_9_BY_15, 1, 0, 0, (char*)lifeTest);
			m_renderer->DrawSolidRectGauge(
				red_building[i]->getX(),
				red_building[i]->getY() + red_building[i]->getSize() / 2 + 3,
				0,
				red_building[i]->getSize(),
				3,
				1,
				0,
				0,
				red_building[i]->getAlhpa(),
				red_building[i]->getLife() / 500.0f,
				0.1
			);
			
		}
		if (blue_building[i] != NULL)
		{
			// Renderer Test
			m_renderer->DrawTexturedRect(
				blue_building[i]->getX(),
				blue_building[i]->getY(),
				0,
				blue_building[i]->getSize(),
				blue_building[i]->getRed(),
				blue_building[i]->getGreen(),
				blue_building[i]->getBlue(),
				blue_building[i]->getAlhpa(),
				buildingTex[1],
				0.1
			);
			m_renderer->DrawSolidRectGauge(
				blue_building[i]->getX(),
				blue_building[i]->getY() + blue_building[i]->getSize() / 2 + 3,
				0,
				blue_building[i]->getSize(),
				3,
				0,
				0,
				1,
				blue_building[i]->getAlhpa(),
				blue_building[i]->getLife() / 500.0f,
				0.1
			);
			string tempstr = to_string(blue_building[i]->getLife());
			const char* lifeTest = tempstr.c_str();
			m_renderer->DrawText(blue_building[i]->getX(), blue_building[i]->getY() + blue_building[i]->getSize() / 2, GLUT_BITMAP_9_BY_15, 0, 0, 1, (char*)lifeTest);
		}
	}
	// 캐릭터
	for (int i = 0; i < RECTSIZE; i++)
	{
		if (red_Char[i] != NULL)
		{
			// Renderer Test
			m_renderer->DrawTexturedRectSeq(
				red_Char[i]->getX(),
				red_Char[i]->getY(),
				0,
				red_Char[i]->getSize(),
				red_Char[i]->getRed(),
				red_Char[i]->getGreen(),
				red_Char[i]->getBlue(),
				red_Char[i]->getAlhpa(),
				char_ani,
				red_Char[i]->getAniSqs(),
				0,
				12,
				8,
				0.2
			);
			m_renderer->DrawSolidRectGauge(
				red_Char[i]->getX(),
				red_Char[i]->getY() + red_Char[i]->getSize() / 2 + 3,
				0,
				red_Char[i]->getSize(),
				3,
				1,
				0,
				0,
				red_Char[i]->getAlhpa(),
				red_Char[i]->getLife() / 100,
				0.2
			);
		}
		if (blue_Char[i] != NULL)
		{
			// Renderer Test
			m_renderer->DrawTexturedRectSeq(
				blue_Char[i]->getX(),
				blue_Char[i]->getY(),
				0,
				blue_Char[i]->getSize(),
				blue_Char[i]->getRed(),
				blue_Char[i]->getGreen(),
				blue_Char[i]->getBlue(),
				blue_Char[i]->getAlhpa(),
				char_ani,
				blue_Char[i]->getAniSqs(),
				4,
				12,
				8,
				0.2
			);
			m_renderer->DrawSolidRectGauge(
				blue_Char[i]->getX(),
				blue_Char[i]->getY() + blue_Char[i]->getSize()/2 + 3,
				0,
				blue_Char[i]->getSize(),
				3,
				0,
				0,
				1,
				blue_Char[i]->getAlhpa(),
				blue_Char[i]->getLife() / 100,
				0.2
			);
		}
	}
	// 총알
	for (int i = 0; i < BULLETSIZE; i++)
	{
		if (red_Bullet[i] != NULL)
		{
			// Renderer Test
			m_renderer->DrawSolidRect(
				red_Bullet[i]->getX(),
				red_Bullet[i]->getY(),
				0,
				red_Bullet[i]->getSize(),
				red_Bullet[i]->getRed(),
				red_Bullet[i]->getGreen(),
				red_Bullet[i]->getBlue(),
				red_Bullet[i]->getAlhpa(),
				0.3
			);
		}
		if (blue_Bullet[i] != NULL)
		{
			// Renderer Test
			m_renderer->DrawSolidRect(
				blue_Bullet[i]->getX(),
				blue_Bullet[i]->getY(),
				0,
				blue_Bullet[i]->getSize(),
				blue_Bullet[i]->getRed(),
				blue_Bullet[i]->getGreen(),
				blue_Bullet[i]->getBlue(),
				blue_Bullet[i]->getAlhpa(),
				0.3
			);
		}
	}
	// 화살
	for (int i = 0; i < ARROWSIZE; i++)
	{
		if (red_Arrow[i] != NULL)
		{
			// Renderer Test
			m_renderer->DrawSolidRect(
				red_Arrow[i]->getX(),
				red_Arrow[i]->getY(),
				0,
				red_Arrow[i]->getSize(),
				red_Arrow[i]->getRed(),
				red_Arrow[i]->getGreen(),
				red_Arrow[i]->getBlue(),
				red_Arrow[i]->getAlhpa(),
				0.3
			);
		}
		if (blue_Arrow[i] != NULL)
		{
			// Renderer Test
			m_renderer->DrawSolidRect(
				blue_Arrow[i]->getX(),
				blue_Arrow[i]->getY(),
				0,
				blue_Arrow[i]->getSize(),
				blue_Arrow[i]->getRed(),
				blue_Arrow[i]->getGreen(),
				blue_Arrow[i]->getBlue(),
				blue_Arrow[i]->getAlhpa(),
				0.3
			);
		}
	}
	// 파티클
	for (int i = 0; i < BULLETSIZE; ++i)	// 파티클
	{
		if (red_Bullet[i] != NULL)
		{
			vec2 tempVec2 = calculatePacticleVector(red_Bullet[i]->getVectorX(), red_Bullet[i]->getVectorY());
			m_renderer->DrawParticle(
				red_Bullet[i]->getX(),
				red_Bullet[i]->getY(),
				red_Bullet[i]->getZ(),
				20,
				1,
				1,
				1,
				1,
				tempVec2.x,
				tempVec2.y,
				partice_tex,
				red_Bullet[i]->getCountTime(),
				0.8);
		}
		if (blue_Bullet[i] != NULL)
		{
			vec2 tempVec2 = calculatePacticleVector(blue_Bullet[i]->getVectorX(), blue_Bullet[i]->getVectorY());
			m_renderer->DrawParticle(
				blue_Bullet[i]->getX(),
				blue_Bullet[i]->getY(),
				blue_Bullet[i]->getZ(),
				20,
				1,
				1,
				1,
				1,
				tempVec2.x,
				tempVec2.y,
				partice_tex,
				blue_Bullet[i]->getCountTime(),
				0.8);
		}
	}

	m_renderer->DrawParticleClimate(0, 0, 0, 1, 1, 1, 1, 1, -0.1, -0.1, partice_tex, climateTime, 0.8);
}

void SceneMgr::Click(float x, float y)
{
	float inputX = x - WIN_HALF_WIDE;
	float inputY = WIN_HALF_HIGHT - y;
	if (blue_Char_spwn_t >= 7 && inputY <= 0)
	{
		blue_Char_spwn_posX = inputX;
		blue_Char_spwn_posY = inputY;
		blue_Char_spwn_t = 0;
		blue_Char_spwn_flag = true;
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
		a.setLife(b.getLife());
		b.setLife(b.getLife());
		cout << a.getType() << " - " << b.getType() << endl;
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

vec2 SceneMgr::calculateVector(float speed)
{
	vec2 vector;

	vector.x = getRandomfloat(-10.0f, 10.0f);
	vector.y = getRandomfloat(-10.0f, 10.0f);

	float vectorSpeed = speed / sqrt(vector.x * vector.x + vector.y * vector.y);	// 속도 / 벡터 크기(노멀라이즈 * 속도)

	vector.x *= vectorSpeed;
	vector.y *= vectorSpeed;

	return vector;
}

vec2 SceneMgr::calculatePacticleVector(float x,float y)
{
	vec2 vector;

	vector.x = -x;
	vector.y = -y;

	float vectorSpeed = 1 / sqrt(vector.x * vector.x + vector.y * vector.y);	// 속도 / 벡터 크기(노멀라이즈 * 속도)

	vector.x *= vectorSpeed;
	vector.y *= vectorSpeed;

	return vector;
}