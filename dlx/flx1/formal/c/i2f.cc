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
    softfloat_roundingMode = rounding_mode;
    softfloat_exceptionFlags = 0;
    softfloat_detectTininess = softfloat_tininess_beforeRounding;

    f_result = i32_to_f32(in_a);
    result = f_result.v;

    exceptions = softfloat_exceptionFlags & 0x1f;

    Hector::endCapture();
}
