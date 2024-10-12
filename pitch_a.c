/* ITU-T G.729 Software Package Release 2 (November 2006) */
/*
   ITU-T G.729A Speech Coder    ANSI-C Source Code
   Version 1.1    Last modified: September 1996

   Copyright (c) 1996,
   AT&T, France Telecom, NTT, Universite de Sherbrooke
   All rights reserved.
*/

/*---------------------------------------------------------------------------*
 * Pitch related functions                                                   *
 * ~~~~~~~~~~~~~~~~~~~~~~~                                                   *
 *---------------------------------------------------------------------------*/

#include "typedef.h"
#include "basic_op.h"
#include "oper_32b.h"
#include "ld8a.h"
#include "tab_ld8a.h"

/*---------------------------------------------------------------------------*
 * Function  Pitch_ol_fast                                                   *
 * ~~~~~~~~~~~~~~~~~~~~~~~                                                   *
 * Compute the open loop pitch lag. (fast version)                           *
 *                                                                           *
 *---------------------------------------------------------------------------*/


Word16 Pitch_ol_fast(  /* output: open loop pitch lag                        */
        Word16 signal[],    /* input : signal used to compute the open loop pitch */
        /*     signal[-pit_max] to signal[-1] should be known */
        Word16   pit_max,   /* input : maximum pitch lag                          */
        Word16   L_frame    /* input : length of frame to compute pitch           */
)
{
    Word16  i, j, nf;
    Word16  max1, max2, max3;
    Word16  max_h, max_l, ener_h, ener_l;
    Word16  T1, T2, T3;
    Word16  *p;
    Word32  max, sum;

    /* Scaled signal */

    Word16 scaled_signal[L_FRAME + PIT_MAX];
    Word16 *scal_sig = &scaled_signal[pit_max];

    /*--------------------------------------------------------*
     *  Verification for risk of overflow.                    *
     *--------------------------------------------------------*/

    sum = 0;
    for (i = -pit_max; i < L_frame; i += 2)
        sum = L_mac(sum, signal[i], signal[i]);

    /*--------------------------------------------------------*
     * Scaling of input signal.                               *
     *                                                        *
     *   if sum >= 2^20 -> scal_sig[i] = signal[i]            *
     *   else             scal_sig[i] = signal[i] << 3        *
     *--------------------------------------------------------*/

    if (sum < (Word32)1048576L)  /* if sum < 2^20 */
    {
        for (i = -pit_max; i < L_frame; i++)
            scal_sig[i] = shl(signal[i], 3);
    }
    else
    {
        for (i = -pit_max; i < L_frame; i++)
            scal_sig[i] = signal[i];
    }

    /*--------------------------------------------------------------------*
     *  The pitch lag search is divided in three sections.                *
     *--------------------------------------------------------------------*/

    /* First section */

    max = MIN_32;
    T1  = 20;  /* Initialize T1 */

    for (i = 20; i < 40; i++)
    {
        sum = 0;
        for (j = 0; j < L_frame; j += 2)
            sum = L_mac(sum, scal_sig[j], scal_sig[j - i]);
        if (sum > max)
        {
            max = sum;
            T1 = i;
        }
    }

    /* Compute energy of maximum */

    sum = 1;  /* to avoid division by zero */
    for (i = 0; i < L_frame; i += 2)
        sum = L_mac(sum, scal_sig[i - T1], scal_sig[i - T1]);

    /* max1 = max / sqrt(energy) */

    sum = Inv_sqrt(sum);  /* 1/sqrt(energy), result in Q30 */
    L_Extract(max, &max_h, &max_l);
    L_Extract(sum, &ener_h, &ener_l);
    max1 = (Word16)(Mpy_32(max_h, max_l, ener_h, ener_l));  /* Convert to Word16 */

    /* Second section */

    max = MIN_32;
    T2  = 40;  /* Initialize T2 */

    for (i = 40; i < 80; i++)
    {
        sum = 0;
        for (j = 0; j < L_frame; j += 2)
            sum = L_mac(sum, scal_sig[j], scal_sig[j - i]);
        if (sum > max)
        {
            max = sum;
            T2 = i;
        }
    }

    /* Compute energy of maximum */

    sum = 1;  /* to avoid division by zero */
    for (i = 0; i < L_frame; i += 2)
        sum = L_mac(sum, scal_sig[i - T2], scal_sig[i - T2]);

    /* max2 = max / sqrt(energy) */

    sum = Inv_sqrt(sum);  /* 1/sqrt(energy), result in Q30 */
    L_Extract(max, &max_h, &max_l);
    L_Extract(sum, &ener_h, &ener_l);
    max2 = (Word16)(Mpy_32(max_h, max_l, ener_h, ener_l));  /* Convert to Word16 */

    /* Third section */

    max = MIN_32;
    T3  = 80;  /* Initialize T3 */

    for (i = 80; i < 143; i += 2)
    {
        sum = 0;
        for (j = 0; j < L_frame; j += 2)
            sum = L_mac(sum, scal_sig[j], scal_sig[j - i]);
        if (sum > max)
        {
            max = sum;
            T3 = i;
        }
    }

    /* Test around max3 */

    for (nf = -1; nf <= 1; nf++)
    {
        i = T3 + nf;
        if (i < 80 || i > 143)
            continue;
        sum = 0;
        for (j = 0; j < L_frame; j += 2)
            sum = L_mac(sum, scal_sig[j], scal_sig[j - i]);
        if (sum > max)
        {
            max = sum;
            T3 = i;
        }
    }

    /* Compute energy of maximum */

    sum = 1;  /* to avoid division by zero */
    for (i = 0; i < L_frame; i += 2)
        sum = L_mac(sum, scal_sig[i - T3], scal_sig[i - T3]);

    /* max3 = max / sqrt(energy) */

    sum = Inv_sqrt(sum);  /* 1/sqrt(energy), result in Q30 */
    L_Extract(max, &max_h, &max_l);
    L_Extract(sum, &ener_h, &ener_l);
    max3 = (Word16)(Mpy_32(max_h, max_l, ener_h, ener_l));  /* Convert to Word16 */

    /*-----------------------*
     * Test for multiple.    *
     *-----------------------*/

    /* if (abs(T2*2 - T3) < 5) */
    if (abs_s(sub(shl(T2, 1), T3)) < 5)
        max2 = add(max2, shr(max3, 2));

    /* if (abs(T2*3 - T3) < 7) */
    if (abs_s(sub(add(shl(T2, 1), T2), T3)) < 7)
        max2 = add(max2, shr(max3, 2));

    /* if (abs(T1*2 - T2) < 5) */
    if (abs_s(sub(shl(T1, 1), T2)) < 5)
        max1 = mac(max1, max2, 6554);  /* 6554 ~ 0.20 in Q15 */

    /* if (abs(T1*3 - T2) < 7) */
    if (abs_s(sub(add(shl(T1, 1), T1), T2)) < 7)
        max1 = mac(max1, max2, 6554);

    /*--------------------------------------------------------------------*
     * Compare the 3 sections maxima.                                     *
     *--------------------------------------------------------------------*/

    if (max1 < max2)
    {
        max1 = max2;
        T1 = T2;
    }
    if (max1 < max3)
    {
        T1 = T3;
    }

    return T1;
}





