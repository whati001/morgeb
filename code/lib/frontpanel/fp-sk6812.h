#ifndef FP_SK6812_H
#define FP_SK6812_H

#include <Arduino.h>
#include "fp.h"

/*
 * Struct to describe which color the frontpanel should light up
 */
struct fp_color_
{
    uint8_t g;
    uint8_t r;
    uint8_t b;
    uint8_t w;
};

/*
 * Default color for on state
 */
#define FP_DEF_ON_COLOR \
    {                   \
        0, 0, 0, 10     \
    }

/*
 * Default color for off state
 */
#define FP_DEF_OFF_COLOR \
    {                    \
        0, 0, 0, 0       \
    }

class SK6812FrontPanel_ : public FrontPanel_
{
private:
    fp_color_ on_color_;
    fp_color_ off_color_;

public:
    SK6812FrontPanel_(fp_dimension_ dimension, fp_layout_ layout);
    SK6812FrontPanel_(fp_dimension_ dimension, fp_layout_ layout, uint8_t leds_per_char);
    SK6812FrontPanel_(fp_dimension_ dimension, fp_layout_ layout, uint8_t leds_per_char, fp_color_ color);

    uint8_t sync_row_data(uint8_t row);

    // void testMe();
    // void update(uint8_t hour, uint8_t minute, uint8_t second);

    // void drawPreIt();
    // void drawPreIs();

    // void drawMinFive();
    // void drawMinTen();
    // void drawMinQuarter();
    // void drawMinTwenty();
    // void drawMinTwentyFive();
    // void drawMinHalf();

    // void drawTypePast();
    // void drawTypeTo();

    // void drawHourOne();
    // void drawHourTwo();
    // void drawHourThree();
    // void drawHourFour();
    // void drawHourFive();
    // void drawHourSix();
    // void drawHourSeven();
    // void drawHourEight();
    // void drawHourNine();
    // void drawHourTen();
    // void drawHourEleven();
    // void drawHourTwelve();

    // void drawFulloclock();

    // void show();
    // void clear();
};

#endif