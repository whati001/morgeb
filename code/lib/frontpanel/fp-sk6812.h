#ifndef FP_SK6812_H
#define FP_SK6812_H

#include <Arduino.h>
#include "fp.h"

/*
 * Struct to describe which color the frontpanel should light up
 */
struct fp_color_
{
    uint8_t g;
    uint8_t r;
    uint8_t b;
    uint8_t w;
};

/*
 * Default color for on state
 */
#define FP_DEF_ON_COLOR \
    {                   \
        0, 0, 0, 10     \
    }

/*
 * Default color for off state
 */
#define FP_DEF_OFF_COLOR \
    {                    \
        0, 0, 0, 0       \
    }

class SK6812FrontPanel_ : public FrontPanel_
{
private:
    fp_color_ on_color_;
    fp_color_ off_color_;

public:
    SK6812FrontPanel_(fp_dimension_ dimension, fp_layout_ layout);
    SK6812FrontPanel_(fp_dimension_ dimension, fp_layout_ layout, uint8_t leds_per_char);
    SK6812FrontPanel_(fp_dimension_ dimension, fp_layout_ layout, uint8_t leds_per_char, fp_color_ color);

    void update_color(fp_color_ color);
    uint8_t sync_row(uint8_t row);
    uint8_t sync_all();

    void draw_pre_it();
    void draw_pre_is();

    void draw_min_five();
    void draw_min_ten();
    void draw_min_quarter();
    void draw_min_twenty();
    void draw_min_twentyfive();
    void draw_min_half();

    void draw_type_past();
    void draw_type_to();

    void draw_hour_one();
    void draw_hour_two();
    void draw_hour_three();
    void draw_hour_four();
    void draw_hour_five();
    void draw_hour_six();
    void draw_hour_seven();
    void draw_hour_eight();
    void draw_hour_nine();
    void draw_hour_ten();
    void draw_hour_eleven();
    void draw_hour_twelve();

    void draw_full_oclock();

    void show();
    void clear();

    static void print_color(fp_color_ color)
    {
        Serial.print("Color {g: ");
        Serial.print(color.g);
        Serial.print(", r: ");
        Serial.print(color.r);
        Serial.print(", b: ");
        Serial.print(color.b);
        Serial.print(", w: ");
        Serial.print(color.w);
        Serial.println("}");
    }
};

#endif