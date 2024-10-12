/* ITU-T G.729 Software Package Release 2 (November 2006) */
/*
   ITU-T G.729A Speech Coder    ANSI-C Source Code
   Version 1.1    Last modified: September 1996

   Copyright (c) 1996,
   AT&T, France Telecom, NTT, Universite de Sherbrooke
   All rights reserved.
*/

/*-------------------------------------------------------------------*
 * Function  Convolve:                                               *
 *           ~~~~~~~~~                                               *
 *-------------------------------------------------------------------*
 * Perform the convolution between two vectors x[] and h[] and       *
 * write the result in the vector y[].                               *
 * All vectors are of length N.                                      *
 *-------------------------------------------------------------------*/

#include "typedef.h"
#include "basic_op.h"
#include "ld8a.h"

void Convolve(
  Word16 x[],      /* (i)     : input vector                           */
  Word16 h[],      /* (i) Q12 : impulse response                       */
  Word16 y[],      /* (o)     : output vector                          */
  Word16 L         /* (i)     : vector size                            */
)
{
   Word16 i, n;
   Word32 s;

   for (n = 0; n < L; n++)
   {
     s = 0;
     for (i = 0; i <= n; i++)
       s = L_mac(s, x[i], h[n-i]);

     s    = L_shl(s, 3);                   /* h is in Q12 and saturation */
     y[n] = (Word16)(s >> 16);
   }

   return;
}

/*-----------------------------------------------------*
 * procedure Syn_filt:                                 *
 *           ~~~~~~~~                                  *
 * Do the synthesis filtering 1/A(z).                  *
 *-----------------------------------------------------*/


void Syn_filt(
        Word16 a[],     /* (i) Q12 : a[m+1] prediction coefficients   (m=10)  */
        Word16 x[],     /* (i)     : input signal                             */
        Word16 y[],     /* (o)     : output signal                            */
        Word16 lg,      /* (i)     : size of filtering                        */
        Word16 mem[],   /* (i/o)   : memory associated with this filtering.   */
        Word16 update   /* (i)     : 0=no update, 1=update of memory.         */
)
{
    Word16 i, j;
    Word32 s;
    Word16 tmp[100];  /* This is usually done by memory allocation (lg+M) */
    Word16 *yy = tmp; /* Trực tiếp khởi tạo yy bằng tmp để tránh việc gán sau này */

    /* Copy mem[] to yy[] */

    for(i = 0; i < M; i++)
    {
        yy[i] = mem[i];  /* Sử dụng chỉ mục thay vì tăng con trỏ để dễ tối ưu hơn */
    }

    /* Do the filtering. */

    for (i = 0; i < lg; i++)
    {
        s = L_mult(x[i], a[0]);  /* Tính s ban đầu */
        for (j = 1; j <= M; j++)
            s = L_msu(s, a[j], yy[i+M-j]);  /* Truy cập trực tiếp tới phần tử thay vì dùng con trỏ */

        s = L_shl(s, 3);
        yy[i+M] = round(s);  /* Gán giá trị trực tiếp vào tmp */
    }

    /* Copy filtered signal to y[] */

    for(i = 0; i < lg; i++)
    {
        y[i] = yy[i+M];  /* Truy cập trực tiếp vào yy */
    }

    /* Update of memory if update==1 */

    if(update != 0)
    {
        for (i = 0; i < M; i++)
        {
            mem[i] = yy[lg + i];  /* Sử dụng yy để tránh việc truy cập qua y */
        }
    }

    return;
}


/*-----------------------------------------------------------------------*
 * procedure Residu:                                                     *
 *           ~~~~~~                                                      *
 * Compute the LPC residual  by filtering the input speech through A(z)  *
 *-----------------------------------------------------------------------*/

void Residu(
  Word16 a[],    /* (i) Q12 : prediction coefficients                     */
  Word16 x[],    /* (i)     : speech (values x[-m..-1] are needed         */
  Word16 y[],    /* (o)     : residual signal                             */
  Word16 lg      /* (i)     : size of filtering                           */
)
{
  Word16 i, j;
  Word32 s;

  for (i = 0; i < lg; i++)
  {
    s = L_mult(x[i], a[0]);
    for (j = 1; j <= M; j++)
      s = L_mac(s, a[j], x[i-j]);

    s = L_shl(s, 3);
    y[i] = round(s);
  }
  return;
}