/*--------------------------------------------------------------------------*
 *  Function  Dot_Product()                                                 *
 *  ~~~~~~~~~~~~~~~~~~~~~~                                                  *
 *--------------------------------------------------------------------------*/

Word32 Dot_Product(      /* (o)   :Result of scalar product. */
       Word16   x[],     /* (i)   :First vector.             */
       Word16   y[],     /* (i)   :Second vector.            */
       Word16   lg       /* (i)   :Number of point.          */
)
{
  Word16 i;
  Word32 sum;

  sum = 0;
  for(i=0; i<lg; i++)
    sum = L_mac(sum, x[i], y[i]);

  return sum;
}

/*--------------------------------------------------------------------------*
 *  Function  Pitch_fr3_fast()                                              *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~                                              *
 * Fast version of the pitch close loop.                                    *
 *--------------------------------------------------------------------------*/

Word16 Pitch_fr3_fast(/* (o)     : pitch period.                          */
        Word16 exc[],       /* (i)     : excitation buffer                      */
        Word16 xn[],        /* (i)     : target vector                          */
        Word16 h[],         /* (i) Q12 : impulse response of filters.           */
        Word16 L_subfr,     /* (i)     : Length of subframe                     */
        Word16 t0_min,      /* (i)     : minimum value in the searched range.   */
        Word16 t0_max,      /* (i)     : maximum value in the searched range.   */
        Word16 i_subfr,     /* (i)     : indicator for first subframe.          */
        Word16 *pit_frac    /* (o)     : chosen fraction.                       */
)
{
    Word16 t, t0;
    Word16 Dn[L_SUBFR];
    Word16 exc_tmp[L_SUBFR];
    Word32 max, corr;

    /*-----------------------------------------------------------------*
     * Compute correlation of target vector with impulse response.     *
     *-----------------------------------------------------------------*/

    // Gọi Cor_h_X(h, xn, Dn) một lần duy nhất để tính toán Dn
    Cor_h_X(h, xn, Dn);

    /*-----------------------------------------------------------------*
     * Find maximum integer delay.                                     *
     *-----------------------------------------------------------------*/

    max = MIN_32;
    t0 = t0_min; // Đặt t0 ban đầu thành t0_min

    // Giảm bớt phép tính L_sub bằng cách so sánh trực tiếp
    for(t = t0_min; t <= t0_max; t++)
    {
        corr = Dot_Product(Dn, &exc[-t], L_subfr);
        if (corr > max) { max = corr; t0 = t; }
    }

    /*-----------------------------------------------------------------*
     * Test fractions.                                                 *
     *-----------------------------------------------------------------*/

    // Fraction 0
    Pred_lt_3(exc, t0, 0, L_subfr);
    max = Dot_Product(Dn, exc, L_subfr);
    *pit_frac = 0;

    // Nếu là subframe đầu tiên và t0 > 84 thì không cần tính phân số
    if ((i_subfr == 0) && (t0 > 84))
        return t0;

    // Lưu trữ trạng thái hiện tại của exc
    Copy(exc, exc_tmp, L_subfr);

    // Fraction -1/3
    Pred_lt_3(exc, t0, -1, L_subfr);
    corr = Dot_Product(Dn, exc, L_subfr);
    if (corr > max) {
        max = corr;
        *pit_frac = -1;
        Copy(exc, exc_tmp, L_subfr);
    }

    // Fraction +1/3
    Pred_lt_3(exc, t0, 1, L_subfr);
    corr = Dot_Product(Dn, exc, L_subfr);
    if (corr > max) {
        max = corr;
        *pit_frac = 1;
    } else {
        // Khôi phục trạng thái exc nếu phân số không cải thiện
        Copy(exc_tmp, exc, L_subfr);
    }

    return t0;
}



