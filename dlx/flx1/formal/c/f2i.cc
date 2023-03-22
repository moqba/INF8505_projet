#include "Hector.h"
#include "softfloat.h"

int float_rounding_mode = 0;

void hector_wrapper()
{
    uint8_t rounding_mode;
    uint8_t exceptions;

    uint32_t in_a, in_b, result;
    float32_t f_a, f_b, f_result;

    Hector::registerInput("in_a", in_a);
    Hector::registerInput("rounding_mode", rounding_mode);

    Hector::registerOutput("result", result);
    Hector::registerOutput("exceptions", exceptions);

    Hector::beginCapture();
    f_a.v = in_a;
    softfloat_roundingMode = rounding_mode;
    softfloat_exceptionFlags = 0;
    softfloat_detectTininess = softfloat_tininess_beforeRounding;

    result = f32_to_i32_r_minMag(f_a, false);

    exceptions = softfloat_exceptionFlags & 0x1f;

    Hector::endCapture();
}
