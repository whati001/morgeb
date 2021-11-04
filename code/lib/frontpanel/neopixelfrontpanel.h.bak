#ifndef NEOPIXLEFRONTPANEL_H
#define NEOPIXLEFRONTPANEL_H

#include <Adafruit_NeoPixel.h>
#include "frontpanel.h"

#define DEF_PIN 2
#define DEF_PIXEL_PER_CHAR 1

class NeoPixelFrontPanel_ : public FrontPanel_
{
private:
    uint32_t color_;
    uint16_t pin_;
    uint8_t pixelPerChar_;
    Adafruit_NeoPixel pixels_;

    uint64_t getPixelCount() const;
    void drawWord(fpanel_word_ word);

public:
    NeoPixelFrontPanel_(fpanel_layout_ layout, uint32_t color);
    NeoPixelFrontPanel_(fpanel_layout_ layout, uint32_t color, uint16_t pin);
    NeoPixelFrontPanel_(fpanel_layout_ layout, uint32_t color, uint16_t pin, uint8_t pixelPerChar);

    void init();
    void testMe();
    void update(uint8_t hour, uint8_t minute, uint8_t second);

    void drawPreIt();
    void drawPreIs();

    void drawMinFive();
    void drawMinTen();
    void drawMinQuarter();
    void drawMinTwenty();
    void drawMinTwentyFive();
    void drawMinHalf();

    void drawTypePast();
    void drawTypeTo();

    void drawHourOne();
    void drawHourTwo();
    void drawHourThree();
    void drawHourFour();
    void drawHourFive();
    void drawHourSix();
    void drawHourSeven();
    void drawHourEight();
    void drawHourNine();
    void drawHourTen();
    void drawHourEleven();
    void drawHourTwelve();

    void drawFulloclock();

    void show();
    void clear();
};

// extern NeoPixelFrontPanel_ FrontPanel;

#endif