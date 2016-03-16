/* Problem 2.66 */

/*
 * Generate mask indicating leftmost 1 in x.  Assume w=32
 * For example 0xFF00 -> 0x8000, and 0x6600 -> 0x4000.
 * If x = 0, then return 0.
 * this function follow the bit-level integer coding rule(page 120)
 * contain at most 15 arithmetic, bit-wise, and logical operations
 */
int leftmost_one(unsigned x)
{
	// follow the Hint:First transform x into a bit vector of the form [0..01...1]
	// then can use the expression x ^ (x >> 1) keep the most significant 1
	// use dichotomy to save op and or-op to set low-order 1
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16); 

	return x ^ (x >> 1);
}


//int main()
//{
//	unsigned i = 0xFF00;
//	unsigned j = 0x6600;
//
//	printf("%.2x\n", leftmost_one(i));
//	printf("%.2x\n", leftmost_one(j));
//}