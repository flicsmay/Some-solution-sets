/* Problem 2.93 */

/* following the bit-level floating-point coding rule (page 131 eng ver)*/
#include "floating_point_lib.h"

/* Compute 2*f. If f is NaN, then return f */
float_bits float_twice(float_bits f)
{
	unsigned exp = (f >> 23) & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	if (is_NaN_32(f))
		return f;
	if (exp == 0) // denormailzed
		return f & 0xFF800000 | frac << 1; // save others | fractions * 2
	else if (exp < 254)
		return f & 0x807FFFFF | (exp + 1) << 23; // save other bits | add 1 in exponent
	else
		return f & 0xFF800000; // exp == 254, and just clear the fractions bits of f
}


//// Functions f2u() and u2f() are defined in floating_point_lib.h
//int main()
//{
//	unsigned NaN = 0xFFF00000;
//	float f = -200;// make it easier to test
//	unsigned fbit = f2u(f);
//
//	printf("%f\n", u2f(float_twice(fbit)));
//	printf("%f\n", u2f(float_twice(NaN)));
//}
//// printf 2*f upper and NaN lower