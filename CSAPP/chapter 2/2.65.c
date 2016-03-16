/* Problem 2.65 */

/*
 * Return 1 when x contains an odd numbers of 1s ; 0 otherwise
 * Assume w=32 , and this function follow the rules in page 120(eng ver)
 * contain total at most 12 arithm, bit-wise, and logical op
 */
int odd_ones(unsigned x)
{
	//totoally 12 operation
	//xor-op set a bit to 0 when there are 2(even) 1s which can be remove
	//binary op use fewer op
	x ^= (x >> 16);
	x ^= (x >> 8);
	x ^= (x >> 4);
	x ^= (x >> 2);
	x ^= (x >> 1);
	
	return !!(x & 1); //convert int to bool
}



//int main()
//{
//	unsigned i = 0xFFFFFFFF;
//	unsigned j = 0xFFFFFFFE;
//
//	printf("%d | %d\n", odd_ones(i), odd_ones(j));
//}
////i has 32 1s and j has 31 1s