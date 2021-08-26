#ifndef NEOPIXLEFRONTPANEL_H
#define NEOPIXLEFRONTPANEL_H

#include <Adafruit_NeoPixel.h>
#include "frontpanel.h"

/*
 * Struct to describe each word from the front panel
 * each word on the front panel is defined via:
 *   - start index
 *   - len of the word, due to it consists of consecutive characters
 */
struct neopixel_fpanel_word_
{
    uint8_t start;
    uint8_t len;
};

/*
 * Struct to describe all the words from your front panel
 * each word is encoded via the struct neopixel_fpanel_word_
 */
#define neopixel_fpanel_layout_len_ 23
struct neopixel_fpanel_layout_
{
    neopixel_fpanel_word_ PRE_IT;
    neopixel_fpanel_word_ PRE_IS;

    neopixel_fpanel_word_ MIN_FIVE;
    neopixel_fpanel_word_ MIN_TEN;
    neopixel_fpanel_word_ MIN_QUARTER;
    neopixel_fpanel_word_ MIN_TWENTY;
    neopixel_fpanel_word_ MIN_TWENTYFIVE;
    neopixel_fpanel_word_ MIN_HALF;

    neopixel_fpanel_word_ TYPE_PAST;
    neopixel_fpanel_word_ TYPE_TO;

    neopixel_fpanel_word_ HOUR_ONE;
    neopixel_fpanel_word_ HOUR_TWO;
    neopixel_fpanel_word_ HOUR_THREE;
    neopixel_fpanel_word_ HOUR_FOUR;
    neopixel_fpanel_word_ HOUR_FIVE;
    neopixel_fpanel_word_ HOUR_SIX;
    neopixel_fpanel_word_ HOUR_SEVEN;
    neopixel_fpanel_word_ HOUR_EIGHT;
    neopixel_fpanel_word_ HOUR_NINE;
    neopixel_fpanel_word_ HOUR_TEN;
    neopixel_fpanel_word_ HOUR_ELEVEN;
    neopixel_fpanel_word_ HOUR_TWELVE;

    neopixel_fpanel_word_ FULL_OCLOCK;
};
class NeoPixelFrontPanel_ : public FrontPanel_
{
private:
    uint16_t pin_;
    uint32_t color_;
    uint8_t pixelPerChar_;
    neopixel_fpanel_layout_ layout_;
    Adafruit_NeoPixel pixels_;

    uint64_t getPixelCount() const;
    void drawWord(neopixel_fpanel_word_ word);

public:
    NeoPixelFrontPanel_(neopixel_fpanel_layout_ layout, uint16_t pin, uint32_t color_, uint8_t pixelPerChar);

    void init();
    void testMe();

    void drawPreIt();
    void drawPreIs();

    void drawMinFive();
    void drawMinTen();
    void drawMinQuarter();
    void drawMeTwenty();
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

extern NeoPixelFrontPanel_ FrontPanel;

#endif