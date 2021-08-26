#ifndef FRONT_H
#define FRONT_H

#include <stdint.h>

class FrontPanel_
{

public:
    FrontPanel_();

    virtual void init() = 0;
    virtual void testMe() = 0;

    virtual void drawPreIt() = 0;
    virtual void drawPreIs() = 0;

    virtual void drawMinFive() = 0;
    virtual void drawMinTen() = 0;
    virtual void drawMinQuarter() = 0;
    virtual void drawMeTwenty() = 0;
    virtual void drawMinTwentyFive() = 0;
    virtual void drawMinHalf() = 0;

    virtual void drawTypePast() = 0;
    virtual void drawTypeTo() = 0;

    virtual void drawHourOne() = 0;
    virtual void drawHourTwo() = 0;
    virtual void drawHourThree() = 0;
    virtual void drawHourFour() = 0;
    virtual void drawHourFive() = 0;
    virtual void drawHourSix() = 0;
    virtual void drawHourSeven() = 0;
    virtual void drawHourEight() = 0;
    virtual void drawHourNine() = 0;
    virtual void drawHourTen() = 0;
    virtual void drawHourEleven() = 0;
    virtual void drawHourTwelve() = 0;

    virtual void drawFulloclock() = 0;
};

#endif