/* Problem 2.95 */

/* following the bit-level floating-point coding rule (page 131 eng ver)*/
#include "floating_point_lib.h"

/*
 * Compute (int) f
 * If conbersion cause overflow or f is NaN, return 0x80000000
 */
int float_f2i(float_bits f)
{
	unsigned exp = (f >> 23) & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	if (is_NaN_32(f))
		return 0x80000000;
	if (exp < 127)
		return 0;
	else if (exp >= 127 + 31) // overflow
		return 0x80000000;

	if ((exp - 127) > 23) // 23-bits fractions in single-precision
		return f & 0x80000000 | (frac | 0x800000) << (exp - 127 - 23); // must add the implicitly 1 before shift left
	else
		return f & 0x80000000 | (frac | 0x800000) >> (23 + 127 - exp);
}


//int main()
//{
//	unsigned NaN = 0xFFF00000;
//	float f = 200;// make it esaier to test
//	unsigned float_bit = f2u(f);
//
//	printf("%d\n", float_f2i(float_bit));
//	printf("%d\n", float_f2i(NaN));
//	printf("%d\n", float_f2i(f2u(0.5)));
//}