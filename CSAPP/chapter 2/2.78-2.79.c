/* Problems 2.78-2.79 */

// I actually beileve that 2.78 and 2.79 are indentical.
// So I will only get the soultion of 2.78

#include <limits.h>

/*
 * mutiply x by 3 / 4. follow the bit-level integer rules
 * and it should not overflow as well as rounded toward 0
 * this equcation is acutally ((x << 1) + x) >> 2 and
 * is the same as (x >> 1) + (x >> 2)
 */
int mul3div4(int x)
{
	int w = sizeof(int) << 3;
	int result = (x >> 1) + (x >> 2);

	result += (x & 0x1) && (x & 0x2);// add 1 in lower bit
	result += (x >> (w - 1)) && (x & 0x3);// to rounding to 0 detail in 2.77
	return result;
}


//int main()
//{
//	int min = INT_MIN;
//	int num = 129;
//
//	printf("%d\n", mul3div4(num));
//	printf("%d\n", mul3div4(-num));
//	printf("%.2x\n", mul3div4(min));
//}