#include "Hector.h"
#include "softfloat.h"

int float_rounding_mode = 0;

void hector_wrapper()
{
    uint8_t rounding_mode;
    uint8_t exceptions;

    uint32_t multiplier, multiplicand, product;
    float32_t f_multiplier, f_multiplicand, f_product;

    Hector::registerInput("multiplier", multiplier);
    Hector::registerInput("multiplicand", multiplicand);
    Hector::registerInput("rounding_mode", rounding_mode);

    Hector::registerOutput("product", product);
    Hector::registerOutput("exceptions", exceptions);

    Hector::beginCapture();
    f_multiplier.v = multiplier;
    f_multiplicand.v = multiplicand;
    softfloat_roundingMode = rounding_mode;
    softfloat_exceptionFlags = 0;
    softfloat_detectTininess = softfloat_tininess_beforeRounding;

    f_product = f32_mul(f_multiplier, f_multiplicand);

    product = f_product.v;
    exceptions = softfloat_exceptionFlags & 0x1f;

    Hector::endCapture();
}
