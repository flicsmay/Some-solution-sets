/* Problem 2.92 */

/* following the bit-level floating-point coding rule (page 131 eng ver)*/
#include "floating_point_lib.h"

/* Compute |f|.  If f is NaN, then return f. */
float_bits float_absval(float_bits f)
{
	if (is_NaN_32(f))
		return f;
	return f & 0x7FFFFFFF; // keep other bits and switch sign to 0
}

//// Functions f2u() and u2f() are defined in floating_point_lib.h
//int main()
//{
//	unsigned NaN = 0xFFF00000;
//	float f = -200;// make it easier to test
//	unsigned fbit = f2u(f);
//
//	printf("%f\n", u2f(float_absval(fbit)));
//	printf("%f\n", u2f(float_absval(NaN)));
//}
//// print |f| upper and NaN lower