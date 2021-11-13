
#include "fp-sk6812.h"

SK6812FrontPanel_::SK6812FrontPanel_(fp_dimension_ dimension, fp_layout_ layout) : SK6812FrontPanel_(dimension, layout, FP_DEF_LEDS_PER_CHAR){};
SK6812FrontPanel_::SK6812FrontPanel_(fp_dimension_ dimension, fp_layout_ layout, uint8_t leds_per_char) : SK6812FrontPanel_(dimension, layout, leds_per_char, FP_DEF_ON_COLOR){};
SK6812FrontPanel_::SK6812FrontPanel_(fp_dimension_ dimension, fp_layout_ layout, uint8_t leds_per_char, fp_color_ color) : FrontPanel_(dimension, layout, leds_per_char), on_color_(color), off_color_(FP_DEF_OFF_COLOR){};

void SK6812FrontPanel_::draw_pre_it()
{
    draw_word(&layout_.PRE_IT);
}

void SK6812FrontPanel_::draw_pre_is()
{
    draw_word(&layout_.PRE_IS);
}

void SK6812FrontPanel_::draw_min_five()
{
    draw_word(&layout_.MIN_FIVE);
}
void SK6812FrontPanel_::draw_min_ten()
{
    draw_word(&layout_.MIN_TEN);
}
void SK6812FrontPanel_::draw_min_quarter()
{
    draw_word(&layout_.MIN_QUARTER);
}
void SK6812FrontPanel_::draw_min_twenty()
{
    draw_word(&layout_.MIN_TWENTY);
}
void SK6812FrontPanel_::draw_min_twentyfive()
{
    draw_word(&layout_.MIN_TWENTYFIVE);
}
void SK6812FrontPanel_::draw_min_half()
{
    draw_word(&layout_.MIN_HALF);
}

void SK6812FrontPanel_::draw_type_past()
{
    draw_word(&layout_.TYPE_PAST);
}
void SK6812FrontPanel_::draw_type_to()
{
    draw_word(&layout_.TYPE_TO);
}

void SK6812FrontPanel_::draw_hour_one()
{
    draw_word(&layout_.HOUR_ONE);
}
void SK6812FrontPanel_::draw_hour_two()
{
    draw_word(&layout_.HOUR_TWO);
}
void SK6812FrontPanel_::draw_hour_three()
{
    draw_word(&layout_.HOUR_THREE);
}
void SK6812FrontPanel_::draw_hour_four()
{
    draw_word(&layout_.HOUR_FOUR);
}
void SK6812FrontPanel_::draw_hour_five()
{
    draw_word(&layout_.HOUR_FIVE);
}
void SK6812FrontPanel_::draw_hour_six()
{
    draw_word(&layout_.HOUR_SIX);
}
void SK6812FrontPanel_::draw_hour_seven()
{
    draw_word(&layout_.HOUR_SEVEN);
}
void SK6812FrontPanel_::draw_hour_eight()
{
    draw_word(&layout_.HOUR_EIGHT);
}
void SK6812FrontPanel_::draw_hour_nine()
{
    draw_word(&layout_.HOUR_NINE);
}
void SK6812FrontPanel_::draw_hour_ten()
{
    draw_word(&layout_.HOUR_TEN);
}
void SK6812FrontPanel_::draw_hour_eleven()
{
    draw_word(&layout_.HOUR_ELEVEN);
}
void SK6812FrontPanel_::draw_hour_twelve()
{
    draw_word(&layout_.HOUR_TWELVE);
}

void SK6812FrontPanel_::draw_full_oclock()
{
    draw_word(&layout_.FULL_OCLOCK);
}

uint8_t SK6812FrontPanel_::sync_all()
{
    for (uint8_t idx = 0; idx < dimension_.height; idx++)
    {
        if (sync_row(idx) == 0)
        {
            return 0;
        }
    }

    return 1;
}

void SK6812FrontPanel_::update(uint8_t hour, uint8_t minute, uint8_t second)
{
    Serial.print("Update time to:");
    Serial.print(hour);
    Serial.print(":");
    Serial.print(minute);
    Serial.print(".");
    Serial.println(second);

    clear_all();

    draw_pre_it();
    draw_pre_is();

    switch (minute)
    {
    case 5:
    case 55:
        draw_min_five();
        break;
    case 10:
    case 50:
        draw_min_ten();
        break;
    case 15:
    case 45:
        draw_min_quarter();
        break;
    case 20:
    case 40:
        draw_min_twenty();
        break;
    case 25:
    case 35:
        draw_min_twentyfive();
        break;
    case 30:
        draw_min_half();
        break;
    case 0:
        draw_full_oclock();
        break;
    default:
        break;
    }

    if (minute > 30)
    {
        draw_type_to();
    }
    else
    {
        draw_type_past();
    }

    switch (hour)
    {
    case 1:
    case 13:
        draw_hour_one();
        break;
    case 2:
    case 14:
        draw_hour_two();
        break;
    case 3:
    case 15:
        draw_hour_three();
        break;
    case 4:
    case 16:
        draw_hour_four();
        break;
    case 5:
    case 17:
        draw_hour_five();
        break;
    case 6:
    case 18:
        draw_hour_six();
        break;
    case 7:
    case 19:
        draw_hour_seven();
        break;
    case 8:
    case 20:
        draw_hour_eight();
        break;
    case 9:
    case 21:
        draw_hour_nine();
        break;
    case 10:
    case 22:
        draw_hour_ten();
        break;
    case 11:
    case 23:
        draw_hour_eleven();
        break;
    case 12:
    case 24:
        draw_hour_twelve();
        break;
    default:
        break;
    }
    sync_all();

    return;
}