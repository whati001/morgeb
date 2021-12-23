#include <Arduino.h>
#include "fp.h"
#include "stdlib.h"

FrontPanel_::FrontPanel_(fp_dimension_ dimension, fp_layout_ layout) : FrontPanel_(dimension, layout, FP_DEF_LEDS_PER_CHAR){};
FrontPanel_::FrontPanel_(fp_dimension_ dimension, fp_layout_ layout, uint8_t leds_per_char) : dimension_(dimension), layout_(layout), leds_per_char_(leds_per_char)
{
    layout_rows_ = (uint8_t **)malloc(sizeof(uint8_t *) * dimension_.height);
    // #TODO: check if memory is NULL

    for (uint8_t idx = 0; idx < dimension_.height; idx++)
    {
        uint8_t *row = (uint8_t *)calloc(dimension_.width, sizeof(uint8_t));
        // #TODO: check if memory is NULL
        layout_rows_[idx] = row;
    }

    layout_rows_pin_map_ = (uint8_t *)calloc(dimension_.height, sizeof(uint8_t));
};

FrontPanel_::~FrontPanel_()
{
    for (uint8_t idx = 0; idx < dimension_.height; idx++)
    {
        free(layout_rows_[idx]);
    }
    free(layout_rows_);
    free(layout_rows_pin_map_);
}

uint8_t FrontPanel_::init()
{
    for (uint8_t idx = 0; idx < FP_LAYOUT_WORD_COUNT; idx++)
    {
        fp_word_ *word = ((fp_word_ *)&layout_) + idx;
        uint8_t row_idx = word->start / dimension_.width;
        layout_rows_pin_map_[row_idx] = word->pin;
        // #TODO: add some check if the pin value is greather than available digital pins of board
    }

    return 1;
}

uint8_t FrontPanel_::clear_row(uint8_t row)
{
    if (row > dimension_.height)
    {
        return 0;
    }
    memset(layout_rows_[row], 0, sizeof(uint8_t) * dimension_.width);
    return 1;
}

uint8_t FrontPanel_::clear_all()
{
    for (uint8_t idx = 0; idx < dimension_.height; idx++)
    {
        if (clear_row(idx) == 0)
        {
            return 0;
        }
    }
    return 1;
}

uint8_t FrontPanel_::draw_word(fp_word_ *word)
{
    uint8_t row_idx = word->start / dimension_.width;
    uint8_t row_start = word->start - (row_idx * dimension_.width);

    if (row_idx > dimension_.height)
    {
        return 0;
    }
    if (row_start + word->len > dimension_.width)
    {
        return 0;
    }

    memset(&layout_rows_[row_idx][row_start], 1, sizeof(uint8_t) * word->len);
    return 1;
}

void FrontPanel_::test_me()
{
    clear_all();
    sync_all();
    delay(1000);

    for (uint8_t idx = 0; idx < FP_LAYOUT_WORD_COUNT; idx++)
    {
        fp_word_ *word = ((fp_word_ *)&layout_) + idx;
        clear_all();
        draw_word(word);
        sync_all();
        delay(1000);
    }
}

void FrontPanel_::update(uint8_t hour, uint8_t minute, uint8_t second)
{
    Serial.print("Update time to:");
    Serial.print(hour);
    Serial.print(":");
    Serial.print(minute);
    Serial.print(".");
    Serial.println(second);

    clear_all();

    // draw IT IS
    draw_pre_it();
    draw_pre_is();

    // check if we are past
    uint8_t is_past = (minute > 30) ? 0 : 1;

    // draw minutes
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

    if (is_past)
    {
        draw_type_to();
        // next hour needs to get displayed
        hour = (hour++ % 24);
    }
    else
    {
        draw_type_past();
        // hour will be fine
    }

    // draw hour
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