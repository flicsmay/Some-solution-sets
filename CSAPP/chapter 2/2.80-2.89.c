/* Problems 2.80-2.89 */

/* 2.80 */

// A. 1^(w-k) 0^(k) -> ~((1 << k) - 1)
// B. 0^(w-k-j) 1^(k) 0^(j) -> ( ~((1 << k) - 1)) << j

/* 2.81 */
// A. (x < y) == (-x > -y) -> false // x = INT_MIN
// B. ((x + y) << 4) + y - x == 17 * y + 15 * x -> true
// C. ~x + ~y + 1 == ~(x + y) -> true
// D. (ux - uy) == -(unsigned)(y - x) -> true
// E. ((x >> 2) << 2) <= x -> true


/* 2.82 */
// A. x = Y / (2^k - 1) (as x * 2^k = Y + x(infinite))
// B. (a)101 = 5/7 .(b)0110 = 6/15 .(c)010011 = 18/63 (using formula above)


/* 2.83 */
// determine whether frist argument is less than or equal to second arg
// whether equal as 0 ;      x < 0 and y > 0 ;       x < y ( in both pos and neg)
// (((ux << 1) == 0) && ((uy << 1) == 0)) || (sx && !sy) || (ux <= uy)


/* 2.84 */
// A. number 7.0 -> M: 0 E : 10..01 F: 110..
// B. The largest odd integer thar can be represented exactly
//    M: 0 E: 11...10 F: 1....1 // According to the n and k 
//    it is common that n is much greater than k
// C. The reciprocal of the smallest positive normalized value
//    // The smallest positive positive normalized value is 0-0...01-00...0
//    // and it is acutally 2^(-2^(k-1) + 2) and reciprocal is 2^(2^(k-1) - 2)
//    M: 0 E: 11..101 F: 0..0


/* 2.85 */
// extend precision floating-point format : 15 exponent bits 63 fraction
//											Value			Decimal
// Smallest positive denormalized : (2^(2-2^(14))*2^(-63)   3.6451e-4951
// Smallest positive normalized :	(2^(-2^14 + 2))			3.621e-4932
// Largest normalized			:   (2^64-1)*2^(2^14-1-63)	1.1897e+4932 // add 2^63 and then minus


/* 2.86 */
// 7 bits exponent, 8 bits fraction
// Description				Hex			M			E			V
// -0						0x8000		0			-62			--
// smallest value > 2		0x4001		257/256		1			257*2^(-7)
// 512						0x4800		1			9			--
// Largest denormalized		0x00FF		255/256		-62			255*2^(-70) // 62+8
// -Inifinte				0xFF00		--			--			--
// Num with hex represen 3BB0 --		17/16			-4		17*2^(-8)


/* 2.87 */
// convert Format A to the closest value in B. round toward infinite
//				Format A						Format B
//		bits			value			bits				value
// 1 01111 001			-9/8		1 0111 0010				-9/8
// 0 10110 011			176			0 1110 0110				176
// 1 00111 010			-5/1024		1 0000 0101				-5/1024
// 0 00000 111			7/2^(-17)	0 0000 0001				2^(-10)
// 1 11100 000			-2^(13)		1 1111 0000				-infinite
// 0 10111 100			3*2^7		0 1111 0000				infinite


/* 2.88 */
// A. (float)x == (float)dx -> true
// B. dx - dy == (double) (x-y) -> false // when x = INT_MIN and y = INT_MAX
// C. (dx + dy) + dz == dx + (dy + dz) -> true // 
// D. (dx * dy) * dz == dx * (dy * dz) -> true // at least I can't find a 0 when I test
// E. dx / dx == dz / dz -> false // when z = 0

//#include <limits.h>
//
///* For test only */
//int main()
//{
//	int x = 0;
//	int y = INT_MAX;
//	int z = 0;
//	double dx = (double)x;
//	double dy = (double)y;
//	double dz = (double)z;
//
//	int expre = (dx / dx == dz / dz);
//
//	printf("%d\n", expre);
//}


/* 2.89 */
void fpwr2(int x)
{
	/* Result exponent and fraction */
	unsigned exp, frac;
	unsigned u;
	float *fp = &u;

	if (x < -149) // Too small. Return 0.0
	{
		exp = 0;
		frac = 0;
	}
	else if (x < -126) // Denormalized result
	{
		exp = 0;
		frac = 1 << (x + 149);
	}
	else if (x < 128) // Norimalized result.
	{
		exp = x + 127;
		frac = 0;
	}
	else // too big. return infinite
	{
		exp = 255;
		frac = 0;
	}

	/* Pack exp and frac into 32 bits */
	u = exp << 23 | frac;
	/* Return as float */

	// I modify the function to check the function easier
	printf("%f\n", *fp);
	printf("%.2x\n", u);
}


//int main()
//{
//	int neg_ovf = -150;
//	int pos_ovf = 128;
//
//	fpwr2(neg_ovf);
//	fpwr2(neg_ovf + 1);
//	fpwr2(pos_ovf);
//	fpwr2(pos_ovf - 1);
//}
//// Both the upper two print 0 and I guess the reason is that 
//// the precision is not enough to cover all fraction.