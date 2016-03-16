/* Problem 2.71 */

// A. without take sign-extension into consideration if the num < 0
// B:

typedef unsigned packed_t;
/* Extract byte from word.  Return as signed integer
   use only left and right shift, along with one subtraction */
int xbyte(packed_t word, int bytenum)
{
	// use only right and left shift to implement sign extension
	// shift the byte to most signficant byte and shift back
	// bytenum 3 in high-order so (3 - bytenum)
	// I used to use word driectly but maybe packed_t is a pointer ... so
	int ret = word << ((3 - bytenum) << 3);

	return ret >> 24;
}


//int main()
//{
//	unsigned i = 0xABCD1234;
//	int j = 0;
//
//	for (j = 0; j < 4; j++)
//	{
//		printf("%.2x\n", xbyte(i, j));
//	}
//}
////34, 12, 0xf...cd, 0xf...ab