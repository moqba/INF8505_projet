#include "coder.h"

void write_APP0info()
{
    writeword(APP0info.marker);
    writeword(APP0info.length);
    writebyte('J'); writebyte('F'); writebyte('I'); writebyte('F'); writebyte(0);
    writebyte(APP0info.versionhi); writebyte(APP0info.versionlo);
    writebyte(APP0info.xyunits);
    writeword(APP0info.xdensity); writeword(APP0info.ydensity);
    writebyte(APP0info.thumbnwidth); writebyte(APP0info.thumbnheight);
}

void write_SOF0info()
{
    writeword(SOF0info.marker);
    writeword(SOF0info.length);
    writebyte(SOF0info.precision);
    writeword(SOF0info.height); writeword(SOF0info.width);
    writebyte(SOF0info.nrofcomponents);
    writebyte(SOF0info.IdY);  writebyte(SOF0info.HVY);  writebyte(SOF0info.QTY);
    writebyte(SOF0info.IdCb); writebyte(SOF0info.HVCb); writebyte(SOF0info.QTCb);
    writebyte(SOF0info.IdCr); writebyte(SOF0info.HVCr); writebyte(SOF0info.QTCr);
}

void write_DQTinfo()
{
    writeword(DQTinfo.marker);
    writeword(DQTinfo.length);
    writebyte(DQTinfo.QTYinfo);  writearray(DQTinfo.Ytable,64);
    writebyte(DQTinfo.QTCbinfo); writearray(DQTinfo.Cbtable,64);
}


void write_DHTinfo()
{
    writeword(DHTinfo.marker);
    writeword(DHTinfo.length);
    writebyte (DHTinfo.HTYDCinfo);
    writearray(DHTinfo.YDC_nrcodes, 16);
    writearray(DHTinfo.YDC_values,  12);
    writebyte (DHTinfo.HTYACinfo);
    writearray(DHTinfo.YAC_nrcodes, 16);
    writearray(DHTinfo.YAC_values,  162);
    writebyte (DHTinfo.HTCbDCinfo);
    writearray(DHTinfo.CbDC_nrcodes,16);
    writearray(DHTinfo.CbDC_values, 12);
    writebyte (DHTinfo.HTCbACinfo);
    writearray(DHTinfo.CbAC_nrcodes,16);
    writearray(DHTinfo.CbAC_values, 162);
}

void write_SOSinfo()
{
    writeword(SOSinfo.marker);
    writeword(SOSinfo.length);
    writebyte(SOSinfo.nrofcomponents);
    writebyte(SOSinfo.IdY);  writebyte(SOSinfo.HTY);
    writebyte(SOSinfo.IdCb); writebyte(SOSinfo.HTCb);
    writebyte(SOSinfo.IdCr); writebyte(SOSinfo.HTCr);
    writebyte(SOSinfo.Ss);   writebyte(SOSinfo.Se); writebyte(SOSinfo.Bf);
}

void write_headers()
{
    writeword(0xFFD8); //SOI
    write_APP0info();
    write_DQTinfo();
    write_SOF0info();
    write_DHTinfo();
    write_SOSinfo();
}