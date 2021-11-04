#ifndef FP_SK6812_H
#define FP_SK6812_H

#include "fp-color.h"

#define FP_PIN_ORDER_LEN 10
const uint8_t FP_DEF_PIN_ORDER[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
#define FP_DEF_PIXEL_PER_CHAR 1

class SK6812FrontPanel_ : public ColorFrontpanel_
{
private:
    uint8_t pin_order_[10];
    uint8_t pixels_per_char_;

    uint64_t getPixelCount() const;
    void drawWord(fp_word_ word);

public:
    SK6812FrontPanel_(fp_layout_ layout);
    SK6812FrontPanel_(fp_layout_ layout, fp_color_ color);
    SK6812FrontPanel_(fp_layout_ layout, fp_color_ color, uint8_t pin_order[]);
    SK6812FrontPanel_(fp_layout_ layout, fp_color_ color, uint8_t pin_order[], uint8_t pixels_per_char);

    // void init();
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