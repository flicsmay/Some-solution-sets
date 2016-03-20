/* Problem 2.91 */

/* following the bit-level floating-point coding rule (page 131 eng ver)*/
#include "floating_point_lib.h"

/* Compute -f.  If f is NaN, then return f */
float_bits float_negate(float_bits f)
{
	if (is_NaN_32(f)) // be define in floating_point_lib.h
		return f;
	return f ^ 0x80000000; // switch the sign bit with XOR-op
}


//// Functions f2u() and u2f() are defined in floating_point_lib.h
//int main()
//{
//	unsigned NaN = 0xFFF00000;
//	float f = 200;// make it easier to test
//	unsigned fbit = f2u(f);
//
//	printf("%f\n", u2f(float_negate(fbit)));
//	printf("%f\n", u2f(float_negate(NaN)));
//}
//// print -f upper and NaN lower