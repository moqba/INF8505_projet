/*
-- File : coder.c
--
-- Contents: A BMP truecolor to JPEG encoder
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/


#include "coder.h"

#define DCTSIZE 8

#define CONST_BITS  8
#define FIX_0_382683433  ((int)   98)		/* FIX(0.382683433) */
#define FIX_0_541196100  ((int)  139)		/* FIX(0.541196100) */
#define FIX_0_707106781  ((int)  181)		/* FIX(0.707106781) */
#define FIX_1_306562965  ((int)  334)		/* FIX(1.306562965) */

#define MAX(a,b) ((a)>(b)?(a):(b))

INLINE int calc_nrbits(int in)
{
  int out=0;
  // this function takes the absoluut value and then calculates the number of used bits.
  int val = in<0?-in:in;
  if (val>=(1<<16)) { val>>=6; out+=6; }
  if (val>=(1<<8))  { val>>=5; out+=5; }
  if (val>=(1<<4))  { val>>=4; out+=4; }
  if (val>=(1<<2))  { val>>=3; out+=3; }
  if (val>=(1<<1))  { val>>=2; out+=2; }
  if (val>=(1<<0))  {          out+=1; }
  return out;
}

unsigned int shiftword16 = 0;
unsigned int shiftpos16  = 0;

#define WRITEBUF_SIZE 256
unsigned char  writebuf[WRITEBUF_SIZE];
unsigned char* pwritebuf=writebuf;

INLINE void writebuf_add(unsigned char a)
{
    if (pwritebuf<(writebuf+WRITEBUF_SIZE)) {
        *pwritebuf++ = a;
    }
    else {
        writearray(writebuf,WRITEBUF_SIZE);
        pwritebuf=writebuf;
        *pwritebuf++ = a;
    }
}

INLINE void writebuf_flush()
{
    writearray(writebuf,pwritebuf-writebuf);
}

void writebits_add(unsigned value, unsigned len)
{
    // the additional bits won't fit
    int freebits = 16-shiftpos16;
    shiftword16 <<= freebits; // shift the remaining bits
    shiftword16 |= (value>>(len-freebits)); // add the bits that still fit
    unsigned outword16 = shiftword16;
    shiftpos16 = len-freebits;
    shiftword16 = value; // &((1<<shiftpos16)-1);
    unsigned hibyte = (outword16>>8)&0xff;
    writebuf_add(hibyte);
    if (hibyte==0xff) { writebuf_add(0); }
    unsigned lobyte = outword16&0xff;
    writebuf_add(lobyte);
    if (lobyte==0xff) { writebuf_add(0); }
}

INLINE void writebits(unsigned value, unsigned len)
{
  //  printf("wb(val=0x%x len=%d) ; w16=0x%x p16=%d\n", value, len, shiftword16, shiftpos16);
  // start intrinsic 1
  if (len+shiftpos16<16) {
    // the additional bits fit
    shiftword16 <<= len;
    shiftword16  |= value;
    shiftpos16   += len;
  }
  else {
      writebits_add(value,len);
  }
}

void vlc_flush()
{
  if (shiftpos16==8) {
    unsigned int byte = shiftword16&0xff;
    writebuf_add(byte);
    // the last byte could be 0xff (high chance, because it is "1" padded)
    if (byte==0xff) writebuf_add(0);
  }
  else if (shiftpos16==0) {
    ; // do nothing
  }
  writebuf_flush();
}

