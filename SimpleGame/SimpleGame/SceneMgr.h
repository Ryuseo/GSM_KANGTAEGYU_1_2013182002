#pragma once
class SceneMgr
{
private:
    int     argc;
    char    **argv;
    Rect*   rect;
    int     rectNum = 0;

    void    insertRect(float x, float y);
    int     getRandomNumber(int min, int max);
    float   getRandomfloat(float min, float max);

public:
    SceneMgr(int argc, char **argv);
    ~SceneMgr();
    void    Update();
    Rect    RenderObject(int i);
    void    Click(float x, float y);
};

