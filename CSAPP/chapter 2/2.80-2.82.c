/* Problems 2.80-2.82 */

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


