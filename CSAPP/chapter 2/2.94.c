/* Problem 2.94 */

/* following the bit-level floating-point coding rule (page 131 eng ver)*/
#include "floating_point_lib.h"

/* Compute 0.5*f. If f is NaN, then return f */
float_bits float_half(float_bits f)
{
	unsigned exp = (f >> 23) & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	if (is_NaN_32(f))
		return f;
	else if (exp == 0) // denormailzed  
		return f & 0x80000000 | frac >> 1;
	else if (exp == 1) // Convert normailzed to denormailzed add 1 in fornt of fraction
		return f & 0x80400000 | frac >> 1;
	else
		return f & 0x807FFFFF | (exp - 1) << 23; // save other bits | exp - 1
}


//// Functions f2u() and u2f() are defined in floating_point_lib.h
//int main()
//{
//	unsigned NaN = 0xFFF00000;
//	float f = -200;// make it easier to test
//	unsigned fbit = f2u(f);
//
//	printf("%f\n", u2f(float_half(fbit)));
//	printf("%f\n", u2f(float_half(NaN)));
//}
//// printf 1/2* f upper and NaN lower