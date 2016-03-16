/* Problem 2.70 */

/*
 * Return 1 when x can be represented as an n-bit 2's complement
 * number; 0 otherwise
 * Assume  1 <= n <= w
 * this function follow the bit-level integer coding rules (p120 eng ver)
 */
int fits_bits(int x, int n)
{
	// if x can be represented as n-bit 2's comple
	// the high-order w-n bits must be either all 0 or all 1
	x >>= (n - 1);

	// the remaing bits either all 0 or all 1
	return !x || !(~x);
}

//
//int main()
//{
//	int i = 511;
//	int j = 512;
//
//	printf("%d\n", fits_bits(i, 10));
//	printf("%d\n", fits_bits(j, 10));
//}
//// the range of x should be between 2**(n-1) - 1 to (-2**(n))