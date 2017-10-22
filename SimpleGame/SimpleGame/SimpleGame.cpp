/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include <random>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "SceneMgr.h"
#include "Renderer.h"

#define RectSize 96

using namespace std;


Renderer *g_Renderer = NULL;

SceneMgr scenemgr;

// 내 함수
void renderFunc();
void update();
bool leftMouseButtonDown(int button, int state);
bool leftMouseButtonUp(int button, int state);
bool isClick(float x, float y);
void click(float x, float y);
void drag(float x, float y);
int getRandomNumber(int min, int max);
float getRandomfloat(float min, float max);

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
    //g_Renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);

    scenemgr.Update();
    renderFunc();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
    static float downPos[2];    //0은 x, 1은 y
    static bool clickBool = false;;
    if (leftMouseButtonDown(button, state))
    {
        downPos[0] = x;
        downPos[1] = y;
        clickBool = true;
    }
    else if (leftMouseButtonUp(button, state))    //(button == GLUT_LEFT_BUTTON && state == GLUT_UP
    {
        if (isClick(downPos[0] - x, downPos[1] - y))    //((-1 < x && x < 1) && (-1 < y && y < 1))
        {
            click(downPos[0], downPos[1]);
        }
        else
        {
            drag(x, y);
        }
        clickBool = false;
    }
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

void renderFunc()
{
    for (int i = 0; i < 100; ++i)
    {
        g_Renderer->DrawSolidRect(scenemgr.RenderObject(i));
    }
}

bool leftMouseButtonDown(int button, int state)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        return true;
    }
    return false;
}

bool leftMouseButtonUp(int button, int state)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        return true;
    }
    return false;
}

bool isClick(float x, float y)
{
    if ((-1 < x && x < 1) && (-1 < y && y < 1))
    {
        return true;
    }
    return false;
}

void click(float x, float y)
{
    cout << "click" << endl;
    //scenemgr.Click(x, y);
}

void drag(float x, float y)
{
    cout << "drag" << endl;
    //scenemgr.Click(x, y);
}

int getRandomNumber(int min, int max)
{
    //< 1단계. 시드 설정
    random_device rn;
    default_random_engine rnd(rn());

    //< 2단계. 분포 설정 ( 정수 )
    uniform_int_distribution<int> range(min, max);

    //< 3단계. 값 추출
    return range(rnd);
}

float getRandomfloat(float min, float max)
{
    //< 1단계. 시드 설정
    random_device rn;
    default_random_engine rnd(rn());

    //< 2단계. 분포 설정 ( 정수 )
    uniform_real_distribution<float> range(min, max);

    //< 3단계. 값 추출
    return range(rnd);
}
