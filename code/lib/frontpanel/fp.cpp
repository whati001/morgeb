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