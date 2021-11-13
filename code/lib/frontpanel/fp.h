#ifndef FP_H
#define FP_H

#include <stdint.h>

/*
 * Struct to describe each word from the front panel
 * each word on the front panel is defined via:
 *   - start index
 *   - len of the word, due to it consists of consecutive characters
 *   - pin index -> will be mapped to pin_ordering_ array
 */
struct fp_word_
{
    uint8_t start;
    uint8_t len;
    uint8_t pin;
};

/*
 * Struct to describe all the words from your front panel
 * each word is encoded via the struct fp_word_
 */
#define FP_LAYOUT_WORD_COUNT 23

/*
 * Default amount of pixels per character
 */
#define FP_DEF_LEDS_PER_CHAR 1

/*
 * The Frontpanel is more or less a matrix of leds
 * The aim of this struct is to evaluate how many
 * characters are in a single row
 */
struct fp_dimension_
{
    uint8_t height;
    uint8_t width;
};

/*
 * This struct defines where the words are to light up
 * In addition, the pin already identifies how many characters
 * are connected into a single strip
 */
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

/*
 * This class will handle all the lightning.
 * To simplify everything, we do not work here with 
 * leds counts, instead with character counts.
 * 
 * To guaranty nice consistent lightning, multiple leds per char
 * can be used. The amount of leds is defined via the member variable
 * leds_per_char_, which can be set via ctor or setter.
 * 
 * The class will hold an uint_8 array with 1 and 0, which represent
 * on and off respectively.
 * 
 * In addition, this lib assumes, that each character is equipped 
 * with leds, otherwise the computation will not work out
 *
 * #TODO: add support for skipping unused characters
 */
class FrontPanel_
{
public:
    /*
     * Iterate over the fp_layout_ and prepare the
     * uint_8 array holding the on and off values grouped by
     * the pin number
     * 
     * This function will set following member values properly
     *  * layout_rows_
     *  * layout_rows_pin_map_
     * 
     */
    uint8_t init();

protected:
    /*
     * Holds the dimension of the frontpanel
     */
    fp_dimension_ dimension_;
    /*
     * Holds the layout of the frontpanel
     */
    fp_layout_ layout_;
    /*
     * Holds the amount of leds per char
     */
    uint8_t leds_per_char_;
    /*
     * Holds the on/off values for each row
     * It's an two dimensional array
     */
    uint8_t **layout_rows_;
    /*
     * Array holding the pin number for each row
     */
    uint8_t *layout_rows_pin_map_;

public:
    FrontPanel_(fp_dimension_ dimension, fp_layout_ layout);
    FrontPanel_(fp_dimension_ dimension, fp_layout_ layout, uint8_t leds_per_char_);

    ~FrontPanel_();

    uint8_t clear_row(uint8_t row);
    uint8_t clear_all();
    uint8_t draw_word(fp_word_ *word);
    void test_me();

    virtual uint8_t sync_row(uint8_t row) = 0;
    virtual uint8_t sync_all() = 0;

    virtual void update(uint8_t hour, uint8_t minute, uint8_t second) = 0;

    virtual void draw_pre_it() = 0;
    virtual void draw_pre_is() = 0;

    virtual void draw_min_five() = 0;
    virtual void draw_min_ten() = 0;
    virtual void draw_min_quarter() = 0;
    virtual void draw_min_twenty() = 0;
    virtual void draw_min_twentyfive() = 0;
    virtual void draw_min_half() = 0;

    virtual void draw_type_past() = 0;
    virtual void draw_type_to() = 0;

    virtual void draw_hour_one() = 0;
    virtual void draw_hour_two() = 0;
    virtual void draw_hour_three() = 0;
    virtual void draw_hour_four() = 0;
    virtual void draw_hour_five() = 0;
    virtual void draw_hour_six() = 0;
    virtual void draw_hour_seven() = 0;
    virtual void draw_hour_eight() = 0;
    virtual void draw_hour_nine() = 0;
    virtual void draw_hour_ten() = 0;
    virtual void draw_hour_eleven() = 0;
    virtual void draw_hour_twelve() = 0;

    virtual void draw_full_oclock() = 0;
};

#endif