
#include "fp-sk6812.h"

SK6812FrontPanel_::SK6812FrontPanel_(fp_dimension_ dimension, fp_layout_ layout) : SK6812FrontPanel_(dimension, layout, FP_DEF_LEDS_PER_CHAR){};
SK6812FrontPanel_::SK6812FrontPanel_(fp_dimension_ dimension, fp_layout_ layout, uint8_t leds_per_char) : SK6812FrontPanel_(dimension, layout, leds_per_char, FP_DEF_ON_COLOR){};
SK6812FrontPanel_::SK6812FrontPanel_(fp_dimension_ dimension, fp_layout_ layout, uint8_t leds_per_char, fp_color_ color) : FrontPanel_(dimension, layout, leds_per_char), on_color_(color), off_color_(FP_DEF_OFF_COLOR){};

// void SK6812FrontPanel_::set_output(uint8_t pin)
// {
//     _pin_mask = digitalPinToBitMask(pin);
//     _port = portOutputRegister(digitalPinToPort(pin));
//     _port_reg = portModeRegister(digitalPinToPort(pin));
// }