/*---------------------------------------------------------------------*
 * Function  G_pitch:                                                  *
 *           ~~~~~~~~                                                  *
 *---------------------------------------------------------------------*
 * Compute correlations <xn,y1> and <y1,y1> to use in gains quantizer. *
 * Also compute the gain of pitch. Result in Q14                       *
 *  if (gain < 0)  gain =0                                             *
 *  if (gain >1.2) gain =1.2                                           *
 *---------------------------------------------------------------------*/


Word16 G_pitch(      /* (o) Q14 : Gain of pitch lag saturated to 1.2       */
        Word16 xn[],       /* (i)     : Pitch target.                            */
        Word16 y1[],       /* (i)     : Filtered adaptive codebook.              */
        Word16 g_coeff[],  /* (i)     : Correlations need for gain quantization. */
        Word16 L_subfr     /* (i)     : Length of subframe.                      */
)
{
    Word16 i;
    Word16 xy, yy, exp_xy, exp_yy, gain;
    Word32 s;

    Word16 scaled_y1[L_SUBFR];

    /*-------------------------------------------------------------*
     * Thay vì chia "y1[]" cho 4 ở mỗi vòng lặp,
     * chuyển phép chia ra ngoài vòng lặp.
     *-------------------------------------------------------------*/

    for(i = 0; i < L_subfr; i++) {
        scaled_y1[i] = shr(y1[i], 2); // Tối ưu hơn khi thực hiện chỉ một phép tính chia
    }

    /*-------------------------------------------------------------*
     * Tính tích vô hướng <y1[], y1[]>
     *-------------------------------------------------------------*/

    Overflow = 0;
    s = 1;  /* Tránh trường hợp giá trị bằng 0 */

    // Thực hiện tính toán trong vòng lặp
    for(i = 0; i < L_subfr; i++) {
        s = L_mac(s, y1[i], y1[i]);
    }

    // Kiểm tra Overflow và xử lý
    if (Overflow == 0) {
        exp_yy = norm_l(s);
        yy = round(L_shl(s, exp_yy));
    } else {
        // Tránh overflow bằng cách sử dụng scaled_y1
        s = 1;
        for(i = 0; i < L_subfr; i++) {
            s = L_mac(s, scaled_y1[i], scaled_y1[i]);
        }
        exp_yy = norm_l(s);
        yy = round(L_shl(s, exp_yy));
        exp_yy = sub(exp_yy, 4); // Điều chỉnh giá trị overflow
    }

    /*-------------------------------------------------------------*
     * Tính tích vô hướng <xn[], y1[]>
     *-------------------------------------------------------------*/

    Overflow = 0;
    s = 0;

    // Sử dụng vòng lặp tính toán
    for(i = 0; i < L_subfr; i++) {
        s = L_mac(s, xn[i], y1[i]);
    }

    // Xử lý trường hợp overflow
    if (Overflow == 0) {
        exp_xy = norm_l(s);
        xy = round(L_shl(s, exp_xy));
    } else {
        s = 0;
        for(i = 0; i < L_subfr; i++) {
            s = L_mac(s, xn[i], scaled_y1[i]);
        }
        exp_xy = norm_l(s);
        xy = round(L_shl(s, exp_xy));
        exp_xy = sub(exp_xy, 2); // Điều chỉnh khi xảy ra overflow
    }

    // Cập nhật g_coeff
    g_coeff[0] = yy;
    g_coeff[1] = sub(15, exp_yy);
    g_coeff[2] = xy;
    g_coeff[3] = sub(15, exp_xy);

    /*-------------------------------------------------------------*
     * Nếu xy <= 0 thì trả về gain = 0
     *-------------------------------------------------------------*/

    if (xy <= 0) {
        g_coeff[3] = -15;   /* Điều chỉnh exp_xy về -15 */
        return 0;
    }

    /*-------------------------------------------------------------*
     * Tính gain = xy / yy
     *-------------------------------------------------------------*/

    xy = shr(xy, 1);  // Đảm bảo xy nhỏ hơn yy để tránh tràn
    gain = div_s(xy, yy);

    // Điều chỉnh gain theo exp_xy và exp_yy
    i = sub(exp_xy, exp_yy);
    gain = shr(gain, i);  // Xử lý tràn nếu gain > 1.99 ở Q14

    // Giới hạn giá trị gain không vượt quá 1.2 (tương đương 19661 ở Q14)
    if (gain > 19661) {
        gain = 19661;
    }

    return gain;
}




