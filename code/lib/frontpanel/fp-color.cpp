#include "fp.h"
#include "fp-color.h"

ColorFrontpanel_::ColorFrontpanel_(fp_layout_ layout) : ColorFrontpanel_(layout, FP_DEF_COLOR){};
ColorFrontpanel_::ColorFrontpanel_(fp_layout_ layout, fp_color_ color) : FrontPanel_(layout), color_(color){};