/*INLINE*/ void jpeg_fdct_ifast (signed char* data_in, DCTELEM * data_out)
{
  int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
  int tmp10, tmp11, tmp12, tmp13;
  int z1, z2, z3, z4, z5, z11, z13;
  DCTELEM* data_out_ptr;
  DCTELEM* data_tmp_ptr;
  DCTELEM* dataptr;
  DCTELEM TMP_DCT[64]; // Allow acq/rel put by avoiding read from DU_DCT
  signed char* data_in_ptr;

  /* Pass 1: process rows. */

  data_in_ptr  = data_in;
  data_tmp_ptr = TMP_DCT;
  for (int i=0; i<DCTSIZE; i++) {
    tmp0 = data_in_ptr[0] + data_in_ptr[7];
    tmp7 = data_in_ptr[0] - data_in_ptr[7];
    tmp1 = data_in_ptr[1] + data_in_ptr[6];
    tmp6 = data_in_ptr[1] - data_in_ptr[6];
    tmp2 = data_in_ptr[2] + data_in_ptr[5];
    tmp5 = data_in_ptr[2] - data_in_ptr[5];
    tmp3 = data_in_ptr[3] + data_in_ptr[4];
    tmp4 = data_in_ptr[3] - data_in_ptr[4];

    /* Even part */

    tmp10 = tmp0 + tmp3;	/* phase 2 */
    tmp13 = tmp0 - tmp3;
    tmp11 = tmp1 + tmp2;
    tmp12 = tmp1 - tmp2;

    data_tmp_ptr[0] = tmp10 + tmp11; /* phase 3 */
    data_tmp_ptr[4] = tmp10 - tmp11;

    z1 = ((tmp12 + tmp13) * FIX_0_707106781)>>CONST_BITS; /* c4 */
    data_tmp_ptr[2] = tmp13 + z1;	/* phase 5 */
    data_tmp_ptr[6] = tmp13 - z1;

    /* Odd part */

    tmp10 = tmp4 + tmp5;	/* phase 2 */
    tmp11 = tmp5 + tmp6;
    tmp12 = tmp6 + tmp7;

    /* The rotator is modified from fig 4-8 to avoid extra negations. */
    z5 = ((tmp10 - tmp12) * FIX_0_382683433)>>CONST_BITS; /* c6 */
    z2 = ((tmp10 * FIX_0_541196100)>>CONST_BITS) + z5; /* c2-c6 */
    z4 = ((tmp12 * FIX_1_306562965)>>CONST_BITS) + z5; /* c2+c6 */
    z3 = ((tmp11 * FIX_0_707106781)>>CONST_BITS); /* c4 */

    z11 = tmp7 + z3;		/* phase 5 */
    z13 = tmp7 - z3;

    data_tmp_ptr[5] = z13 + z2;	/* phase 6 */
    data_tmp_ptr[3] = z13 - z2;
    data_tmp_ptr[1] = z11 + z4;
    data_tmp_ptr[7] = z11 - z4;

    data_in_ptr  += DCTSIZE;		/* advance pointer to next row */
    data_tmp_ptr += DCTSIZE;		/* advance pointer to next row */
  }

  /* Pass 2: process columns. */

  data_tmp_ptr = TMP_DCT;
  data_out_ptr = data_out;
  for (int i=0; i<DCTSIZE; i++) {
    tmp0 = data_tmp_ptr[DCTSIZE*0] + data_tmp_ptr[DCTSIZE*7];
    tmp7 = data_tmp_ptr[DCTSIZE*0] - data_tmp_ptr[DCTSIZE*7];
    tmp1 = data_tmp_ptr[DCTSIZE*1] + data_tmp_ptr[DCTSIZE*6];
    tmp6 = data_tmp_ptr[DCTSIZE*1] - data_tmp_ptr[DCTSIZE*6];
    tmp2 = data_tmp_ptr[DCTSIZE*2] + data_tmp_ptr[DCTSIZE*5];
    tmp5 = data_tmp_ptr[DCTSIZE*2] - data_tmp_ptr[DCTSIZE*5];
    tmp3 = data_tmp_ptr[DCTSIZE*3] + data_tmp_ptr[DCTSIZE*4];
    tmp4 = data_tmp_ptr[DCTSIZE*3] - data_tmp_ptr[DCTSIZE*4];

    /* Even part */

    tmp10 = tmp0 + tmp3;	/* phase 2 */
    tmp13 = tmp0 - tmp3;
    tmp11 = tmp1 + tmp2;
    tmp12 = tmp1 - tmp2;

    data_out_ptr[DCTSIZE*0] = tmp10 + tmp11; /* phase 3 */
    data_out_ptr[DCTSIZE*4] = tmp10 - tmp11;

    z1 = ((tmp12 + tmp13) * FIX_0_707106781)>>CONST_BITS; /* c4 */
    data_out_ptr[DCTSIZE*2] = tmp13 + z1; /* phase 5 */
    data_out_ptr[DCTSIZE*6] = tmp13 - z1;

    /* Odd part */

    tmp10 = tmp4 + tmp5;	/* phase 2 */
    tmp11 = tmp5 + tmp6;
    tmp12 = tmp6 + tmp7;

    /* The rotator is modified from fig 4-8 to avoid extra negations. */
    z5 = ((tmp10 - tmp12) * FIX_0_382683433)>>CONST_BITS; /* c6 */
    z2 = ((tmp10 * FIX_0_541196100)>>CONST_BITS) + z5; /* c2-c6 */
    z4 = ((tmp12 * FIX_1_306562965)>>CONST_BITS) + z5; /* c2+c6 */
    z3 = ((tmp11 * FIX_0_707106781)>>CONST_BITS); /* c4 */

    z11 = tmp7 + z3;		/* phase 5 */
    z13 = tmp7 - z3;

    data_out_ptr[DCTSIZE*5] = z13 + z2; /* phase 6 */
    data_out_ptr[DCTSIZE*3] = z13 - z2;
    data_out_ptr[DCTSIZE*1] = z11 + z4;
    data_out_ptr[DCTSIZE*7] = z11 - z4;

    data_tmp_ptr++;			/* advance pointer to next column */
    data_out_ptr++;			/* advance pointer to next column */
  }
}

