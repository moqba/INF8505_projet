/*
-- Test sieve of eratosthenes (computing prime numbers).
-- [based on "Doug's shootout" http://www.bagley.org/~doug]
--
-- Copyright (c) 2014-2016 Synopsys, Inc. This Synopsys processor model
-- captures an ASIP Designer Design Technique. The model and all associated
-- documentation are proprietary to Synopsys, Inc. and may only be used
-- pursuant to the terms and conditions of a written license agreement with
-- Synopsys, Inc.  All other use, reproduction, modification, or distribution
-- of the Synopsys processor model or the associated  documentation is
-- strictly prohibited.
*/


#define N 128

int main()
{
    chess_message( "// prime numbers:" );
    static int flags[N+1];
    int count = 0;

    for (int i = 2; i <= N; i++) flags[i] = 1;

    for (int i = 2; i <= N; i++) {
        if (flags[i]) {
            // i is prime, its multiples are not
            chess_report(i);
            count++;
            for (int k = i + i; k<= N; k += i) flags[k] = 0;
        }
    }

    chess_message( "// count primes upto " << N );
    chess_report(count);

    return 0;
}
