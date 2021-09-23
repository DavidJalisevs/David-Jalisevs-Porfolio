#pragma once
#include <iostream>

using namespace std;

class Animation
{
    class State* current;
public:
    Animation();
    void setCurrent(State* s)
    {
        current = s;
    }
    void idle();
    void jumping();
    void climbing();
};