INLINE int quantization(DCTELEM DU_DCT[64],
	         int     quanttbl[64],
		 SWORD   DU_ZZ[64])
{
  // Quantize/descale the coefficients, and store into output array
  int last_coef=0;
  for (int i = 0; i < 64; i++) chess_unroll_loop(2) {
      /* Apply the quantization and scaling factor */
      int itemp = (DU_DCT[i]*quanttbl[i])>>15;
      if (DU_DCT[i]<0) itemp++;

      //zigzag reorder
      int idx=zigzag[i];
      DU_ZZ[idx] = itemp;

      // determine last coef
      if (itemp!=0) last_coef = MAX(last_coef,idx);
    }
  return last_coef;
}


SWORD DCY,DCCb,DCCr; //DC coefficients used for differential encoding

int*       blk_quant[6] = { quantY, quantY, quantY, quantY, quantC,  quantC  };
SWORD*     blk_DC[6]    = { &DCY,   &DCY,   &DCY,   &DCY,   &DCCb,   &DCCr   };
bitstring* blk_HTDC[6]  = { YDC_HT, YDC_HT, YDC_HT, YDC_HT, CbDC_HT, CbDC_HT };
bitstring* blk_HTAC[6]  = { YAC_HT, YAC_HT, YAC_HT, YAC_HT, CbAC_HT, CbAC_HT };

void process_DU(SBYTE   pPIX[64],
		int     blk)
{
  DCTELEM DU_DCT[64];
  SWORD DU_ZZ[64]; //zigzag reordered DU which will be Huffman coded
  int end0pos;

 fdct_main:
  {
    jpeg_fdct_ifast(pPIX, DU_DCT);
  }

 quant_main:
  {
    int* quant = blk_quant[blk];
    end0pos = quantization(DU_DCT,quant,DU_ZZ);
  }

 vlc_main:
  {
    bitstring* HTDC    = blk_HTDC[blk];
    bitstring* HTAC    = blk_HTAC[blk];
    bitstring EOB      = HTAC[0x00];
    bitstring M16zeroes= HTAC[0xF0];

    SWORD* DC = blk_DC[blk];
    SWORD Diff=DU_ZZ[0]-*DC;
    *DC=DU_ZZ[0];
    //Encode DC
    if (Diff==0) {
      writebits(HTDC[0].value, HTDC[0].length); //Diff might be 0
    }
    else {
      int nr_bits = calc_nrbits(Diff);
      int value   = Diff<=0?Diff+(1<<nr_bits)-1:Diff;
      writebits(HTDC[nr_bits].value, HTDC[nr_bits].length);
      writebits(value, nr_bits);
    }

    //end0pos = first element in reverse order !=0
    if (end0pos==0) {
      writebits(EOB.value, EOB.length);
    }
    else {
      //Encode ACs
      int i=1;
      while (i<=end0pos) chess_loop_range(1,) {
	  int startpos=i;
	  while ((DU_ZZ[i]==0) && (i<=end0pos)) i++ ;
	  int nrzeroes=i-startpos;
	  if (nrzeroes>=16) {
	    for (int nrmarker=0; nrmarker<nrzeroes/16; nrmarker++) chess_loop_range(1,) {
		writebits(M16zeroes.value, M16zeroes.length);
	      }
	    nrzeroes=nrzeroes%16;
	  }
	  int coef = DU_ZZ[i];
	  int len = calc_nrbits(coef);
	  writebits(HTAC[nrzeroes*16+len].value, HTAC[nrzeroes*16+len].length);
	  int value = coef<=0?coef+(1<<len)-1:coef;
	  writebits(value, len); // bitcode[DU[i]]);
	  i++;
	}
      if (end0pos!=63) writebits(EOB.value, EOB.length);
    }
  }
}

