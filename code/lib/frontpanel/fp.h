#ifndef FP_H
#define FP_H

#include <stdint.h>

/*
 * Struct to describe each word from the front panel
 * each word on the front panel is defined via:
 *   - start index
 *   - len of the word, due to it consists of consecutive characters
 */
struct fp_word_
{
    uint8_t start;
    uint8_t len;
};

/*
 * Struct to describe all the words from your front panel
 * each word is encoded via the struct fp_word_
 */
#define fpanel_layout_len_ 23
struct fp_layout_
{
    fp_word_ PRE_IT;
    fp_word_ PRE_IS;

    fp_word_ MIN_FIVE;
    fp_word_ MIN_TEN;
    fp_word_ MIN_QUARTER;
    fp_word_ MIN_TWENTY;
    fp_word_ MIN_TWENTYFIVE;
    fp_word_ MIN_HALF;

    fp_word_ TYPE_PAST;
    fp_word_ TYPE_TO;

    fp_word_ HOUR_ONE;
    fp_word_ HOUR_TWO;
    fp_word_ HOUR_THREE;
    fp_word_ HOUR_FOUR;
    fp_word_ HOUR_FIVE;
    fp_word_ HOUR_SIX;
    fp_word_ HOUR_SEVEN;
    fp_word_ HOUR_EIGHT;
    fp_word_ HOUR_NINE;
    fp_word_ HOUR_TEN;
    fp_word_ HOUR_ELEVEN;
    fp_word_ HOUR_TWELVE;

    fp_word_ FULL_OCLOCK;
};

class FrontPanel_
{
protected:
    fp_layout_ layout_;

public:
    FrontPanel_();
    FrontPanel_(fp_layout_ layout);

    // virtual void init() = 0;
    // virtual void testMe() = 0;
    // virtual void update(uint8_t hour, uint8_t minute, uint8_t second) = 0;

    // virtual void drawPreIt() = 0;
    // virtual void drawPreIs() = 0;

    // virtual void drawMinFive() = 0;
    // virtual void drawMinTen() = 0;
    // virtual void drawMinQuarter() = 0;
    // virtual void drawMinTwenty() = 0;
    // virtual void drawMinTwentyFive() = 0;
    // virtual void drawMinHalf() = 0;

    // virtual void drawTypePast() = 0;
    // virtual void drawTypeTo() = 0;

    // virtual void drawHourOne() = 0;
    // virtual void drawHourTwo() = 0;
    // virtual void drawHourThree() = 0;
    // virtual void drawHourFour() = 0;
    // virtual void drawHourFive() = 0;
    // virtual void drawHourSix() = 0;
    // virtual void drawHourSeven() = 0;
    // virtual void drawHourEight() = 0;
    // virtual void drawHourNine() = 0;
    // virtual void drawHourTen() = 0;
    // virtual void drawHourEleven() = 0;
    // virtual void drawHourTwelve() = 0;

    // virtual void drawFulloclock() = 0;
};

#endif