/* Problems 2.80-2.85 */

/* 2.80 */

// A. 1^(w-k) 0^(k) -> ~((1 << k) - 1)
// B. 0^(w-k-j) 1^(k) 0^(j) -> ( ~((1 << k) - 1)) << j

/* 2.81 */
// A. (x < y) == (-x > -y) -> false
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
