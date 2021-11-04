#include "fp.h"
#include "fp-sk6812.h"

SK6812FrontPanel_::SK6812FrontPanel_(fp_layout_ layout) : ColorFrontpanel_(layout, FP_DEF_COLOR){};

SK6812FrontPanel_::SK6812FrontPanel_(fp_layout_ layout, fp_color_ color) : SK6812FrontPanel_(layout, color, (uint8_t *)FP_DEF_PIN_ORDER, FP_DEF_PIXEL_PER_CHAR){};

SK6812FrontPanel_::SK6812FrontPanel_(fp_layout_ layout, fp_color_ color, uint8_t pin_order[])
    : SK6812FrontPanel_(layout, color, pin_order, FP_DEF_PIXEL_PER_CHAR){};

SK6812FrontPanel_::SK6812FrontPanel_(fp_layout_ layout, fp_color_ color, uint8_t pin_order[], uint8_t pixels_per_char)
    : ColorFrontpanel_(layout, color), pixels_per_char_(pixels_per_char)
{
    for (uint8_t idx = 0; idx < FP_PIN_ORDER_LEN; idx++)
    {
        pin_order_[idx] = pin_order[idx];
    }
};