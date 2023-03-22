/*
-- File : coder.h
--
-- Contents: Header file for BMP truecolor to JPEG encoder
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/


#define INLINE inline
//#define INLINE 

// data-types
#define BYTE unsigned char
#define SBYTE signed char
#define SWORD signed short int
#define WORD unsigned short int
#define DWORD unsigned long int
#define SDWORD signed long int

typedef short DCTELEM;

typedef struct {
  BYTE B,G,R;
} colorRGB;

typedef struct {
  BYTE length;
  WORD value;
} bitstring;

struct image {
  colorRGB *RGB_buffer; //image to be encoded
  WORD width; // image dimensions divisible by 8
  WORD height;
};

// write file headers
void write_headers();

// top level function.
void main_encoder(struct image* img);


// input/output
void init_input(struct image* img);
void fini_input(struct image* img);
void init_output();
int  fini_output();


// the writing of the file is in the testbench.
void writebyte(BYTE a);
void writeword(WORD a);
void writearray(void* p, int n);

// global variables
extern BYTE zigzag[64];

// (integer) Quantization tables. Should be filled in before calling main_encoder.
extern int quantY[64];
extern int quantC[64];

// The Huffman tables we'll use. Should be filled in before calling main_encoder.
extern bitstring YDC_HT[12];
extern bitstring CbDC_HT[12];
extern bitstring YAC_HT[256];
extern bitstring CbAC_HT[256];

static struct APP0infotype {
    WORD marker;           // = 0xFFE0
    WORD length;           // = 16 for usual JPEG, no thumbnail
    BYTE JFIFsignature[5]; // = "JFIF",'\0'
    BYTE versionhi;        // 1
    BYTE versionlo;        // 1
    BYTE xyunits;          // 0 = no units, normal density
    WORD xdensity;         // 1
    WORD ydensity;         // 1
    BYTE thumbnwidth;      // 0
    BYTE thumbnheight;     // 0
} APP0info={0xFFE0,16,'J','F','I','F',0,1,1,0,1,1,0,0};

struct  SOF0infotype {
    WORD marker;           // = 0xFFC0
    WORD length;           // = 17 for a truecolor YCbCr JPG
    BYTE precision ;       // Should be 8: 8 bits/sample
    WORD height ;
    WORD width;
    BYTE nrofcomponents;   //Should be 3: We encode a truecolor JPG
    BYTE IdY;              // = 1
    BYTE HVY;              // = 0x22 sampling factors for Y (bit 0-3 vert., 4-7 hor.)
    BYTE QTY;              // Quantization Table number for Y = 0
    BYTE IdCb;             // = 2
    BYTE HVCb;             // = 0x11
    BYTE QTCb;             // 1
    BYTE IdCr;             // = 3
    BYTE HVCr;             // = 0x11
    BYTE QTCr;             // Normally equal to QTCb = 1
};
// Default sampling factors are 1,1 for every image component: No downsampling

struct DQTinfotype {
    WORD marker;           // = 0xFFDB
    WORD length;           // = 132
    BYTE QTYinfo;          // = 0:  bit 0..3: number of QT = 0 (table for Y)
    /**/                   //       bit 4..7: precision of QT, 0 = 8 bit
    BYTE Ytable[64];
    BYTE QTCbinfo;         // = 1 (quantization table for Cb,Cr}
    BYTE Cbtable[64];
};

// Ytable from DQTinfo should be equal to a scaled and zizag reordered version
// of the table which can be found in "tables.h": std_luminance_qt
// Cbtable , similar = std_chrominance_qt
// We'll init them in the program using set_DQTinfo function

struct DHTinfotype {
    WORD marker;           // = 0xFFC4
    WORD length;           //0x01A2
    BYTE HTYDCinfo;
    // bit 0..3: number of HT (0..3), for Y =0
    //bit 4  :type of HT, 0 = DC table,1 = AC table
    //bit 5..7: not used, must be 0
    BYTE YDC_nrcodes[16];  //at index i = nr of codes with length i
    BYTE YDC_values[12];
    BYTE HTYACinfo;        // = 0x10
    BYTE YAC_nrcodes[16];
    BYTE YAC_values[162];  //we'll use the standard Huffman tables
    BYTE HTCbDCinfo;       // = 1
    BYTE CbDC_nrcodes[16];
    BYTE CbDC_values[12];
    BYTE HTCbACinfo;       //  = 0x11
    BYTE CbAC_nrcodes[16];
    BYTE CbAC_values[162];
};

struct SOSinfotype {
    WORD marker;           // = 0xFFDA
    WORD length;           // = 12
    BYTE nrofcomponents;   // Should be 3: truecolor JPG
    BYTE IdY;              // 1
    BYTE HTY;              // 0 bits 0..3: AC table (0..3)
    /**/                   //   bits 4..7: DC table (0..3)
    BYTE IdCb;             // 2
    BYTE HTCb;             // 0x11
    BYTE IdCr;             // 3
    BYTE HTCr;             // 0x11
    BYTE Ss,Se,Bf;         // not interesting, they should be 0,63,0
};

extern struct SOF0infotype SOF0info;
extern struct DQTinfotype  DQTinfo;
extern struct DHTinfotype  DHTinfo;
extern struct SOSinfotype  SOSinfo;

