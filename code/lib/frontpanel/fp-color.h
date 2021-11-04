#ifndef FP_COLOR_H
#define FP_COLOR_H

#include "fp.h"

/*
 * Struct to describe which color the frontpanel should light up
 * In case, we use simple leds, this 
 */
struct fp_color_
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t white;
};
#define FP_DEF_COLOR \
    {                \
        0, 0, 0, 0   \
    }

class ColorFrontpanel_ : public FrontPanel_
{
private:
    fp_color_ color_;

public:
    ColorFrontpanel_(fp_layout_ layout);
    ColorFrontpanel_(fp_layout_ layout, fp_color_ color);
};

#endif