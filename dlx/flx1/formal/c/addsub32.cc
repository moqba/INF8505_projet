#include "Hector.h"
#include "softfloat.h"

int float_rounding_mode = 0;

void hector_wrapper()
{
    uint8_t rounding_mode;
    uint8_t exceptions;

    uint32_t in_a, in_b, result;
    float32_t f_a, f_b, f_result;
    uint8_t mode;

    Hector::registerInput("in_a", in_a);
    Hector::registerInput("in_b", in_b);
    Hector::registerInput("rounding_mode", rounding_mode);
    Hector::registerInput("mode", mode);

    Hector::registerOutput("result", result);
    Hector::registerOutput("exceptions", exceptions);

    Hector::beginCapture();
    f_a.v = in_a;
    f_b.v = in_b;
    softfloat_roundingMode = rounding_mode;
    softfloat_exceptionFlags = 0;
    softfloat_detectTininess = softfloat_tininess_beforeRounding;

    if (mode == 0)
      f_result = f32_add(f_a, f_b);
    else
      f_result = f32_sub(f_a, f_b);

    result = f_result.v;
    exceptions = softfloat_exceptionFlags & 0x1f;

    Hector::endCapture();
}