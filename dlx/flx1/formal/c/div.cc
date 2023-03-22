#include "Hector.h"
#include <inttypes.h>

void
div1 (uint32_t a, uint32_t b, uint32_t &quo, uint32_t &rem)
{
  uint64_t prem = a;
  uint32_t pquo = 0;
  Hector::show ("a", a);
  Hector::show ("b", b);
  Hector::show ("pquo", pquo);
  Hector::show ("pquo", pquo);
  Hector::show ("prem", prem);
  Hector::show ("prem", prem);
  for( int i = 0; i < 32; i++ ) {
    int shift = 31 - i;
    uint64_t sdiv = ((uint64_t) b) << shift;
    pquo *= 2;
    if( prem >= sdiv ) {
      pquo += 1;
      prem -= sdiv;
    }
    Hector::show ("pquo", pquo);
    Hector::show ("prem", prem);
  }
  rem = prem;
  quo = pquo;
}

void hector_wrapper()
{
    uint32_t in_a, in_b, quo, rem;

    Hector::registerInput("in_a", in_a);
    Hector::registerInput("in_b", in_b);
    Hector::registerOutput("out_q", quo);
    Hector::registerOutput("out_r", rem);

    Hector::beginCapture();

    div1(in_a,in_b,quo,rem);

    Hector::endCapture();
}
