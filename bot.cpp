#include "bot.h"

#include <future>
#include <chrono>
#include <qglobal.h>
#include <thread>
#include <random>

using namespace std;

static random_device rd;
static mt19937 gen(rd());
static uniform_int_distribution<> dis(1, 1000);
static uniform_int_distribution<> dis2(2, 4);
static uniform_int_distribution<> dis3(0, 3);
static uniform_int_distribution<> dis4(2, 8);

Bot::Bot()
{
    m_isPlayer = false;
//    m_isFreezed = true;
    connect(this, SIGNAL(nextStep()), SLOT(moveProcess()));
    std::thread tr(&Bot::navigator, this);
    tr.detach();
}

Bot::~Bot()
{

}



void Bot::moveProcess()
{
//    concreteStep(step_down);
//    fire();
//    concreteStep(step_right);
//    fire();
//    freeze();


    if (m_isFreezed)
    {
        return;
    }

    static int counter = dis4(gen);
    static int step = 0;

    concreteStep(m_nextStep);

    step++;
    if (step == counter)
    {
        fire();
        step = 0;
//        freeze();
    }
}

void Bot::navigator()
{
    static int milisec = 0;

    this_thread::sleep_for(chrono::milliseconds(milisec));

    milisec += 10;

    int counter = dis2(gen);
    while (true)
    {
        if (counter == 0)
        {
            m_nextStep = static_cast<Step>(dis3(gen));
            counter = dis2(gen);
        }
        counter--;

        emit nextStep();
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}
