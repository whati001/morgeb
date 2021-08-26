#include "neopixelfrontpanel.h"
#include <Adafruit_NeoPixel.h>

uint64_t NeoPixelFrontPanel_::getPixelCount() const
{
    uint64_t pixelCount = 0;
    neopixel_fpanel_word_ *curWord = (neopixel_fpanel_word_ *)&layout_;
    for (uint8_t idx = 0; idx < neopixel_fpanel_layout_len_; idx++)
    {

        pixelCount += (curWord + idx)->len;
    }
    return pixelCount;
}

NeoPixelFrontPanel_::NeoPixelFrontPanel_(neopixel_fpanel_layout_ layout, uint16_t pin, uint32_t color, uint8_t pixelPerChar)
    : FrontPanel_(), pin_(pin), color_(color), pixelPerChar_(pixelPerChar), layout_(layout){};

void NeoPixelFrontPanel_::init()
{
    uint64_t pixelCount = getPixelCount();
    pixels_ = Adafruit_NeoPixel(pixelCount, pin_, NEO_GRB + NEO_KHZ800);
    pixels_.begin();
    pixels_.show();
}

void NeoPixelFrontPanel_::testMe()
{
    pixels_.clear();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawPreIt();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawPreIs();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawMinFive();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawMinTen();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawMinQuarter();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawMeTwenty();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawMinTwentyFive();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawMinHalf();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawTypePast();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawTypeTo();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawHourOne();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawHourTwo();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawHourThree();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawHourFour();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawHourFive();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawHourSix();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawHourSeven();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawHourEight();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawHourNine();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawHourTen();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawHourEleven();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawHourTwelve();
    pixels_.show();
    delay(1000);

    pixels_.clear();
    drawFulloclock();
    pixels_.show();
    delay(1000);
}

void NeoPixelFrontPanel_::drawWord(neopixel_fpanel_word_ word)
{
    pixels_.fill(color_, word.start, word.len);
}

void NeoPixelFrontPanel_::drawPreIt()
{
    drawWord(layout_.PRE_IT);
}

void NeoPixelFrontPanel_::drawPreIs()
{
    drawWord(layout_.PRE_IS);
}

void NeoPixelFrontPanel_::drawMinFive()
{
    drawWord(layout_.MIN_FIVE);
}
void NeoPixelFrontPanel_::drawMinTen()
{
    drawWord(layout_.MIN_TEN);
}
void NeoPixelFrontPanel_::drawMinQuarter()
{
    drawWord(layout_.MIN_QUARTER);
}
void NeoPixelFrontPanel_::drawMeTwenty()
{
    drawWord(layout_.MIN_TWENTY);
}
void NeoPixelFrontPanel_::drawMinTwentyFive()
{
    drawWord(layout_.MIN_TWENTYFIVE);
}
void NeoPixelFrontPanel_::drawMinHalf()
{
    drawWord(layout_.MIN_HALF);
}

void NeoPixelFrontPanel_::drawTypePast()
{
    drawWord(layout_.TYPE_PAST);
}
void NeoPixelFrontPanel_::drawTypeTo()
{
    drawWord(layout_.TYPE_TO);
}

void NeoPixelFrontPanel_::drawHourOne()
{
    drawWord(layout_.HOUR_ONE);
}
void NeoPixelFrontPanel_::drawHourTwo()
{
    drawWord(layout_.HOUR_TWO);
}
void NeoPixelFrontPanel_::drawHourThree()
{
    drawWord(layout_.HOUR_THREE);
}
void NeoPixelFrontPanel_::drawHourFour()
{
    drawWord(layout_.HOUR_FOUR);
}
void NeoPixelFrontPanel_::drawHourFive()
{
    drawWord(layout_.HOUR_FIVE);
}
void NeoPixelFrontPanel_::drawHourSix()
{
    drawWord(layout_.HOUR_SIX);
}
void NeoPixelFrontPanel_::drawHourSeven()
{
    drawWord(layout_.HOUR_SEVEN);
}
void NeoPixelFrontPanel_::drawHourEight()
{
    drawWord(layout_.HOUR_EIGHT);
}
void NeoPixelFrontPanel_::drawHourNine()
{
    drawWord(layout_.HOUR_NINE);
}
void NeoPixelFrontPanel_::drawHourTen()
{
    drawWord(layout_.HOUR_TEN);
}
void NeoPixelFrontPanel_::drawHourEleven()
{
    drawWord(layout_.HOUR_ELEVEN);
}
void NeoPixelFrontPanel_::drawHourTwelve()
{
    drawWord(layout_.HOUR_TWELVE);
}

void NeoPixelFrontPanel_::drawFulloclock()
{
    drawWord(layout_.FULL_OCLOCK);
}

void NeoPixelFrontPanel_::show()
{
    pixels_.show();
}

void NeoPixelFrontPanel_::clear()
{
    pixels_.clear();
}