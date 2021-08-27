#ifndef FRONT_H
#define FRONT_H

#include <stdint.h>

/*
 * Struct to describe each word from the front panel
 * each word on the front panel is defined via:
 *   - start index
 *   - len of the word, due to it consists of consecutive characters
 */
struct fpanel_word_
{
    uint8_t start;
    uint8_t len;
};

/*
 * Struct to describe all the words from your front panel
 * each word is encoded via the struct fpanel_word_
 */
#define fpanel_layout_len_ 23
struct fpanel_layout_
{
    fpanel_word_ PRE_IT;
    fpanel_word_ PRE_IS;

    fpanel_word_ MIN_FIVE;
    fpanel_word_ MIN_TEN;
    fpanel_word_ MIN_QUARTER;
    fpanel_word_ MIN_TWENTY;
    fpanel_word_ MIN_TWENTYFIVE;
    fpanel_word_ MIN_HALF;

    fpanel_word_ TYPE_PAST;
    fpanel_word_ TYPE_TO;

    fpanel_word_ HOUR_ONE;
    fpanel_word_ HOUR_TWO;
    fpanel_word_ HOUR_THREE;
    fpanel_word_ HOUR_FOUR;
    fpanel_word_ HOUR_FIVE;
    fpanel_word_ HOUR_SIX;
    fpanel_word_ HOUR_SEVEN;
    fpanel_word_ HOUR_EIGHT;
    fpanel_word_ HOUR_NINE;
    fpanel_word_ HOUR_TEN;
    fpanel_word_ HOUR_ELEVEN;
    fpanel_word_ HOUR_TWELVE;

    fpanel_word_ FULL_OCLOCK;
};

class FrontPanel_
{
protected:
    fpanel_layout_ layout_;

public:
    FrontPanel_();
    FrontPanel_(fpanel_layout_ layout);

    virtual void init() = 0;
    virtual void testMe() = 0;
    virtual void update(uint8_t hour, uint8_t minute, uint8_t second) = 0;

    virtual void drawPreIt() = 0;
    virtual void drawPreIs() = 0;

    virtual void drawMinFive() = 0;
    virtual void drawMinTen() = 0;
    virtual void drawMinQuarter() = 0;
    virtual void drawMinTwenty() = 0;
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