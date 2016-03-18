/* Problems 2.76-2.77 */


/* 2.76 */
// write the expression to multipy integer x by factor K
// use only operations +, - and <<

// A. K = 17 -> (x << 4) + x
// B. K = -7 -> x - (x << 3)
// C. K = 60 -> (x << 6) - (x << 2)
// D. K = -112 -> (x << 4) - (x << 7)


/* 2.77 */


/*
 * Divide by power of two . Assume 0 <= k < w-1
 * This function follow the bit-level integer rules(page 120)
 */
int divide_power2(int x, int k)
{
	int w = sizeof(int) << 3;
	int result = x >> k;
	
	// rounding to 0, so if negative and have remainder the result plus 1
	result += (x >> (w - 1)) && (x & ((1 << k) - 1));
	return result;
}



//int main()
//{
//	int num = 12340;
//	
//	printf("%d\n", divide_power2(num, 4));
//	printf("%d\n", divide_power2(-num, 4));
//}
//// 12340 / 2^4 = 771.25