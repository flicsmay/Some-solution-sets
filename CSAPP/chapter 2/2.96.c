/* Problem 2.96 */

/* following the bit-level floating-point coding rule (page 131 eng ver)*/
#include "floating_point_lib.h"
#include <limits.h>

/* Compute (float)i */
float_bits float_i2f(int i)
{
	unsigned f = i;
	unsigned exp = 0;
	unsigned frac = 0;
	int index = 31;
	unsigned mask = 0x80000000;// to selet the most significant bit

	if (i < 0)// Convert two-complement to unsigned
	{
		f = ~i; // switch all bit then add 1 to be unsigned
		if (f != INT_MAX)
			f += 1;
	}
	for (index = 31; index >= 0; index--)
	{
		if (f & mask)
			break; // find the most significant bit
		mask >>= 1;
	}
	if (index < 0)
		return i & 0x80000000;

	exp = index + 127; // 0x7F = 127 = 0(in float)
	if (index > 23) // 23 bits fraction in sigle-precision
		frac = (f >> (index - 23)) & 0x7FFFFF;
	else
		frac = (f << (23 - index)) & 0x7FFFFF;
	return i & 0x80000000 | (exp << 23) | frac; // sign | exponent | fraction
}


//int main()
//{
//	int i = 200;
//	int MIN = INT_MIN;
//
//	printf("%f\n", u2f(float_i2f(i)));
//	printf("%f\n", u2f(float_i2f(MIN)));
//}