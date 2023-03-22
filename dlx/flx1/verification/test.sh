#!/bin/bash

# build
chessmk -m driver/test

# round to nearest even
for FN in f32_add \
          f32_sub \
          f32_mul \
          f32_div \
          f32_sqrt \
          f32_roundToInt \
          i32_to_f32 \
          ui32_to_f32 \
          f32_eq \
          f32_lt \
          f32_le \
          ; do
  ./testfloat_gen -tininessbefore $FN |& \
  chessmk driver/test -Ss +X $FN |& \
  ./testfloat_ver -tininessbefore $FN
done

# to int: round to zero
for FN in f32_to_i32 \
          f32_to_ui32 \
          ; do
  ./testfloat_gen -rminMag $FN |& \
  chessmk driver/test -Ss +X $FN |& \
  ./testfloat_ver -rminMag $FN
done