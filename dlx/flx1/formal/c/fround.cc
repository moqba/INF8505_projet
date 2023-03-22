#include "Hector.h"
#include "softfloat.h"

int float_rounding_mode = 0;

void hector_wrapper()
{
    uint8_t rounding_mode;
    uint8_t imode;
    uint8_t exceptions;

    uint32_t in_a, in_b, result;
    float32_t f_a, f_b, f_result;

    Hector::registerInput("in_a", in_a);
    Hector::registerInput("rounding_mode", rounding_mode);
    Hector::registerInput("imode", imode);

    Hector::registerOutput("result", result);
    Hector::registerOutput("exceptions", exceptions);

    Hector::beginCapture();
    f_a.v = in_a;
    softfloat_roundingMode = rounding_mode;
    softfloat_exceptionFlags = 0;
    softfloat_detectTininess = softfloat_tininess_beforeRounding;

    uint8_t sfmode;
    if (imode == 0) sfmode = softfloat_round_near_maxMag;       // roundf
    if (imode == 1) sfmode = softfloat_round_min;               // floorf
    if (imode == 2) sfmode = softfloat_round_max;               // ceilf
    if (imode == 3) sfmode = softfloat_round_minMag;            // truncf

    f_result = f32_roundToInt(f_a, sfmode, false);
    result = f_result.v;

    exceptions = softfloat_exceptionFlags & 0x1f;

    Hector::endCapture();
}