void load_data_unit_from_RGB_buffer(struct image* img,
				    int           mbx,
				    int           mby,
				    int           blk, /* Y=0..3, Cb=4, Cr=5 */
				    SBYTE         DU[64]
				    )
{
  int width  = img->width;
  int height = img->height;
  static SBYTE         CDU[2][64];

  if (blk<4) {
    int bx = blk&1;
    int by = blk>>1;
    colorRGB* pRGBbuf = img->RGB_buffer;
    for (int y2=0;y2<4;y2++) {
	for (int x2=0;x2<4;x2++) {
	    int Cb=0;
	    int Cr=0;
	    for (int y=0;y<2;y++) chess_unroll_loop(*) {
		for (int x=0;x<2;x++) chess_unroll_loop(*) {
		    BYTE R = pRGBbuf[(height-1-(mby*16+by*8+y2*2+y))*width+(mbx*16+bx*8+x2*2+x)].R;
		    BYTE G = pRGBbuf[(height-1-(mby*16+by*8+y2*2+y))*width+(mbx*16+bx*8+x2*2+x)].G;
		    BYTE B = pRGBbuf[(height-1-(mby*16+by*8+y2*2+y))*width+(mbx*16+bx*8+x2*2+x)].B;
		    DU[(y2*2+y)*8+(x2*2+x)]  = ((BYTE)( ( 19595*R + 38470*G +  7471*B)>>16 ) - 128);
		    Cb += (int)((SBYTE)( (-11058*R - 21708*G + 32768*B)>>16 ) );
		    Cr += (int)((SBYTE)( ( 32768*R - 27438*G -  5328*B)>>16 ) );
		  }
	      }
	    CDU[0][(by*4+y2)*8+(bx*4+x2)] = Cb>>2;
	    CDU[1][(by*4+y2)*8+(bx*4+x2)] = Cr>>2;
	  }
      }
  }
  else {
    for (int y=0;y<8;y++) {
      for (int x=0;x<8;x++) {
	DU[y*8+x] = CDU[blk-4][y*8+x];
      }
    }
  }
}

void main_encoder(struct image* img)
{
 vlc_init:
  {
    DCY=0;DCCb=0;DCCr=0; //DC coefficients used for differential encoding
  }
    for (int ypos=0; ypos<img->height/16; ypos++) {
      for (int xpos=0; xpos<img->width/16; xpos++) {
	for (int blk=0; blk<6; blk++) {
	  SBYTE DU[64];
	loading:
	  load_data_unit_from_RGB_buffer(img,
					 xpos,ypos,
					 blk,
					 DU);
	  process_DU(DU,blk);
	}
      }
    }

 vlc_fini:
  {
    //Do the bit alignment of the EOI marker
    int bytepos = 8-(shiftpos16&0x7);
    if (bytepos<8) {
      //filling bitstring for the bit alignment of the EOI marker
      writebits((1<<bytepos)-1, bytepos);
    }
    vlc_flush(); // 1byte can de stuck in the shift register
  }
}

