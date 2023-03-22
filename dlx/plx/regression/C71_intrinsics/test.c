/*
-- Test expressions on floats.
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


unsigned long long T[] = {
                  0x0000000008000000ULL,
                  0x0000000000800900ULL,
                  0x0000000080800900ULL,
                  0x00000000F0800900ULL,
                  0x00000000FC800900ULL,
                  0,
                  (unsigned long long)-1,
                  0x8000000000000000ULL,
                  0x1000000000004000ULL,
                  0xF0000000F0800900ULL,
                  0xFFC0000000000900ULL,
                  0x0808080808080808ULL // sentinel
                };

void test_clb()
{
    chess_message( "// test_clb()" );

    int i = 0;
    while (T[i] != 0x0808080808080808ULL) {
        chess_report ((unsigned long long)T[i]);

        chess_report ( clb((int)T[i])                );
        chess_report ( clb((unsigned)T[i])           );
        chess_report ( clb((long long)T[i])          );
        chess_report ( clb((unsigned long long)T[i]) );
        i++;
    }
}


int main()
{
    test_clb();
    return 0;
}

