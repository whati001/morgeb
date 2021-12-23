
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