/* Problem 2.69 */

/*
 * Do rotating left shift.  Assume 0 <= n <= w
 * Examples when x = 0x12345678 and w = 32
 *    n=4 -> 0x23456781, n=20 -> 0x67812345
 * this function follow the bit-level integer coding rules (p120 eng ver)
 */
unsigned rotate_left(unsigned x, int n)
{
	unsigned w = (sizeof(int)) << 3;

	//some bit-wise op ...
	return (x << n) | (x >> (w - n));
}


//int main()
//{
//	unsigned i = 0x12345678;
//
//	printf("%.2x\n", rotate_left(i, 4));
//	printf("%.2x\n", rotate_left(i, 20));
//}