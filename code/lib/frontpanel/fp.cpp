#include <Arduino.h>
#include "fp.h"
#include "stdlib.h"

FrontPanel_::FrontPanel_(fp_dimension_ dimension, fp_layout_ layout) : FrontPanel_(dimension, layout, FPANEL_DEF_PIXEL_PER_CHAR){};
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
    for (uint8_t idx = 0; idx < FPANEL_LAYOUT_WORD_COUNT_; idx++)
    {
        fp_word_ *word = ((fp_word_ *)&layout_) + idx;
        uint8_t row_idx = word->start / dimension_.width;
        layout_rows_pin_map_[row_idx] = word->pin;
        // #TODO: add some check if the pin value is greather than available digital pins of board
    }

    return 1;
}