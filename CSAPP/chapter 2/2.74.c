/* Problem 2.74 */

#include <limits.h>

/* 
 * Determine whether arguments can be subtracted
 * without overfolw
 * return 1 if computation x - y does not overflow
 */
int tsub_ok(int x, int y)
{
	int w = sizeof(int) << 3;
	int result_sign = (x - y) >> (w - 1);

	x >>= (w - 1);
	y >>= (w - 1);

	// there are two situation that will occur overflow
	// x > 0 and y < 0 and ans_sign < 0 positive overflow
	// x < 0 and y > 0 and ans_sign > 0 negative overflow
	// so you can write as follow :

	//return !((x & (!y)& (!ans_sign)) |
	//	((!x) & y & ans_sign));

	//or there are a simpler way (notice that y always equals to ans above)
	return !((x != y) && (y == result_sign));
}


//int main()
//{
//	int Max = INT_MAX;
//	int Min = INT_MIN;
//
//	printf("%d\n", tsub_ok(Max, Max));
//	printf("%d\n", tsub_ok(Min, Min));
//	printf("%d\n", tsub_ok(Max, Min));
//	printf("%d\n", tsub_ok(Min, Max));
//	printf("%d\n", tsub_ok(Min, 1));
//}