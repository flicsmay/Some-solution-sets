/* Problem 2.72-2.73 */

/* 2.72 */

// A. the sizeof(val) return a value type of size_t
//    and size_t is atually the type unsigned int
//    when int op unsigned int that int will transfer 
//    to unsigned int and the result always greater than 0

// B. if (maxbytes > 0 && maxbytes >= sizeof(val))


/* 2.73 */

#include <limits.h>

/* Addition that saturates to TMin or TMax
   following the bit-level integer coding rule (page 120)*/
int saturating_add(int x, int y)
{
	// as to follow the rule there are not conditional here
	// so use some w bits mask to select which one to return

	int w = sizeof(int) << 3;
	int pos_ovf = 0;
	int neg_ovf = 0;
	int nop_ovf = 0;
	int answer = x + y;
	int ans_sign = answer >> (w - 1);// extend the answer sign to w bits

	x >>= (w - 1);// extend sign to w bits
	y >>= (w - 1);// extend sign to w bits

	// set all bits to 1 when an overflow occurance similary hereinafter
	pos_ovf = (~x) & (~y) & ans_sign; // 1 1 0 and set 1
	neg_ovf = x & y & (~ans_sign); // 0 0 1 and set 1
	nop_ovf = ~(pos_ovf | neg_ovf); // set 1 when both 0 above

	// the three w-bits mask to select which one to return
	return (pos_ovf & INT_MAX) | (nop_ovf & answer) | (neg_ovf & INT_MIN);
}


//int main()
//{
//	int i = INT_MIN;
//	int j = INT_MAX;
//	
//	printf("%.2x\n", saturating_add(i, i));
//	printf("%.2x\n", saturating_add(j, j));
//	printf("%.2x\n", saturating_add(i, j));
//}
//// print 0xffffffff 0x7fffffff and 0xffffffff(-1)