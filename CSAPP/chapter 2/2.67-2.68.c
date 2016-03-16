/* Problem 2.67-2.68 */


/* 2.67 */

// A. Obviously is the left shift equals to 32 bits
// B. int beyond_msb = 2 << 31; (line 6)
//
// C. int set_msb = ((1 << 15) << 15) << 1;    //since I can't get a 16-bit machine
//    int beyond_msb = ((1 << 15) << 15) << 2; //I'm not sure whether it works or not
//
//    return set_msb && ! beyond_msb;


/* 2.68 */

/* 
 * Mask with least signficant n bits set to 1
 * Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF // I think the frist example in book should be 0x3F
 * Assume 1 <= n <= w
 * this function following the bit-level integer coding rules (page 120 (eng ver))
 */
int lower_one_mask(int n)
{
	//using 2 << (n-1) but not 1 << n is that 1 << n will fail when n = w(32)
	return ((2 << (n - 1)) - 1);
}


//int main()
//{
//	int i = 6;
//	int j = 17;
//	int k = 32;
//
//	printf("%.2x\n", lower_one_mask(i));
//	printf("%.2x\n", lower_one_mask(j));
//	printf("%.2x\n", lower_one_mask(k));
//}