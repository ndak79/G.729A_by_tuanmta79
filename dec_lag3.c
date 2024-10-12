/* ITU-T G.729 Software Package Release 2 (November 2006) */
/*
   ITU-T G.729A Speech Coder    ANSI-C Source Code
   Version 1.1    Last modified: September 1996

   Copyright (c) 1996,
   AT&T, France Telecom, NTT, Universite de Sherbrooke
   All rights reserved.
*/

/*------------------------------------------------------------------------*
 *    Function Dec_lag3                                                   *
 *             ~~~~~~~~                                                   *
 *   Decoding of fractional pitch lag with 1/3 resolution.                *
 * See "Enc_lag3.c" for more details about the encoding procedure.        *
 *------------------------------------------------------------------------*/

#include "typedef.h"
#include "basic_op.h"
#include "ld8a.h"

void Dec_lag3(
        Word16 index,       /* input : received pitch index           */
        Word16 pit_min,     /* input : minimum pitch lag              */
        Word16 pit_max,     /* input : maximum pitch lag              */
        Word16 i_subfr,     /* input : subframe flag                  */
        Word16 *T0,         /* output: integer part of pitch lag      */
        Word16 *T0_frac     /* output: fractional part of pitch lag   */
)
{
    Word16 i, temp, T0_min, T0_max;

    if (i_subfr == 0)  /* Nếu là subframe đầu tiên */
    {
        if (sub(index, 197) < 0)
        {
            /* Tính toán *T0 và *T0_frac cho subframe đầu tiên */

            *T0 = add(mult(add(index, 2), 10923), 19);

            temp = add(*T0, *T0);  /* temp = *T0 * 2 */
            temp = add(temp, *T0); /* temp = *T0 * 3 */
            *T0_frac = add(sub(index, temp), 58);
        }
        else
        {
            *T0 = sub(index, 112);
            *T0_frac = 0;
        }
    }
    else  /* Nếu là subframe thứ hai */
    {
        /* Tìm T0_min và T0_max cho subframe thứ hai */

        T0_min = sub(*T0, 5);
        if (sub(T0_min, pit_min) < 0)
        {
            T0_min = pit_min;
        }

        T0_max = add(T0_min, 9);
        if (sub(T0_max, pit_max) > 0)
        {
            T0_max = pit_max;
            T0_min = sub(T0_max, 9);
        }

        /* Tính toán *T0 và *T0_frac cho subframe thứ hai */

        i = sub(mult(add(index, 2), 10923), 1);
        *T0 = add(i, T0_min);

        temp = add(i, i);  /* temp = i * 2 */
        temp = add(temp, i); /* temp = i * 3 */
        *T0_frac = sub(sub(index, 2), temp);
    }

    return;
}



