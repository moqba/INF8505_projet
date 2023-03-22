/*
-- Test code with switch statements.
-- [based on real code]
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/



int foo(int r, int a) { return r + a * 1000; }


int jmptab;


int compander(int a)
{
    chess_message( "// compander(" << a << ")  jmptab = " << jmptab );

    int value = 0;

    switch (jmptab)
    {
    case 1:  /**********************************************************/

        chess_separator();

        chess_separator();
        jmptab = 6;
        break;

    case 2:  /**********************************************************/
        chess_separator();

        if ((a & 3) == 1)
        {
            value = foo(value,1);
        }
        else
        {
            if ((a & 3) == 2)
            {
                value = foo(value,2);
            }
            else
            {
                if ((a & 3) == 3)
                {
                    value = foo(value,3);
                }
                else
                {
                    value = foo(value,4);
                }
            }
        }

        chess_separator();
        jmptab = 7;
        break;

    case 3:  /**********************************************************/
        chess_separator();

        chess_separator();
        jmptab = 8;
        break;

    case 4:  /**********************************************************/
        chess_separator();

        chess_separator();
        jmptab = 9;
        break;

    case 5:  /**********************************************************/
        chess_separator();

        chess_separator();
        jmptab = 10;
        break;

    case 6:  /**********************************************************/
        chess_separator();

        chess_separator();
        jmptab = 2;
        break;

    case 7:  /**********************************************************/
        chess_separator();

        if ((a & 3) == 1)
        {
            value = foo(value,5);
        }
        else
        {
            if ((a & 3) == 2)
            {
                value = foo(value,6);
            }
            else
            {
                if ((a & 3) == 3)
                {
                    value = foo(value,7);
                }
                else
                {
                    value = foo(value,8);
                }
            }
        }

        chess_separator();
        jmptab = 3;
        break;

    case 8:  /**********************************************************/
        chess_separator();

        chess_separator();
        jmptab = 4;
        break;

    case 9:  /**********************************************************/
        chess_separator();

        chess_separator();
        jmptab = 5;
        break;

    case 10:  /**********************************************************/
        chess_separator();

        chess_separator();
        jmptab = 1;
        break;
    }

    value += jmptab;
    chess_report(value);
    return value;
}


int main()
{
    jmptab = 1;
    int a = 1;
    for (int i = 0; i < 100; i++)
        compander(a++);

    return 0;
}