/*----------------------------------------------------------------------*
 *    Function Enc_lag3                                                 *
 *             ~~~~~~~~                                                 *
 *   Encoding of fractional pitch lag with 1/3 resolution.              *
 *----------------------------------------------------------------------*
 * The pitch range for the first subframe is divided as follows:        *
 *   19 1/3  to   84 2/3   resolution 1/3                               *
 *   85      to   143      resolution 1                                 *
 *                                                                      *
 * The period in the first subframe is encoded with 8 bits.             *
 * For the range with fractions:                                        *
 *   index = (T-19)*3 + frac - 1;   where T=[19..85] and frac=[-1,0,1]  *
 * and for the integer only range                                       *
 *   index = (T - 85) + 197;        where T=[86..143]                   *
 *----------------------------------------------------------------------*
 * For the second subframe a resolution of 1/3 is always used, and the  *
 * search range is relative to the lag in the first subframe.           *
 * If t0 is the lag in the first subframe then                          *
 *  t_min=t0-5   and  t_max=t0+4   and  the range is given by           *
 *       t_min - 2/3   to  t_max + 2/3                                  *
 *                                                                      *
 * The period in the 2nd subframe is encoded with 5 bits:               *
 *   index = (T-(t_min-1))*3 + frac - 1;    where T[t_min-1 .. t_max+1] *
 *----------------------------------------------------------------------*/


Word16 Enc_lag3(     /* output: Return index of encoding */
        Word16 T0,         /* input : Pitch delay              */
        Word16 T0_frac,    /* input : Fractional pitch delay   */
        Word16 *T0_min,    /* in/out: Minimum search delay     */
        Word16 *T0_max,    /* in/out: Maximum search delay     */
        Word16 pit_min,    /* input : Minimum pitch delay      */
        Word16 pit_max,    /* input : Maximum pitch delay      */
        Word16 pit_flag    /* input : Flag for 1st subframe    */
)
{
    Word16 index, i;

    if (pit_flag == 0)   /* if 1st subframe */
    {
        /*-------------------------------------------------------------*
         * encode pitch delay (with fraction)
         * Tối ưu hóa phép tính thay vì thực hiện add(add(T0, T0), T0)
         *-------------------------------------------------------------*/

        if (T0 <= 85)
        {
            /* index = t0*3 - 58 + t0_frac */
            i = T0 * 3;  // Tránh sử dụng nhiều phép cộng
            index = i - 58 + T0_frac;  // Gom các phép cộng và trừ lại thành một
        }
        else {
            index = T0 + 112;  // Tối ưu hóa việc dùng add
        }

        /*-------------------------------------------------------------*
         * find T0_min and T0_max for second subframe
         * Tránh việc gọi hàm sub hoặc add quá nhiều lần không cần thiết
         *-------------------------------------------------------------*/

        *T0_min = T0 - 5;
        if (*T0_min < pit_min)
        {
            *T0_min = pit_min;
        }

        *T0_max = *T0_min + 9;
        if (*T0_max > pit_max)
        {
            *T0_max = pit_max;
            *T0_min = *T0_max - 9;
        }
    }
    else      /* if second subframe */
    {
        /*-------------------------------------------------------------*
         * encode pitch delay for second subframe
         * Tránh sử dụng nhiều phép cộng lồng nhau, gom lại thành một phép tính duy nhất
         *-------------------------------------------------------------*/

        i = (T0 - *T0_min) * 3;  // Tránh sử dụng add(add(i, i), i)
        index = i + 2 + T0_frac;  // Gom các phép cộng lại
    }

    return index;
}


