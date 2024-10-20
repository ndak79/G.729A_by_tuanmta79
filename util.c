/* ITU-T G.729 Software Package Release 2 (November 2006) */
/*
   ITU-T G.729A Speech Coder    ANSI-C Source Code
   Version 1.1    Last modified: September 1996

   Copyright (c) 1996,
   AT&T, France Telecom, NTT, Universite de Sherbrooke
   All rights reserved.
*/

/*-------------------------------------------------------------------*
 * Function  Set zero()                                              *
 *           ~~~~~~~~~~                                              *
 * Set vector x[] to zero                                            *
 *-------------------------------------------------------------------*/

#include "typedef.h"
#include "basic_op.h"
#include "ld8a.h"

#include <string.h>  // Thư viện chứa memset và memcpy

void Set_zero(
        Word16 x[],       /* (o)    : vector to clear     */
        Word16 L          /* (i)    : length of vector    */
)
{
    // Sử dụng memset để đặt tất cả phần tử trong mảng về 0
    memset(x, 0, L * sizeof(Word16));
}

/*-------------------------------------------------------------------*
 * Function  Copy:                                                   *
 *           ~~~~~                                                   *
 * Copy vector x[] to y[]                                            *
 *-------------------------------------------------------------------*/

void Copy(
        Word16 x[],      /* (i)   : input vector   */
        Word16 y[],      /* (o)   : output vector  */
        Word16 L         /* (i)   : vector length  */
)
{
    // Sử dụng memcpy để sao chép mảng x sang y
    memcpy(y, x, L * sizeof(Word16));
}


/* Random generator  */

Word16 Random()
{
  static Word16 seed = 21845;

  /* seed = seed*31821 + 13849; */
  seed = (Word16)(L_add(L_shr(L_mult(seed, 31821), 1), 13849L));

  return(seed);
}

