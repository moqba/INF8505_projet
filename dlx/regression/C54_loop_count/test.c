/*
-- Test loop counts with side-effects. 
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model 
-- captures an ASIP Designer Design Technique. The model and all associated 
-- documentation are proprietary to Synopsys, Inc. and may only be used 
-- pursuant to the terms and conditions of a written license agreement with 
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution 
-- of the Synopsys processor model or the associated  documentation is 
-- strictly prohibited. 
*/



int up_counts(int ff)
{
    chess_message("// up_counts(" << ff << ')');
    int ii = 0;
    do { chess_report(ii); ii++; } while (  ii < 1 * ff);   chess_report(1000 + ii);
    do { chess_report(ii);       } while (++ii < 2 * ff);   chess_report(2000 + ii);
    do { chess_report(ii);       } while (ii++ < 3 * ff);   chess_report(3000 + ii);
    while (  ii < 4 * ff) { chess_report(ii); ii++; }       chess_report(4000 + ii);
    while (++ii < 5 * ff) { chess_report(ii);       }       chess_report(5000 + ii);
    while (ii++ < 6 * ff) { chess_report(ii);       }       chess_report(6000 + ii);
    for (/**/;   ii < 7 * ff; ii++) { chess_report(ii); }   chess_report(7000 + ii);
    for (/**/; ++ii < 8 * ff; /**/) { chess_report(ii); }   chess_report(8000 + ii);
    for (/**/; ii++ < 9 * ff; /**/) { chess_report(ii); }   chess_report(9000 + ii);
    return ii;
}

int down_counts(int ff)
{
    chess_message( "// down_counts(" << ff << ')' );
    int ii = 40;
    do { chess_report(ii); ii--; } while (  ii > 9 * ff);   chess_report(1000 + ii);
    do { chess_report(ii);       } while (--ii > 8 * ff);   chess_report(2000 + ii);
    do { chess_report(ii);       } while (ii-- > 7 * ff);   chess_report(3000 + ii);
    while (  ii > 6 * ff) { chess_report(ii); ii--; }       chess_report(4000 + ii);
    while (--ii > 5 * ff) { chess_report(ii);       }       chess_report(5000 + ii);
    while (ii-- > 4 * ff) { chess_report(ii);       }       chess_report(6000 + ii);
    for (/**/;   ii > 3 * ff; ii--) { chess_report(ii); }   chess_report(7000 + ii);
    for (/**/; --ii > 2 * ff; /**/) { chess_report(ii); }   chess_report(8000 + ii);
    for (/**/; ii-- > 1 * ff; /**/) { chess_report(ii); }   chess_report(9000 + ii);
    return ii;
}

int main()
{
    chess_report(  up_counts(0));
    chess_report(  up_counts(1));
    chess_report(  up_counts(4));
    chess_report(down_counts(0));
    chess_report(down_counts(1));
    chess_report(down_counts(4));
    return 0;
}
