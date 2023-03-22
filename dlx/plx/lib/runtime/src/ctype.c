/*
-- File: ctype.c
--
-- Contents: Table base implementation of ctype.h functions.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



#include <ctype.h>

unsigned char _ct_code[256] = {
    /*   0 :    NUL */     _ct_C,
    /*   1 :    SOH */     _ct_C,
    /*   2 :    STX */     _ct_C,
    /*   3 :    ETX */     _ct_C,
    /*   4 :    EOT */     _ct_C,
    /*   5 :    ENQ */     _ct_C,
    /*   6 :    ACK */     _ct_C,
    /*   7 :    BEL */     _ct_C,
    /*   8 :    BS  */     _ct_C,
    /*   9 :    HT  */     _ct_C|_ct_S|_ct_B,
    /*  10 :    LF  */     _ct_C|_ct_S,
    /*  11 :    VT  */     _ct_C|_ct_S,
    /*  12 :    FF  */     _ct_C|_ct_S,
    /*  13 :    CR  */     _ct_C|_ct_S,
    /*  14 :    SO  */     _ct_C,
    /*  15 :    SI  */     _ct_C,
    /*  16 :    DLE */     _ct_C,
    /*  17 :    DC1 */     _ct_C,
    /*  18 :    DC2 */     _ct_C,
    /*  19 :    DC3 */     _ct_C,
    /*  20 :    DC4 */     _ct_C,
    /*  21 :    NAK */     _ct_C,
    /*  22 :    SYN */     _ct_C,
    /*  23 :    ETB */     _ct_C,
    /*  24 :    CAN */     _ct_C,
    /*  25 :    EM  */     _ct_C,
    /*  26 :    SUB */     _ct_C,
    /*  27 :    ESC */     _ct_C,
    /*  28 :    FS  */     _ct_C,
    /*  29 :    GS  */     _ct_C,
    /*  30 :    RS  */     _ct_C,
    /*  31 :    US  */     _ct_C,
    /*  32 :  SPACE */     _ct_S|_ct_B,
    /*  33 :      ! */     _ct_P,
    /*  34 :      " */     _ct_P,
    /*  35 :      # */     _ct_P,
    /*  36 :      $ */     _ct_P,
    /*  37 :      % */     _ct_P,
    /*  38 :      & */     _ct_P,
    /*  39 :      ' */     _ct_P,
    /*  40 :      ( */     _ct_P,
    /*  41 :      ) */     _ct_P,
    /*  42 :      * */     _ct_P,
    /*  43 :      + */     _ct_P,
    /*  44 :      , */     _ct_P,
    /*  45 :      - */     _ct_P,
    /*  46 :      . */     _ct_P,
    /*  47 :      / */     _ct_P,
    /*  48 :      0 */     _ct_D|_ct_X,
    /*  49 :      1 */     _ct_D|_ct_X,
    /*  50 :      2 */     _ct_D|_ct_X,
    /*  51 :      3 */     _ct_D|_ct_X,
    /*  52 :      4 */     _ct_D|_ct_X,
    /*  53 :      5 */     _ct_D|_ct_X,
    /*  54 :      6 */     _ct_D|_ct_X,
    /*  55 :      7 */     _ct_D|_ct_X,
    /*  56 :      8 */     _ct_D|_ct_X,
    /*  57 :      9 */     _ct_D|_ct_X,
    /*  58 :      : */     _ct_P,
    /*  59 :      ; */     _ct_P,
    /*  60 :      < */     _ct_P,
    /*  61 :      = */     _ct_P,
    /*  62 :      > */     _ct_P,
    /*  63 :      ? */     _ct_P,
    /*  64 :      @ */     _ct_P,
    /*  65 :      A */     _ct_U|_ct_X,
    /*  66 :      B */     _ct_U|_ct_X,
    /*  67 :      C */     _ct_U|_ct_X,
    /*  68 :      D */     _ct_U|_ct_X,
    /*  69 :      E */     _ct_U|_ct_X,
    /*  70 :      F */     _ct_U|_ct_X,
    /*  71 :      G */     _ct_U,
    /*  72 :      H */     _ct_U,
    /*  73 :      I */     _ct_U,
    /*  74 :      J */     _ct_U,
    /*  75 :      K */     _ct_U,
    /*  76 :      L */     _ct_U,
    /*  77 :      M */     _ct_U,
    /*  78 :      N */     _ct_U,
    /*  79 :      O */     _ct_U,
    /*  80 :      P */     _ct_U,
    /*  81 :      Q */     _ct_U,
    /*  82 :      R */     _ct_U,
    /*  83 :      S */     _ct_U,
    /*  84 :      T */     _ct_U,
    /*  85 :      U */     _ct_U,
    /*  86 :      V */     _ct_U,
    /*  87 :      W */     _ct_U,
    /*  88 :      X */     _ct_U,
    /*  89 :      Y */     _ct_U,
    /*  90 :      Z */     _ct_U,
    /*  91 :      [ */     _ct_P,
    /*  92 :      \ */     _ct_P,
    /*  93 :      ] */     _ct_P,
    /*  94 :      ^ */     _ct_P,
    /*  95 :      _ */     _ct_P,
    /*  96 :      ` */     _ct_P,
    /*  97 :      a */     _ct_L|_ct_X,
    /*  98 :      b */     _ct_L|_ct_X,
    /*  99 :      c */     _ct_L|_ct_X,
    /* 100 :      d */     _ct_L|_ct_X,
    /* 101 :      e */     _ct_L|_ct_X,
    /* 102 :      f */     _ct_L|_ct_X,
    /* 103 :      g */     _ct_L,
    /* 104 :      h */     _ct_L,
    /* 105 :      i */     _ct_L,
    /* 106 :      j */     _ct_L,
    /* 107 :      k */     _ct_L,
    /* 108 :      l */     _ct_L,
    /* 109 :      m */     _ct_L,
    /* 110 :      n */     _ct_L,
    /* 111 :      o */     _ct_L,
    /* 112 :      p */     _ct_L,
    /* 113 :      q */     _ct_L,
    /* 114 :      r */     _ct_L,
    /* 115 :      s */     _ct_L,
    /* 116 :      t */     _ct_L,
    /* 117 :      u */     _ct_L,
    /* 118 :      v */     _ct_L,
    /* 119 :      w */     _ct_L,
    /* 120 :      x */     _ct_L,
    /* 121 :      y */     _ct_L,
    /* 122 :      z */     _ct_L,
    /* 123 :      { */     _ct_P,
    /* 124 :      | */     _ct_P,
    /* 125 :      } */     _ct_P,
    /* 126 :      ~ */     _ct_P,
    /* 127 :    DEL */     _ct_C
};

