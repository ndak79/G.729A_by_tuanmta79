
/*___________________________________________________________________________
 |                                                                           |
 | Basics operators.                                                         |
 |___________________________________________________________________________|
*/

/*___________________________________________________________________________
 |                                                                           |
 |   Include-Files                                                           |
 |___________________________________________________________________________|
*/

#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#include "basic_op.h"

/*___________________________________________________________________________
 |                                                                           |
 |   Local Functions                                                         |
 |___________________________________________________________________________|
*/

/*___________________________________________________________________________
 |                                                                           |
 |   Constants and Globals                                                   |
 |___________________________________________________________________________|
*/
Flag Overflow =0;
Flag Carry =0;

/*___________________________________________________________________________
 |                                                                           |
 |   Functions                                                               |
 |___________________________________________________________________________|
*/

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : add                                                     |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |    Performs the addition (var1+var2) with overflow control and saturation;|
 |    the 16 bit result is set at +32767 when overflow occurs or at -32768   |
 |    when underflow occurs.                                                 |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
 |___________________________________________________________________________|
*/

Word16 add(Word16 var1, Word16 var2)
{
    // Tính tổng của var1 và var2 trong 32-bit
    Word32 L_sum = (Word32)var1 + (Word32)var2;

    // Kiểm tra tràn số và giới hạn phạm vi 16-bit bằng toán tử ba ngôi
    Word16 var_out = (L_sum > 0x00007fffL) ? (Overflow = 1, MAX_16) :
                     (L_sum < (Word32)0xffff8000L) ? (Overflow = 1, MIN_16) :
                     (Overflow = 0, (Word16)L_sum);

    return var_out;
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : sub                                                     |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |    Performs the subtraction (var1+var2) with overflow control and satu-   |
 |    ration; the 16 bit result is set at +32767 when overflow occurs or at  |
 |    -32768 when underflow occurs.                                          |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
 |___________________________________________________________________________|
*/

Word16 sub(Word16 var1, Word16 var2)
{
    // Tính hiệu của var1 và var2 trong phạm vi 32-bit
    Word32 L_diff = (Word32)var1 - (Word32)var2;

    // Kiểm tra tràn số và giới hạn phạm vi 16-bit bằng toán tử ba ngôi
    Word16 var_out = (L_diff > 0x00007fffL) ? (Overflow = 1, MAX_16) :
                     (L_diff < (Word32)0xffff8000L) ? (Overflow = 1, MIN_16) :
                     (Overflow = 0, (Word16)L_diff);

    return var_out;
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : abs_s                                                   |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |    Absolute value of var1; abs_s(-32768) = 32767.                         |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0x0000 0000 <= var_out <= 0x0000 7fff.                |
 |___________________________________________________________________________|
*/

Word16 abs_s(Word16 var1)
{
    // Kiểm tra nếu var1 là giá trị tối thiểu (trường hợp đặc biệt)
    if (var1 == (Word16)0x8000)
        return MAX_16;

    // Sử dụng toán tử ba ngôi để trả về giá trị tuyệt đối
    return (var1 < 0) ? -var1 : var1;
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : shl                                                     |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Arithmetically shift the 16 bit input var1 left var2 positions.Zero fill|
 |   the var2 LSB of the result. If var2 is negative, arithmetically shift   |
 |   var1 right by -var2 with sign extension. Saturate the result in case of |
 |   underflows or overflows.                                                |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
 |___________________________________________________________________________|
*/

Word16 shl(Word16 var1, Word16 var2)
{
    Word32 resultat;

    // Nếu var2 < 0, thực hiện phép dịch phải
    if (var2 < 0)
    {
        // Thực hiện phép dịch phải trực tiếp thay vì gọi hàm shr
        return (var2 < -15) ? (var1 < 0 ? -1 : 0) : (Word16)(var1 >> -var2);
    }

    // Nếu var2 >= 0, thực hiện phép dịch trái
    resultat = (Word32)var1 << var2;

    // Kiểm tra điều kiện tràn số
    if ((var2 > 15 && var1 != 0) || (resultat != (Word32)((Word16)resultat)))
    {
        Overflow = 1;
        return (var1 > 0) ? MAX_16 : MIN_16;
    }

    // Nếu không tràn số, trả về kết quả
    return (Word16)resultat;
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : shr                                                     |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Arithmetically shift the 16 bit input var1 right var2 positions with    |
 |   sign extension. If var2 is negative, arithmetically shift var1 left by  |
 |   -var2 with sign extension. Saturate the result in case of underflows or |
 |   overflows.                                                              |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
 |___________________________________________________________________________|
*/

Word16 shr(Word16 var1, Word16 var2)
{
    // Nếu var2 < 0, thực hiện phép dịch trái (shl)
    if (var2 < 0)
    {
        return shl(var1, -var2);
    }

    // Nếu var2 >= 15, trả về -1 nếu var1 âm, 0 nếu var1 dương
    if (var2 >= 15)
    {
        return (var1 < 0) ? (Word16)(-1) : (Word16)0;
    }

    // Xử lý dịch phải theo giá trị của var1
    return (var1 < 0) ? ~((~var1) >> var2) : var1 >> var2;
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : mult                                                    |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |    Performs the multiplication of var1 by var2 and gives a 16 bit result  |
 |    which is scaled i.e.:                                                  |
 |             mult(var1,var2) = shr((var1 times var2),15) and               |
 |             mult(-32768,-32768) = 32767.                                  |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
 |___________________________________________________________________________|
*/

Word16 mult(Word16 var1, Word16 var2)
{
    // Tính tích của hai biến 16-bit trong phạm vi 32-bit
    Word32 L_produit = (Word32)var1 * (Word32)var2;

    // Dịch phải 15 bit để đưa kết quả về phạm vi 16-bit
    L_produit >>= 15;

    // Kiểm tra và xử lý tràn số (bit âm)
    L_produit = (L_produit & (Word32)0x00010000L) ? (L_produit | (Word32)0xffff0000L) : L_produit;

    // Kiểm tra tràn số và giới hạn phạm vi 16-bit
    Word16 var_out = (L_produit > 0X00007fffL) ? (Overflow = 1, MAX_16) :
                     (L_produit < (Word32)0xffff8000L) ? (Overflow = 1, MIN_16) :
                     (Overflow = 0, (Word16)L_produit);

    return var_out;
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : L_mult                                                  |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   L_mult is the 32 bit result of the multiplication of var1 times var2    |
 |   with one shift left i.e.:                                               |
 |        L_mult(var1,var2) = shl((var1 times var2),1) and                   |
 |        L_mult(-32768,-32768) = 2147483647.                                |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    L_var_out                                                              |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
 |___________________________________________________________________________|
*/

Word32 L_mult(Word16 var1, Word16 var2)
{
    // Tính tích hai biến 16 bit trong 32 bit
    Word32 L_var_out = (Word32)var1 * (Word32)var2;

    // Kiểm tra xem L_var_out có bằng 0x40000000 không
    if (L_var_out == (Word32)0x40000000L)
    {
        Overflow = 1; // Đánh dấu có tràn số
        return MAX_32; // Trả về giá trị tối đa
    }

    // Nhân đôi kết quả nếu không tràn số
    return L_var_out << 1; // Dịch trái một bit (tương đương nhân 2)
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : negate                                                  |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Negate var1 with saturation, saturate in the case where input is -32768:|
 |                negate(var1) = sub(0,var1).                                |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
 |___________________________________________________________________________|
*/

Word16 negate(Word16 var1)
{
    // Trả về giá trị âm của var1 hoặc MAX_16 nếu var1 là MIN_16
    return (var1 == MIN_16) ? MAX_16 : -var1;
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : extract_h                                               |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Return the 16 MSB of L_var1.                                            |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    L_var1                                                                 |
 |             32 bit long signed integer (Word32 ) whose value falls in the |
 |             range : 0x8000 0000 <= L_var1 <= 0x7fff ffff.                 |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
 |___________________________________________________________________________|
*/

Word16 extract_h(Word32 L_var1)
  {
   Word16 var_out;

   var_out = (Word16) (L_var1 >> 16);
   return(var_out);
  }

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : round                                                   |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Round the lower 16 bits of the 32 bit input number into its MS 16 bits  |
 |   with saturation. Shift the resulting bits right by 16 and return the 16 |
 |   bit number:                                                             |
 |               round(L_var1) = extract_h(L_add(L_var1,32768))              |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    L_var1                                                                 |
 |             32 bit long signed integer (Word32 ) whose value falls in the |
 |             range : 0x8000 0000 <= L_var1 <= 0x7fff ffff.                 |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
 |___________________________________________________________________________|
*/

Word16 round(Word32 L_var1)
  {
   Word16 var_out;
   Word32 L_arrondi;

   L_arrondi = L_add(L_var1, (Word32)0x00008000);
   var_out = (Word16)(L_arrondi >> 16);
   return(var_out);
  }

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : L_mac                                                   |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Multiply var1 by var2 and shift the result left by 1. Add the 32 bit    |
 |   result to L_var3 with saturation, return a 32 bit result:               |
 |        L_mac(L_var3,var1,var2) = L_add(L_var3,(L_mult(var1,var2)).        |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    L_var3   32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    L_var_out                                                              |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
 |___________________________________________________________________________|

 Word32 L_mac(Word32 L_var3, Word16 var1, Word16 var2)
{
    // Tính tích của var1 và var2, sau đó cộng vào L_var3
    return L_add(L_var3, L_mult(var1, var2));
}*/

Word32 L_mac(Word32 L_var3, Word16 var1, Word16 var2)
{
    // Tính tích của var1 và var2 trong 32-bit
    Word32 L_mult_out = (Word32)var1 * (Word32)var2;

    // Kiểm tra tràn số trong phép nhân
    if (L_mult_out == (Word32)0x40000000L)
    {
        Overflow = 1; // Đánh dấu có tràn số
        L_mult_out = MAX_32;
    }
    else
    {
        // Nhân đôi kết quả nếu không tràn
        L_mult_out <<= 1;
    }

    // Tính tổng của L_var3 và kết quả nhân
    Word32 L_var_out = L_var3 + L_mult_out;

    // Kiểm tra tràn số trong phép cộng
    if (((L_var3 ^ L_mult_out) & MIN_32) == 0)
    {
        if ((L_var_out ^ L_var3) & MIN_32)
        {
            L_var_out = (L_var3 < 0) ? MIN_32 : MAX_32;
            Overflow = 1;
        }
    }

    return L_var_out;
}

Word16 mac(Word16 L_var3, Word16 var1, Word16 var2)
{
    // Tính tích của var1 và var2 trong 32-bit
    Word32 L_produit = (Word32)var1 * (Word32)var2;

    // Dịch phải 15 bit để đưa kết quả về phạm vi 16-bit
    L_produit >>= 15;

    // Kiểm tra tràn số và xử lý bit âm
    L_produit = (L_produit & (Word32)0x00010000L) ? (L_produit | (Word32)0xffff0000L) : L_produit;

    // Thêm var3 vào kết quả và kiểm tra giới hạn phạm vi 16-bit
    Word32 L_result = (Word32)L_var3 + L_produit;

    // Xử lý sature
    Word16 var_out;
    var_out = (L_result > 0x00007fffL) ? (Overflow = 1, MAX_16) :
              (L_result < (Word32)0xffff8000L) ? (Overflow = 1, MIN_16) :
              (Overflow = 0, (Word16)L_result);

    return var_out;
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : L_msu                                                   |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Multiply var1 by var2 and shift the result left by 1. Subtract the 32   |
 |   bit result to L_var3 with saturation, return a 32 bit result:           |
 |        L_msu(L_var3,var1,var2) = L_sub(L_var3,(L_mult(var1,var2)).        |
 |                                                                           |
 |   Complexity weight : 1                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    L_var3   32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    L_var_out                                                              |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
 |___________________________________________________________________________|
*/

/*Word32 L_msu(Word32 L_var3, Word16 var1, Word16 var2)
{
    // Tính tích của var1 và var2, sau đó trừ từ L_var3
    return L_sub(L_var3, L_mult(var1, var2));
}*/

Word32 L_msu(Word32 L_var3, Word16 var1, Word16 var2)
{
    Word32 L_var_out;
    Word32 product;

    // Tính tích của var1 và var2 thành số 32-bit
    product = (Word32)var1 * (Word32)var2;

    // Kiểm tra xem product có bằng 0x40000000 không
    if (product == (Word32)0x40000000L)
    {
        Overflow = 1; // Đánh dấu có tràn số
        product = MAX_32; // Trả về giá trị tối đa
    }
    else
    {
        product = product << 1; // Nhân đôi kết quả nếu không tràn số
    }

    // Tính L_var_out = L_var3 - product
    L_var_out = L_var3 - product;

    // Kiểm tra tràn số khi thực hiện phép trừ
    if (((L_var3 ^ product) & MIN_32) != 0)
    {
        if ((L_var_out ^ L_var3) & MIN_32)
        {
            L_var_out = (L_var3 < 0L) ? MIN_32 : MAX_32;
            Overflow = 1;
        }
    }

    return L_var_out;
}


Word32 L_add(Word32 L_var1, Word32 L_var2)
  {
   Word32 L_var_out = L_var1 + L_var2;

   if (((L_var1 ^ L_var2) & MIN_32) == 0)
     {
      if ((L_var_out ^ L_var1) & MIN_32)
        {
         L_var_out = (L_var1 < 0) ? MIN_32 : MAX_32;
         Overflow = 1;
        }
     }
   return(L_var_out);
  }

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : L_sub                                                   |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   32 bits subtraction of the two 32 bits variables (L_var1-L_var2) with   |
 |   overflow control and saturation; the result is set at +214783647 when   |
 |   overflow occurs or at -214783648 when underflow occurs.                 |
 |                                                                           |
 |   Complexity weight : 2                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    L_var1   32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
 |                                                                           |
 |    L_var2   32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    L_var_out                                                              |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
 |___________________________________________________________________________|
*/

Word32 L_sub(Word32 L_var1, Word32 L_var2)
  {
   Word32 L_var_out = L_var1 - L_var2;

   if (((L_var1 ^ L_var2) & MIN_32) != 0)
     {
      if ((L_var_out ^ L_var1) & MIN_32)
        {
         L_var_out = (L_var1 < 0L) ? MIN_32 : MAX_32;
         Overflow = 1;
        }
     }
   return(L_var_out);
  }

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : L_negate                                                |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Negate the 32 bit variable L_var1 with saturation; saturate in the case |
 |   where input is -2147483648 (0x8000 0000).                               |
 |                                                                           |
 |   Complexity weight : 2                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    L_var1   32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    L_var_out                                                              |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
 |___________________________________________________________________________|
*/

Word32 L_negate(Word32 L_var1)
{
    // Trả về MAX_32 nếu L_var1 là MIN_32, ngược lại trả về -L_var1
    return (L_var1 == MIN_32) ? MAX_32 : -L_var1;
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : mult_r                                                  |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Same as mult with rounding, i.e.:                                       |
 |     mult_r(var1,var2) = shr(((var1*var2) + 16384),15) and                 |
 |     mult_r(-32768,-32768) = 32767.                                        |
 |                                                                           |
 |   Complexity weight : 2                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
 |___________________________________________________________________________|
*/

Word16 mult_r(Word16 var1, Word16 var2)
{
    // Thực hiện phép nhân, cộng để làm tròn và dịch phải 15 bit
    Word32 L_produit_arr = ((Word32)var1 * (Word32)var2 + 0x00004000L) >> 15;

    // Kiểm tra và xử lý dấu âm
    L_produit_arr = (L_produit_arr & 0x00010000L) ? (L_produit_arr | 0xffff0000L) : L_produit_arr;

    // Kiểm tra tràn số và giới hạn kết quả trong phạm vi 16-bit
    Word16 var_out = (L_produit_arr > 0X00007fffL) ? (Overflow = 1, MAX_16) :
                     (L_produit_arr < (Word32)0xffff8000L) ? (Overflow = 1, MIN_16) :
                     (Overflow = 0, (Word16)L_produit_arr);

    return var_out;
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : L_shl                                                   |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Arithmetically shift the 32 bit input L_var1 left var2 positions. Zero  |
 |   fill the var2 LSB of the result. If var2 is negative, L_var1 right by   |
 |   -var2 arithmetically shift with sign extension. Saturate the result in  |
 |   case of underflows or overflows.                                        |
 |                                                                           |
 |   Complexity weight : 2                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    L_var1   32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    L_var_out                                                              |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
 |___________________________________________________________________________|
*/

Word32 L_shl(Word32 L_var1, Word16 var2)
{
    // Nếu var2 <= 0, ta chuyển sang xử lý dịch phải
    if (var2 <= 0) {
        var2 = -var2;
        // Kiểm tra nếu dịch phải >= 31 thì trả về -1 cho số âm, 0 cho số dương
        if (var2 >= 31) {
            return (L_var1 < 0L) ? -1 : 0;
        }
        // Xử lý dịch phải cho số âm và dương
        if (L_var1 < 0) {
            return ~((~L_var1) >> var2);
        }
        return L_var1 >> var2;
    }

    // Kiểm tra tràn số trước khi dịch trái
    if (var2 >= 31 || L_var1 > (0x7FFFFFFF >> var2) || L_var1 < (Word32)(0x80000000 >> var2)) {
        Overflow = 1;
        return (L_var1 > 0) ? MAX_32 : MIN_32;
    }

    // Dịch trái trực tiếp var2 bit
    return L_var1 << var2;
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : L_shr                                                   |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Arithmetically shift the 32 bit input L_var1 right var2 positions with  |
 |   sign extension. If var2 is negative, arithmetically shift L_var1 left   |
 |   by -var2 and zero fill the var2 LSB of the result. Saturate the result  |
 |   in case of underflows or overflows.                                     |
 |                                                                           |
 |   Complexity weight : 2                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    L_var1   32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    L_var_out                                                              |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
 |___________________________________________________________________________|
*/

Word32 L_shr(Word32 L_var1, Word16 var2)
{
    // Nếu var2 < 0, thực hiện dịch trái thay vì gọi L_shl
    if (var2 < 0) {
        var2 = -var2;

        // Kiểm tra tràn trước khi dịch trái
        if (var2 >= 31 || L_var1 > (0x7FFFFFFF >> var2) || L_var1 < (Word32)(0x80000000 >> var2)) {
            Overflow = 1;
            return (L_var1 > 0) ? MAX_32 : MIN_32;
        }

        // Dịch trái trực tiếp var2 bit
        return L_var1 << var2;
    }

    // Nếu var2 >= 31, trả về -1 cho số âm, 0 cho số dương
    if (var2 >= 31) {
        return (L_var1 < 0L) ? -1 : 0;
    }

    // Dịch phải trực tiếp var2 bit cho số âm và dương
    if (L_var1 < 0) {
        return ~((~L_var1) >> var2);  // Xử lý số âm
    }

    return L_var1 >> var2;  // Xử lý số dương
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : L_shr_r                                                 |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Same as L_shr(L_var1,var2)but with rounding. Saturate the result in case|
 |   of underflows or overflows :                                            |
 |    If var2 is greater than zero :                                         |
 |       L_shr_r(var1,var2) = L_shr(L_add(L_var1,2**(var2-1)),var2)          |
 |    If var2 is less than zero :                                            |
 |       L_shr_r(var1,var2) = L_shr(L_var1,var2).                            |
 |                                                                           |
 |   Complexity weight : 3                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    L_var1                                                                 |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= var1 <= 0x7fff ffff.                   |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    L_var_out                                                              |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= var_out <= 0x7fff ffff.                |
 |___________________________________________________________________________|
*/

Word32 L_shr_r(Word32 L_var1, Word16 var2)
{
    if (var2 > 31) {
        return 0;  // Nếu var2 > 31, trả về 0 ngay lập tức
    }

    Word32 L_var_out = L_shr(L_var1, var2);

    if (var2 > 0 && (L_var1 & ((Word32)1 << (var2 - 1))) != 0) {
        L_var_out++;  // Làm tròn kết quả nếu bit cần làm tròn được bật
    }

    return L_var_out;
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : L_abs                                                   |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |    Absolute value of L_var1; Saturate in case where the input is          |
 |                                                               -214783648  |
 |                                                                           |
 |   Complexity weight : 3                                                   |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    L_var1                                                                 |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= var1 <= 0x7fff ffff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    L_var_out                                                              |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x0000 0000 <= var_out <= 0x7fff ffff.                |
 |___________________________________________________________________________|
*/

Word32 L_abs(Word32 L_var1)
{
    if (L_var1 == MIN_32) {
        return MAX_32;  // Nếu L_var1 là giá trị nhỏ nhất, trả về giá trị lớn nhất
    }

    return (L_var1 < 0) ? -L_var1 : L_var1;  // Trả về giá trị tuyệt đối
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : norm_s                                                  |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Produces the number of left shift needed to normalize the 16 bit varia- |
 |   ble var1 for positive values on the interval with minimum of 16384 and  |
 |   maximum of 32767, and for negative values on the interval with minimum  |
 |   of -32768 and maximum of -16384; in order to normalize the result, the  |
 |   following operation must be done :                                      |
 |                    norm_var1 = shl(var1,norm_s(var1)).                    |
 |                                                                           |
 |   Complexity weight : 15                                                  |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0x0000 0000 <= var_out <= 0x0000 000f.                |
 |___________________________________________________________________________|
*/

Word16 norm_s(Word16 var1)
{
    if (var1 == 0) {
        return 0;  // Nếu var1 là 0, trả về 0 ngay lập tức
    }

    if (var1 == (Word16)0xffff) {
        return 15;  // Nếu var1 là giá trị cực đại của Word16, trả về 15
    }

    if (var1 < 0) {
        var1 = ~var1;  // Lấy giá trị tuyệt đối nếu var1 âm
    }

    Word16 var_out = 0;
    while (var1 < 0x4000) {
        var1 <<= 1;  // Dịch trái để tìm số bit cần thiết
        var_out++;   // Tăng giá trị var_out cho mỗi lần dịch
    }

    return var_out;  // Trả về số bit đã dịch
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : norm_l                                                  |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Produces the number of left shift needed to normalize the 32 bit varia- |
 |   ble l_var1 for positive values on the interval with minimum of          |
 |   1073741824 and maximum of 2147483647, and for negative values on the in-|
 |   terval with minimum of -2147483648 and maximum of -1073741824; in order |
 |   to normalize the result, the following operation must be done :         |
 |                   norm_L_var1 = L_shl(L_var1,norm_l(L_var1)).             |
 |                                                                           |
 |   Complexity weight : 30                                                  |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    L_var1                                                                 |
 |             32 bit long signed integer (Word32) whose value falls in the  |
 |             range : 0x8000 0000 <= var1 <= 0x7fff ffff.                   |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0x0000 0000 <= var_out <= 0x0000 001f.                |
 |___________________________________________________________________________|
*/

Word16 norm_l(Word32 L_var1)
{
    if (L_var1 == 0) {
        return 0;  // Nếu L_var1 là 0, trả về 0 ngay lập tức
    }

    if (L_var1 == (Word32)0xffffffffL) {
        return 31;  // Nếu L_var1 là giá trị cực đại của Word32, trả về 31
    }

    if (L_var1 < 0) {
        L_var1 = ~L_var1;  // Lấy giá trị tuyệt đối nếu L_var1 âm
    }

    Word16 var_out = 0;
    while (L_var1 < (Word32)0x40000000L) {
        L_var1 <<= 1;  // Dịch trái để tìm số bit cần thiết
        var_out++;     // Tăng giá trị var_out cho mỗi lần dịch
    }

    return var_out;  // Trả về số bit đã dịch
}

/*___________________________________________________________________________
 |                                                                           |
 |   Function Name : div_s                                                   |
 |                                                                           |
 |   Purpose :                                                               |
 |                                                                           |
 |   Produces a result which is the fractional  integer division of var1 by  |
 |   var2; var1 and var2 must be positive and var2 must be greater or equal  |
 |   to var1; the result is positive (leading bit equal to 0) and truncated  |
 |   to 16 bits.                                                             |
 |   If var1 = var2 then div(var1,var2) = 32767.                             |
 |                                                                           |
 |   Complexity weight : 18                                                  |
 |                                                                           |
 |   Inputs :                                                                |
 |                                                                           |
 |    var1                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0x0000 0000 <= var1 <= var2 and var2 != 0.            |
 |                                                                           |
 |    var2                                                                   |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : var1 <= var2 <= 0x0000 7fff and var2 != 0.            |
 |                                                                           |
 |   Outputs :                                                               |
 |                                                                           |
 |    none                                                                   |
 |                                                                           |
 |   Return Value :                                                          |
 |                                                                           |
 |    var_out                                                                |
 |             16 bit short signed integer (Word16) whose value falls in the |
 |             range : 0x0000 0000 <= var_out <= 0x0000 7fff.                |
 |             It's a Q15 value (point between b15 and b14).                 |
 |___________________________________________________________________________|
*/

Word16 div_s(Word16 var1, Word16 var2)
{
    Word16 var_out = 0;
    Word32 L_num;
    Word32 L_denom;

    // Kiểm tra điều kiện chia cho 0 trước tiên để tránh lỗi chia cho 0
    if (var2 == 0)
    {
        printf("Division by 0, Fatal error \n");
        exit(0);
    }

    // Kiểm tra điều kiện đầu vào không hợp lệ
    if ((var1 > var2) || (var1 < 0) || (var2 < 0))
    {
        printf("Division Error var1=%d  var2=%d\n", var1, var2);
        exit(0);
    }

    // Nếu var1 bằng 0, kết quả luôn là 0
    if (var1 == 0)
    {
        return 0;
    }

    // Nếu var1 và var2 bằng nhau, trả về MAX_16 ngay lập tức
    if (var1 == var2)
    {
        return MAX_16;
    }

    // Khởi tạo giá trị cho L_num và L_denom
    L_num = (Word32)(var1);
    L_denom = (Word32)(var2);

    // Tối ưu vòng lặp với 15 lần lặp
    for (int iteration = 0; iteration < 15; iteration++)
    {
        var_out <<= 1;  // Dịch trái var_out
        L_num <<= 1;    // Dịch trái L_num

        if (L_num >= L_denom)
        {
            L_num = L_sub(L_num, L_denom); // Lấy phần còn lại
            var_out = add(var_out, 1);     // Tăng giá trị kết quả
        }
    }

    return var_out; // Trả về kết quả cuối cùng
}


Word32 L_add_Mpy_32_16(Word32 L_tmp, Word16 coeff_hi, Word16 coeff_lo, Word16 g_pitch)
{
    Word32 L_mult_out, L_var_out;
    Word32 L_32;
    Word32 mult_hi, mult_lo;
    Word16 mult_res_lo;

    // Tính L_mult của coeff_hi và g_pitch
    L_mult_out = (Word32)coeff_hi * (Word32)g_pitch;
    if (L_mult_out == (Word32)0x40000000L)
    {
        Overflow = 1;
        L_mult_out = MAX_32;
    }
    else
    {
        L_mult_out <<= 1;
    }

    // Tính mult của coeff_lo và g_pitch
    mult_lo = (Word32)coeff_lo * (Word32)g_pitch;
    mult_lo >>= 15;
    mult_res_lo = (mult_lo & (Word32)0x00010000L) ? (mult_lo | (Word32)0xffff0000L) : (Word16)mult_lo;

    // Tính L_mac dựa trên mult và nhân 1
    mult_hi = (Word32)mult_res_lo * 1;
    if (mult_hi == (Word32)0x40000000L)
    {
        Overflow = 1;
        mult_hi = MAX_32;
    }
    else
    {
        mult_hi <<= 1;
    }

    // Tính L_mac tổng của L_mult_out và mult_hi
    L_32 = L_mult_out + mult_hi;
    if (((L_mult_out ^ mult_hi) & MIN_32) == 0)
    {
        if ((L_32 ^ L_mult_out) & MIN_32)
        {
            L_32 = (L_mult_out < 0) ? MIN_32 : MAX_32;
            Overflow = 1;
        }
    }

    // Tính L_add(L_tmp, L_32)
    L_var_out = L_tmp + L_32;
    if (((L_tmp ^ L_32) & MIN_32) == 0)
    {
        if ((L_var_out ^ L_tmp) & MIN_32)
        {
            L_var_out = (L_tmp < 0) ? MIN_32 : MAX_32;
            Overflow = 1;
        }
    }

    return L_var_out;
}


Word32 L_msu_mult(Word16 alp, Word16 sq2, Word16 sq, Word16 alp_16)
{
    Word32 product1, product2, result;

    // Tính tích của alp và sq2 (tương tự L_mult)
    product1 = (Word32)alp * (Word32)sq2;
    if (product1 == (Word32)0x40000000L)
    {
        Overflow = 1;
        product1 = MAX_32;
    }
    else
    {
        product1 = product1 << 1; // Nhân đôi kết quả
    }

    // Tính tích của sq và alp_16 (tương tự L_mult)
    product2 = (Word32)sq * (Word32)alp_16;
    if (product2 == (Word32)0x40000000L)
    {
        Overflow = 1;
        product2 = MAX_32;
    }
    else
    {
        product2 = product2 << 1; // Nhân đôi kết quả
    }

    // Trừ product2 từ product1 (tương tự L_msu)
    result = product1 - product2;

    // Kiểm tra tràn số
    if (((product1 ^ product2) & MIN_32) != 0)
    {
        if ((result ^ product1) & MIN_32)
        {
            result = (product1 < 0L) ? MIN_32 : MAX_32;
            Overflow = 1;
        }
    }

    return result;
}


Word16 L_esm(Word16 a, Word16 b, Word16 n)
{
    Word32 L_var_out;
    Word32 L_temp;

    // Tính tích hai biến 16 bit trong 32 bit và kiểm tra tràn số
    L_var_out = (Word32)a * (Word32)b;

    // Kiểm tra xem L_var_out có bằng 0x40000000 không
    if (L_var_out == (Word32)0x40000000L) {
        Overflow = 1; // Đánh dấu có tràn số
        return MAX_32; // Trả về giá trị tối đa
    }

    // Nhân đôi kết quả nếu không tràn số
    L_var_out <<= 1; // Dịch trái một bit (tương đương nhân 2)

    // Kiểm tra tràn số trước khi dịch trái
    if (n >= 31 || L_var_out > (0x7FFFFFFF >> n) || L_var_out < (Word32)(0x80000000 >> n)) {
        Overflow = 1;
        return (L_var_out > 0) ? MAX_32 : MIN_32;
    }

    // Dịch trái L_var_out
    L_temp = L_var_out << n;

    // Trả về phần cao của L_temp
    return (Word16)(L_temp >> 16);
}

Word32 L_ssm(Word32 var1, Word16 var2, Word16 var3, Word16 var4)
{
    Word32 L_mult_out, L_shr_out, L_sub_out;

    // Tính tích hai biến 16 bit trong 32 bit
    L_mult_out = (Word32)var2 * (Word32)var3;

    // Kiểm tra tràn số và xử lý kết quả của L_mult
    if (L_mult_out == (Word32)0x40000000L) {
        Overflow = 1;
        L_mult_out = MAX_32;
    } else {
        L_mult_out <<= 1; // Nhân đôi kết quả nếu không tràn số
    }

    // Xử lý dịch phải/trái dựa trên giá trị của var4
    if (var4 != 0) {
        Word16 abs_var4 = (var4 < 0) ? -var4 : var4;

        if (abs_var4 >= 31) {
            L_shr_out = (L_mult_out < 0L) ? MIN_32 : MAX_32;  // Quá giới hạn dịch
        } else {
            L_shr_out = (var4 < 0) ? (L_mult_out << abs_var4) : (L_mult_out >> abs_var4);  // Dịch trái/phải
        }
    } else {
        L_shr_out = L_mult_out;  // Không dịch
    }

    // Thực hiện phép trừ L_sub
    L_sub_out = var1 - L_shr_out;

    // Kiểm tra tràn số cho L_sub
    if (((var1 ^ L_shr_out) & MIN_32) && ((L_sub_out ^ var1) & MIN_32)) {
        L_sub_out = (var1 < 0L) ? MIN_32 : MAX_32;
        Overflow = 1;
    }

    return L_sub_out;
}
